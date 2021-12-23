#include "aoc.h"

namespace day15
{

  int Heuristic(const Index2D& index, const Array2D<int>& array)
  {
    return std::abs(index.x - array.width + 1) && std::abs(index.y - array.height + 1);
  }

  std::vector<std::pair<int, Index2D>> Branch(const Index2D& index, const Array2D<int>& array)
  {
    Index2D indices[4]{{index.x - 1, index.y},
                       {index.x, index.y - 1},
                       {index.x + 1, index.y},
                       {index.x, index.y + 1}};
    std::vector<std::pair<int, Index2D>> moves;
    for(auto& index : indices)
    {
      if(array.IsInside(index))
        moves.emplace_back(std::pair<int, Index2D>{array[index], index});
    }
    return moves;
  }

  int Goal(const Index2D& index, const Array2D<int>& array)
  {
    return index.x == array.width - 1 && index.y == array.height - 1;
  }

  int Pathfinder(const Array2D<int>& array)
  {
    return Helper::AStar(Index2D{0, 0},
                         [array](const Index2D& index) { return Heuristic(index, array); },
                         [array](const Index2D& index) { return Branch(index, array); },
                         [array](const Index2D& index) { return Goal(index, array); });
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
