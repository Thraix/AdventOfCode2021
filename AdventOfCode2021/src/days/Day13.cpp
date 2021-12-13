#include "aoc.h"

namespace day13
{

  void Fold(std::set<Index2D>& indices, bool x, int fold)
  {
    std::set<Index2D> newIndices;
    for(auto& index : indices)
    {
      // y axis
      if(x)
      {
        Index2D newIndex = index;
        if(newIndex.x > fold)
          newIndex.x = fold - (newIndex.x - 1) % fold - 1;
        newIndices.emplace(newIndex);
      }
      else
      {
        Index2D newIndex = index;
        if(newIndex.y > fold)
          newIndex.y = fold - (newIndex.y - 1) % fold - 1;
        newIndices.emplace(newIndex);
      }
    }
    indices = newIndices;
  }

  struct Paper
  {
    std::set<Index2D> indices;
    std::vector<std::pair<bool, int>> folds;
  };

  REGISTER_DAY(day13, Paper, int);

  REGISTER_TEST_EXAMPLE(day13, ExampleInput, 1, 17);
  REGISTER_TEST        (day13, Input,        1, 716);
  REGISTER_TEST_EXAMPLE(day13, ExampleInput, 2, 16);
  REGISTER_TEST        (day13, Input,        2, 97);

  READ_INPUT(input)
  {
    Paper paper;
    std::string str;
    while(getline(input, str))
    {
      if(str.empty())
        break;
      Index2D index;
      char c;
      std::stringstream ss{str};
      ss >> index.x >> c >> index.y;
      paper.indices.emplace(index);
    }

    while(getline(input, str))
    {
      char c, c2;
      std::string s;
      int i;
      std::stringstream ss{str};
      ss >> s >> s >> c >> c2 >> i;
      paper.folds.emplace_back(c == 'x', i);
    }
    return paper;
  }

  OUTPUT1(input)
  {
    std::set<Index2D> indices = input.indices;
    Fold(indices, input.folds.front().first, input.folds.front().second);
    return indices.size();
  }

  OUTPUT2(input)
  {
    std::set<Index2D> indices = input.indices;
    for(auto& fold : input.folds)
    {
      Fold(indices, fold.first, fold.second);
    }

    Index2D max = *indices.begin();
    for(auto index : indices)
    {
      max.x = std::max(index.x, max.x);
      max.y = std::max(index.y, max.y);
    }
    Array2D<char> board{max.x + 1, max.y + 1};
    board.Fill(' ');
    for(auto& index : indices)
    {
      board[index] = '#';
    }
    std::cout << board;
    // Not the "correct" output to part 2, but it verifies something at least
    return indices.size();
  }
}
