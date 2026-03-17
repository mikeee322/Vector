#include <iostream>
#include "vector.hpp"
bool testDefaultVector()
{
  topit::Vector< int > v;
  return v.isEmpty();
}

bool testVectorWithValue() {
  topit::Vector< int > v;
}

int main() {
  ///std::cout << "Def vect should be empty: " << testDefaultVector() << "\n";
  using test_t = bool(*)();
  using pair_t = std::pair< const char*, test_t>;
  pair_t tests[] {
    {"Def vect is empty", testDefaultVector},
    {" Vect with any value is not empty", testVectorWithValue}
  };

  const size_t count = sizeof(tests) / sizeof(pair_t);
  std::cout << std::boolalpha;
  for (size_t i = 0; i < count; ++i) {
    bool res = tests[i].second();
    std::cout << tests[i].first << " : " << res << "\n";
  }
}
