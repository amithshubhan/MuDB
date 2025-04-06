#include "lsm/StorageEngine.hpp"
#include <iostream>

int main() {
    StorageEngine engine;

    // Add entries to fill MemTable
    engine.put("apple", "red");
    engine.put("banana", "yellow");
    engine.put("grape", "purple");

    // Force flush here, if your threshold is > 3
    // Optional: manually call flush if implemented

    std::cout << "Wrote 3 keys. Now flushing...\n";

    // Add a few more (optional, to trigger another flush)
    engine.put("cherry", "dark red");

    // Retrieve from SSTable after flush
    auto result = engine.get("banana");
    if (result.has_value()) {
        std::cout << "Retrieved 'banana': " << result.value() << "\n";
    } else {
        std::cout << "banana not found\n";
    }

    // Try a non-existing key
    auto missing = engine.get("pineapple");
    if (missing.has_value()) {
        std::cout << "Found pineapple: " << missing.value() << "\n";
    } else {
        std::cout << "pineapple not found (as expected)\n";
    }

    return 0;
}
