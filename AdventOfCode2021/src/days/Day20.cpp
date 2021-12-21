#include "aoc.h"

namespace day20
{
  struct Data
  {
    std::string line;
    Array2D<char> grid;
  };

  int GetNumber(const Array2D<char>& array, Index2D index)
  {
    int num = 0;
    for(int y = index.y - 1; y <= index.y + 1; y++)
    {
      for(int x = index.x - 1; x <= index.x + 1; x++)
      {
        num <<= 1;
        Index2D newIndex{x, y};
        if(array.IsInside(newIndex) && array[newIndex] == '#')
          num |= 1;
      }
    }
    return num;
  }

  int Solve(const Data& input, int iter)
  {
    int SIZE = (2 * iter) * 2;
    Array2D<char> output{input.grid.width + SIZE, input.grid.height + SIZE};
    Index2D index{0, 0};
    output.Fill('.');
    for(auto& val : input.grid)
    {
      output.Set(index.x + SIZE / 2, index.y + SIZE / 2, val);
      input.grid.Increment(index);
    }
    for(int i = 0; i < iter; i++)
    {
      Array2D<char> cpy = output;
      Index2D index{0, 0};
      for(auto& grid : output)
      {
        int num = GetNumber(cpy, index);
        output[index] = input.line[num];
        output.Increment(index);
      }
      std::string str;
    }

    int count = 0;
    for(int y = iter; y < output.height - iter; y++)
      for(int x = iter; x < output.width - iter; x++)
        if(output.Get(x, y) == '#')
          count++;

    return count;
  }

  REGISTER_DAY(day20, Data, int);

  REGISTER_TEST_EXAMPLE(day20, ExampleInput, 1, 35);
  REGISTER_TEST        (day20, Input,        1, 5203);
  REGISTER_TEST_EXAMPLE(day20, ExampleInput, 2, 3351);
  REGISTER_TEST        (day20, Input,        2, 18806);

  READ_INPUT(input)
  {
    Data data;
    input >> data.line;
    std::string str;
    getline(input, str);
    data.grid = Input::ReadArray2D(input);
    return data;
  }

  OUTPUT1(input)
  {
    return Solve(input, 2);
  }

  OUTPUT2(input)
  {
    return Solve(input, 50);
  }
}
