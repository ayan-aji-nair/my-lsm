#include <gtest/gtest.h>
#include <string>
#include <string_view>
#include <filesystem>

#include "wal/wal_writer.h"
#include "wal/wal_reader.h"

using namespace mylsm;

TEST(WalReaderTest, TestReplay) {

  std::filesystem::remove_all("/Users/ayan/Projects/lsm/data");
  WalWriter writer("/Users/ayan/Projects/lsm/data");

  auto s = writer.Append({"a", "1", ValueType::kPut, 1});
  s = writer.Append({"a", "", ValueType::kDelete, 2});

  s = writer.Flush();

  WalReader reader("/Users/ayan/Projects/lsm/data/wal/log_0.wal");

  auto ops = reader.ReadAll();

  ASSERT_EQ(ops.size(), 2);
  EXPECT_EQ(ops[0].key, "a");
  EXPECT_EQ(ops[0].type, ValueType::kPut);
  EXPECT_EQ(ops[1].type, ValueType::kDelete);

  std::filesystem::remove_all("/Users/ayan/Projects/lsm/data/wal");
}
