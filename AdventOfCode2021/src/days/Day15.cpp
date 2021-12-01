#include "aoc.h"

namespace day15
{
  REGISTER_DAY(day15, std::vector<int>, int);

  REGISTER_TEST_EXAMPLE(day15, ExampleInput, 1, 0);
  REGISTER_TEST        (day15, Input,        1, 0);
  REGISTER_TEST_EXAMPLE(day15, ExampleInput, 2, 0);
  REGISTER_TEST        (day15, Input,        2, 0);

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
