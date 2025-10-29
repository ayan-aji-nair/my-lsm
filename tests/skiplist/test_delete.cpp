#include <gtest/gtest.h>
#include <string>
#include <string_view>

#include "util/skiplist.h"

using namespace mylsm;

TEST(SkipListTest, InsertAndDelete) {
  mylsm::SkipList sl(.5);
  
  sl.insert("Hello", "1");

  EXPECT_TRUE(sl.search("Hello"));

  sl.del("Hello");

  EXPECT_FALSE(sl.search("Hello"));
}
