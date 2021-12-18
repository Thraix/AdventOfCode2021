#include "aoc.h"

namespace day18
{
  struct Node
  {
    Node* parent = nullptr;
    int value = 0;
    std::vector<Node> nodes;

    Node() = default;

    Node(const std::string& str)
      : nodes{Node{}, Node{}}
    {
      UpdateParents();
      std::stringstream ss{str};
      ss >> *this;
    }

    Node(int value)
      : value{value}
    {}

    Node(const Node& left, const Node& right)
      : nodes{left, right}
    {
      UpdateParents();
    }

    Node& Left()
    {
      return nodes[0];
    }

    const Node& Left() const
    {
      return nodes[0];
    }

    Node& Right()
    {
      return nodes[1];
    }

    const Node& Right() const
    {
      return nodes[1];
    }

    bool IsNumber() const
    {
      return nodes.size() == 0;
    }

    int& Number()
    {
      return value;
    }

    int Number() const
    {
      return value;
    }

    int Calculate()
    {
      int i = 0;
      if(Left().IsNumber())
        i += 3 * Left().Number();
      else
        i += 3 * Left().Calculate();

      if(Right().IsNumber())
        i += 2 * Right().Number();
      else
        i += 2 * Right().Calculate();
      return i;
    }

    void AddToLeft(int value, Node* from)
    {
      if(Left().IsNumber())
        Left().Number() += value;
      else
      {
        Node& node = Left();
        if(&node == from)
        {
          if(parent != nullptr)
            parent->AddToLeft(value, this);
        }
        else
          node.AddToRightDown(value);
      }
    }

    void AddToRightDown(int value)
    {
      if(Right().IsNumber())
        Right().Number() += value;
      else
      {
        Right().AddToRightDown(value);
      }
    }

    void AddToRight(int value, Node* from)
    {
      if(Right().IsNumber())
        Right().Number() += value;
      else
      {
        Node& node = Right();
        if(&node == from)
        {
          if(parent != nullptr)
            parent->AddToRight(value, this);
        }
        else
          node.AddToLeftDown(value);
      }

    }

    void AddToLeftDown(int value)
    {
      if(Left().IsNumber())
        Left().Number() += value;
      else
      {
        Left().AddToLeftDown(value);
      }
    }

    bool Explode(int depth = 0)
    {
      if(depth >= 4)
      {
        parent->AddToLeft(Left().Number(), this);
        parent->AddToRight(Right().Number(), this);

        if(!parent->Left().IsNumber() && &parent->Left() == this)
          parent->Left() = 0;
        if(!parent->Right().IsNumber() && &parent->Right() == this)
          parent->Right() = 0;
        return true;
      }
      if(!Left().IsNumber())
        if(Left().Explode(depth + 1))
          return true;
      if(!Right().IsNumber())
        if(Right().Explode(depth + 1))
          return true;
      return false;
    }

    bool Split()
    {
      if(!Left().IsNumber())
      {
        if(Left().Split())
          return true;
      }
      else if(Left().Number() >= 10)
      {
        int val = Left().Number();
        Node node{(val >> 1), (val >> 1) + (val % 2)};
        node.parent = this;
        Left() = node;
        return true;
      }

      if(!Right().IsNumber())
      {
        if(Right().Split())
          return true;
      }
      else if(Right().Number() >= 10)
      {
        int val = Right().Number();
        Node node{(val >> 1), (val >> 1) + (val % 2)};
        node.parent = this;
        Right() = node;
        return true;
      }
      return false;
    }

    void UpdateParents()
    {
      if(!Left().IsNumber())
      {
        Left().parent = this;
        Left().UpdateParents();
      }
      if(!Right().IsNumber())
      {
        Right().parent = this;
        Right().UpdateParents();
      }
    }

    void Print(std::ostream& stream, int depth) const
    {
      std::vector<char> depthStart{'|', '<', '{', '(', '['};
      std::vector<char> depthEnd{'|', '>', '}', ')', ']'};
      stream << depthStart[depth];
      if(Left().IsNumber())
        stream << Left().Number();
      else
        Left().Print(stream, depth + 1);
      stream << ",";
      if(Right().IsNumber())
        stream << Right().Number();
      else
        Right().Print(stream, depth + 1);
      stream << depthEnd[depth];
    }

    void operator=(int value)
    {
      nodes.clear();
      this->value = value;
    }

    friend std::ostream& operator<<(std::ostream& stream, const Node& node)
    {
      node.Print(stream, 0);
      return stream;
    }

    friend std::istream& operator>>(std::istream& stream, Node& node)
    {
      stream >> "[";
      if(stream.peek() == '[')
      {
        Node left{Node{}, Node{}};
        stream >> left;
        left.parent = &node;
        node.Left() = left;
      }
      else
      {
        int i;
        stream >> i;
        node.Left() = i;
      }
      stream >> ",";
      if(stream.peek() == '[')
      {
        Node right{Node{}, Node{}};
        stream >> right;
        right.parent = &node;
        node.Right() = right;
      }
      else
      {
        int i;
        stream >> i;
        node.Right() = i;
      }
      stream >> "]";
      return stream;
    }
  };

  Node Reduce(const Node& lhs, const Node& rhs)
  {
    Node node{lhs, rhs};
    bool changed = true;
    while(changed)
    {
      changed = false;
      while(node.Explode())
        changed = true;
      if(node.Split())
        changed = true;
    }
    return node;
  }

  REGISTER_DAY(day18, std::vector<Node>, int);

  REGISTER_TEST_EXAMPLE(day18, ExampleInput, 1, 4140);
  REGISTER_TEST        (day18, Input,        1, 4137);
  REGISTER_TEST_EXAMPLE(day18, ExampleInput, 2, 3993);
  REGISTER_TEST        (day18, Input,        2, 4573);

  READ_INPUT(input)
  {
    std::vector<Node> nodes;
    std::string str;
    while(getline(input, str))
    {
      nodes.emplace_back(str);
    }
    return nodes;
  }

  OUTPUT1(input)
  {
    Node node = input[0];
    for(size_t i = 1; i < input.size(); i++)
    {
      node = Reduce(node, input[i]);
    }
    return node.Calculate();
  }

  OUTPUT2(input)
  {
    int max = 0;
    for(size_t i = 0; i < input.size() - 1; i++)
    {
      for(size_t j = 1; j < input.size(); j++)
      {
        max = std::max(max, Reduce(input[j], input[i]).Calculate());
        max = std::max(max, Reduce(input[i], input[j]).Calculate());
      }
    }
    return max;
  }
}
