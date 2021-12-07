#include "aoc.h"

namespace day07
{
  REGISTER_DAY(day07, std::vector<int>, int);

  REGISTER_TEST_EXAMPLE(day07, ExampleInput, 1, 37);
  REGISTER_TEST        (day07, Input,        1, 359648);
  REGISTER_TEST_EXAMPLE(day07, ExampleInput, 2, 168);
  REGISTER_TEST        (day07, Input,        2, 100727924);

  READ_INPUT(input)
  {
    return Input::ReadInts(input, ',');
  }

  OUTPUT1(input)
  {
    int max = Helper::Max(input);
    int min = Helper::Min(input);
    int minCost = std::numeric_limits<int>::max();
    for(int i = min; i < max + 1; i++)
    {
      int cost = 0;
      for(auto num : input)
      {
        cost += std::abs(num - i);
      }
      minCost = std::min(minCost, cost);
    }
    return minCost;
  }

  OUTPUT2(input)
  {
    int max = Helper::Max(input);
    int min = Helper::Min(input);
    int minCost = std::numeric_limits<int>::max();
    for(int i = min; i < max + 1; i++)
    {
      int cost = 0;
      for(auto num : input)
      {
        int steps = std::abs(num - i);
        cost += steps * (steps + 1) / 2;
      }
      minCost = std::min(minCost, cost);
    }
    return minCost;
  }
}
