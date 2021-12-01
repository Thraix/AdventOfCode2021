#pragma once

#include "Array2D.h"

#include <stdint.h>
#include <iostream>
#include <string>

struct Input
{
  static Array2D<char> ReadArray2D(std::istream& input)
  {
    std::vector<char> data;
    int width = 0;
    int height = 0;
    std::string str;
    while (getline(input, str))
    {
      width = str.length();
      height++;
      for (auto c : str)
        data.emplace_back(c);
    }
    return Array2D<char>(width, height, data);
  }

  static std::vector<int> ReadInts(std::istream& input)
  {
    std::vector<int> ints;
    std::string str;
    while (getline(input, str))
      ints.push_back(std::atoi(str.c_str()));
    return ints;
  }

  static std::vector<int64_t> ReadInt64s(std::istream& input)
  {
    std::vector<int64_t> ints;
    std::string str;
    while (getline(input, str))
      ints.push_back(std::atoll(str.c_str()));
    return ints;
  }
};
