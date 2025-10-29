#pragma once

#include <gtest/gtest.h>
#include <filesystem>
#include <string>

#include "db.h"

namespace fs = std::filesystem;
using namespace mylsm;

class DBTest : public ::testing::Test {
  protected:
    fs::path tmp;

    void SetUp() override {
      tmp = fs::temp_directory_path() / ("mylsm_db_" + std::to_string(::getpid()) + "_" + std::to_string(::testing::UnitTest::GetInstance()->random_seed()));
      fs::remove_all(tmp);
      fs::create_directories(tmp);
    }

    void TearDown() override {
      fs::remove_all(tmp);
    }

    DB makeDB() {
      return DB(DBConfig{ .wal_path = tmp });
    }
};
