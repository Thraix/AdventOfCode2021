#include "aoc.h"

namespace day23
{

  using State = std::map<Index2D, char>;

  bool Find(const State& state, const Index2D& pos, char c)
  {
    auto it = state.find(pos);
    if(it != state.end())
      return it->second == c;
    return false;
  }

  bool ValidateState(const State& state)
  {
    return Find(state, {2, 1}, 'A') &&
           Find(state, {2, 2}, 'A') &&
           Find(state, {4, 1}, 'B') &&
           Find(state, {4, 2}, 'B') &&
           Find(state, {6, 1}, 'C') &&
           Find(state, {6, 2}, 'C') &&
           Find(state, {8, 1}, 'D') &&
           Find(state, {8, 2}, 'D');
  }

  int Heuristic(const State& state)
  {
    int h = 0;
    for(auto& piece : state)
    {
      // Cost to move piece to the top of the room
      if(piece.second == 'A' && piece.first.x != 2)
        h += std::abs(piece.first.x - 2) + std::abs(piece.first.y - 0) + 1;
      if(piece.second == 'B' && piece.first.x != 4)
        h += (std::abs(piece.first.x - 4) + std::abs(piece.first.y - 0) + 1) * 10;
      if(piece.second == 'C' && piece.first.x != 6)
        h += (std::abs(piece.first.x - 6) + std::abs(piece.first.y - 0) + 1) * 100;
      if(piece.second == 'D' && piece.first.x != 8)
        h += (std::abs(piece.first.x - 8) + std::abs(piece.first.y - 0) + 1) * 1000;
    }
    return h;
  }

  int GetCost(char c)
  {
    switch(c)
    {
    case 'A': return 1;
    case 'B': return 10;
    case 'C': return 100;
    case 'D': return 1000;
    }
    std::cout << "Invalid char: " << c << std::endl;
    return 0;
  }

  std::vector<std::pair<int, State>> ValidStates(const State& state, int h)
  {
    std::vector<std::pair<int, State>> newStates;
    for(auto& piece : state)
    {
      if(piece.first.y > 0)
      { // Piece is in the room, move to hallway

        // Check if already at correct position
        bool canMove = false;
        if(piece.first.x == (piece.second - 'A') * 2 + 2)
        {
          for(int i = piece.first.y + 1; i < 1 + h; i++)
          {
            if(state.find({piece.first.x, i})->second != piece.second)
            {
              canMove = true;
              break;
            }
          }
        }
        else
          canMove = true;

        // Check if piece is obstructed by others in the room
        for(int i = piece.first.y - 1; i > 0; i--)
        {
          if(state.count({piece.first.x, i}) != 0)
          {
            canMove = false;
            break;
          }
        }

        if(canMove)
        {
          // Check hallways to the left
          for(int i = piece.first.x - 1; i >= 0; i--)
          {
            // Is valid position in hallway
            if(i == 0 || i % 2 == 1 || i == 10)
            {
              if(state.count({i, 0}) == 0)
              {
                State newState = state;
                newState[{i, 0}] = piece.second;
                newState.erase(piece.first);
                newStates.emplace_back(std::pair<int, State>{(piece.first.y + std::abs(piece.first.x - i)) * GetCost(piece.second), newState});
              }
              else
                break;
            }
          }

          // Check hallways to the right
          for(int i = piece.first.x + 1; i < 11; i++)
          {
            // Is valid position in hallway
            if(i == 0 || i % 2 == 1 || i == 10)
            {
              if(state.count({i, 0}) == 0)
              {
                State newState = state;
                newState[{i, 0}] = piece.second;
                newState.erase(piece.first);
                newStates.emplace_back(std::pair<int, State>{(piece.first.y + std::abs(piece.first.x - i)) * GetCost(piece.second), newState});
              }
              else
                break;
            }
          }
        }
      }
      else
      { // Piece is in the hallway, move to room

        int x = (piece.second - 'A') * 2 + 2;
        int dir = Helper::Sign(x - piece.first.x);
        bool canMove = true;

        // Check if hallway is clear to correct position
        for(int i = piece.first.x + dir; (dir < 0 && i > x) || (dir > 0 && i < x); i += dir)
        {
          if(state.count({i, 0}) != 0)
          {
            canMove = false;
            break;
          }
        }

        if(canMove)
        {
          // Check if room is filled with same piece or no pieces
          int pos = h;
          for(int i = 1; i < 1 + h; i++)
          {
            if(state.count({x, i}) != 0)
            {
              if(state.find({x, i})->second == piece.second)
              {
                if(pos == h)
                  pos = i - 1;
              }
              else
              {
                pos = 0;
                break;
              }
            }
          }
          if(pos != 0)
          {
            State newState = state;
            newState[{x, pos}] = piece.second;
            newState.erase(piece.first);
            newStates.emplace_back(std::pair<int, State>{(pos + std::abs(piece.first.x - x)) * GetCost(piece.second), newState});
          }
        }
      }
    }
    return newStates;
  }


  std::vector<std::pair<int, State>> ValidStates4(const State& state)
  {
    return ValidStates(state, 4);
  }

  int Solve(const State& state, int h)
  {
    return Helper::AStar(state,
                         &Heuristic,
                         [h](const State& state) { return ValidStates(state, h); },
                         &ValidateState);
  }

  REGISTER_DAY(day23, State, int);

  REGISTER_TEST_EXAMPLE(day23, ExampleInput, 1, 12521);
  REGISTER_TEST        (day23, Input,        1, 14350);
  REGISTER_TEST_EXAMPLE(day23, ExampleInput, 2, 44169);
  REGISTER_TEST        (day23, Input,        2, 49742);

  READ_INPUT(input)
  {
    std::string str;
    getline(input, str);
    getline(input, str);
    getline(input, str);
    std::map<Index2D, char> state;
    state.emplace(Index2D{2, 1}, str[3]);
    state.emplace(Index2D{4, 1}, str[5]);
    state.emplace(Index2D{6, 1}, str[7]);
    state.emplace(Index2D{8, 1}, str[9]);

    getline(input, str);
    state.emplace(Index2D{2, 2}, str[3]);
    state.emplace(Index2D{4, 2}, str[5]);
    state.emplace(Index2D{6, 2}, str[7]);
    state.emplace(Index2D{8, 2}, str[9]);

    return state;
  }

  OUTPUT1(input)
  {
    return Solve(input, 2);
  }

  OUTPUT2(input)
  {
    State state;
    for(auto& piece : input)
    {
      if(piece.first.y == 2)
        state.emplace(Index2D{piece.first.x, 4}, piece.second);
      else
        state.emplace(piece.first, piece.second);
    }
    state.emplace(Index2D{2, 2}, 'D');
    state.emplace(Index2D{2, 3}, 'D');
    state.emplace(Index2D{4, 2}, 'C');
    state.emplace(Index2D{4, 3}, 'B');
    state.emplace(Index2D{6, 2}, 'B');
    state.emplace(Index2D{6, 3}, 'A');
    state.emplace(Index2D{8, 2}, 'A');
    state.emplace(Index2D{8, 3}, 'C');

    return Solve(state, 4);
  }
}
