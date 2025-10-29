#pragma once

#include <cstdint>
#include <string_view>
#include <string>
#include <utility>

namespace mylsm {
  using SequenceNumber = uint64_t;
  enum class ValueType : uint8_t { kPut = 1, kDelete = 2 };

  using Bytes = std::string_view;
  constexpr std::string kEmptyValue = "";

  // defines a write operation
  struct WriteOp {
    std::string key;
    std::string value;
    ValueType type;
    SequenceNumber seq;
  };

  struct Snapshot {
    SequenceNumber snapshot_seq;
  };

  struct Status {
    bool ok = true;
    std::string msg;
    static constexpr Status OK() { return {}; }
    static Status Err(std::string m) { return Status {false, std::move(m) }; }
  };
}
