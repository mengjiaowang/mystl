#include <gtest/gtest.h>
#include "../hash_map"
#include "../hash_multimap"

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

  TEST(TestHashMultiMap, TestHashMultiMapEmpty)
  {
    mystl::hash_multimap<int,int> test_map;
    EXPECT_TRUE(test_map.empty());
  }

  TEST(TestHashMultiMap, TestHashMultiMapInsert)
  {
    mystl::hash_multimap<int,int> test_map;
    test_map.insert(mystl::pair<int,int>(1,11));
    test_map.insert(mystl::pair<int,int>(2,12));
    test_map.insert(mystl::pair<int,int>(2,122));
    test_map.insert(mystl::pair<int,int>(3,13));
    test_map.insert(mystl::pair<int,int>(4,14));
    EXPECT_EQ(5, test_map.size());
  }

  TEST(TestHashMultiMap, TestHashMultiMapIterator)
  {
    mystl::hash_multimap<int,int> test_map;
    test_map.insert(mystl::pair<int,int>(1,11));
    test_map.insert(mystl::pair<int,int>(2,12));
    test_map.insert(mystl::pair<int,int>(2,122));
    test_map.insert(mystl::pair<int,int>(3,13));
    test_map.insert(mystl::pair<int,int>(4,14));

    mystl::hash_multimap<int,int>::iterator iter;
    iter = test_map.begin();
    EXPECT_EQ(1, iter->first);
    EXPECT_EQ(11, iter->second);
    ++iter;

    EXPECT_EQ(2, iter->first);
    EXPECT_EQ(12, iter->second);
    ++iter;

    EXPECT_EQ(2, iter->first);
    EXPECT_EQ(122, iter->second);
    ++iter;

    EXPECT_EQ(3, iter->first);
    EXPECT_EQ(13, iter->second);
    ++iter;

    EXPECT_EQ(4, iter->first);
    EXPECT_EQ(14, iter->second);
  }

  TEST(TestHashMultiMap, TestHashMultiMapFind)
  {
    mystl::hash_multimap<int,int> test_map;
    test_map.insert(mystl::pair<int,int>(1,11));
    test_map.insert(mystl::pair<int,int>(2,12));
    test_map.insert(mystl::pair<int,int>(2,122));
    test_map.insert(mystl::pair<int,int>(3,13));
    test_map.insert(mystl::pair<int,int>(4,14));

    mystl::hash_multimap<int,int>::iterator iter;
    iter = test_map.find(1);
    EXPECT_TRUE(iter != test_map.end());
    iter = test_map.find(10);
    EXPECT_TRUE(iter == test_map.end());
  }

  TEST(TestHashMultiMap, TestHashMultiMapErase)
  {
    mystl::hash_multimap<int,int> test_map;
    test_map.insert(mystl::pair<int,int>(1,11));
    test_map.insert(mystl::pair<int,int>(2,12));
    test_map.insert(mystl::pair<int,int>(2,122));
    test_map.insert(mystl::pair<int,int>(3,13));
    test_map.insert(mystl::pair<int,int>(4,14));

    EXPECT_EQ(5, test_map.size());
    test_map.erase(1);
    EXPECT_EQ(4, test_map.size());
    test_map.erase(2);
    EXPECT_EQ(2, test_map.size());
  }
}
