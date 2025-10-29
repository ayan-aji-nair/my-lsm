#include "wal_writer.h"

// TODO: checksums
// TODO flexible flushing to disk
namespace mylsm {
  WalWriter::WalWriter(const std::string& path) {
    // create path_ and file_ objects
    std::filesystem::path wal_dir = std::filesystem::path(path)  / "wal";
    std::filesystem::create_directories(wal_dir);

    path_ = wal_dir / "log_0.wal";
    file_.open(path_, std::ios::binary | std::ios::out | std::ios::app);

    if (!file_.is_open())
      throw std::runtime_error("Failed to open WAL file at " + path_.string());
    
  }

  WalWriter::~WalWriter() {
    // flush to disk and close
    file_.flush();
    file_.close();
  }

  Status WalWriter::Append(const WriteOp& w) {
    // append the operation to file
    if (!file_.is_open()) return Status::Err("WAL not open");
      // write from the WriteOp
      // seq - 8 bytes
      // type - 1 byte
      // key length - 4 bytes
      // data - string
      // value - string
      uint64_t seq = w.seq;
      uint8_t type = static_cast<uint8_t>(w.type);
      uint32_t key_len = static_cast<uint32_t>(w.key.size());
      uint32_t val_len = static_cast<uint32_t>(w.value.size());

      // reinterpret the seq as a string
      file_.write(reinterpret_cast<const char*>(&seq), sizeof(seq));
      file_.write(reinterpret_cast<const char*>(&type), sizeof(type));
      file_.write(reinterpret_cast<const char*>(&key_len), sizeof(key_len));
      file_.write(w.key.data(), key_len);
      file_.write(reinterpret_cast<const char*>(&val_len), sizeof(val_len));
      file_.write(w.value.data(), val_len);

      if (!file_) return Status::Err("Failed to write to WAL");

      return Status::OK();
  }

  Status WalWriter::Flush() {
    if (!file_.is_open()) return Status::Err("WAL file not open");

    file_.flush();

    return Status::OK();
  }
};
