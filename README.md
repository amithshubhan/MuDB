
# 🐘 MuDB

MuDB is a lightweight, write-optimized NoSQL-style **storage engine** built in modern **C++**, based on the architecture of **Log-Structured Merge Trees (LSM Trees)**. Inspired by LevelDB and RocksDB, it focuses on scalable, high-throughput key-value storage with efficient disk usage.

---

## 🚀 Architecture Overview

### 🔹 1. **MemTable (In-Memory Write Buffer)**
- In-memory structure using `std::map`
- Holds recent writes sorted by key
- Flushes to disk as SSTables when full

### 🔹 2. **SSTables (Sorted String Tables)**
- Immutable, disk-based files storing key-value data
- Binary format with optional **block-level compression**
- Includes:
  - **Data blocks** (compressed)
  - **Index block** for fast key lookups
  - **Footer** pointing to index metadata

### 🔹 3. **Multi-Level Storage (LSM Tree Design)**
- SSTables are organized in multiple levels:
  - **Level-0**: New, unsorted overlapping files
  - **Level-1+**: Sorted, non-overlapping ranges
- **Compaction** merges files across levels to reduce read amplification and reclaim space

### 🔹 4. **Compression**
- Each SSTable block is optionally compressed using `zlib`
- Reduces storage size and I/O costs
- Compression and decompression handled transparently during read/write

### 🔹 5. **Lookup Flow**
1. Search MemTable (in memory)
2. Search SSTables in Level-0 to Level-N
3. Use **Index Block** for binary search
4. **Decompress block**, extract key-value

---

## 🧩 Technology Stack

- **Language:** C++17
- **Compression:** zlib
- **Build System:** Makefile
- **Platform Support:** macOS (M1), Linux

---

## 🛠️ Build & Run

```bash
make           # Compiles the project
./build/lsm_engine   # Runs the executable
```

Clean up:

```bash
make clean
```

---

## 📦 Dependencies

- **C++17** or later
- **zlib** library

Install on macOS:

```bash
brew install zlib
```

Install on Ubuntu/Debian:

```bash
sudo apt install zlib1g-dev
```

---

## 🧠 Future Enhancements

- Bloom filters for fast negative lookups
- Range queries and prefix scans
- Write-Ahead Log (WAL) for crash recovery
- TTL-based deletes and compaction tuning
- Pluggable compression backends (Snappy, LZ4)

---

## 📚 Inspired By

- [LevelDB by Google](https://github.com/google/leveldb)
- [RocksDB by Facebook](https://github.com/facebook/rocksdb)
- LSM Tree research papers and implementation blogs

---

## 🤝 Contribute

MuDB is under active development — feedback, ideas, and contributions are welcome!

