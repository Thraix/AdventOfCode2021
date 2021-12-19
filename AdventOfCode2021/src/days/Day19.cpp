#include "aoc.h"

namespace day19
{
  constexpr int MAX_ORIENTATIONS = 24;
  constexpr int MIN_OVERLAP = 12;

  struct Scanner
  {
    std::set<Index3D> beacons;
  };
  struct Overlap
  {
    bool overlapping = false;
    int orientation = 0;
    Index3D offset{0, 0};

    friend std::ostream& operator<<(std::ostream& stream, const Overlap& overlap)
    {
      if(overlap.overlapping)
        return stream << "true " << overlap.orientation << " " << overlap.offset;
      else return stream << "false";
    }

    operator bool()
    {
      return overlapping;
    }
  };

  Index3D RotateY (const Index3D& index) { return Index3D{-index.z, index.y,  index.x}; }
  Index3D RotateY2(const Index3D& index) { return Index3D{-index.x, index.y, -index.z}; }
  Index3D RotateY3(const Index3D& index) { return Index3D{ index.z, index.y, -index.x}; }

  Index3D RotateX (const Index3D& index) { return Index3D{index.x, -index.z,  index.y}; }
  Index3D RotateX2(const Index3D& index) { return Index3D{index.x, -index.y, -index.z}; }
  Index3D RotateX3(const Index3D& index) { return Index3D{index.x,  index.z, -index.y}; }

  Index3D RotateZ (const Index3D& index) { return Index3D{-index.y,  index.x, index.z}; }
  Index3D RotateZ2(const Index3D& index) { return Index3D{-index.x, -index.y, index.z}; }
  Index3D RotateZ3(const Index3D& index) { return Index3D{ index.y, -index.x, index.z}; }

  Index3D Orient(const Index3D& index, int i)
  {
    switch(i)
    {
      // Facing forward
      case 0: return index;
      case 1: return RotateZ(index);
      case 2: return RotateZ2(index);
      case 3: return RotateZ3(index);

      // Facing left
      case 4: return RotateY(index);
      case 5: return RotateX(RotateY(index));
      case 6: return RotateX2(RotateY(index));
      case 7: return RotateX3(RotateY(index));

      // Facing backward
      case 8: return RotateY2(index);
      case 9: return RotateZ(RotateY2(index));
      case 10: return RotateZ2(RotateY2(index));
      case 11: return RotateZ3(RotateY2(index));

      // Facing right
      case 12: return RotateY3(index);
      case 13: return RotateX(RotateY3(index));
      case 14: return RotateX2(RotateY3(index));
      case 15: return RotateX3(RotateY3(index));

      // Facing down
      case 16: return RotateX(index);
      case 17: return RotateY(RotateX(index));
      case 18: return RotateY2(RotateX(index));
      case 19: return RotateY3(RotateX(index));

      // Facing up
      case 20: return RotateX3(index);
      case 21: return RotateY(RotateX3(index));
      case 22: return RotateY2(RotateX3(index));
      case 23: return RotateY3(RotateX3(index));
    }
    std::cout << "Invalid orientation: " << i << std::endl;
    return index;
  }

  Overlap IsOverlapping(const std::set<Index3D>& layout, const Scanner& scanner)
  {
    for(auto& index : layout)
    {
      int beaconsLeft = scanner.beacons.size();
      for(auto it = scanner.beacons.begin(); it != scanner.beacons.end(); it++)
      {
        if(beaconsLeft < MIN_OVERLAP)
          break;
        beaconsLeft--;

        for(int i = 0; i < MAX_ORIENTATIONS; i++)
        {
          Index3D offset = index - Orient(*it, i);
          int count = 0;
          for(auto it2 = scanner.beacons.begin(); it2 != scanner.beacons.end(); it2++)
          {
            if(layout.count(offset + Orient(*it2, i)))
            {
              count++;
            }
          }
          if(count >= MIN_OVERLAP)
            return {true, i, offset};
        }
      }
    }
    return {false, 0, Index3D{0, 0}};
  }

  std::pair<int, int> Solve(std::vector<Scanner> scanners)
  {
    // Find first overlap to initialize the "correct" layout
    std::set<Index3D> layout;
    for(auto it = scanners.begin(); it != scanners.end(); it++)
    {
      bool found = false;
      for(auto it2 = it; it2 != scanners.end(); it2++)
      {
        if(it == it2)
          continue;
        Overlap overlap = IsOverlapping(it->beacons, *it2);
        if(overlap)
        {
          layout = it->beacons;
          scanners.erase(it);
          found = true;
          break;
        }
      }
      if(found)
        break;
    }

    // Find overlapping scanners one by one
    std::vector<Index3D> scannerPos{Index3D{0, 0, 0}};
    while(!scanners.empty())
    {
      bool removed = false;
      for(auto it = scanners.begin(); it != scanners.end(); it++)
      {
        Overlap overlap = IsOverlapping(layout, *it);
        if(overlap)
        {
          for(auto& beacon : it->beacons)
          {
            layout.emplace(overlap.offset + Orient(beacon, overlap.orientation));
          }
          scannerPos.emplace_back(overlap.offset);
          scanners.erase(it);
          removed = true;
          break;
        }
      }
      if(!removed)
      {
        std::cout << "Could not find position of any remaining scanners" << std::endl;
        break;
      }
    }

    // Find largest manhattan distance between two scanners
    int maxDistance = 0;
    for(int i = 0; i < scannerPos.size(); i++)
    {
      for(int j = i + 1; j < scannerPos.size(); j++)
      {
        Index3D distance = scannerPos[i] - scannerPos[j];
        maxDistance = std::max(maxDistance, std::abs(distance.x) + std::abs(distance.y) + std::abs(distance.z));
      }
    }
    return {layout.size(), maxDistance};
  }

  REGISTER_DAY(day19, std::vector<Scanner>, int);

  REGISTER_TEST_EXAMPLE(day19, ExampleInput, 1, 79);
  REGISTER_TEST        (day19, Input,        1, 359);
  REGISTER_TEST_EXAMPLE(day19, ExampleInput, 2, 3621);
  REGISTER_TEST        (day19, Input,        2, 12292);

  READ_INPUT(input)
  {
    std::vector<Scanner> scanners;
    std::string str;
    while(getline(input, str))
    {
      Scanner scanner;
      getline(input, str);
      while(!str.empty())
      {
        std::stringstream ss{str};
        Index3D index;
        ss >> index.x >> "," >> index.y >> "," >> index.z;
        scanner.beacons.emplace(index);
        str.clear();
        getline(input, str);
      }
      scanners.emplace_back(scanner);
    }
    return scanners;
  }

  OUTPUT1(input)
  {
    return Solve(input).first;
  }

  OUTPUT2(input)
  {
    return Solve(input).second;
  }
}
