#include "aoc.h"

namespace day18
{
  REGISTER_DAY(day18, std::vector<int>, int);

  REGISTER_TEST_EXAMPLE(day18, ExampleInput, 1, 0);
  REGISTER_TEST        (day18, Input,        1, 0);
  REGISTER_TEST_EXAMPLE(day18, ExampleInput, 2, 0);
  REGISTER_TEST        (day18, Input,        2, 0);

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
