#pragma once

#include "aoc.h"
#include <chrono>
#include <vector>
#include <iostream>

aoc::Registry* aoc::Registry::GetInstance()
{
  static aoc::Registry* instance = new aoc::Registry();
  return instance;
}

int main()
{
  auto totalStart = std::chrono::steady_clock::now();
  int passed = 0;
  for (auto day : aoc::Registry::GetDays())
  {
    std::cout << TERM_GREEN << "[ RUN     ] " << TERM_CLEAR << day->GetName() << std::endl;
    auto start = std::chrono::steady_clock::now();
    bool res = day->Run();
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    if (res)
    {
      std::cout << TERM_GREEN << "[=========] " << TERM_CLEAR << std::endl;
      std::cout << TERM_GREEN << "[      OK ] " << TERM_CLEAR << day->GetName() << " Took: " << elapsed.count() << "s" << std::endl;
      passed++;
    }
    else
    {
      std::cout << TERM_RED << "[=========] " << TERM_CLEAR << std::endl;
      std::cout << TERM_RED << "[  FAILED ] " << TERM_CLEAR << day->GetName() << std::endl;
    }
    std::cout << std::endl;
  }
  auto totalEnd = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsed = totalEnd - totalStart;

  if (passed != aoc::Registry::GetDays().size())
  {
    std::cout << std::endl << TERM_RED << "[  FAILED ] " << TERM_CLEAR << passed << "/" << aoc::Registry::GetDays().size() << " days passed in " << elapsed.count() << "s" << std::endl;
    return 1;
  }
  else 
  {
    std::cout << std::endl << TERM_GREEN << "[  PASSED ] " << TERM_CLEAR << "All days passed in " << elapsed.count() << "s" << std::endl;
    return 0;
  }
}
