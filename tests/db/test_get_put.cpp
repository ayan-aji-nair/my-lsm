#include "db_fixture.h"

#include <optional>

TEST_F(DBTest, DBPutGet) {
  auto db = makeDB();
  EXPECT_TRUE(db.Put("a", "1").ok);
  EXPECT_TRUE(db.Put("b", "2").ok);
  auto v = db.Get("a");
  ASSERT_TRUE(v.has_value());
  EXPECT_EQ(*v, "1");
  EXPECT_EQ(db.Get("d"), std::nullopt);
}
