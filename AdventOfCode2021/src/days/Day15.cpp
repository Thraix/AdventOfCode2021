#include "aoc.h"

namespace day15
{
  int Pathfinder(const Array2D<int>& array)
  {
    std::stack<Index2D> initial{};
    initial.emplace(Index2D{0, 0});

    std::set<Index2D> visited;
    visited.emplace(Index2D{0, 0});
    std::multimap<int, Index2D> paths;
    paths.emplace(0, Index2D{0, 0});

    int solution = 0;

    while(!paths.empty())
    {
      auto it = paths.begin();
      Index2D index = it->second;
      int val = it->first;
      if(index.x == array.width - 1 && index.y == array.height - 1)
      {
        solution = it->first;
        break;
      }
      paths.erase(it);
      Index2D indices[4]{{index.x - 1, index.y},
                         {index.x, index.y - 1},
                         {index.x + 1, index.y},
                         {index.x, index.y + 1}};
      for(auto& ind : indices)
      {
        if(array.IsInside(ind) && visited.count(ind) == 0)
        {
          paths.emplace(val + array[ind], ind);
          visited.emplace(ind);
        }
      }
    }
    return solution;
  }

  REGISTER_DAY(day15, Array2D<int>, int);

  REGISTER_TEST_EXAMPLE(day15, ExampleInput, 1, 40);
  REGISTER_TEST        (day15, Input,        1, 714);
  REGISTER_TEST_EXAMPLE(day15, ExampleInput, 2, 315);
  REGISTER_TEST        (day15, Input,        2, 2948);

  READ_INPUT(input)
  {
    return Input::ReadDigitsAsArray2D(input);
  }

  OUTPUT1(input)
  {
    return Pathfinder(input);
  }

  OUTPUT2(input)
  {
    Array2D<int> array{input.width * 5, input.height * 5};
    Index2D index{0, 0};
    for(auto& val : array)
    {
      val = input.GetMod(index.x, index.y) + index.x / input.width + index.y / input.height;
      if(val >= 10)
        val = val % 10 + 1;
      array.Increment(index);
    }
    return Pathfinder(array);
  }
}
