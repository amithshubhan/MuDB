#pragma once

#include "LSMTree.hpp"
#include <string>
#include <optional>

class StorageEngine {
public:
    StorageEngine();
    void put(const std::string& key, const std::string& value);
    std::optional<std::string> get(const std::string& key);
    void remove(const std::string& key);

private:
    LSMTree lsm;
};
