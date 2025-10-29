#include <iostream>

#include "db.h"

namespace mylsm {
  DB::DB(const DBConfig& cfg) 
    : cfg_(cfg), 
    //wal_writer_(std::make_unique<WalWriter>(cfg_.wal_path.string())),
    wal_writer_(nullptr),
    active_(std::make_unique<MemTable>()),
    imm_(nullptr) {
      std::filesystem::path read_path = cfg_.wal_path / "wal" / "log_0.wal";
      WalReader reader(read_path);

      SequenceNumber max_seq = 0;
      for (const WriteOp& op : reader.ReadAll()) {
        switch(op.type) {
          case ValueType::kPut: {
            Status s = active_->Put(op.key, op.value);
            break;
          }
          case ValueType::kDelete: {
            Status s = active_->Erase(op.key);
            break;
          }
        }
        max_seq = std::max(max_seq, op.seq);
      }

      next_seq_ = max_seq + 1;

      wal_writer_ = std::make_unique<WalWriter>(cfg_.wal_path.string());
    }

  DB::~DB() {}

  Status DB::Put(const Bytes& key, const Bytes& value) {
    WriteOp op {
      .key = std::string(key),
      .value = std::string(value),
      .type = ValueType::kPut,
      .seq = next_seq_
    };

    Status wal_res = wal_writer_->Append(op);
    if (!wal_res.ok) return Status::Err(wal_res.msg);

    next_seq_++;

    Status memtable_res = active_->Put(key, value);
    if (!memtable_res.ok) return Status::Err(memtable_res.msg);

    return Status::OK();
  } 

  std::optional<std::string> DB::Get(const Bytes& key) {
    return active_->Get(key);
  }

  Status DB::Erase(const Bytes& key) {
    WriteOp op {
      .key = std::string(key),
      .value = kEmptyValue, // tombstone marker
      .type = ValueType::kDelete,
      .seq = next_seq_
    };
    
    Status wal_res = wal_writer_->Append(op);
    if (!wal_res.ok) return Status::Err(wal_res.msg);

    next_seq_++;

    Status memtable_res = active_->Erase(key);

    if(!memtable_res.ok) return Status::Err(memtable_res.msg);

    return Status::OK();
  }
}
