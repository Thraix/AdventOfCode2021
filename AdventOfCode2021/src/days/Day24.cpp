#include "aoc.h"

namespace day24
{

  enum class Operation
  {
    Inp, Add, Mul, Div, Mod, Eql
  };

  struct Instruction
  {
    Operation operation;
    char dst;
    std::string src;
  };

  int64_t Read(const std::string& str, const std::map<char, int64_t>& data)
  {
    if(str[0] >= 'a' && str[0] <= 'z')
    {
      auto it = data.find(str[0]);
      if(it != data.end())
        return it->second;
      return 0;
    }
    return atoll(str.c_str());
  };

  int64_t Read(char c, const std::map<char, int64_t>& data)
  {
    auto it = data.find(c);
    if(it != data.end())
      return it->second;
    return 0;
  }

  bool ValidateInput(const std::vector<Instruction>& instructions, const std::string& str)
  {
    int inputOffset = 0;
    std::map<char, int64_t> data;
    for(int i = 0; i < instructions.size(); i++)
    {
      switch(instructions[i].operation)
      {
        case Operation::Inp:
          data[instructions[i].dst] = str[inputOffset++] - '0';
          break;
        case Operation::Add:
          data[instructions[i].dst] = Read(instructions[i].dst, data) + Read(instructions[i].src, data);
          break;
        case Operation::Mul:
          data[instructions[i].dst] = Read(instructions[i].dst, data) * Read(instructions[i].src, data);
          break;
        case Operation::Div:
          data[instructions[i].dst] = Read(instructions[i].dst, data) / Read(instructions[i].src, data);
          break;
        case Operation::Mod:
          data[instructions[i].dst] = Read(instructions[i].dst, data) % Read(instructions[i].src, data);
          break;
        case Operation::Eql:
          data[instructions[i].dst] = Read(instructions[i].dst, data) == Read(instructions[i].src, data) ? 1 : 0;
          break;
        default:
          std::cout << "Invalid operation" << std::endl;
      }
    }
    return data['z'] == 0;
  }

  REGISTER_DAY(day24, std::vector<Instruction>, int64_t);

  REGISTER_TEST(day24, Input, 1, 99919765949498);
  REGISTER_TEST(day24, Input, 2, 24913111616151);

  READ_INPUT(input)
  {
    std::vector<Instruction> instructions;
    std::string str;
    while(getline(input, str))
    {
      Instruction instruction;
      std::string_view sv(str.c_str(), 3);
      if(sv == "inp")
        instruction.operation = Operation::Inp;
      else if(sv == "add")
        instruction.operation = Operation::Add;
      else if(sv == "mul")
        instruction.operation = Operation::Mul;
      else if(sv == "div")
        instruction.operation = Operation::Div;
      else if(sv == "mod")
        instruction.operation = Operation::Mod;
      else if(sv == "eql")
        instruction.operation = Operation::Eql;
      else
        std::cout << "Invalid operation: " << sv << std::endl;
      instruction.dst = str[4];
      if(instruction.operation != Operation::Inp)
        instruction.src = str.substr(6);
      instructions.emplace_back(instruction);
    }
    return instructions;
  }

  OUTPUT1(input)
  {
    std::string str = "99919765949498";
    if(ValidateInput(input, str))
      return atoll(str.c_str());
    return 0;
  }

  OUTPUT2(input)
  {
    std::string str = "24913111616151";
    if(ValidateInput(input, str))
      return atoll(str.c_str());
    return 0;
  }
}
