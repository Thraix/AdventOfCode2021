#include "aoc.h"

namespace day23
{
  
  using State = std::map<Index2D, char>;

  struct Node
  {
    std::vector<std::pair<Index2D, int>> paths; // cost to walk to node
  };

  struct Data
  {
    std::map<Index2D, Node> paths;
    std::map<Index2D, char> players;
  };

  void Map(std::pair<const Index2D, Node>& node1, std::pair<const Index2D, Node>& node2)
  {
    int cost = std::abs(node1.first.x - node2.first.x) + std::abs(node1.first.y - node2.first.y);
    node1.second.paths.emplace_back(std::pair<Index2D, int>{node2.first, cost});
    node2.second.paths.emplace_back(std::pair<Index2D, int>{node1.first, cost});
  }

  bool Find(const std::map<Index2D, char>& state, const Index2D& pos, char c)
  {
    auto it = state.find(pos);
    if(it != state.end())
      return it->second == c;
    return false;
  }

  bool ValidateState(const std::map<Index2D, char>& state)
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

  void Print(const State& state)
  {
    for(int i = -1; i < 4; i++)
    {
      for(int j = -1; j < 12; j++)
      {
        auto it = state.find(Index2D{j, i});
        if(it != state.end())
          std::cout << it->second;
        else if((j >= 0 && j < 11 && i == 0) || (j > 1 && j < 9 && (j % 2 == 0) && i > 0 && i < 3))
        {
          std::cout << '.';
        }
        else
          std::cout << '#';
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }

  int Heuristic(const std::map<Index2D, char>& state)
  {
    int h = 0;
    for(auto& player : state)
    {
      if(player.second == 'A' && player.first.x != 2)
        h += std::abs(player.first.x - 2) + std::abs(player.first.y - 0) + 1;
      if(player.second == 'B' && player.first.x != 4)
        h += (std::abs(player.first.x - 4) + std::abs(player.first.y - 0) + 1) * 10;
      if(player.second == 'C' && player.first.x != 6)
        h += (std::abs(player.first.x - 6) + std::abs(player.first.y - 0) + 1) * 100;
      if(player.second == 'D' && player.first.x != 8)
        h += (std::abs(player.first.x - 8) + std::abs(player.first.y - 0) + 1) * 1000;
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

  std::vector<std::pair<int, State>> ValidStates(const std::map<Index2D, char>& state)
  {
    std::vector<std::pair<int, State>> newStates;
    for(auto& player : state)
    {
      // is in room
      if(player.first.y > 0)
      {
        bool canMove = false;
        if(player.first.x == (player.second - 'A') * 2 + 2)
        {
          for(int i = player.first.y + 1; i < 3; i++)
          {
            if(state.find({player.first.x, i})->second != player.second)
            {
              canMove = true;
            }
          }
        }
        else
          canMove = true;
        for(int i = player.first.y - 1; i > 0; i--)
        {
          if(state.count({player.first.x, i}) != 0)
          {
            canMove = false;
            break;
          }
        }
        if(canMove)
        {
          for(int i = player.first.x - 1; i >= 0; i--)
          {
            // Is valid position in hallway
            if(i == 0 || i % 2 == 1)
            {
              if(state.count({i, 0}) == 0)
              {
                State newState = state;
                newState[{i, 0}] = player.second;
                newState.erase(player.first);
                newStates.emplace_back(std::pair<int, State>{(player.first.y + std::abs(player.first.x - i)) * GetCost(player.second), newState});
              }
            }
          }
          for(int i = player.first.x + 1; i < 11; i++)
          {
            // Is valid position in hallway
            if(i == 0 || i % 2 == 1)
            {
              if(state.count({i, 0}) == 0)
              {
                State newState = state;
                newState[{i, 0}] = player.second;
                newState.erase(player.first);
                newStates.emplace_back(std::pair<int, State>{(player.first.y + std::abs(player.first.x - i)) * GetCost(player.second), newState});
              }
            }
          }
        }
      }
      else
      {
        bool xd = Find(state, {3, 0}, 'B') && Find(state, {5, 0}, 'C');
        int x = (player.second - 'A') * 2 + 2;
        int dir = Helper::Sign(x - player.first.x);
        bool canMove = true;
        for(int i = player.first.x + dir; i > 0 && i < 11; i += dir)
        {
          if(state.count({i, 0}) != 0)
          {
            canMove = false;
            break;
          }
        }
        if(canMove)
        {
          int pos = 2;
          for(int i = 1; i < 3; i++)
          {
            if(state.count({x, i}) != 0)
            {
              if(state.find({x, i})->second == player.second)
              {
                if(pos == 2)
                  pos = i - 1;
              }
              else
              {
                pos = 0;
                break;
              }
            }
          }
          if(xd)
          {
            // std::cout << x << " " <<  pos << std::endl;
            // Print(state);
          }
          if(pos != 0)
          {
            State newState = state;
            newState[{x, pos}] = player.second;
            newState.erase(player.first);
            newStates.emplace_back(std::pair<int, State>{(pos + std::abs(player.first.x - x)) * GetCost(player.second), newState});
          }
        }
      }
    }
    return newStates;
        // return newStates;
  }

  REGISTER_DAY(day23, Data, int);

  REGISTER_TEST_EXAMPLE(day23, ExampleInput, 1, 12521);
  REGISTER_TEST        (day23, Input,        1, 0);
  REGISTER_TEST_EXAMPLE(day23, ExampleInput, 2, 0);
  REGISTER_TEST        (day23, Input,        2, 0);

  READ_INPUT(input)
  {
    std::map<Index2D, Node> nodes;

    // Hallway
    nodes.emplace(Index2D{0, 0}, Node{});
    nodes.emplace(Index2D{1, 0}, Node{});
    nodes.emplace(Index2D{3, 0}, Node{});
    nodes.emplace(Index2D{5, 0}, Node{});
    nodes.emplace(Index2D{7, 0}, Node{});
    nodes.emplace(Index2D{9, 0}, Node{});
    nodes.emplace(Index2D{10, 0}, Node{});

    // Rooms
    nodes.emplace(Index2D{2, 1}, Node{});
    nodes.emplace(Index2D{2, 2}, Node{});
    nodes.emplace(Index2D{4, 1}, Node{});
    nodes.emplace(Index2D{4, 2}, Node{});
    nodes.emplace(Index2D{6, 1}, Node{});
    nodes.emplace(Index2D{6, 2}, Node{});
    nodes.emplace(Index2D{8, 1}, Node{});
    nodes.emplace(Index2D{8, 2}, Node{});



    auto it = nodes.find({2, 1});
    auto it2 = nodes.find({0, 0});
    Map(*it, *it2);

    it = nodes.find({8, 1});
    it2 = nodes.find({10, 0});
    Map(*it, *it2);

    for(int i = 0; i < 4; i++)
    {
      auto itOver = nodes.find({2 + i * 2, 1});
      auto itUnder = nodes.find({2 + i * 2, 2});

      auto it1 = nodes.find({itOver->first.x - 1, 0});
      auto it2 = nodes.find({itOver->first.x + 1, 0});

      Map(*itOver, *itUnder);
      Map(*itOver, *it1);
      Map(*itOver, *it2);
    }

    std::string str;
    getline(input, str);
    getline(input, str);
    getline(input, str);
    std::map<Index2D, char> players;
    players.emplace(Index2D{2, 1}, str[3]);
    players.emplace(Index2D{4, 1}, str[5]);
    players.emplace(Index2D{6, 1}, str[7]);
    players.emplace(Index2D{8, 1}, str[9]);

    getline(input, str);
    players.emplace(Index2D{2, 2}, str[3]);
    players.emplace(Index2D{4, 2}, str[5]);
    players.emplace(Index2D{6, 2}, str[7]);
    players.emplace(Index2D{8, 2}, str[9]);

    return Data{nodes, players};
  }

  OUTPUT1(input)
  {

    std::multimap<int, State> states;
    std::set<State> visitedStates;
    states.emplace(0, input.players);
    int i = 0;
    while(!states.empty())
    {
      i++;
      auto it = states.begin();
      int stateCost = it->first;
      const State state = it->second;
      states.erase(it);
      // Print(state);
      if(stateCost == 440)
      {
        // std::cout << stateCost << std::endl;
        // Print(state);

      }
      if(ValidateState(state))
      {
        return stateCost;
      }
      for(auto& newState : ValidStates(state))
      {
        states.emplace(stateCost + newState.first, newState.second);
        // Print(newState.second);
      }
    }

    return 0;
    // std::set<State> visitedStates;
    // std::multimap<int, std::pair<int, State>> states;
    // states.emplace(Heuristic(input.players), std::pair<int, State>{0, input.players});
    // int i = 0;
    // while(!states.empty())
    // {
    //   i++;
    //   auto it = states.begin();
    //   int stateH = it->first;
    //   int stateCost = it->second.first;
    //   const State state = it->second.second;
    //   states.erase(it);
    //   if(i % 10000 == 0)
    //   {
    //     std::cout << visitedStates.size() << std::endl;
    //     std::cout << stateCost << std::endl;
    //   }

    //   if(ValidateState(state))
    //   {
    //     return stateCost;
    //   }

    //   for(auto[pos, val] : state)
    //   {
    //     for(auto& [pathPos, cost] : input.paths.find(pos)->second.paths)
    //     {
    //       if(state.count(pathPos) == 0)
    //       {
    //         State newState = state;
    //         int totalCost = stateCost + cost * GetCost(val);
    //         if(totalCost <= stateCost)
    //         {
    //           std::cout << "cost did not increase" << std::endl;
    //           continue;
    //         }
    //         newState[pathPos] = val;
    //         newState.erase(pos);
    //         if(visitedStates.find(newState) == visitedStates.end())
    //         {
    //           states.emplace(totalCost + Heuristic(newState), std::pair<int, State>{totalCost, newState});
    //           visitedStates.emplace(newState);
    //           // Print(newState);
    //         }
    //       }
    //     }
    //   }
    // }
    return 0;
  }

  OUTPUT2(input)
  {
    return 0;
  }
}
