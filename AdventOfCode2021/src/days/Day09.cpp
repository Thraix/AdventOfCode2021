#include "aoc.h"

namespace day09
{
  REGISTER_DAY(day09, Array2D<int>, int);

  REGISTER_TEST_EXAMPLE(day09, ExampleInput, 1, 15);
  REGISTER_TEST        (day09, Input,        1, 478);
  REGISTER_TEST_EXAMPLE(day09, ExampleInput, 2, 1134);
  REGISTER_TEST        (day09, Input,        2, 1327014);

  READ_INPUT(input)
  {
    return Input::ReadDigitsAsArray2D(input);
  }

  OUTPUT1(input)
  {
    int count = 0;
    input.Each([&count](auto&& array, const Index2D& index) {
      Index2D indices[4]{{index.x - 1, index.y},
                         {index.x, index.y - 1},
                         {index.x + 1, index.y},
                         {index.x, index.y + 1}};
      for(auto&& ind : indices)
      {
        if(array.IsInside(ind) && array[ind] <= array[index])
          return;
      }
      count += array[index] + 1;
    });
    return count;
  }

  OUTPUT2(input)
  {
    std::vector<Index2D> basins;
    input.Each([&basins](auto&& array, const Index2D& index) {
      Index2D indices[4]{{index.x - 1, index.y},
                         {index.x, index.y - 1},
                         {index.x + 1, index.y},
                         {index.x, index.y + 1}};
      for(auto&& ind : indices)
      {
        if(array.IsInside(ind) && array[ind] <= array[index])
          return;
      }
      basins.emplace_back(index);
    });

    std::vector<int> numbers;
    for(auto&& basin : basins)
    {
      std::stack<Index2D> stack;
      std::set<Index2D> visited;
      stack.emplace(basin);
      visited.emplace(basin);
      while(!stack.empty())
      {
        auto index = stack.top();
        stack.pop();
        Index2D indices[4]{{index.x - 1, index.y},
                           {index.x, index.y - 1},
                           {index.x + 1, index.y},
                           {index.x, index.y + 1}};
        for(auto&& ind : indices)
        {
          if(input.IsInside(ind) && input[ind] != 9 && visited.find(ind) == visited.end())
          {
            stack.emplace(ind);
            visited.emplace(ind);
          }
        }
      }
      numbers.emplace_back(visited.size());
    }

    std::sort(numbers.begin(), numbers.end());
    return numbers[numbers.size() - 1] * numbers[numbers.size() - 2] * numbers[numbers.size() - 3];
  }
}
