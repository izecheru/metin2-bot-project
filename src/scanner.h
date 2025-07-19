#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "signature.h"
#include <unordered_map>
#include "singleton.h"

class PatternScanner :public Singleton<PatternScanner>
{
public:

  struct PatternByte
  {
    uint8_t value;
    bool isWildcard;
  };

  std::vector<PatternByte> toBytes(const std::string& pattern);
  std::uint8_t* scan(std::string& signature);
};