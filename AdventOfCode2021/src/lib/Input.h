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
    return ReadInts(input, '\n');
  }

  static std::vector<int64_t> ReadInt64s(std::istream& input)
  {
    return ReadInt64s(input, '\n');
  }

  static std::vector<int> ReadInts(std::istream& input, char delimiter)
  {
    std::vector<int> ints;
    std::string str;
    while (getline(input, str, delimiter))
      ints.emplace_back(std::atoi(str.c_str()));
    return ints;
  }

  static std::vector<int64_t> ReadInt64s(std::istream& input, char delimiter)
  {
    std::vector<int64_t> ints;
    std::string str;
    while (getline(input, str, delimiter))
      ints.emplace_back(std::atoll(str.c_str()));
    return ints;
  }
};
