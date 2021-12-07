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
  Timer totalTimer;
  int passed = 0;
  for (auto day : aoc::Registry::GetDays())
  {
    std::cout << TERM_GREEN << "[ RUN     ] " << TERM_CLEAR << day->GetName() << std::endl;
    Timer timer;
    bool res = day->Run();
    timer.Stop();

    if (res)
    {
      std::cout << TERM_GREEN << "[=========] " << TERM_CLEAR << std::endl;
      std::cout << TERM_GREEN << "[      OK ] " << TERM_CLEAR << day->GetName() << " Took: " << timer.Elapsed() << "s" << std::endl;
      passed++;
    }
    else
    {
      std::cout << TERM_RED << "[=========] " << TERM_CLEAR << std::endl;
      std::cout << TERM_RED << "[  FAILED ] " << TERM_CLEAR << day->GetName() << std::endl;
    }
    std::cout << std::endl;
  }
  totalTimer.Stop();

  if (passed != aoc::Registry::GetDays().size())
  {
    std::cout << std::endl << TERM_RED << "[  FAILED ] " << TERM_CLEAR << passed << "/" << aoc::Registry::GetDays().size() << " days passed in " << totalTimer.Elapsed() << "s" << std::endl;
    return 1;
  }
  else 
  {
    std::cout << std::endl << TERM_GREEN << "[  PASSED ] " << TERM_CLEAR << "All days passed in " << totalTimer.Elapsed() << "s" << std::endl;
    return 0;
  }
}
