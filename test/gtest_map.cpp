#include <gtest/gtest.h>
#include "../map"
#include "../multimap"
#include "../mystl_pair.h"

namespace mystl_test
{
  TEST(TestMap, TestMapConstructor)
  {
    mystl::map<int, int> test_map;
    EXPECT_EQ(0, test_map.size());
  }

  TEST(TestMap, TestMapInsert1)
  {
    mystl::map<int, int> test_map;
    test_map[1] = 1;
    test_map[2] = 2;
    test_map[3] = 3;
    test_map[4] = 4;
    EXPECT_EQ(4, test_map.size());
  }

  TEST(TestMap, TestMapInsert2)
  {
    mystl::map<int, int> test_map;
    test_map[1] = 1;
    test_map[2] = 2;
    test_map[3] = 3;
    test_map[4] = 4;

    mystl::map<int, int>::iterator iter;
    int key = 1, value = 1;
    for(iter = test_map.begin(); iter != test_map.end(); ++iter)
    {
      EXPECT_EQ(key++, iter->first);
      EXPECT_EQ(value++, iter->second);
    }
  }

  /*
  TEST(TestMultiMap, TestMultiMapInsert)
  {
    mystl::multimap<int, int> test_multimap;
    test_multimap.insert(mystl::pair<int, int>(1,1));
    test_multimap.insert(mystl::pair<int, int>(1,2));
    test_multimap.insert(mystl::pair<int, int>(2,1));
    test_multimap.insert(mystl::pair<int, int>(2,2));
    test_multimap.insert(mystl::pair<int, int>(3,1));
  }

  TEST(TestMultiMap, TestMultiMapIterator)
  {
    mystl::multimap<int, int> test_multimap;
    test_multimap.insert(mystl::pair<int, int>(1,1));
    test_multimap.insert(mystl::pair<int, int>(1,2));
    test_multimap.insert(mystl::pair<int, int>(2,1));
    test_multimap.insert(mystl::pair<int, int>(2,2));
    test_multimap.insert(mystl::pair<int, int>(3,1));

    mystl::multimap<int, int>::iterator iter;
    for(iter = test_multimap.begin(); iter != test_multimap.end(); ++iter)
    {
      std::cout << iter->first << " " << iter->second << std::endl;
    }
  }
  */
}
