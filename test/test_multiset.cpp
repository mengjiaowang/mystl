#include <iostream>
#include "../multiset"

int main()
{
  // test constructor
  mystl::multiset<int> test_multiset;
  // test inesrt
  test_multiset.insert(1);
  test_multiset.insert(2);
  test_multiset.insert(3);
  // test size
  std::cout << test_multiset.size() << std::endl;
  // test find
  mystl::multiset<int>::iterator iter;
  iter = test_multiset.find(3);
  if(iter != test_multiset.end())
  {
    std::cout << "element found!" << std::endl;
  }
  else
  {
    std::cout << "element not found!" << std::endl;
  }

  iter = test_multiset.find(5);
  if(iter != test_multiset.end())
  {
    std::cout << "element found!" << std::endl;
  }
  else
  {
    std::cout << "element not found!" << std::endl;
  }

  // test iterator
  for(iter = test_multiset.begin(); iter != test_multiset.end(); ++iter)
  {
    std::cout << *iter << " ";
  }
  std::cout << std::endl;
  return 0;
}
