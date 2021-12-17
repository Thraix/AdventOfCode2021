#include "aoc.h"

namespace day17
{
  struct Area
  {
    Index2D p1;
    Index2D p2;
  };

  REGISTER_DAY(day17, Area, int);

  REGISTER_TEST_EXAMPLE(day17, ExampleInput, 1, 45);
  REGISTER_TEST        (day17, Input,        1, 2701);
  REGISTER_TEST_EXAMPLE(day17, ExampleInput, 2, 112);
  REGISTER_TEST        (day17, Input,        2, 1070);

  READ_INPUT(input)
  {

    Area area;
    input >> "target area: x=" >> area.p1.x >> ".." >> area.p2.x >> ", y=" >> area.p1.y >> ".." >> area.p2.y;
    return area;
  }

  OUTPUT1(input)
  {
    int v = -input.p1.y;
    return v * (v - 1) / 2;
  }

  OUTPUT2(input)
  {
    int count = 0;
    for(int y = input.p1.y-1; y <= -input.p1.y; y++)
    {
      for(int x = 1; x <= input.p2.x; x++)
      {
        int xPos = 0;
        int yPos = 0;

        int vx = x;
        int vy = y;
        while(xPos <= input.p2.x && yPos >= input.p1.y)
        {
          if(xPos >= input.p1.x && xPos <= input.p2.x && yPos >= input.p1.y && yPos <= input.p2.y)
          {
            count++;
            break;
          }
          xPos += vx;
          yPos += vy;
          vx--;
          if(vx < 0)
            vx = 0;
          vy--;
        }
      }
    }
    return count;
  }
}
