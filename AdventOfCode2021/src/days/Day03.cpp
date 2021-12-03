#include "aoc.h"

namespace day03
{
  REGISTER_DAY(day03, std::set<std::string>, int);

  REGISTER_TEST_EXAMPLE(day03, ExampleInput, 1, 198);
  REGISTER_TEST        (day03, Input,        1, 2498354);
  REGISTER_TEST_EXAMPLE(day03, ExampleInput, 2, 230);
  REGISTER_TEST        (day03, Input,        2, 3277956);

  READ_INPUT(input)
  {
    std::set<std::string> strings;
    std::string str;
    while(getline(input, str))
    {
      strings.emplace(str);
    }
    return strings;
  }

  OUTPUT1(input)
  {
    int mask = 0;
    int gamma = 0;
    int width = input.begin()->size();
    for(int x = 0; x < width; x++)
    {
      mask |= 1 << width - x - 1;
      int count = 0;
      for(auto&& str : input)
      {
        if(str[x] == '1')
          count++;
      }
      if(count >= input.size() / 2)
      {
        gamma |= (1 << (width - x - 1));
      }
    }
    return gamma * ((~gamma) & mask);
  }

  OUTPUT2(input)
  { 
    int width = input.begin()->size();

    std::set<std::string> oxygen = input;
    std::set<std::string> carbon = input;
    for(int i = 0; i < width; i++)
    {
      char mostCommon = '0';
      int count = 0;
      for(auto it = oxygen.begin(); it != oxygen.end(); it++)
      {
        if(it->at(i) == '1')
          count++;
      }
      if(count * 2 >= oxygen.size())
        mostCommon = '1';
      for(auto it = oxygen.begin(); it != oxygen.end();)
      {
        if(oxygen.size() == 1)
          break;
        if(it->at(i) != mostCommon)
          it = oxygen.erase(it);
        else
          it++;
      }

      char leastCommon = '0';
      count = 0;
      for(auto it = carbon.begin(); it != carbon.end(); it++)
      {
        if(it->at(i) == '1')
          count++;
      }
      if(count * 2 < carbon.size())
        leastCommon = '1';
      for(auto it = carbon.begin(); it != carbon.end();)
      {
        if(carbon.size() == 1)
          break;
        if(it->at(i) != leastCommon)
          it = carbon.erase(it);
        else
          it++;
      }
    }
    int oxygenVal = Helper::BinStrToInt(*oxygen.begin());
    int carbonVal = Helper::BinStrToInt(*carbon.begin());
    return oxygenVal * carbonVal;
  }
}
