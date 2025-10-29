#include "wal_reader.h"
#include <iostream>

// TODO: checksums
// TODO flexible flushing to disk
namespace mylsm {
  WalReader::WalReader(const std::string& path) {
    // create path_ and file_ objects
    path_ = std::filesystem::path(path);
    file_.open(path_, std::ios::binary);
    //if (!file_.exists())
    //  throw std::runtime_error("Failed to open WAL file at " + path_.string());
  }

  WalReader::~WalReader() {
    // flush to disk and close
    file_.close();
  }

  template<typename T>
  std::optional<T> WalReader::readValue(std::ifstream& file) {
    // return an optional in the case that we can't read in a value of the wanted size
    T value;
    if (!file.read(reinterpret_cast<char*>(&value), sizeof(T))) return std::nullopt;

    return value;
  }

  inline bool readBytes(std::ifstream& file, std::string& out, uint32_t n) {
    // make sure the string is exactly the right size
    out.resize(n);
    // return true if n == 0 or if we can successfully copy the file data into the string buffer
    return n == 0 || static_cast<bool>(file.read(out.data(), n));
  }

  std::optional<WriteOp> WalReader::readOne(std::ifstream& file) {
    WriteOp op;

    auto seq = readValue<SequenceNumber>(file);
    if (!seq) return std::nullopt;
    op.seq = *seq;

    auto typeb = readValue<uint8_t>(file);
    if (!typeb) return std::nullopt;
    op.type = static_cast<ValueType>(*typeb);


    auto keyLen = readValue<uint32_t>(file);
    if (!keyLen) return std::nullopt;
    // reject super duper large keys and values
    if (*keyLen > (1u<<20)) return std::nullopt;
    if (!readBytes(file, op.key, *keyLen)) return std::nullopt;

    auto valLen = readValue<uint32_t>(file);
    if (!valLen) return std::nullopt;
    if (*valLen > (1u<<20)) return std::nullopt;
    if (!readBytes(file, op.value, *valLen)) return std::nullopt;

    return op;
  }

  std::vector<WriteOp> WalReader::ReadAll() {
    std::vector<WriteOp> ops;
    while (true) {
      auto op = readOne(file_);
      if (!op.has_value()) break;
      // transfer the struct to the vector (after getting the value from the optional)
      ops.push_back(std::move(*op));
    }

    return ops;
  }
};
