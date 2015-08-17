#include "../hashset"
#include <iostream>

int main()
{
  // test constructor
  mystl::hash_set<int> test_hs;

  // test empty
  std::cout << "empty = " << test_hs.empty() << std::endl;

  // test inesrt
  test_hs.insert(1);
  test_hs.insert(2);
  test_hs.insert(3);

  // test size
  std::cout << "size = " << test_hs.size() << std::endl;

  // test insert
  mystl::pair<mystl::hash_set<int>::iterator,
    bool> p = test_hs.insert(1);
  std::cout << "insert status = " << p.second << std::endl;

  return 0;
}
