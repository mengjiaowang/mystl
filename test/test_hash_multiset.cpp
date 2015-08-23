#include "../hash_multiset"
#include <iostream>

int main()
{
  mystl::hash_multiset<int> test_set;

  //test empty
  std::cout << "empty = " << test_set.empty() << std::endl;

  //test insert
  test_set.insert(1);
  test_set.insert(1);
  test_set.insert(2);
  test_set.insert(2);
  test_set.insert(3);

  //test size
  std::cout << "size = " << test_set.size() << std::endl;

  //test count
  std::cout << "count(1) = " << test_set.count(1) << std::endl;
  std::cout << "count(2) = " << test_set.count(2) << std::endl;
  std::cout << "count(3) = " << test_set.count(3) << std::endl;

  //test erase
  test_set.erase(1);

  //test iterator
  mystl::hash_multiset<int>::iterator iter;
  for(iter = test_set.begin(); iter != test_set.end(); ++iter)
  {
    std::cout << *iter << " ";
  }
  std::cout << std::endl;

  return 0;
}
