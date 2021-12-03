#pragma once

#include <algorithm>
#include <functional>
#include <numeric>
#include <set>
#include <vector>

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
        val |= (1 << str.size() - i - 1);
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
        val |= (1 << str.size() - i - 1);
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
      std::set<char> localIntersection;
      std::set_intersection(intersection.cbegin(), intersection.cend(), list[i].cbegin(), list[i].cend(), std::inserter(localIntersection, localIntersection.begin()));
      intersection = localIntersection;
    }
    return intersection;
  }
};
