#pragma once

#include "MemTable.hpp"
#include "SSTable.hpp"
#include <map>
#include <filesystem>
#include <vector>
#include <string>
#include <optional>

class LSMTree {
public:
    LSMTree();
    void put(const std::string& key, const std::string& value);
    std::optional<std::string> get(const std::string& key);
    void remove(const std::string& key);
    void maybeFlush();


private:
    MemTable memtable;
    std::string sstableDir = "data/sstables";
    std::vector<SSTable> sstables; // Future: support multiple levels
    void flushToDisk();
};
