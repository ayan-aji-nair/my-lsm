#pragma once
#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <vector>
#include <utility>
#include <cstddef>

#include "util/skiplist.h"
#include "wal/wal_writer.h"

// implement all this in a memory arena for speed

namespace mylsm {
  struct MemTableOptions {
    size_t soft_capacity_bytes = 8 * 1024 * 1024;
    bool track_bytes_precisely = false;
  };

  // TODO: use string_view for Get
  class MemTable {
    public:
      MemTable();
      ~MemTable();

      [[nodiscard]] Status Put(const Bytes& key, const Bytes& value);
      [[nodiscard]] std::optional<std::string> Get(const Bytes& key) const;
      [[nodiscard]] Status Erase(const Bytes& key);
      [[nodiscard]] size_t Size() const noexcept;

    private:
      size_t size_;
      SkipList sl_;
  };
};
