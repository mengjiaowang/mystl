#include <iostream>
#include "../multimap"

int main()
{
  // test constructor
  mystl::multimap<int, int> test_multimap;

  // test insert
  test_multimap.insert(std::pair<int, int>(1,1));
  test_multimap.insert(std::pair<int, int>(1,2));
  test_multimap.insert(std::pair<int, int>(2,1));
  test_multimap.insert(std::pair<int, int>(2,2));
  test_multimap.insert(std::pair<int, int>(3,1));

  // test iterator
  mystl::multimap<int, int>::iterator iter;
  for(iter = test_multimap.begin(); iter != test_multimap.end(); ++iter)
  {
    std::cout << iter->first << " " << iter->second << std::endl;
  }
  std::cout << std::endl;

  return 0;
}
