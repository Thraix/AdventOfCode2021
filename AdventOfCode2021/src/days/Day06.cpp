#include "aoc.h"

namespace day06
{

  int64_t GetPopulation(std::vector<int64_t>& lenternfishes, int days)
  {
    for(int i = 0; i < days; i++)
    {
      int64_t newBorn = lenternfishes[0];
      for(int j = 1; j < lenternfishes.size(); j++)
      {
        lenternfishes[j - 1] = lenternfishes[j];
      }
      lenternfishes[8] = newBorn;
      lenternfishes[6] += newBorn;
    }
    return Helper::Sum<int64_t>(lenternfishes);
  }

  REGISTER_DAY(day06, std::vector<int64_t>, int64_t);

  REGISTER_TEST_EXAMPLE(day06, ExampleInput, 1, 5934);
  REGISTER_TEST        (day06, Input,        1, 374994);
  REGISTER_TEST_EXAMPLE(day06, ExampleInput, 2, 26984457539);
  REGISTER_TEST        (day06, Input,        2, 1686252324092);

  READ_INPUT(input)
  {
    std::vector<int64_t> ints;
    ints.resize(9);

    std::string str;
    while(getline(input, str, ','))
    {
      ints[atoi(str.c_str())]++;
    }
    return ints;
  }

  OUTPUT1(inputConst)
  {
    InputType input = inputConst;
    return GetPopulation(input, 80);
  }

  OUTPUT2(inputConst)
  {
    InputType input = inputConst;
    return GetPopulation(input, 256);
  }
}
