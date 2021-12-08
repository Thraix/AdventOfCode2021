#include "aoc.h"

namespace day08
{
  struct Signal
  {
    std::vector<std::set<char>> numbers;
    std::vector<std::set<char>> display;
  };

  REGISTER_DAY(day08, std::vector<Signal>, int);

  REGISTER_TEST_EXAMPLE(day08, ExampleInput, 1, 26);
  REGISTER_TEST        (day08, Input,        1, 301);
  REGISTER_TEST_EXAMPLE(day08, ExampleInput, 2, 61229);
  REGISTER_TEST        (day08, Input,        2, 908067);

  READ_INPUT(input)
  {
    std::string str;
    std::vector<Signal> signals;
    while(getline(input, str))
    {
      Signal signal;
      std::stringstream ss{str};
      for(int i = 0; i < 10; i++)
      {
        std::string s;
        ss >> s;
        std::set<char> set;
        for(char c : s)
          set.emplace(c);
        signal.numbers.emplace_back(set);
      }
      char c;
      ss >> c;
      for(int i = 0; i < 4; i++)
      {
        std::string s;
        ss >> s;
        std::set<char> set;
        for(char c : s)
          set.emplace(c);
        signal.display.emplace_back(set);
      }
      signals.emplace_back(signal);
    }
    return signals;
  }

  OUTPUT1(input)
  {
    int count = 0;
    for(auto&& signal : input)
    {
      for(auto&& number : signal.display)
      {
        if(number.size() == 2 || number.size() == 3  || number.size() == 4 || number.size() == 7)
          count++;
      }
    }
    return count;
  }

  OUTPUT2(input)
  {
    int sum = 0;
    for(auto&& signal : input)
    {
      std::vector<std::set<char>> numbers(10);
      // Find all numbers with unique amount of segments
      for(auto&& number : signal.numbers)
      {
        if(number.size() == 2)
          numbers[1] = number;
        if(number.size() == 3)
          numbers[7] = number;
        if(number.size() == 4)
          numbers[4] = number;
        if(number.size() == 7)
          numbers[8] = number;
      }

      // Find all numbers with five and six segments
      std::vector<std::set<char>> fivesegs;
      std::vector<std::set<char>> sixsegs;
      for(auto&& number : signal.numbers)
      {
        if(number.size() == 5)
          fivesegs.emplace_back(number);
        if(number.size() == 6)
          sixsegs.emplace_back(number);
      }

      // Find number 3 (only five segment number which 1 is a subset of)
      for(auto it = fivesegs.begin(); it != fivesegs.end(); it++)
      {
        if(Helper::IsSubset(numbers[1], *it))
        {
          numbers[3] = *it;
          fivesegs.erase(it);
          break;
        }
      }

      // Find number 6 (only six segment number which is not a subset of 1)
      for(auto it = sixsegs.begin(); it != sixsegs.end(); it++)
      {
        if(!Helper::IsSubset(numbers[1], *it))
        {
          numbers[6] = *it;
          sixsegs.erase(it);
          break;
        }
      }

      // Find number 5 (only five segment number which is a subset of 6)
      for(auto it = fivesegs.begin(); it != fivesegs.end(); it++)
      {
        if(Helper::IsSubset(*it, numbers[6]))
        {
          numbers[5] = *it;
          fivesegs.erase(it);
          break;
        }
      }
      // Find number 2 (last five segment number)
      numbers[2] = fivesegs.front();

      // Find number 9 (only six segment number which 4 is a subset of)
      for(auto it = sixsegs.begin(); it != sixsegs.end(); it++)
      {
        if(Helper::IsSubset(numbers[4], *it))
        {
          numbers[9] = *it;
          sixsegs.erase(it);
          break;
        }
      }

      // Find number 0 (last six segment number)
      numbers[0] = sixsegs.front();

      // Calculate the segment display
      int num = 0;
      for(auto number : signal.display)
      {
        auto it = std::find(numbers.begin(), numbers.end(), number);
        int i = it - numbers.begin();
        num = num * 10 + i;
      }
      sum += num;
    }
    return sum;
  }
}
