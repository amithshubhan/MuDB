#include "lsm/SSTable.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include <chrono>
#include <zlib.h>
  
namespace fs = std::filesystem;

SSTable::SSTable(const std::string& filepath) : filepath(filepath) {}

std::string decompressData(const std::string& input, size_t originalSize) {
    std::string out(originalSize, 0);
    uLongf destLen = originalSize;

    int res = uncompress(reinterpret_cast<Bytef*>(&out[0]), &destLen,
                         reinterpret_cast<const Bytef*>(input.data()), input.size());

    if (res != Z_OK) throw std::runtime_error("Decompression failed");
    return out;
}

std::optional<std::string> SSTable::get(const std::string& key) const {
    std::ifstream file(filepath, std::ios::binary);
    if (!file) return std::nullopt;

    // Read uncompressed size (first 4 bytes)
    uint32_t originalSize;
    file.read(reinterpret_cast<char*>(&originalSize), sizeof(originalSize));

    // Read the rest of the compressed data
    std::string compressedData((std::istreambuf_iterator<char>(file)), {});

    // Decompress
    std::string decompressed = decompressData(compressedData, originalSize);

    // Search in decompressed data
    std::istringstream stream(decompressed);
    std::string line;

    while (std::getline(stream, line)) {
        auto delim = line.find(':');
        if (delim != std::string::npos) {
            std::string k = line.substr(0, delim);
            std::string v = line.substr(delim + 1);
            if (k == key) {
                return v;
            }
        }
    }
    return std::nullopt;
}



#include <zlib.h>

std::string compressData(const std::string& input) {
    uLong srcLen = input.size();
    uLong destLen = compressBound(srcLen);
    std::string out(destLen, 0);

    int res = compress(reinterpret_cast<Bytef*>(&out[0]), &destLen,
                       reinterpret_cast<const Bytef*>(input.data()), srcLen);

    if (res != Z_OK) throw std::runtime_error("Compression failed");

    out.resize(destLen); // trim to actual compressed size
    return out;
}

std::string SSTable::write(const std::map<std::string, std::string>& data, const std::string& directory) {
    // Generate unique filename
    auto timestamp = std::chrono::system_clock::now().time_since_epoch().count();
    std::string filename = "sst_" + std::to_string(timestamp) + ".dat";
    std::string fullpath = fs::path(directory) / filename;

    // Build raw content first
    std::string rawData;
    for (const auto& [key, value] : data) {
        rawData += key + ":" + value + "\n";
    }

    // Compress the raw content
    std::string compressedData = compressData(rawData);

    // Write compressed data to file (binary mode!)
    std::ofstream file(fullpath, std::ios::binary);
    if (!file) throw std::runtime_error("Failed to open file for writing");

    // Optional: write original size as header (needed for decompression)
    uint32_t originalSize = rawData.size();
    file.write(reinterpret_cast<char*>(&originalSize), sizeof(originalSize));

    // Write compressed data
    file.write(compressedData.data(), compressedData.size());

    return fullpath;
}

