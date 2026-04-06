#include <ios>
#include <iostream>
#include <iomanip>
#include "vector.hpp"

using vec = topit::Vector<int>;

bool testDefaultVector()
{
  vec v;
  return v.isEmpty();
}

bool testVectorWithValue()
{
  vec v;
  v.pushBack(1);
  return v.isEmpty() == false;
}

bool testGetSizeWithValues()
{
  vec v;
  for (int i = 1; i <= 3; ++i)
  {
    v.pushBack(i);
  }
  return v.getSize() == 3;
}

bool testGetSizeWithoutValues()
{
  vec v;
  return v.getSize() == 0;
}

bool testGetCapacityWithValues()
{
  vec v;
  for (int i = 0; i < 3; ++i)
  {
    v.pushBack(i);
  }
  return v.getCapacity() == 10;
}

bool testGetCapacityWithoutValues()
{
  vec v;
  return v.getCapacity() == 0;
}

bool testPushBack()
{
  vec v;
  v.pushBack(1);
  return v[0] == 1;
}

bool testPopBackValue()
{
  vec v;
  v.pushBack(1);
  v.popBack();
  return v.getSize() == 0;
}

bool testPopBackNoValue()
{
  vec v;
  try
  {
    v.popBack();
  }
  catch (std::out_of_range&)
  {
    return true;
  }
  return false;
}

bool testElementAccess()
{
  vec v;
  v.pushBack(1);
  v.pushBack(2);

  return (v[0] == 1) && (v[1] == 2);
}

bool testElementConstAccess()
{
  vec v;
  v.pushBack(1);
  v.pushBack(2);

  const vec& ref = v;
  return (ref[0] == 1) && (ref[1] == 2);
}

bool testElementCheckedAccess()
{
  vec v;
  try
  {
    v.at(0);
  }
  catch (std::out_of_range&)
  {
    return true;
  }
  return false;
}

bool testElementInboundCheckedAccess()
{
  vec v;
  v.pushBack(1);

  try
  {
    int& x = v.at(0);
    return x == 1;
  }
  catch (...)
  {
    return false;
  }
}

bool testElementInboundCheckedConstAccess()
{
  vec v;
  v.pushBack(1);
  const vec& ref = v;

  try
  {
    const int& x = ref.at(0);
    return x == 1;
  }
  catch (...)
  {
    return false;
  }
}

bool testCopyConstructor()
{
  vec v;
  v.pushBack(1);

  vec copy(v);

  if (v.getSize() != copy.getSize())
  {
    return false;
  }
  for (size_t i = 0; i < v.getSize(); ++i)
  {
    if (v[i] != copy[i])
    {
      return false;
    }
  }
  return true;
}

bool testAssignmentOperator()
{
  vec v;
  for (int i = 1; i <= 3; ++i)
  {
    v.pushBack(i);
  }
  vec other;
  other = v;

  if (v.getSize() != other.getSize())
  {
    return false;
  }
  for (size_t i = 0; i < v.getSize(); ++i)
  {
    if (v[i] != other[i])
    {
      return false;
    }
  }
  return true;
}

bool testAssignmentOperatorWithoutValues()
{
  vec v, other;
  other = v;
  return v.getSize() == other.getSize();
}

bool testPushFront()
{
  vec v;
  v.pushFront(3);
  return v[0] == 3;
}

bool testPushFrontManyValues()
{
  vec v;

  for (int i = 3; i >= 1; --i)
  {
    v.pushFront(i);
  }
  return v[0] == 1 && v[1] == 2 && v[2] == 3;
}

bool testPopFront()
{
  vec v;
  v.pushFront(1);
  v.popFront();
  return v.getSize() == 0;
}

bool testPopFrontNoValue()
{
  vec v;
  try
  {
    v.popFront();
  }
  catch (std::out_of_range&)
  {
    return true;
  }
  return false;
}

bool testSwap()
{
  vec v;
  for (int i = 1; i <= 3; ++i)
  {
    v.pushBack(i);
  }
  vec other;
  v.swap(other);

  if (!(v.getSize() == 0 && other.getSize() == 3))
  {
    return false;
  }
  for (size_t i = 0; i < other.getSize(); ++i)
  {
    if (other[i] != static_cast<int>(i + 1))
    {
      return false;
    }
  }
  return true;
}

bool testBaseInsert()
{
  vec v;
  v.pushBack(1);
  v.pushBack(3);

  try
  {
    v.insert(1, 2);
    return v[1] == 2;
  }
  catch (...)
  {
    return false;
  }
}

bool testOverflowInsert()
{
  vec v;
  v.pushBack(1);

  try
  {
    v.insert(10, 2);
  }
  catch (std::range_error&)
  {
    return true;
  }
  return false;
}

bool testBaseErase()
{
  vec v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);

  v.erase(1);

  return v.getSize() == 2 && v[1] == 3;
}

bool testNoValuesErase()
{
  vec v;

  try
  {
    v.erase(0);
  }
  catch (std::range_error&)
  {
    return true;
  }
  return false;
}

bool testOverflowErase()
{
  vec v;
  v.pushBack(1);

  try
  {
    v.erase(10);
  }
  catch (std::range_error&)
  {
    return true;
  }
  return false;
}

bool testManyBaseInsert()
{
  vec rhs;
  for (int i = 1; i <= 6; ++i)
  {
    rhs.pushBack(i);
  }

  vec v;
  for (int i = 1; i <= 3; ++i)
  {
    v.pushBack(i);
  }
  v.insert(1, rhs, 3, 4);
  return v[1] == 4 && v[2] == 5 && v.getSize() == 5;
}

bool testManyIncorrectRhsInsert()
{
  vec rhs;
  for (int i = 1; i <= 6; ++i)
  {
    rhs.pushBack(i);
  }
  vec v;
  v.pushBack(1);
  try
  {
    v.insert(1, rhs, 4, 10);
  }
  catch (std::range_error&)
  {
    return true;
  }
  return false;
}

bool testManyIncorrectVInsert()
{
  vec rhs;
  for (int i = 1; i <= 6; ++i)
  {
    rhs.pushBack(i);
  }
  vec v;
  v.pushBack(1);

  try
  {
    v.insert(100, rhs, 3, 4);
  }
  catch (std::range_error&)
  {
    return true;
  }
  return false;
}

bool testManyIncorrectIndexesInsert()
{
  vec rhs;
  for (int i = 1; i <= 6; ++i)
  {
    rhs.pushBack(i);
  }
  vec v;
  v.pushBack(1);

  try
  {
    v.insert(1, rhs, 4, 3);
  }
  catch (std::range_error&)
  {
    return true;
  }
  return false;
}

bool testBaseManyErase()
{
  vec v;
  for (int i = 1; i <= 3; ++i)
  {
    v.pushBack(i);
  }
  v.erase(1, 2);

  return v.getSize() == 1 && v[0] == 1;
}

bool testOverflowIndexesManyErase()
{
  vec v;
  v.pushBack(1);

  try
  {
    v.erase(5, 10);
  }
  catch (std::range_error&)
  {
    return true;
  }
  return false;
}

bool testUncorrectIndexesManyErase()
{
  vec v;
  v.pushBack(1);

  try
  {
    v.erase(2, 1);
  }
  catch (std::range_error&)
  {
    return true;
  }
  return false;
}

bool testInitializerListConstructor()
{
  vec v{1, 2};
  return v.getSize() == 2;
}

int main()
{
  using test_t = bool(*)();
  using pair_t = std::pair<const char*, test_t>;

  pair_t tests[] =
  {
    {"Default vector is empty", testDefaultVector},
    {"Vector with amy value is not empty", testVectorWithValue},
    {"Correct size of vector", testGetSizeWithValues},
    {"Correct size of empty vector", testGetSizeWithoutValues},
    {"Correct capacity of vector", testGetCapacityWithValues},
    {"Correct capacity of empty vector", testGetCapacityWithoutValues},
    {"Correct adding one element to the ending", testPushBack},
    {"Correct deleting last value", testPopBackValue},
    {"Correct deleting no values from ending", testPopBackNoValue},
    {"Inbound access elements", testElementAccess},
    {"Inbound access const elements", testElementConstAccess},
    {"Correct unworking at method", testElementCheckedAccess},
    {"Correct working at method", testElementInboundCheckedAccess},
    {"Correct working const at method", testElementInboundCheckedConstAccess},
    {"Sizes must be as elemets", testCopyConstructor},
    {"The copy operator is working", testAssignmentOperator},
    {"The copy operator is working without values", testAssignmentOperatorWithoutValues},
    {"Correct adding one element to the beginning", testPushFront},
    {"Correct adding many values to the beginning", testPushFrontManyValues},
    {"Correct deleting first value", testPopFront},
    {"Correct deleting no values from beginning", testPopFrontNoValue},
    {"Correct swapping vectors", testSwap},
    {"Correct inserting one value", testBaseInsert},
    {"Correct throwing invalid index in insert", testOverflowInsert},
    {"Correct erasing one value", testBaseErase},
    {"Correct erasing from empty vector", testNoValuesErase},
    {"Correct throwing invalid index in erasing", testOverflowErase},
    {"Correct inserting many values", testManyBaseInsert},
    {"Correct throwing incorrect index of inserting vector", testManyIncorrectRhsInsert},
    {"Correct throwing incorrect index of vector for insert", testManyIncorrectVInsert},
    {"Correct throwing invalid order of indexes in inserting vector", testManyIncorrectIndexesInsert},
    {"Correct erasing many elements", testBaseManyErase},
    {"Correct throwing overflow indexes of many erasing", testOverflowIndexesManyErase},
    {"Correct throwing uncorrect indexes of many erasing", testUncorrectIndexesManyErase},
    {"Vector with initializer list must be same size as init-list", testInitializerListConstructor}
  };

  bool all = true;
  const size_t count = sizeof(tests) / sizeof(pair_t);
  std::cout << std::boolalpha;
  for (size_t i = 0; i < count; ++i)
  {
    bool res = tests[i].second();
    std::cout << std::left << std::setw(61) << tests[i].first << ": " << res << "\n";
    all = all && res;
  }
  std::cout << "RESULT: " << all << "\n";
}
