#include "aoc.h"

namespace day25
{
  REGISTER_DAY(day25, Array2D<char>, int);

  REGISTER_TEST_EXAMPLE(day25, ExampleInput, 1, 58);
  REGISTER_TEST        (day25, Input,        1, 419);

  READ_INPUT(input)
  {
    return Input::ReadArray2D(input);
  }

  OUTPUT1(inputConst)
  {
    Array2D<char> input = inputConst;
    bool hasMoved = true;
    int i = 0;
    while(hasMoved)
    {
      hasMoved = false;
      Array2D<char> cpy = input;
      Index2D index{0, 0};
      for(auto& c : cpy)
      {
        if(c == '>')
        {
          Index2D newIndex = index;
          newIndex.x = (newIndex.x + 1) % cpy.width;
          if(cpy[newIndex] == '.')
          {
            input[newIndex] = '>';
            input[index] = '.';
            hasMoved = true;
          }
        }
        cpy.Increment(index);
      }
      cpy = input;
      index = {0, 0};
      for(auto& c : cpy)
      {
        if(c == 'v')
        {
          Index2D newIndex = index;
          newIndex.y = (newIndex.y + 1) % cpy.height;
          if(cpy[newIndex] == '.')
          {
            input[newIndex] = 'v';
            input[index] = '.';
            hasMoved = true;
          }
        }
        cpy.Increment(index);
      }
      i++;
    }
    return i;
  }

  OUTPUT2(input)
  {
    return 0;
  }
}
