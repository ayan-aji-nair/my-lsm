#pragma once

#include <bitset>
#include <fstream>
#include <filesystem>
#include <string>
#include <optional>
#include <vector>

#include "common/types.h"

namespace mylsm {

  class WalReader {
  public:
    explicit WalReader(const std::string&);
    ~WalReader();

    [[nodiscard]] std::vector<WriteOp> ReadAll();

  private:
    // actual file
    std::ifstream file_;
    // path
    std::filesystem::path path_;

    template <typename T> std::optional<T> readValue(std::ifstream& file);
    std::optional<WriteOp> readOne(std::ifstream& file);
  };
}
