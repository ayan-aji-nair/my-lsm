#include <gtest/gtest.h>
#include <string>
#include <string_view>
#include <optional>

#include "util/skiplist.h"

using namespace mylsm;

TEST(SkipListTest, RewriteKey) {
  
  mylsm::SkipList sl(.5);
  
  sl.insert("Hello", "1");

  EXPECT_EQ(sl.get("Hello"), "1");

  sl.insert("Hello", "2");

  EXPECT_EQ(sl.get("Hello"), "2");
}
