#include "aoc.h"

namespace day05
{
  struct Line
  {
    int x1;
    int y1;
    int x2;
    int y2;
  };

  REGISTER_DAY(day05, std::vector<Line>, int);

  REGISTER_TEST_EXAMPLE(day05, ExampleInput, 1, 5);
  REGISTER_TEST        (day05, Input,        1, 5442);
  REGISTER_TEST_EXAMPLE(day05, ExampleInput, 2, 12);
  REGISTER_TEST        (day05, Input,        2, 19571);

  READ_INPUT(input)
  {
    std::string str;
    std::vector<Line> lines;
    while(getline(input, str))
    {
      std::stringstream ss{str};
      Line line;
      ss >> line.x1 >> "," >> line.y1 >> "->" >> line.x2 >> "," >> line.y2;
      lines.emplace_back(line);
    }
    return lines;
  }

  OUTPUT1(input)
  {
    Index2D max;
    for(auto& line : input)
    {
      max.x = std::max({max.x, line.x1, line.x2});
      max.y = std::max({max.y, line.y1, line.y2});
    }
    Array2D<uint8_t> overlap{max.x + 1, max.y + 1};
    for(auto& line : input)
    {
      if(line.x1 == line.x2 || line.y1 == line.y2)
      {
        int width = std::max(std::abs(line.x1 - line.x2), std::abs(line.y1 - line.y2)) + 1;
        int deltaX = Helper::Sign(line.x2 - line.x1);
        int deltaY = Helper::Sign(line.y2 - line.y1);
        for(int i = 0; i < width; i++)
        {
          Index2D index{line.x1 + deltaX * i, line.y1 + deltaY * i};
          overlap[index]++;
        }
      }
    }
    int count = 0;
    overlap.Each([&](const Array2D<uint8_t>& overlap, const Index2D& index)
    {
      if(overlap[index] > 1)
        count++;
    });
    return count;
  }

  OUTPUT2(input)
  {
    Index2D max;
    for(auto& line : input)
    {
      max.x = std::max({max.x, line.x1, line.x2});
      max.y = std::max({max.y, line.y1, line.y2});
    }
    Array2D<uint8_t> overlap{max.x + 1, max.y + 1};
    for(auto& line : input)
    {
      int width = std::max(std::abs(line.x1 - line.x2), std::abs(line.y1 - line.y2)) + 1;
      int deltaX = Helper::Sign(line.x2 - line.x1);
      int deltaY = Helper::Sign(line.y2 - line.y1);
      for(int i = 0; i < width; i++)
      {
        Index2D index{line.x1 + deltaX * i, line.y1 + deltaY * i};
        overlap[index]++;
      }
    }
    int count = 0;
    overlap.Each([&](const Array2D<uint8_t>& overlap, const Index2D& index)
    {
      if(overlap[index] > 1)
        count++;
    });
    return count;
  }
}
