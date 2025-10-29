#include "db_fixture.h"

TEST_F(DBTest, DBOverwrite) {
  auto db = makeDB();
  EXPECT_TRUE(db.Put("a", "1").ok);
  EXPECT_TRUE(db.Put("a", "2").ok);
  EXPECT_TRUE(db.Put("a", "3").ok);
  auto v = db.Get("a");
  ASSERT_TRUE(v.has_value());
  EXPECT_EQ(*v, "3");
}
