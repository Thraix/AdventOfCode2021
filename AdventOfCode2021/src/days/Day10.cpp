#include "aoc.h"

namespace day10
{
  REGISTER_DAY(day10, std::vector<std::string>, int64_t);

  REGISTER_TEST_EXAMPLE(day10, ExampleInput, 1, 26397);
  REGISTER_TEST        (day10, Input,        1, 240123);
  REGISTER_TEST_EXAMPLE(day10, ExampleInput, 2, 288957);
  REGISTER_TEST        (day10, Input,        2, 3260812321);

  READ_INPUT(input)
  {
    return Input::ReadLines(input);
  }

  OUTPUT1(input)
  {
    std::map<char, int64_t> values{{')', 3}, {']', 57}, {'}', 1197}, {'>', 25137}};
    Mapper<char, char> mapper{{'(', ')'}, {'[', ']'}, {'{', '}'}, {'<', '>'}};
    int64_t count = 0;
    for(auto&& str : input)
    {
      std::stack<char> stack;
      stack.emplace(str[0]);
      for(size_t i = 1; i < str.size(); i++)
      {
        char* ptr = mapper.GetFirst(str[i]);
        if(ptr)
        {
          if(stack.top() != *ptr)
          {
            count += values[str[i]];
            break;
          }
          stack.pop();
        }
        else
        {
          stack.emplace(str[i]);
        }
      }
    }
    return count;
  }

  OUTPUT2(input)
  {
    Mapper<char, char> mapper{{'(', ')'}, {'[', ']'}, {'{', '}'}, {'<', '>'}};
    std::map<char, int64_t> values{{'(', 1}, {'[', 2}, {'{', 3}, {'<', 4}};
    int64_t count = 0;
    std::vector<int64_t> scores;
    for(auto&& str : input)
    {
      std::stack<char> stack;
      stack.emplace(str[0]);
      bool valid = true;
      for(size_t i = 1; i < str.size(); i++)
      {
        char* ptr = mapper.GetFirst(str[i]);
        if(ptr)
        {
          if(stack.top() != *ptr)
          {
            valid = false;
            break;
          }
          stack.pop();
        }
        else
        {
          stack.emplace(str[i]);
        }
      }
      if(valid)
      {
        int64_t score = 0;
        while(!stack.empty())
        {
          score *= 5;
          score += values[stack.top()];
          stack.pop();
        }
        scores.emplace_back(score);
      }
    }
    std::sort(scores.begin(), scores.end());
    return scores[scores.size() / 2];
  }
}
