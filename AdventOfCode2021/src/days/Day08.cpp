#include "aoc.h"

namespace day08
{
  struct Line
  {
    std::vector<std::string> numbers;
    std::vector<std::string> display;
  };

  REGISTER_DAY(day08, std::vector<Line>, int);

  REGISTER_TEST_EXAMPLE(day08, ExampleInput, 1, 26);
  REGISTER_TEST        (day08, Input,        1, 301);
  REGISTER_TEST_EXAMPLE(day08, ExampleInput, 2, 61229);
  REGISTER_TEST        (day08, Input,        2, 908067);

  READ_INPUT(input)
  {
    std::string str;
    std::vector<Line> lines;
    while(getline(input, str))
    {
      Line line;
      std::stringstream ss{str};
      for(int i = 0; i < 10; i++)
      {
        std::string s;
        ss >> s;
        line.numbers.emplace_back(s);
      }
      char c;
      ss >> c;
      for(int i = 0; i < 4; i++)
      {
        std::string s;
        ss >> s;
        line.display.emplace_back(s);
      }
      lines.emplace_back(line);
    }
    return lines;
  }

  OUTPUT1(input)
  {
    int count = 0;
    for(auto&& line : input)
    {
      for(auto&& number : line.display)
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
    for(auto&& line : input)
    {
      std::vector<std::string> numbers(10);
      // Find all numbers with unique amount of segments
      for(auto&& number : line.numbers)
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

      // Find all numbers with five segments
      std::vector<std::string> fivesegs;
      for(auto&& number : line.numbers)
      {
        if(number.size() == 5)
          fivesegs.emplace_back(number);
      }
      // Find all numbers with six segments
      std::vector<std::string> sixsegs;
      for(auto&& number : line.numbers)
      {
        if(number.size() == 6)
          sixsegs.emplace_back(number);
      }

      // Find number 3 (only five segment number which contans all segments from 1)
      for(auto it = fivesegs.begin(); it != fivesegs.end(); it++)
      {
        if(it->find(numbers[1][0]) != std::string::npos && it->find(numbers[1][1]) != std::string::npos)
        {
          numbers[3] = *it;
          fivesegs.erase(it);
          break;
        }
      }

      // Find number 6 (only six segment number which does not contain all segments from 1)
      for(auto it = sixsegs.begin(); it != sixsegs.end(); it++)
      {
        if(it->find(numbers[1][0]) == std::string::npos || it->find(numbers[1][1]) == std::string::npos)
        {
          numbers[6] = *it;
          sixsegs.erase(it);
          break;
        }
      }

      // Find number 5 (only five segment number which is contained in a 6)
      for(auto it = fivesegs.begin(); it != fivesegs.end(); it++)
      {
        if(numbers[6].find(it->at(0)) != std::string::npos &&
           numbers[6].find(it->at(1)) != std::string::npos &&
           numbers[6].find(it->at(2)) != std::string::npos &&
           numbers[6].find(it->at(3)) != std::string::npos &&
           numbers[6].find(it->at(4)) != std::string::npos)
        {
          numbers[5] = *it;
          fivesegs.erase(it);
          break;
        }
      }
      // Find number 2 (last five segment number)
      numbers[2] = fivesegs.front();

      // Find number 9 (last number which is a subset of 4)
      for(auto it = sixsegs.begin(); it != sixsegs.end(); it++)
      {
        if(it->find(numbers[4][0]) != std::string::npos &&
           it->find(numbers[4][1]) != std::string::npos &&
           it->find(numbers[4][2]) != std::string::npos &&
           it->find(numbers[4][3]) != std::string::npos)
        {
          numbers[9] = *it;
          sixsegs.erase(it);
          break;
        }
      }

      // Find number 0 (last six segment number)
      numbers[0] = sixsegs.front();

      // Sort all numbers
      int i = 0;
      for(auto&& number : numbers)
      {
        std::sort(number.begin(), number.end());
        i++;
      }
      // Calculate the segment display
      int num = 0;
      for(auto number : line.display)
      {
        std::sort(number.begin(), number.end());
        auto it = std::find(numbers.begin(), numbers.end(), number);
        int i = it - numbers.begin();
        num = num * 10 + i;
      }
      sum += num;
    }
    return sum;
  }
}
