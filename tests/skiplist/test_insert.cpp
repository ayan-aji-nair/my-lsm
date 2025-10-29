#include <gtest/gtest.h>
#include <string>
#include <string_view>

#include "util/skiplist.h"

using namespace mylsm;

TEST(SkipListTest, InsertAndFind) {
  mylsm::SkipList sl(.5);
  
  std::string s1 = "Hello";
  std::string s2 = "There";
  std::string s3 = "Bye";

  std::string_view v1 = s1;
  std::string_view v2 = s2;
  std::string_view v3 = s3;

  sl.insert(v1, "1");
  sl.insert(v2, "2");
  sl.insert(v3, "3");

  EXPECT_TRUE(sl.search(v1));
  EXPECT_TRUE(sl.search(v2));
  EXPECT_TRUE(sl.search(v3));
  
  std::string s4 = "Goodbye";
  std::string s5 = "Wrong";

  std::string_view v4 = s4;
  std::string_view v5 = s5;

  EXPECT_FALSE(sl.search(v4));
  EXPECT_FALSE(sl.search(v5));
}
