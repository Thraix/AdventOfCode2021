#include "aoc.h"

namespace day02
{
  enum class Dir
  {
    Forward, Down, Up
  };
  struct Move
  {
    Dir dir;
    int amount;
  };

  REGISTER_DAY(day02, std::vector<Move>, int);

  REGISTER_TEST_EXAMPLE(day02, ExampleInput, 1, 150);
  REGISTER_TEST        (day02, Input,        1, 1815044);
  REGISTER_TEST_EXAMPLE(day02, ExampleInput, 2, 900);
  REGISTER_TEST        (day02, Input,        2, 1739283308);

  READ_INPUT(input)
  {
    std::vector<Move> moves;
    std::string str;
    while (getline(input, str))
    {
      std::stringstream ss{ str };
      std::string s;
      int i;
      ss >> s >> i;
      if (s == "forward")
        moves.emplace_back(Move{Dir::Forward, i});
      else if(s == "down")
        moves.emplace_back(Move{Dir::Down, i});
      else if(s == "up")
        moves.emplace_back(Move{Dir::Up, i});
    }
    return moves;
  }

  OUTPUT1(input)
  {
    int x = 0;
    int y = 0;
    for (auto&& move : input)
    {
      switch (move.dir)
      {
      case Dir::Forward:
        x += move.amount;
        break;
      case Dir::Down:
        y += move.amount;
        break;
      case Dir::Up:
        y -= move.amount;
        break;
      }
    }
    return x * y;
  }

  OUTPUT2(input)
  {
    int x = 0;
    int y = 0;
    int aim = 0;
    for (auto&& move : input)
    {
      switch (move.dir)
      {
      case Dir::Forward:
        x += move.amount;
        y += aim * move.amount;
        break;
      case Dir::Down:
        aim += move.amount;
        break;
      case Dir::Up:
        aim -= move.amount;
        break;
      }
    }
    return x * y;
  }
}
