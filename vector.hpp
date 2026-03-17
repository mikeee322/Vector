#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <iostream>
namespace topit
{
  template <class T>
struct Vector {
    Vector();
    Vector(const Vector< T >&) = default;
    ~Vector();
    Vector< T >& operator=(const Vector < T >&) = delete;

    void pushBacl(const T&);
    bool isEmpty() const noexcept;
  private:
    T* data;
    size_t size_, capasity_;
  };

}
template<class T>
bool topit::Vector<T>::isEmpty() const noexcept {
  return false;
}

template<class T>
topit::Vector<T>::~Vector() {
  delete[] data;
}


template<class T>
topit::Vector<T>::Vector():
  data(nullptr), size_(0), capasity_(0)
{}

#endif
