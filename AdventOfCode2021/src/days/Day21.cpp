#include "aoc.h"

namespace day21
{

  int Mod(int i)
  {
    return (i - 1) % 10 + 1;
  }


  std::pair<int64_t, int64_t> Roll(int position1, int points1, int position2, int points2, bool player1, int depth)
  {
    if(points2 >= 21)
      return {0, 1};
    else if(points1 >= 21)
      return {1, 0};

    // 3: 111
    // 4: 211 121 112
    // 5: 221 212 122 311 131 113
    // 6: 222 321 312 213 231 123 132
    // 7: 223 232 323 133 331 313
    // 8: 233 323 322
    // 9: 333
    std::map<int, int> outcomes{{3, 1}, {4, 3}, {5, 6}, {6, 7}, {7, 6}, {8, 3}, {9, 1}};

    std::pair<int64_t, int64_t> wins{0, 0};
    int initialPos = 0;
    int initialPoints = 0;
    if(player1)
    {
      initialPos = position1;
      initialPoints = points1;
    }
    else
    {
      initialPos = position2;
      initialPoints = points2;
    }
    for(auto[value, times] : outcomes)
    {
      if(player1)
      {
        position1 = initialPos;
        points1 = initialPoints;
        position1 = Mod(position1 + value);
        points1 += position1;
      }
      else
      {
        position2 = initialPos;
        points2 = initialPoints;
        position2 = Mod(position2 + value);
        points2 += position2;
      }
      auto subwins = Roll(position1, points1, position2, points2, !player1, depth + 1);
      wins.first += times * subwins.first;
      wins.second += times * subwins.second;
    }
    return wins;
  }

  REGISTER_DAY(day21, std::vector<int>, int64_t);

  REGISTER_TEST_EXAMPLE(day21, ExampleInput, 1, 739785);
  REGISTER_TEST        (day21, Input,        1, 503478);
  REGISTER_TEST_EXAMPLE(day21, ExampleInput, 2, 444356092776315);
  REGISTER_TEST        (day21, Input,        2, 716241959649754);

  READ_INPUT(input)
  {
    std::vector<int> players;
    int i;
    std::string str;
    while(getline(input, str))
    {
      std::stringstream ss{str};
      ss >> "Player" >> i >> "starting position:" >> i;
      players.emplace_back(i);
    }
    return players;
  }

  OUTPUT1(input)
  {
    std::vector<int> positions = input;
    std::vector<int> points;
    points.resize(input.size());
    for(int i = 1; i < 10000; i += 3)
    {
      int index = (i - 1) % 2;
      positions[index] = Mod(positions[index] +  3 * (i + 1));
      points[index] += positions[index];
      if(points[index] >= 1000)
      {
        return ((int64_t)i + 2ll) * (int64_t)points[(index + 1) % 2];
      }
    }
    return 0;
  }

  OUTPUT2(input)
  {
    std::pair<int64_t, int64_t> wins = Roll(input[0], 0, input[1], 0, true, 0);
    return std::max(wins.first, wins.second);
  }
}
