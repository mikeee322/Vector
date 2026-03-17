#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <iostream>
namespace topit
{
  template <class T>
struct Vector {

  private:
    T* data;
    size_t size_, capasity_;
  };
}
#endif
