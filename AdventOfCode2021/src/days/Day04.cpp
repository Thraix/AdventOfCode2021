#include "aoc.h"

namespace day04
{
  struct Game
  {
    std::vector<int> input;
    std::vector<Array2D<int>> boards;
  };

  bool MarkAndCheck(Array2D<int>& board, int number)
  {
    Index2D index = board.Find(number);
    if(index)
    {
      board[index] = -1;
      // Check board is filled
      bool filledX = true;
      bool filledY = true;
      for(int i = 0; i < 5; i++)
      {
        if(board.Get(i, index.y) != -1)
          filledX = false;
        if(board.Get(index.x, i) != -1)
          filledY = false;
      }
      return filledX || filledY;
    }
    return false;
  }

  REGISTER_DAY(day04, Game, int);

  REGISTER_TEST_EXAMPLE(day04, ExampleInput, 1, 4512);
  REGISTER_TEST        (day04, Input,        1, 54275);
  REGISTER_TEST_EXAMPLE(day04, ExampleInput, 2, 1924);
  REGISTER_TEST        (day04, Input,        2, 13158);

  READ_INPUT(input)
  {
    Game game;
    std::string str;
    getline(input, str);
    std::stringstream ss{str};
    while(getline(ss, str, ','))
    {
      game.input.emplace_back(atoi(str.c_str()));
    }
    getline(input, str);
    while(!input.eof())
    {
      Array2D<int> array2D{5, 5};
      for(int y = 0; y < 5; y++)
      {
        getline(input, str);
        std::stringstream ss{str};
        for(int x = 0; x < 5; x++)
        {
          int i;
          ss >> i;
          array2D.Set(x, y, i);
        }
      }
      game.boards.emplace_back(array2D);
      getline(input, str);
    }
    return game;
  }

  OUTPUT1(input)
  {
    Game game = input; // Copy the data to be able to modify it
    int winner = -1;
    int i = 0;
    while(winner == -1)
    {
      int number = game.input[i];
      for(auto& board : game.boards)
      {
        if(MarkAndCheck(board, number))
        {
          int total = 0;
          for(auto& val : board)
          {
            if(val != -1)
              total += val;
          }
          return total * number;
        }
      }
      i++;
    }
    return 0;
  }

  OUTPUT2(input)
  {
    Game game = input; // Copy the data to be able to modify it
    int winner = -1;
    int i = 0;
    while(winner == -1)
    {
      int number = game.input[i];
      for(auto it = game.boards.begin(); it != game.boards.end();)
      {
        if(MarkAndCheck(*it, number))
        {
          if(game.boards.size() == 1)
          {
            int total = 0;
            for(auto& val : game.boards.front())
            {
              if(val != -1)
                total += val;
            }
            return total * number;
          }
          it = game.boards.erase(it);
        }
        else
          it++;
      }
      i++;
    }
    return 0;
  }
}
