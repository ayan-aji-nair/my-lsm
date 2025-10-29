#include <gtest/gtest.h>
#include <string>
#include <string_view>
#include <filesystem>

#include "wal/wal_writer.h"

using namespace mylsm;

TEST(WalWriterTest, FileCreation) {

  std::filesystem::remove_all("/Users/ayan/Projects/lsm/data/wal");

  WalWriter wal("/Users/ayan/Projects/lsm/data/wal");

  WriteOp op{"a", "1", ValueType::kPut, 1};
  auto s = wal.Append(op);

  EXPECT_TRUE(s.ok);
  EXPECT_TRUE(std::filesystem::exists("/Users/ayan/Projects/lsm/data/wal"));

  std::filesystem::remove_all("/Users/ayan/Projects/lsm/data/wal");
}
