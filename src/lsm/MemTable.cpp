#include "lsm/MemTable.hpp"

void MemTable::put(const std::string& key, const std::string& value) {
    table[key] = value;
}

std::optional<std::string> MemTable::get(const std::string& key) {
    auto it = table.find(key);
    if (it != table.end()) {
        return it->second;
    }
    return std::nullopt;
}

std::map<std::string, std::string> MemTable::exportSorted() const {
    return std::map<std::string, std::string>(table.begin(), table.end());
}

void MemTable::clear() {
    table.clear();
}


void MemTable::remove(const std::string& key) {
    table.erase(key);  // TODO: mark tombstone instead
}

size_t MemTable::size() const {
    return table.size();
}
