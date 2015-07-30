#include <iostream>
#include "../mystl_set.h"

int main()
{

  // test constructor
  int num [] = {1, 2, 3, 4, 5};
  mystl::set<int> test_set(num, num + 5);

  // test size
  std::cout << "The size of this set is: " << test_set.size() << std::endl;

  // test iterator
  mystl::set<int>::iterator iter;
  for(iter = test_set.begin(); iter != test_set.end(); ++iter)
  {
    std::cout << *iter << " ";
  }
  std::cout << std::endl;

  // test insert
  test_set.insert(6);
  test_set.insert(7);
  for(iter = test_set.begin(); iter != test_set.end(); ++iter)
  {
    std::cout << *iter << " ";
  }
  std::cout << std::endl;

  // test insert
  int num1 [] = {9, 10, 11};
  test_set.insert(num1, num1+3);
  for(iter = test_set.begin(); iter != test_set.end(); ++iter)
  {
    std::cout << *iter << " ";
  }
  std::cout << std::endl;

  // test find
  iter = test_set.find(10);
  if(iter != test_set.end())
  {
    std::cout << "element found!" << std::endl;
  }
  else
  {
    std::cout << "element not found!" << std::endl;
  }

  iter = test_set.find(20);
  if(iter != test_set.end())
  {
    std::cout << "element found!" << std::endl;
  }
  else
  {
    std::cout << "element not found!" << std::endl;
  }

  return 0;
}
