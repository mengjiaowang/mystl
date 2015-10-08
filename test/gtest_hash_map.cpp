#include <gtest/gtest.h>
#include "../hash_map"

namespace mystl_test
{
  TEST(TestHashMap, TestHashMapConstructor)
  {
    mystl::hash_map<int, int> test_map;
    EXPECT_EQ(0, test_map.size());
  }

  TEST(TestHashMap, TestHashMapInsert1)
  {
    mystl::hash_map<int, int> test_map;
    test_map[1] = 1;
    test_map[2] = 2;
    test_map[3] = 3;
    test_map[4] = 4;
    EXPECT_EQ(4, test_map.size());
  }

  TEST(TestHashMap, TestHashMapInsert2)
  {
    mystl::hash_map<int, int> test_map;
    test_map[1] = 1;
    test_map[2] = 2;
    test_map[3] = 3;
    test_map[4] = 4;

    mystl::hash_map<int, int>::iterator iter;
    int key = 1, value = 1;
    for(iter = test_map.begin(); iter != test_map.end(); ++iter)
    {
      EXPECT_EQ(key++, iter->first);
      EXPECT_EQ(value++, iter->second);
    }
  }
}
