#pragma once

#include <iostream>
#include <vector>

struct Index3D
{
  int x = -1;
  int y = -1;
  int z = -1;

  bool IsValid()
  {
    return x != -1 && y != -1 && z != -1;
  }

  operator bool()
  {
    return IsValid();
  }

  Index3D operator+(const Index3D& other) const
  {
    return Index3D{x + other.x, y + other.y, z + other.z};
  }

  Index3D operator-(const Index3D& other) const
  {
    return Index3D{x - other.x, y - other.y, z - other.z};
  }

  friend std::ostream& operator<<(std::ostream& stream, const Index3D& index)
  {
    return stream << "(" << index.x << " " << index.y << " " << index.z << ")";
  }

  friend bool operator<(const Index3D& lhs, const Index3D& rhs)
  {
    if(lhs.x != rhs.x)
      return lhs.x < rhs.x;
    if(lhs.y != rhs.y)
      return lhs.y < rhs.y;
    return lhs.z < rhs.z;
  }

  friend bool operator==(const Index3D& lhs, const Index3D& rhs)
  {
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
  }

  friend bool operator!=(const Index3D& lhs, const Index3D& rhs)
  {
    return !operator==(lhs, rhs);
  }
};

template <typename T>
struct Array3D
{
  int width;
  int height;
  int length;
  std::vector<T> array3D;

  Array3D()
    : width{0}, height{0}, length{0}
  {}

  Array3D(int width, int height, int length)
    : width{width}, height{height}, length{length}
  {
    array3D.resize(width * height * length);
  }

  Array3D(int width, int height, int length, const std::vector<T>& data)
    : width{width}, height{height}, length{length}, array3D{data}
  {}

  void Fill(const T& value)
  {
    for (int i = 0; i < width * height * length; i++)
    {
      array3D[i] = value;
    }
  }

  int GetIndex(int x, int y, int z) const
  {
    return x + y * width + z * width * height;
  }

  T& Get(int x, int y, int z) 
  {
    return array3D[x + y * width + z * width * height];
  }

  const T& Get(int x, int y, int z) const
  {
    return array3D[x + y * width + z * width * height];
  }

  T& operator[](const Index3D& index)
  {
    return Get(index.x, index.y, index.z);
  }

  const T& operator[](const Index3D& index) const
  {
    return Get(index.x, index.y, index.z);
  }

  T& GetMirror(int x, int y, int z) 
  {
    // if width = 3, it will repeat x like this: 012210012210, same with height and length
    x = (x / width ) % 2 == 0 ? x % width  : width  - (x % width ) - 1;
    y = (y / height) % 2 == 0 ? y % height : height - (y % height) - 1;
    z = (z / length) % 2 == 0 ? z % length : length - (z % length) - 1;
    return array3D[x + y * width + z * width * height];
  }

  const T& GetMirror(int x, int y, int z) const
  {
    // if width = 3, it will repeat x like this: 012210012210, same with height and length
    x = (x / width ) % 2 == 0 ? x % width  : width  - (x % width ) - 1;
    y = (y / height) % 2 == 0 ? y % height : height - (y % height) - 1;
    z = (z / length) % 2 == 0 ? z % length : length - (z % length) - 1;
    return array3D[x + y * width + z * width * height];
  }

  T& GetMod(int x, int y, int z) 
  {
    return array3D[((x % width + width) % width) + ((y % height + height) % height) * width + ((z % length + length) % length) * width * height];
  }

  const T& GetMod(int x, int y, int z) const
  {
    return array3D[((x % width + width) % width) + ((y % height + height) % height) * width + ((z % length + length) % length) * width * height];
  }

  void Set(int x, int y, int z, const T& val)
  {
    Get(x, y, z) = val;
  }

  void SetMod(int x, int y, int z, const T& val)
  {
    GetMod(x, y, z) = val;
  }

  void SetMirror(int x, int y, int z, const T& val)
  {
    GetMirror(x, y, z) = val;
  }

  int GetNeighbors(const T& val, int x, int y, int z, int size = 1) const
  {
    int neighbors = 0;
    for (int zi = z - size; zi <= z + size; zi++)
    {
      for (int yi = y - size; yi <= y + size; yi++)
      {
        for (int xi = x - size; xi <= x + size; xi++)
        {
          if (xi < 0 || yi < 0 || zi < 0 || xi >= width || yi >= height || zi >= length)
            continue;
          if (xi == x && yi == y && zi == z)
            continue;
          if (Get(xi, yi, zi) == val)
            neighbors++;
        }
      }
    }
    return neighbors;
  }

  bool IsInside(const Index3D& index) const
  {
    return index.x >= 0 && index.y >= 0 && index.z >= 0 && index.x < width && index.y < height && index.z < length;
  }

  int Count(const T& val)
  {
    int count = 0;
    for (int z = 0; z < length; z++)
    {
      for (int y = 0; y < height; y++)
      {
        for (int x = 0; x < width; x++)
        {
          if (Get(x, y, z) == val)
            count++;
        }
      }
    }
    return count;
  }

  template <typename Function>
  void Each(Function func) const
  {
    for (int z = 0; z < length; z++)
    {
      for (int y = 0; y < height; y++)
      {
        for (int x = 0; x < width; x++)
        {
          func(*this, Index3D{x, y, z});
        }
      }
    }
  }

  Index3D Find(const T& value)
  {
    for(int z = 0; z < length; z++)
    {
      for(int y = 0; y < height; y++)
      {
        for(int x = 0; x < width; x++)
        {
          if(Get(x, y, z) == value)
            return Index3D{x, y, z};
        }
      }
    }
    return Index3D{};
  }

  void Increment(Index3D& index)
  {
    index.x++;
    if(index.x != width)
      return;
    index.x = 0;
    index.y++;
    if(index.y != height)
      return;
    index.y = 0;
    index.z++;
  }

  typename std::vector<T>::iterator begin()
  {
    return array3D.begin();
  }

  typename std::vector<T>::iterator end()
  {
    return array3D.end();
  }

  typename std::vector<T>::const_iterator begin() const
  {
    return array3D.cbegin();
  }

  typename std::vector<T>::const_iterator end() const
  {
    return array3D.cend();
  }

  friend std::ostream& operator<<(std::ostream& os, const Array3D& array3D)
  {
    for (int z = 0; z < array3D.length; z++)
    {
      std::cout << "z=" << z << std::endl;
      for (int y = 0; y < array3D.height; y++)
      {
        for (int x = 0; x < array3D.width; x++)
        {
          std::cout << array3D.Get(x, y, z);
        }
        std::cout << std::endl;
      }
    }
    return std::cout;
  }
};
