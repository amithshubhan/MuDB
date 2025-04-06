#pragma once

#include <unordered_map>
#include <string>
#include <optional>
#include <map>

class MemTable {
public:
    void put(const std::string& key, const std::string& value);
    std::optional<std::string> get(const std::string& key);
    void remove(const std::string& key);
    size_t size() const;
    std::map<std::string, std::string> exportSorted() const;
    void clear();


private:
    std::unordered_map<std::string, std::string> table;
};
