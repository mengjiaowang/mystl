#include "../mystl_hashtable.h"
#include "../mystl_function.h"
#include <iostream>

int main()
{
  // test constructor
  mystl::hashtable<int, int, std::hash<int>, mystl::identity<int>, std::equal_to<int> >
    test_ht(5, std::hash<int>(), std::equal_to<int>());
  // test insert_unique
  test_ht.insert_unique(1);
  test_ht.insert_unique(63);
  test_ht.insert_unique(108);
  return 0;
}
