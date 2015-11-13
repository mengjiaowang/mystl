#include <gtest/gtest.h>
#include "../mystl_hash_set.h"
#include "../hash_multiset"

namespace mystl_test
{
  TEST(TestHashSet, TestHashSetConstructor)
  {
    mystl::hash_set<int> test_hs;
    EXPECT_EQ(0, test_hs.size());
  }

  TEST(TestHashSet, TestHashSetEmpty)
  {
    mystl::hash_set<int> test_hs;
    EXPECT_TRUE(test_hs.empty());
  }

  TEST(TestHashSet, TestHashSetInsert1)
  {
    mystl::hash_set<int> test_hs;
    test_hs.insert(1);
    test_hs.insert(2);
    test_hs.insert(3);
  }

  TEST(TestHashSet, TestHashSetInsert2)
  {
    mystl::hash_set<int> test_hs;
    test_hs.insert(1);
    test_hs.insert(2);
    test_hs.insert(3);
    mystl::pair<mystl::hash_set<int>::iterator,
      bool> p = test_hs.insert(1);
    EXPECT_FALSE(p.second);
  }

  TEST(TestHashSet, TestHashSetSize)
  {
    mystl::hash_set<int> test_hs;
    test_hs.insert(1);
    test_hs.insert(2);
    test_hs.insert(3);
    EXPECT_EQ(3, test_hs.size());
  }

  TEST(TestHashMultiSet, TestHashMultiSetConstructor)
  {
    mystl::hash_multiset<int> test_hms;
    EXPECT_EQ(0, test_hms.size());
  }

  TEST(TestHashMultiSet, TestHashMultiSetInsert)
  {
    mystl::hash_multiset<int> test_hms;
    test_hms.insert(1);
    test_hms.insert(1);
    test_hms.insert(2);
    test_hms.insert(2);
    test_hms.insert(3);
    EXPECT_EQ(5, test_hms.size());
  }
}

