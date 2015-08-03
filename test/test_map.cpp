#include <iostream>
#include "../map"

int main()
{
  // test constructor
  mystl::map<int, int> test_map;
  // test isnert
  test_map[1] = 1;
  test_map[2] = 2;
  test_map[3] = 3;
  test_map[4] = 4;
  // test size
  std::cout << "the size of the map is:" << test_map.size() << std::endl;
  // test iterator
  mystl::map<int, int>::iterator iter;
  for(iter = test_map.begin(); iter != test_map.end(); ++iter)
  {
    std::cout << "key: " << iter->first << " value: " << iter->second << std::endl;
  }
  return 0;
}
