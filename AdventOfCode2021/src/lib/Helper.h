#pragma once

#include <algorithm>
#include <functional>
#include <map>
#include <numeric>
#include <set>
#include <vector>

#define BIT(x) (1 << (x))

struct Helper
{
  template <typename T, typename S>
  static void RemoveIf(T& t, S func)
  {
    t.erase(std::remove_if(t.begin(), t.end(), func), t.end());
  }

  static bool StartsWith(const std::string& str, const std::string& prefix)
  {
    if (str.size() < prefix.size())
      return false;
    return std::string_view{str.c_str(), prefix.size()} == prefix;
  }

  static bool EndsWith(const std::string& str, const std::string& prefix)
  {
    if (str.size() < prefix.size())
      return false;
    return std::string_view{str.c_str() + str.size() - prefix.size(), prefix.size()} == prefix;
  }

  static int BinStrToInt(const std::string& str)
  {
    if(str.size() >= 32)
    {
      std::cout << "BinStrToInt: Too big string, use BinStrToInt64 instead" << std::endl;
      return 0;
    }

    int val = 0;
    for(size_t i = 0; i < str.size(); i++)
    {
      if(str[i] == '1')
        val |= (1 << (str.size() - i - 1));
    }
    return val;
  }

  static int64_t BinStrToInt64(const std::string& str)
  {
    if(str.size() >= 64)
    {
      std::cout << "BinStrToInt64: Too big string" << std::endl;
      return 0;
    }

    int64_t val = 0;
    for(size_t i = 0; i < str.size(); i++)
    {
      if(str[i] == '1')
        val |= (1ll << (str.size() - i - 1));
    }
    return val;
  }

  template <typename T, typename S>
  static T Sum(const S& container)
  {
    return std::accumulate(container.begin(), container.end(), (T)0, std::plus<T>());
  }

  template <typename T, typename S, typename Container>
  static T Sum(const Container& container, S func)
  {
    return std::accumulate(container.begin(), container.end(), (T)0, func);
  }

  template <typename T, typename S>
  static T Product(const S& container)
  {
    return std::accumulate(container.begin(), container.end(), (T)1, std::multiplies<T>());
  }

  template <typename T, typename S, typename Container>
  static T Product(const Container& container, S func)
  {
    return std::accumulate(container.begin(), container.end(), (T)1, func);
  }

  template <typename Container>
  static typename Container::value_type Min(const Container& container)
  {
    if(container.size() == 0)
    {
      std::cout << "Min: Container empty" << std::endl;
      return typename Container::value_type{};
    }
    typename Container::value_type min = *container.begin();
    for(auto&& element : container)
    {
      min = std::min(min, element);
    }
    return min;
  }

  template <typename Container>
  static typename Container::value_type Max(const Container& container)
  {
    if(container.size() == 0)
    {
      std::cout << "Min: Container empty" << std::endl;
      return typename Container::value_type{};
    }
    typename Container::value_type max= *container.begin();
    for(auto&& element : container)
    {
      max = std::max(max, element);
    }
    return max;
  }

  template <typename T>
  static T Sign(const T& t)
  {
    return t > 0 ? 1 : t < 0 ? -1 : 0;
  }

  template <typename T>
  static std::set<T> GetUnion(const std::vector<std::set<T>>& list)
  {
    std::set<char> uniq;
    for (auto l : list)
    {
      for (auto t : l)
      {
        uniq.emplace(t);
      }
    }
    return uniq;
  }

  template <typename T>
  static std::set<T> GetIntersection(const std::vector<std::set<T>>& list)
  {
    std::set<char> intersection = list[0];

    for (size_t i = 1; i < list.size(); i++)
    {
      for(auto it = intersection.begin(); it != intersection.end();)
      {
        if(list[i].find(*it) == list[i].end())
          it = intersection.erase(it);
        else
          it++;
      }
    }
    return intersection;
  }

  template <typename T>
  static bool IsSubset(const std::set<T>& smallSet, const std::set<T>& bigSet)
  {
    if(bigSet.size() < smallSet.size())
      return false;

    for(auto&& t : smallSet)
    {
      if(bigSet.find(t) == bigSet.end())
        return false;
    }
    return true;
  }

  template <typename T, typename Heuristic, typename Branch, typename Goal>
  static int AStar(const T& initial, Heuristic heuristic, Branch branch, Goal goal)
  {
    std::map<T, int> visited;
    std::multimap<int, std::pair<int, T>> open;
    open.emplace(0, std::pair<int, T>{0, initial});
    int i = 0;
    while(!open.empty())
    {
      i++;
      auto it = open.begin();
      if(goal(it->second.second))
      {
        return it->second.first;
      }
      int stateCost = it->second.first;
      for(auto& newState : branch(it->second.second))
      {
        auto it = visited.find(newState.second);
        int cost = stateCost + newState.first;
        if(it == visited.end() || it->second > cost)
        {
          open.emplace(heuristic(newState.second) + cost, std::pair<int, T>{cost, newState.second});
          visited.emplace(newState.second, cost);
        }
      }
      open.erase(open.begin());
    }
    return 0;
  }

  template <typename T, typename Branch, typename Goal>
  static int Dijkstras(const T& initial, Branch branch, Goal goal)
  {
    return AStar(initial, [](const T&) { return 0; }, branch, goal);
  }
};
