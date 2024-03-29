#include <algorithm>
#include <memory>
#include <iostream>

template <typename T>
class DynamicArray
{

private:
  std::unique_ptr<T[]> data;
  const int min_capacity = 4;
  const int growth_factor = 2;
  int curr_size = 0;
  int curr_capacity = 4;

  void grow()
  {
    int new_capacity = this->curr_capacity * growth_factor;
    this->curr_capacity = new_capacity;
    auto temp = std::make_unique<T[]>(new_capacity);
    for (int i = 0; i < curr_size; i++)
    {
      temp[i] = data[i];
    }
    this->data = std::move(temp);
  }

public:
  void display_info()
  {
    std::cout << "The current array size is: " << this->curr_size << '\n';
    std::cout << "The current array capacity is: " << this->curr_capacity << '\n';
    for (int i = 0; i < curr_size; i++)
    {
      std::cout << data[i] << " ";
    }
    std::cout << std::endl;
  }
  DynamicArray(int capacity)
  {
    if (capacity < 1)
    {
      throw std::invalid_argument("received negative value");
    }
    int new_capacity = std::max(capacity, this->min_capacity);
    this->curr_capacity = new_capacity;
    data = std::make_unique<T[]>(this->curr_capacity);
  }
  ~DynamicArray(){};
  int get_size()
  {
    return curr_size;
  }
  bool IsEmpty()
  {
    return curr_size == 0;
  }
  // Returns the capacity of the vector.
  int get_capacity()
  {
    return curr_capacity;
  }
  // Appends the given value to the end of the vector.
  void push(const T value)
  {
    if (curr_size == curr_capacity)
    {
      grow();
    }
    data[curr_size] = value;
    curr_size += 1;
  }
  // Returns the value stored at the given index
  T get(int index) const
  {
    if (index >= 0 && index < curr_size)
    {
      return data[index];
    }
    throw std::invalid_argument("received negative value");
  }
  // Returns the last item in the vector, and removes it.
  T pop()
  {
    auto element = data[curr_size - 1];
    curr_size -= 1;

    return element;
  }
  // Inserts the given value at the given index, shifting
  // current and trailing items to the right.
  void insert(int index, const T value)
  {
    if (index < 0 || index >= this->curr_size)
    {
      throw std::invalid_argument("index doesn't exist");
    }
    if (this->curr_size == this->curr_capacity)
    {
      grow();
    }
    this->curr_size += 1;
    for (int i = this->curr_size; i > index; i--)
    {
      data[i] = data[i - 1];
    }
    data[index] = value;
  }
  // Prepends the given value to the vector, shifting trailing
  // items to the right.
  void prepend(const T value)
  {
    insert(0, value);
  }
  // Deletes item at index, shifting all trailing elements left.
  void remove(int index)
  {
    if (index < 0 || index >= this->curr_size)
    {
      throw std::invalid_argument("index doesn't exist");
    }
    for (int i = index; i < this->curr_size - 1; i++)
    {
      data[i] = data[i + 1];
    }
    this->curr_size -= 1;
  }
  void remove_element(T value)
  {
    for (int i = 0; i < this->curr_size; ++i)
    {
      if (data[i] == value)
      {
        remove(i);
        --i;
      }
    }
  }
  T find(const T value) const
  {
    for (int i = 0; i < curr_size; i++)
    {
      if (this->data[i] == value)
      {
        return i;
      }
    }
    return -1;
  }
};