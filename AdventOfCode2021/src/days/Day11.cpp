#include "aoc.h"

namespace day11
{

  std::set<Index2D> CalculateFlashing(Array2D<int>& array)
  {
    for(auto& val : array)
      val++;
    std::set<Index2D> flashed;
    bool hasChanged = true;
    while(hasChanged)
    {
      Array2D<int> arrayCpy = array;
      hasChanged = false;
      Index2D index{0, 0};
      for(auto& val : array)
      {
        if(val > 9 && flashed.find(index) == flashed.end())
        {
          flashed.emplace(index);
          hasChanged = true;
          for(int y = -1; y < 2; y++)
          {
            for(int x = -1; x < 2; x++)
            {
              if(x == 0 && y == 0)
                continue;
              Index2D newIndex{index.x + x, index.y + y};
              if(array.IsInside(newIndex))
                arrayCpy[newIndex]++;
            }
          }
        }
        array.Increment(index);
      }
      array = arrayCpy;
    }
    return flashed;
  }

  REGISTER_DAY(day11, Array2D<int>, int);

  REGISTER_TEST_EXAMPLE(day11, ExampleInput, 1, 1656);
  REGISTER_TEST        (day11, Input,        1, 1667);
  REGISTER_TEST_EXAMPLE(day11, ExampleInput, 2, 195);
  REGISTER_TEST        (day11, Input,        2, 488);

  READ_INPUT(input)
  {
    return Input::ReadDigitsAsArray2D(input);
  }

  OUTPUT1(input)
  {
    InputType array = input;

    int count = 0;
    for(int i = 0; i < 100; i++)
    {
      std::set<Index2D> flashed = CalculateFlashing(array);
      count += flashed.size();
      for(auto& flash : flashed)
        array[flash] = 0;
    }
    return count;
  }

  OUTPUT2(input)
  {
    InputType array = input;

    int count = 1;
    while(true)
    {
      std::set<Index2D> flashed = CalculateFlashing(array);
      if(flashed.size() == array.width * array.height)
        return count;
      for(auto& flash : flashed)
        array[flash] = 0;
      count++;
    }
    return count;
  }
}
