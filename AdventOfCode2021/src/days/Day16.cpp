#include "aoc.h"

namespace day16
{
  int64_t Read(const std::string& str, int& offset, int size)
  {
    int64_t i = Helper::BinStrToInt64(str.substr(offset, size));
    offset += size;
    return i;
  }

  std::pair<int64_t, int64_t> ReadPacket(const std::string& str, int& offset)
  {
    int64_t version = Read(str, offset, 3);
    int64_t type = Read(str, offset, 3);

    if(type == 4)
    {
      // Normal packet
      int64_t type = Read(str, offset, 1);
      int64_t val = 0;
      while(type == 1)
      {
        val = (val << 4) | Read(str, offset, 4);
        type = Read(str, offset, 1);
      }
      val = (val << 4) | Read(str, offset, 4);
      return {version, val};
    }
    else
    {
      // Packet containing packets
      int64_t lengthId = Read(str, offset, 1);
      std::vector<int64_t> values;
      int64_t versionTotal = version;
      if(lengthId == 0)
      {
        int64_t totalLength = Read(str, offset, 15);
        int64_t start = offset;
        while(offset < start + totalLength)
        {
          auto[version, value] = ReadPacket(str, offset);
          values.emplace_back(value);
          versionTotal += version;
        }
      }
      else
      {
        int64_t totalPackets = Read(str, offset, 11);
        for(int64_t i = 0; i < totalPackets; i++)
        {
          auto[version, value] = ReadPacket(str, offset);
          values.emplace_back(value);
          versionTotal += version;
        }
      }

      if(type == 0)
        return {versionTotal, std::accumulate(values.begin(), values.end(), 0ll, [](int64_t sum, int64_t val) { return sum + val; })};
      else if(type == 1)
        return {versionTotal, std::accumulate(values.begin(), values.end(), 1ll, [](int64_t prod, int64_t val) { return prod * val; })};
      else if(type == 2)
        return {versionTotal, std::accumulate(values.begin(), values.end(), values.front(), [](int64_t max, int64_t val) { return std::min(max, val); })};
      else if(type == 3)
        return {versionTotal, std::accumulate(values.begin(), values.end(), values.front(), [](int64_t min, int64_t val) { return std::max(min, val); })};
      else if(type == 5)
        return {versionTotal, values[0] > values[1] ? 1 : 0};
      else if(type == 6)
        return {versionTotal, values[0] < values[1] ? 1 : 0};
      else if(type == 7)
        return {versionTotal, values[0] == values[1] ? 1 : 0};
    }
    return {0, 0};
  }

  std::pair<int64_t, int64_t> ReadPacket(const std::string& str)
  {
    int offset = 0;
    return ReadPacket(str, offset);
  }

  REGISTER_DAY(day16, std::string, int64_t);

  REGISTER_TEST_EXAMPLE(day16, ExampleInput, 1, 20);
  REGISTER_TEST        (day16, Input,        1, 984);
  REGISTER_TEST_EXAMPLE(day16, ExampleInput, 2, 1);
  REGISTER_TEST        (day16, Input,        2, 1015320896946);

  READ_INPUT(input)
  {
    std::string str;
    getline(input, str);
    std::string bin;
    for(char c : str)
    {
      if(c >= '0' && c <= '9')
      {
        char val = c - '0'; // vs compiler throws warnings if this is inlined into the bitset function...
        bin += std::bitset<4>(val).to_string();
      }
      else if(c >= 'A' && c <= 'F')
      {
        char val = c - 'A' + 10; // vs compiler throws warnings if this is inlined into the bitset function...
        bin += std::bitset<4>(val).to_string();
      }
    }
    return bin;
  }

  OUTPUT1(input)
  {
    return ReadPacket(input).first;
  }

  OUTPUT2(input)
  {
    return ReadPacket(input).second;
  }
}
