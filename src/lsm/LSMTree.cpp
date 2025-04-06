#include "lsm/LSMTree.hpp"
#include <iostream>

LSMTree::LSMTree() {}



std::optional<std::string> LSMTree::get(const std::string& key) {
    auto memValue = memtable.get(key);
    if (memValue.has_value()) return memValue;

    for (auto& sstable : sstables) {
        auto diskValue = sstable.get(key);
        if (diskValue.has_value()) return diskValue;
    }

    return std::nullopt;
}
void LSMTree::put(const std::string& key, const std::string& value) {
    memtable.put(key, value);
    maybeFlush();
}

// void LSMTree::maybeFlush() {
//     if (memtable.size() >= 3) { // TEMP: flush threshold
//         std::map<std::string, std::string> sortedData;
//         for (const auto& [key, value] : memtable.exportSorted()) {
//             sortedData[key] = value;
//         }

//         std::string file = SSTable::write(sortedData, sstableDir);
//         sstables.emplace_back(file);
//         memtable.clear();
//     }
// }

void LSMTree::maybeFlush() {
    if (memtable.size() >= 3) {  // ✅ Lower flush threshold
        auto sorted = memtable.exportSorted();
        std::string path = SSTable::write(sorted, sstableDir);
        sstables.emplace_back(path);
        memtable.clear();

        std::cout << "Flushed MemTable to SSTable: " << path << std::endl;
    }
}



void LSMTree::remove(const std::string& key) {
    memtable.remove(key);
    // TODO: tombstone entry
}

void LSMTree::flushToDisk() {
    // TODO: Write MemTable to SSTable on disk
}
