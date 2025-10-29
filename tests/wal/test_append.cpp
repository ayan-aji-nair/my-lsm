#include <gtest/gtest.h>
#include <string>
#include <string_view>
#include <filesystem>

#include "wal/wal_writer.h"



using namespace mylsm;

TEST(WalWriterTest, TestAppend) {

  std::filesystem::remove_all("/Users/ayan/Projects/lsm/data/wal");

  WalWriter wal("/Users/ayan/Projects/lsm/data/wal");

  auto s =  wal.Append({"a", "1", ValueType::kPut, 1});
  EXPECT_TRUE(s.ok);

  s = wal.Append({"b", "2", ValueType::kPut, 2});
  EXPECT_TRUE(s.ok);

  s = wal.Append({"b", "", ValueType::kDelete, 3});
  EXPECT_TRUE(s.ok);

  s = wal.Flush();

  std::ifstream file("/Users/ayan/Projects/lsm/data/wal");
  ASSERT_TRUE(file.is_open());

  // find the end of the file
  file.seekg(0, std::ios::end);
  size_t size = file.tellg();

  EXPECT_GT(size, 0);

  std::filesystem::remove_all("/Users/ayan/Projects/lsm/data/wal");
}
