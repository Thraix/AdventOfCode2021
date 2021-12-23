#pragma once

#include <iostream>
#include <vector>

struct Index2D
{
  int x = -1;
  int y = -1;

  bool IsValid()
  {
    return x != -1 && y != -1;
  }

  operator bool()
  {
    return IsValid();
  }

  Index2D operator+(const Index2D& other) const
  {
    return Index2D{x + other.x, y + other.y};
  }

  Index2D operator-(const Index2D& other) const
  {
    return Index2D{x - other.x, y - other.y};
  }

  friend std::ostream& operator<<(std::ostream& stream, const Index2D& index)
  {
    return stream << "(" << index.x << " " << index.y << ")";
  }

  friend bool operator<(const Index2D& lhs, const Index2D& rhs)
  {
    if(lhs.x != rhs.x)
      return lhs.x < rhs.x;
    return lhs.y < rhs.y;
  }

  friend bool operator==(const Index2D& lhs, const Index2D& rhs)
  {
    return lhs.x == rhs.x && lhs.y == rhs.y;
  }

  friend bool operator!=(const Index2D& lhs, const Index2D& rhs)
  {
    return !operator==(lhs, rhs);
  }
};

template <typename T>
struct Array2D
{
  int width;
  int height;
  std::vector<T> array2D;

  Array2D()
    : width{0}, height{0}
  {}

  Array2D(int width, int height)
    : width{width}, height{height}
  {
    array2D.resize(width * height);
  }

  Array2D(int width, int height, const std::vector<T>& data)
    : width{width}, height{height}, array2D{data}
  {}

  void Fill(const T& value)
  {
    for (int i = 0; i < width * height; i++)
    {
      array2D[i] = value;
    }
  }

  int GetIndex(int x, int y) const
  {
    return x + y * width;
  }

  T& Get(int x, int y) 
  {
    return array2D[x + y * width];
  }

  const T& Get(int x, int y) const
  {
    return array2D[x + y * width];
  }

  T& operator[](const Index2D& index)
  {
    return Get(index.x, index.y);
  }

  const T& operator[](const Index2D& index) const
  {
    return Get(index.x, index.y);
  }

  T& GetMirror(int x, int y) 
  {
    // if width = 3, it will repeat x like this: 012210012210, same with height
    x = (x / width ) % 2 == 0 ? x % width  : width  - (x % width ) - 1;
    y = (y / height) % 2 == 0 ? y % height : height - (y % height) - 1;
    return array2D[x + y * width];
  }

  const T& GetMirror(int x, int y) const
  {
    // if width = 3, it will repeat x like this: 012210012210, same with height
    x = (x / width ) % 2 == 0 ? x % width  : width  - (x % width ) - 1;
    y = (y / height) % 2 == 0 ? y % height : height - (y % height) - 1;
    return array2D[x + y * width];
  }

  T& GetMod(int x, int y) 
  {
    return array2D[((x % width + width) % width) + ((y % height + height) % height) * width];
  }

  const T& GetMod(int x, int y) const
  {
    return array2D[((x % width + width) % width) + ((y % height + height) % height) * width];
  }

  void Set(int x, int y, const T& val)
  {
    Get(x, y) = val;
  }

  void SetMod(int x, int y, const T& val)
  {
    GetMod(x, y) = val;
  }

  void SetMirror(int x, int y, const T& val)
  {
    GetMirror(x, y) = val;
  }

  int GetNeighbors(const T& val, int x, int y, int size = 1) const
  {
    int neighbors = 0;
    for (int yi = y - size; yi <= y + size; yi++)
    {
      for (int xi = x - size; xi <= x + size; xi++)
      {
        if (xi < 0 || yi < 0 || xi >= width || yi >= height)
          continue;
        if (xi == x && yi == y)
          continue;
        if (Get(xi, yi) == val)
          neighbors++;
      }
    }
    return neighbors;
  }

  bool IsInside(const Index2D& index) const
  {
    return index.x >= 0 && index.y >= 0 && index.x < width && index.y < height;
  }

  int Count(const T& val)
  {
    int count = 0;
    for (int y = 0; y < height; y++)
    {
      for (int x = 0; x < width; x++)
      {
        if (Get(x, y) == val)
          count++;
      }
    }
    return count;
  }

  void RotateCW()
  {
    Array2D cpy = *this;
    for(int y = 0; y < height; y++)
    {
      for(int x = 0; x < width; x++)
      {
        array2D[height - y - 1 + x * height] = cpy.Get(x, y);
      }
    }
    std::swap(width, height);
  }

  void RotateCCW()
  {
    Array2D cpy = *this;
    for(int y = 0; y < height; y++)
    {
      for(int x = 0; x < width; x++)
      {
        array2D[y + (width - x - 1) * height] = cpy.Get(x, y);
      }
    }
    std::swap(width, height);
  }

  void Rotate180()
  {
    Array2D cpy = *this;
    for(int y = 0; y < height; y++)
    {
      for(int x = 0; x < width; x++)
      {
        array2D[width - x - 1 + (height - y - 1) * width] = cpy.Get(x, y);
      }
    }
  }

  void FlipVertical()
  {
    for(int y = 0; y < height / 2; y++)
    {
      for(int x = 0; x < width; x++)
      {
        std::swap(array2D[GetIndex(x, y)], array2D[GetIndex(x, height-y-1)]);
      }
    }
  }

  void FlipHorizontal()
  {
    for(int y = 0; y < height; y++)
    {
      for(int x = 0; x < width / 2; x++)
      {
        std::swap(array2D[GetIndex(x, y)], array2D[GetIndex(width - x - 1, y)]);
      }
    }
  }

  template <typename Function>
  void Each(Function func) const
  {
    for (int y = 0; y < height; y++)
    {
      for (int x = 0; x < width; x++)
      {
        func(*this, Index2D{x, y});
      }
    }
  }

  Index2D Find(const T& value)
  {
    for(int y = 0; y < height; y++)
    {
      for(int x = 0; x < width; x++)
      {
        if(Get(x, y) == value)
          return Index2D{x, y};
      }
    }
    return Index2D{};
  }

  void Increment(Index2D& index) const
  {
    index.x++;
    if(index.x != width)
      return;
    index.x = 0;
    index.y++;
  }

  typename std::vector<T>::iterator begin()
  {
    return array2D.begin();
  }

  typename std::vector<T>::iterator end()
  {
    return array2D.end();
  }

  typename std::vector<T>::const_iterator begin() const
  {
    return array2D.cbegin();
  }

  typename std::vector<T>::const_iterator end() const
  {
    return array2D.cend();
  }

  friend std::ostream& operator<<(std::ostream& os, const Array2D& array2D)
  {
    for (int y = 0; y < array2D.height; y++) 
    {
      for (int x = 0; x < array2D.width; x++) 
      {
        std::cout << array2D.Get(x, y);
      }
      std::cout << std::endl;
    }
    return std::cout;
  }
};
