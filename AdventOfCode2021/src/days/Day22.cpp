#include "aoc.h"

namespace day22
{

  struct Overlap;

  struct Volume
  {
    int sign = 0;
    Index3D min = Index3D{0, 0};
    Index3D max = Index3D{0, 0};

    Volume() {}

    Volume(int sign, const Index3D & min, const Index3D & max)
      : sign{sign}, min{min}, max{max}
    {}

    int64_t GetCubes() const
    {
      return ((int64_t)max.x - (int64_t)min.x + 1ll) * ((int64_t)max.y - (int64_t)min.y + 1ll) * ((int64_t)max.z - (int64_t)min.z + 1ll);
    }

    Overlap GetOverlap(const Volume& other) const;

    friend std::ostream& operator<<(std::ostream& stream, const Volume& volume)
    {
      return stream << volume.min << " " << volume.max;
    }
  };

  struct Overlap
  {
    bool overlap = false;
    Volume volume;

    Overlap(bool overlap, const Volume& volume)
      : overlap{overlap}, volume{volume}
    {}

    operator bool()
    {
      return overlap;
    }
  };

  Overlap Volume::GetOverlap(const Volume& other) const
  {
    if(min.x > other.max.x || min.y > other.max.y || min.z > other.max.z || max.x < other.min.x || max.y < other.min.y || max.z < other.min.z)
      return Overlap{false, Volume{0, Index3D{}, Index3D{}}};

    return Overlap{true, Volume{-other.sign,
                                Index3D{std::max(min.x, other.min.x), std::max(min.y, other.min.y), std::max(min.z, other.min.z)},
                                Index3D{std::min(max.x, other.max.x), std::min(max.y, other.max.y), std::min(max.z, other.max.z)}}};
  }

  REGISTER_DAY(day22, std::vector<Volume>, int64_t);

  REGISTER_TEST_EXAMPLE(day22, ExampleInput, 1, 474140);
  REGISTER_TEST        (day22, Input,        1, 596598);
  REGISTER_TEST_EXAMPLE(day22, ExampleInput, 2, 2758514936282235);
  REGISTER_TEST        (day22, Input,        2, 1199121349148621);

  READ_INPUT(input)
  {
    std::vector<Volume> volumes;
    std::string str;
    while(getline(input, str))
    {
      Volume volume;
      std::stringstream ss{str};
      std::string s;
      ss >> s >> "x=" >> volume.min.x >> ".." >> volume.max.x >> "," >> "y=" >> volume.min.y >> ".." >> volume.max.y >> "," >> "z=" >> volume.min.z >> ".." >> volume.max.z;
      volume.sign = s == "on" ? 1 : -1;
      volumes.emplace_back(volume);
    }
    return volumes;
  }

  OUTPUT1(input)
  {
    Array3D<char> values{101, 101, 101};
    values.Fill('.');
    for(auto& region : input)
    {
      for(int z = std::max(region.min.z, -50); z <= std::min(region.max.z, 50); z++)
      {
        for(int y = std::max(region.min.y, -50); y <= std::min(region.max.y, 50); y++)
        {
          for(int x = std::max(region.min.x, -50); x <= std::min(region.max.x, 50); x++)
          {
            if(values.IsInside(Index3D{x + 50, y + 50, z + 50}))
            {
              values.Set(x + 50, y + 50, z + 50, region.sign > 0 ? '#' : '.');
            }
          }
        }
      }
    }
    return values.Count('#');
  }

  OUTPUT2(input)
  {
    std::vector<Volume> volumes;
    for(auto& volume : input)
    {
      size_t size = volumes.size();
      for(size_t i = 0; i < size; i++)
      {
        Overlap overlap = volume.GetOverlap(volumes[i]);
        if(overlap)
        {
          volumes.emplace_back(overlap.volume);
        }
      }
      if(volume.sign > 0)
      {
        volumes.emplace_back(volume);
      }
    }
    return Helper::Sum<int64_t>(volumes, [](int64_t sum, const Volume& vol) { return sum + vol.GetCubes() * vol.sign; });
  }
}
