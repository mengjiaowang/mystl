#include "../hash_map"
#include <iostream>

int main()
{
  // test constructor
  mystl::hash_map<int, int> test_hm;

  // test empty
  std::cout << "empty = " << test_hm.empty() << std::endl;

  return 0;
}
