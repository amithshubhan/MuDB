#pragma once

#include <string>
#include <optional>
#include <map>

class SSTable {
public:
    // Load an SSTable from disk
    explicit SSTable(const std::string& filepath);

    // Write a map of key-value pairs to disk as a new SSTable
    static std::string write(const std::map<std::string, std::string>& data, const std::string& directory);

    // Get value for a key (linear scan for now)
    std::optional<std::string> get(const std::string& key) const;

private:
    std::string filepath;
};
