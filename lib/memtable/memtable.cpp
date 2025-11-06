#include "memtable.h"

#define K_ENTRY_OVERHEAD 32
// TODO finish the byte tracking impl


namespace mylsm {
  MemTable::MemTable() : size_(0), sl_(0.5f), approx_bytes_(0) {}

  MemTable::~MemTable() {}

  Status MemTable::Put(const Bytes& key, const Bytes& value) {
    if (key.empty()) return Status::Err("Empty key, cannot be empty");

    // TODO clean this up using the stuff on the left
    // TODO add getters
    // TODO add flush pipeline
    if (!sl_.search(key)) {
      size_++;
      approx_bytes_ += key.size() + value.size() + K_ENTRY_OVERHEAD;
    }
    else {
      approx_bytes_ += (value.size() - sl_.get(key).value().size());
    }

    sl_.insert(key, value);

    return Status::OK();
  }

  std::optional<std::string> MemTable::Get(const Bytes& key) const {
    return sl_.get(key);
  }

  Status MemTable::Erase(const Bytes& key) {
    if (!sl_.search(key)) return Status::Err("Key not found, cannot delete");
    // TODO: for tombstone overhead - 16. replace later
    approx_bytes_ += (16 - sl_.get(key).value().size() + K_ENTRY_OVERHEAD);

    sl_.del(key);
    size_--;
    

    return Status::OK();
  }

  size_t MemTable::Size() const noexcept {
    return size_;
  }

  size_t MemTable::ApproxBytes() const noexcept {
    return approx_bytes_;
  }

}
