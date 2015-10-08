#include <gtest/gtest.h>
#include "../map"

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
}
