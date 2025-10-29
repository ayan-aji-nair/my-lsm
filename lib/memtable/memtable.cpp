#include "memtable.h"


namespace mylsm {
  MemTable::MemTable() : size_(0), sl_(0.5f) {}

  MemTable::~MemTable() {}

  Status MemTable::Put(const Bytes& key, const Bytes& value) {
    if (key.empty()) return Status::Err("Empty key, cannot be empty");
    if (!sl_.search(key)) size_++;
    sl_.insert(key, value);

    return Status::OK();
  }

  std::optional<std::string> MemTable::Get(const Bytes& key) const {
    return sl_.get(key);
  }

  Status MemTable::Erase(const Bytes& key) {
    if (!sl_.search(key)) return Status::Err("Key not found, cannot delete");
    sl_.del(key);
    size_--;

    return Status::OK();
  }

  size_t MemTable::Size() const noexcept {
    return size_;
  }

}
