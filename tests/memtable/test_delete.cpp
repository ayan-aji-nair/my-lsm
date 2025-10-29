#include <gtest/gtest.h>
#include <string>
#include <string_view>

#include "memtable/memtable.h"

using namespace mylsm;

TEST(MemTableTest, InsertAndDelete) {
  mylsm::MemTable mem;
  
  Status out = mem.Put("Hello", "1");

  EXPECT_EQ(mem.Get("Hello"), "1");

  
  out = mem.Erase("Hello");

  EXPECT_EQ(mem.Get("Hello"), std::nullopt);
}
