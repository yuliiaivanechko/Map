#pragma once
// clang-format off
#include <iostream>

template <class T> class Queue 
{
  T *all_data;
  int top;
  int bottom;

  size_t count;

public:
  Queue(const size_t element_count) : top(0), bottom(0), count(0) 
  {
    all_data = new T[element_count];
  }

  ~Queue() 
  {
    delete[] all_data;
    all_data = nullptr;
  }

  void push(const T &value);

  T pop();

  T &front() 
  {
    if (empty()) 
    {
      std::cerr << "Queue is empty\n";
    }
    return all_data[bottom];
  }

  bool empty() const
  {
    if (this->count == 0) 
    {
      return true;
    }
    return false;
  }
};

template <class T> void Queue<T>::push(const T &value) 
{
  if (top == count - 1) 
  {
    std::cerr << "Queue is full, can not add element\n";
  }
  all_data[top++] = value;
  ++count;
}

template <class T> T Queue<T>::pop() 
{
  if (bottom == top) 
  {
    std::cerr << "Queue is empty, can not pop element\n";
  }
  --count;
  return all_data[bottom++];
}
