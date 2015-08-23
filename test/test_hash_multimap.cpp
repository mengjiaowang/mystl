#include "../hash_multimap"
#include <iostream>

int main()
{
  mystl::hash_multimap<int,int> test_map;

  //test empty
  std::cout << "empty = " << test_map.empty() << std::endl;

  //test insert
  test_map.insert(mystl::pair<int,int>(1,11));
  test_map.insert(mystl::pair<int,int>(2,12));
  test_map.insert(mystl::pair<int,int>(2,122));
  test_map.insert(mystl::pair<int,int>(3,13));
  test_map.insert(mystl::pair<int,int>(4,14));

  //test size
  std::cout << "size = " << test_map.size() << std::endl;

  //test iterator
  mystl::hash_multimap<int,int>::iterator iter;
  for(iter = test_map.begin(); iter != test_map.end(); ++iter)
  {
    std::cout << "key: " << iter->first << " value: " << iter->second << std::endl;
  }

  //test find
  iter = test_map.find(1);
  std::cout << "find(1) = " << (iter != test_map.end()) << std::endl;
  iter = test_map.find(10);
  std::cout << "find(10) = " << (iter != test_map.end()) << std::endl;

  //test erase
  std::cout << "size = " << test_map.size() << std::endl;
  test_map.erase(1);
  test_map.erase(2);
  std::cout << "size = " << test_map.size() << std::endl;

  return 0;
}
