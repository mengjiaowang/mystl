#include <iostream>
#include "../pair.h"

int main()
{
  // test constructor
  mystl::pair<int, int> p1(1,1);

  // test value
  std::cout << "first: " << p1.first << " p.second:" << p1.second << std::endl;

  // test make_pair
  mystl::pair<int, int> p2 = mystl::make_pair<int, int>(2, 2);

  // test equal
  std::cout << "p1 == p1: " << (p1 == p2) << std::endl;

  return 0;
}
