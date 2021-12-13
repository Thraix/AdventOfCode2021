#include "aoc.h"

namespace day12
{
  struct Node
  {
    std::set<std::string> connections;
  };

  struct Path
  {
    std::vector<std::string> path{"start"};
    bool hasDuplicate = false;
  };

  using NodeMap = std::map<std::string, Node>;
  REGISTER_DAY(day12, NodeMap, int);

  REGISTER_TEST_EXAMPLE(day12, ExampleInput, 1, 10);
  REGISTER_TEST        (day12, Input,        1, 3887);
  REGISTER_TEST_EXAMPLE(day12, ExampleInput, 2, 36);
  REGISTER_TEST        (day12, Input,        2, 104834);

  READ_INPUT(input)
  {
    NodeMap nodes;
    std::string str;
    while(getline(input, str))
    {
      std::stringstream ss{str};
      std::string from, to;
      getline(ss, from, '-');
      getline(ss, to);
      auto itFrom = nodes.find(from);
      auto itTo = nodes.find(to);
      if(itFrom == nodes.end())
        itFrom = nodes.emplace(from, Node{}).first;
      if(itTo == nodes.end())
        itTo = nodes.emplace(to, Node{}).first;

      itFrom->second.connections.emplace(to);
      itTo->second.connections.emplace(from);
    }
    return nodes;
  }

  OUTPUT1(input)
  {
    int count = 0;
    std::stack<std::vector<std::string>> paths;
    paths.emplace(std::vector<std::string>{"start"});
    while(!paths.empty())
    {
      auto path = paths.top();
      paths.pop();
      if(path.back() == "end")
      {
        count++;
        continue;
      }
      auto it = input.find(path.back());
      for(auto& connection : it->second.connections)
      {
        if(connection[0] >= 'a' && connection[0] <= 'z')
        {
          if(std::find(path.begin(), path.end(), connection) == path.end())
          {
            std::vector<std::string> cpy = path;
            cpy.emplace_back(connection);
            paths.emplace(cpy);
          }
        }
        else
        {
          std::vector<std::string> cpy = path;
          cpy.emplace_back(connection);
          paths.emplace(cpy);
        }
      }
    }
    return count;
  }

  OUTPUT2(input)
  {
    int count = 0;
    std::stack<Path> paths;
    paths.emplace(Path{});
    while(!paths.empty())
    {
      auto path = paths.top();
      paths.pop();
      if(path.path.back() == "end")
      {
        count++;
        continue;
      }

      auto it = input.find(path.path.back());
      for(auto& connection : it->second.connections)
      {
        if(connection[0] >= 'a' && connection[0] <= 'z')
        {
          if(std::find(path.path.begin(), path.path.end(), connection) == path.path.end())
          {
            Path cpy = path;
            cpy.path.emplace_back(connection);
            paths.emplace(cpy);
          }
          else if(!path.hasDuplicate && connection != "start")
          {
            Path cpy = path;
            cpy.path.emplace_back(connection);
            cpy.hasDuplicate = true;
            paths.emplace(cpy);
          }
        }
        else
        {
          Path cpy = path;
          cpy.path.emplace_back(connection);
          paths.emplace(cpy);
        }
      }
    }
    return count;
  }
}
