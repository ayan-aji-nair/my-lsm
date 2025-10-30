#include "db_fixture.h"

TEST_F(DBTest, DBReplay) {
  {
    auto db = makeDB();
    db.Put("a", "1");
    db.Put("b", "2");
    db.Erase("a");
  }

  auto db2 = makeDB();
  EXPECT_EQ(db2.Get("a"), std::nullopt);
  auto vb = db2.Get("b");
  ASSERT_TRUE(vb.has_value());
  EXPECT_EQ(*vb, "2");
}
