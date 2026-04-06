#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef>
#include <cassert>
#include <initializer_list>
#include <stdexcept>
#include <utility>

namespace topit
{
  template <class T>
  struct Vector
  {
    Vector();
    Vector(const Vector<T>&);
    Vector(Vector<T>&&) noexcept;
    explicit Vector(std::initializer_list<T> il);
    ~Vector();

    Vector<T>& operator=(const Vector<T>&);
    Vector<T>& operator=(Vector<T>&&) noexcept;

    T& operator[](size_t index) noexcept;
    const T& operator[](size_t index) const noexcept;

    T& at(size_t id);
    const T& at(size_t id) const;

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    size_t getCapacity() const noexcept;

    void reserve(size_t cap);
    void shrinkToFit();

    void pushBack(const T& k);
    void popBack();

    void pushFront(T val);
    void popFront();

    void swap(Vector<T>& rhs) noexcept;

    void insert(size_t i, const T& val);
    void erase(size_t i);

    void insert(size_t i, const Vector<T>& rhs, size_t beg, size_t end);
    void erase(size_t beg, size_t end);

    void clear(T* data, size_t size);

  private:
    T* data_;
    size_t size_, capacity_;

    explicit Vector(size_t k);

    void pushBackImpl(const T&);
    void reserve(size_t pos, size_t k);
  };
}

template <class T>
topit::Vector<T>::Vector() :
  data_(nullptr), size_(0), capacity_(0)
{}

template <class T>
topit::Vector<T>::Vector(size_t k) :
  data_(static_cast<T*>(::operator new(sizeof(T) * k))),
  size_(0), capacity_(k)
{}

template <class T>
topit::Vector<T>::Vector(std::initializer_list<T> il) :
  Vector(il.size())
{
  size_t i = 0;
  try
  {
    for (auto& v : il)
    {
      new (data_ + i) T(v);
      ++i;
    }
    size_ = il.size();
  }
  catch (...)
  {
    clear(data_, i);
    throw;
  }
}

template <class T>
topit::Vector<T>::Vector(const Vector<T>& rhs) :
  Vector(rhs.size_)
{
  size_t i = 0;
  try
  {
    for (; i < rhs.size_; ++i)
    {
      new (data_ + i) T(rhs.data_[i]);
    }
    size_ = rhs.size_;
  }
  catch (...)
  {
    clear(data_, i);
    throw;
  }
}

template <class T>
topit::Vector<T>::Vector(Vector<T>&& rhs) noexcept :
  data_(rhs.data_), size_(rhs.size_), capacity_(rhs.capacity_)
{
  rhs.data_ = nullptr;
  rhs.size_ = 0;
  rhs.capacity_ = 0;
}

template <class T>
topit::Vector<T>::~Vector()
{
  clear(data_, size_);
  ::operator delete(data_);
}

template <class T>
topit::Vector<T>& topit::Vector<T>::operator=(const Vector<T>& rhs)
{
  if (this != &rhs)
  {
    Vector<T> tmp(rhs);
    swap(tmp);
  }
  return *this;
}

template <class T>
topit::Vector<T>& topit::Vector<T>::operator=(Vector<T>&& rhs) noexcept
{
  if (this != &rhs)
  {
    Vector<T> tmp(std::move(rhs));
    swap(tmp);
  }
  return *this;
}

template <class T>
bool topit::Vector<T>::isEmpty() const noexcept
{
  return size_ == 0;
}

template <class T>
size_t topit::Vector<T>::getSize() const noexcept
{
  return size_;
}

template <class T>
size_t topit::Vector<T>::getCapacity() const noexcept
{
  return capacity_;
}

template <class T>
T& topit::Vector<T>::operator[](size_t index) noexcept
{
  return const_cast<T&>(
    static_cast<const Vector<T>&>(*this)[index]
  );
}

template <class T>
const T& topit::Vector<T>::operator[](size_t index) const noexcept
{
  assert(index < size_);
  return data_[index];
}

template <class T>
T& topit::Vector<T>::at(size_t id)
{
  return const_cast<T&>(
    static_cast<const Vector<T>&>(*this).at(id)
  );
}

template <class T>
const T& topit::Vector<T>::at(size_t id) const
{
  if (id >= size_)
  {
    throw std::out_of_range("bad id");
  }
  return data_[id];
}

template <class T>
void topit::Vector<T>::swap(Vector<T>& rhs) noexcept
{
  std::swap(data_, rhs.data_);
  std::swap(size_, rhs.size_);
  std::swap(capacity_, rhs.capacity_);
}

template <class T>
void topit::Vector<T>::reserve(size_t cap)
{
  if (cap <= capacity_)
  {
    return;
  }
  T* newData = static_cast<T*>(::operator new(sizeof(T) * cap));

  size_t i = 0;
  try
  {
    while (i < size_)
    {
      new (newData + i) T(std::move(data_[i]));
      ++i;
    }
  }
  catch (...)
  {
    while (i > 0)
    {
      --i;
      (newData + i)->~T();
    }
    ::operator delete(newData);
    throw;
  }

  clear(data_, size_);
  ::operator delete(data_);

  data_ = newData;
  capacity_ = cap;
}

template <class T>
void topit::Vector<T>::shrinkToFit()
{
  if (size_ == capacity_)
  {
    return;
  }
  T* newData = nullptr;

  if (size_ > 0)
  {
    newData = static_cast<T*>(::operator new(sizeof(T) * size_));
  }
  size_t i = 0;
  try
  {
    for (; i < size_; ++i)
    {
      new (newData + i) T(std::move(data_[i]));
    }
  }
  catch (...)
  {
    clear(newData, i);
    ::operator delete(newData);
    throw;
  }

  clear(data_, size_);
  ::operator delete(data_);

  data_ = newData;
  capacity_ = size_;
}

template <class T>
void topit::Vector<T>::pushBack(const T& k)
{
  if (size_ == capacity_)
  {
    reserve(capacity_ == 0 ? 1 : capacity_ + 10);
  }
  new (data_ + size_) T(k);
  ++size_;
}

template <class T>
void topit::Vector<T>::popBack()
{
  if (!size_)
  {
    throw std::out_of_range("Vector is empty");
  }
  --size_;
  (data_ + size_)->~T();
}

template <class T>
void topit::Vector<T>::pushFront(T val)
{
  Vector<T> tmp(size_ + 1);

  try
  {
    new (tmp.data_) T(val);

    for (size_t i = 0; i < size_; ++i)
    {
      new (tmp.data_ + i + 1) T(data_[i]);
    }
    tmp.size_ = size_ + 1;
  }
  catch (...)
  {
    clear(tmp.data_, tmp.size_);
    ::operator delete(tmp.data_);
    throw;
  }

  swap(tmp);
}

template <class T>
void topit::Vector<T>::popFront()
{
  if (!size_)
  {
    throw std::out_of_range("Vector is empty");
  }
  Vector<T> tmp(size_ - 1);

  try
  {
    for (size_t i = 1; i < size_; ++i)
    {
      new (tmp.data_ + i - 1) T(data_[i]);
    }
    tmp.size_ = size_ - 1;
  }
  catch (...)
  {
    clear(tmp.data_, tmp.size_);
    ::operator delete(tmp.data_);
    throw;
  }

  swap(tmp);
}

template <class T>
void topit::Vector<T>::insert(size_t i, const T& val)
{
  if (i > size_)
  {
    throw std::range_error("Invalid arguments");
  }
  Vector<T> tmp(size_ + 1);

  try
  {
    size_t pos = 0;

    for (; pos < i; ++pos)
    {
      new (tmp.data_ + pos) T(data_[pos]);
    }
    new (tmp.data_ + pos) T(val);
    ++pos;

    for (; pos < size_ + 1; ++pos)
    {
      new (tmp.data_ + pos) T(data_[pos - 1]);
    }
    tmp.size_ = size_ + 1;
  }
  catch (...)
  {
    clear(tmp.data_, tmp.size_);
    ::operator delete(tmp.data_);
    throw;
  }

  swap(tmp);
}

template <class T>
void topit::Vector<T>::erase(size_t i)
{
  if (i >= size_)
  {
    throw std::range_error("Invalid arguments");
  }
  Vector<T> tmp(size_ - 1);

  try
  {
    size_t pos = 0;

    for (; pos < i; ++pos)
    {
      new (tmp.data_ + pos) T(data_[pos]);
    }
    for (; pos < size_ - 1; ++pos)
    {
      new (tmp.data_ + pos) T(data_[pos + 1]);
    }
    tmp.size_ = size_ - 1;
  }
  catch (...)
  {
    clear(tmp.data_, tmp.size_);
    ::operator delete(tmp.data_);
    throw;
  }

  swap(tmp);
}

template <class T>
void topit::Vector<T>::insert(size_t i, const Vector<T>& rhs, size_t beg, size_t end)
{
  if (i > size_ || beg > end || end >= rhs.size_)
  {
    throw std::range_error("Invalid arguments");
  }
  size_t add = end - beg + 1;
  Vector<T> tmp(size_ + add);

  try
  {
    size_t pos = 0;

    for (; pos < i; ++pos)
    {
      new (tmp.data_ + pos) T(data_[pos]);
    }
    for (size_t j = beg; j <= end; ++j, ++pos)
    {
      new (tmp.data_ + pos) T(rhs.data_[j]);
    }
    for (; pos < size_ + add; ++pos)
    {
      new (tmp.data_ + pos) T(data_[pos - add]);
    }
    tmp.size_ = size_ + add;
  }
  catch (...)
  {
    clear(tmp.data_, tmp.size_);
    ::operator delete(tmp.data_);
    throw;
  }

  swap(tmp);
}

template <class T>
void topit::Vector<T>::erase(size_t beg, size_t end)
{
  if (beg > end || end >= size_)
  {
    throw std::range_error("Invalid arguments");
  }
  size_t rem = end - beg + 1;
  Vector<T> tmp(size_ - rem);

  try
  {
    size_t pos = 0;

    for (; pos < beg; ++pos)
    {
      new (tmp.data_ + pos) T(data_[pos]);
    }
    for (; pos < size_ - rem; ++pos)
    {
      new (tmp.data_ + pos) T(data_[pos + rem]);
    }
    tmp.size_ = size_ - rem;
  }
  catch (...)
  {
    clear(tmp.data_, tmp.size_);
    ::operator delete(tmp.data_);
    throw;
  }

  swap(tmp);
}

template <class T>
void topit::Vector<T>::clear(T* data, size_t size)
{
  while (size > 0)
  {
    --size;
    (data + size)->~T();
  }
}

template <class T>
void topit::Vector<T>::pushBackImpl(const T& val)
{
  new (data_ + size_) T(val);
  ++size_;
}

template <class T>
void topit::Vector<T>::reserve(size_t pos, size_t k)
{
  if (pos > size_)
  {
    throw std::out_of_range("Invalid position");
  }
  Vector<T> tmp(size_ + k);

  try
  {
    size_t i = 0;

    for (; i < pos; ++i)
    {
      new (tmp.data_ + i) T(data_[i]);
    }
    i += k;

    for (; i < size_ + k; ++i)
    {
      new (tmp.data_ + i) T(data_[i - k]);
    }
    tmp.size_ = size_ + k;
  }
  catch (...)
  {
    clear(tmp.data_, tmp.size_);
    ::operator delete(tmp.data_);
    throw;
  }

  swap(tmp);
}

#endif
