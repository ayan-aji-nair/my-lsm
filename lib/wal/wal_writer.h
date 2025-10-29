#pragma once

#include <bitset>
#include <fstream>
#include <filesystem>
#include <string>

#include "common/types.h"

namespace mylsm {

  class WalWriter {
  public:
    explicit WalWriter(const std::string&);
    ~WalWriter();

    [[nodiscard]] Status Append(const WriteOp&);
    [[nodiscard]] Status Flush();

  private:
    // actual file
    std::ofstream file_;
    // path
    std::filesystem::path path_;
  };
}
