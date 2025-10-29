#include "db_fixture.h"

TEST_F(DBTest, DBDelete) {
  auto db = makeDB();
  db.Put("a", "1");

  EXPECT_TRUE(db.Erase("a").ok);
  EXPECT_EQ(db.Get("a"), std::nullopt);
  
}
