#include "lsm/StorageEngine.hpp"

StorageEngine::StorageEngine() : lsm() {}

void StorageEngine::put(const std::string& key, const std::string& value) {
    lsm.put(key, value);
}

std::optional<std::string> StorageEngine::get(const std::string& key) {
    return lsm.get(key);
}

void StorageEngine::remove(const std::string& key) {
    lsm.remove(key);
}
