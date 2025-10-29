#pragma once

#include <filesystem>
#include <memory>
#include <optional>
#include <string>

#include "common/types.h"
#include "wal/wal_writer.h"
#include "wal/wal_reader.h"
#include "memtable/memtable.h"

namespace mylsm {
  struct DBConfig {
    std::filesystem::path wal_path;
    size_t memtable_soft_limit_bytes = 32 * 1024 * 1024;
  };

  class DB {
  public:
    explicit DB(const DBConfig&);
    ~DB();

    DB(const DB&) = delete; // no copy construction
    DB& operator=(const DB&) = delete; // disable copy assignments
    DB(DB&&) noexcept = default; // allow move construction
    DB& operator=(DB&&)  noexcept = default; // allow move assignment

    Status Put(const Bytes&, const Bytes&);
    std::optional<std::string> Get(const Bytes&);
    Status Erase(const Bytes&);

  private:
    // this order is the order of defn!!!!
    DBConfig cfg_;

    std::unique_ptr<WalWriter> wal_writer_;
    std::unique_ptr<WalReader> wal_reader_;
    std::unique_ptr<MemTable> active_;
    std::unique_ptr<MemTable> imm_;

    SequenceNumber next_seq_ = 1;
  }; 
}
