#include "aoc.h"

namespace day14
{
  struct Data
  {
    std::string str;
    std::map<std::string, char> pairs;
  };


  REGISTER_DAY(day14, Data, int64_t);

  REGISTER_TEST_EXAMPLE(day14, ExampleInput, 1, 1588);
  REGISTER_TEST        (day14, Input,        1, 4517);
  REGISTER_TEST_EXAMPLE(day14, ExampleInput, 2, 2188189693529);
  REGISTER_TEST        (day14, Input,        2, 4704817645083);

  READ_INPUT(input)
  {
    Data data;
    getline(input, data.str);
    std::string str;
    getline(input, str);

    while(getline(input, str))
    {
      data.pairs.emplace(str.substr(0, 2), str[6]);
    }
    return data;
  }

  OUTPUT1(input)
  {
    std::string str = input.str;
    for(int i = 0; i < 10; i++)
    {
      std::string newString;
      for(int j = 0; j < str.size() - 1; j++)
      {
        auto it = input.pairs.find(str.substr(j, 2));
        newString.push_back(str[j]);
        newString.push_back(it->second);
      }
      newString.push_back(str.back());
      str = newString;
    }
    std::map<char, int64_t> occurences;
    for(char c : str)
    {
      occurences[c]++;
    }
    int64_t min = occurences.begin()->second;
    char minChar = occurences.begin()->first;
    int64_t max = occurences.begin()->second;
    char maxChar = occurences.begin()->first;
    for(auto& occurence : occurences)
    {
      if(occurence.second < min)
      {
        min = occurence.second;
        minChar = occurence.first;
      }
      if(occurence.second > max)
      {
        max = occurence.second;
        maxChar = occurence.first;
      }
    }
    return occurences[maxChar] - occurences[minChar];
  }

  OUTPUT2(input)
  {
    std::string str = input.str;
    std::map<std::string, int64_t> pairCounts;
    for(int j = 0; j < str.size() - 1; j++)
    {
      pairCounts[input.str.substr(j, 2)]++;
    }
    for(int i = 0; i < 40; i++)
    {
      std::map<std::string, int64_t> cpy = pairCounts;
      for(auto& pairCount : cpy)
      {
        if(pairCount.second <= 0)
          continue;
        auto it = input.pairs.find(pairCount.first);
        std::string firstPair = pairCount.first.substr(0, 1) + it->second;
        std::string secondPair = it->second + pairCount.first.substr(1, 1);
        pairCounts[firstPair] += pairCount.second;
        pairCounts[secondPair] += pairCount.second;
        pairCounts[pairCount.first] -= pairCount.second;
      }
    }
    std::map<char, int64_t> occurences;
    for(auto& pairCount : pairCounts)
    {
      if(pairCount.second != 0)
        occurences[pairCount.first[0]] += pairCount.second;
    }
    occurences[str.back()]++;
    int64_t min = occurences.begin()->second;
    char minChar = occurences.begin()->first;
    int64_t max = occurences.begin()->second;
    char maxChar = occurences.begin()->first;
    for(auto& occurence : occurences)
    {
      if(occurence.second < min)
      {
        min = occurence.second;
        minChar = occurence.first;
      }
      if(occurence.second > max)
      {
        max = occurence.second;
        maxChar = occurence.first;
      }
    }
    return occurences[maxChar] - occurences[minChar];
  }
}
