#include "aoc.h"

namespace day05
{
  REGISTER_DAY(day05, std::vector<int>, int);

  REGISTER_TEST_EXAMPLE(day05, ExampleInput, 1, 0);
  REGISTER_TEST        (day05, Input,        1, 0);
  REGISTER_TEST_EXAMPLE(day05, ExampleInput, 2, 0);
  REGISTER_TEST        (day05, Input,        2, 0);

  READ_INPUT(input)
  {
    return Input::ReadInts(input);
  }

  OUTPUT1(input)
  {
    return 0;
  }

  OUTPUT2(input)
  {
    return 0;
  }
}
