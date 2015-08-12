#include "../mystl_hashtable.h"
#include "../mystl_function.h"
#include <iostream>

int main()
{
  // test constructor
  mystl::hashtable<int, int, std::hash<int>, mystl::identity<int>,
    std::equal_to<int> > test_ht(5, std::hash<int>(), std::equal_to<int>());
  // test insert_unique
  test_ht.insert_unique(1);
  test_ht.insert_unique(63);
  test_ht.insert_unique(108);

  // test iterator
  mystl::hashtable<int, int, std::hash<int>, mystl::identity<int>,
    std::equal_to<int> >::iterator iter;
  for(iter = test_ht.begin(); iter != test_ht.end(); ++iter)
  {
    std::cout << "value: " << (*iter) << std::endl;
  }
  std::cout << std::endl;

  // test insert_equal
  test_ht.insert_equal(1);
  test_ht.insert_equal(63);
  test_ht.insert_equal(108);

  // test iterator after insert_equal
  for(iter = test_ht.begin(); iter != test_ht.end(); ++iter)
  {
    std::cout << "value: " << (*iter) << std::endl;
  }
  std::cout << std::endl;

  // test find
  iter = test_ht.find(1);
  std::cout << "found = " << (iter != test_ht.end()) << std::endl;
  iter = test_ht.find(2);
  std::cout << "found = " << (iter != test_ht.end()) << std::endl;

  // test count
  mystl::hashtable<int, int, std::hash<int>, mystl::identity<int>,
    std::equal_to<int> >::size_type n = 0;
  n = test_ht.count(1);
  std::cout << "count = " << n << std::endl;
  n = test_ht.count(2);
  std::cout << "count = " << n << std::endl;
  std::cout << std::endl;

  // test copy constructor
  mystl::hashtable<int, int, std::hash<int>, mystl::identity<int>,
    std::equal_to<int> > test_ht_cpy(test_ht);
  for(iter = test_ht.begin(); iter != test_ht.end(); ++iter)
  {
    std::cout << "value: " << (*iter) << std::endl;
  }
  std::cout << std::endl;
  test_ht_cpy.clear();

  // test resize
  test_ht.clear();
  for(int i = 0; i != 100; ++i)
  {
    test_ht.insert_unique(i);
  }
  for(iter = test_ht.begin(); iter != test_ht.end(); ++iter)
  {
    std::cout << (*iter) << " ";
  }
  std::cout << std::endl;

  return 0;
}
