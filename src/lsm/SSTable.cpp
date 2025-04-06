#include "lsm/SSTable.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include <chrono>
#include <zlib.h>

namespace fs = std::filesystem;

SSTable::SSTable(const std::string& filepath) : filepath(filepath) {}

std::optional<std::string> SSTable::get(const std::string& key) const {
    std::ifstream file(filepath);
    std::string line;
    
    while (std::getline(file, line)) {
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

std::string SSTable::write(const std::map<std::string, std::string>& data, const std::string& directory) {
    // Generate unique filename
    auto timestamp = std::chrono::system_clock::now().time_since_epoch().count();
    std::string filename = "sst_" + std::to_string(timestamp) + ".dat";
    std::string fullpath = fs::path(directory) / filename;

    std::ofstream file(fullpath);
    for (const auto& [key, value] : data) {
        file << key << ":" << value << "\n";
    }
    return fullpath;
}

std::string compressBlock(const std::string& data) {
    uLong srcLen = data.size();
    uLong destLen = compressBound(srcLen);
    std::string out(destLen, '\0');

    if (compress((Bytef*)&out[0], &destLen, (const Bytef*)data.data(), srcLen) != Z_OK) {     
        throw std::runtime_error("Compression failed");
    }

    out.resize(destLen); // trim to actual size
    return out;
}

std::string decompressBlock(const std::string& compressed, uLong originalSize) {
    std::string out(originalSize, '\0');
    uLongf destLen = originalSize;

    if (uncompress((Bytef*)&out[0], &destLen, (const Bytef*)compressed.data(), compressed.size()) != Z_OK) {
        throw std::runtime_error("Decompression failed");
    }

    return out;
}
