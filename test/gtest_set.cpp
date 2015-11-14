#include <gtest/gtest.h>
#include "../set"
#include "../multiset"

namespace mystl_test
{
  TEST(TestSet, TestConstructor)
  {
    int num [] = {1, 2, 3, 4, 5};
    mystl::set<int> test_set(num, num + 5);
    EXPECT_EQ(5, test_set.size());
  }

  TEST(TestSet, TestIterator)
  {
    int num [] = {1, 2, 3, 4, 5};
    mystl::set<int> test_set(num, num + 5);
    mystl::set<int>::iterator iter;
    int index = 0;
    for(iter = test_set.begin(); iter != test_set.end(); ++iter)
    {
      EXPECT_EQ(num[index++], *iter);
    }
  }

  TEST(TestSet, TestInsert1)
  {
    int num [] = {1, 2, 3, 4, 5, 6, 7};
    mystl::set<int> test_set(num, num + 5);
    test_set.insert(6);
    test_set.insert(7);
    EXPECT_EQ(7, test_set.size());
    mystl::set<int>::iterator iter;
    int index = 0;
    for(iter = test_set.begin(); iter != test_set.end(); ++iter)
    {
      EXPECT_EQ(num[index++], *iter);
    }
  }

  TEST(TestSet, TestInsert2)
  {
    int num [] = {1, 2, 3, 4, 5, 6, 7};
    mystl::set<int> test_set(num, num + 5);
    test_set.insert(num + 5, num + 7);
    EXPECT_EQ(7, test_set.size());
    mystl::set<int>::iterator iter;
    int index = 0;
    for(iter = test_set.begin(); iter != test_set.end(); ++iter)
    {
      EXPECT_EQ(num[index++], *iter);
    }
  }

  TEST(TestSet, TestFind)
  {
    int num [] = {1, 2, 3, 4, 5, 6, 7};
    mystl::set<int> test_set(num, num + 7);
    mystl::set<int>::iterator iter;
    iter = test_set.find(1);
    EXPECT_TRUE(iter != test_set.end());
    iter = test_set.find(10);
    EXPECT_TRUE(iter == test_set.end());
  }

  TEST(TestMultiSet, TestConstructor)
  {
    mystl::multiset<int> test_multiset;
    EXPECT_EQ(0, test_multiset.size());
  }

  TEST(TestMultiSet, TestInsert)
  {
    mystl::multiset<int> test_multiset;
    test_multiset.insert(1);
    test_multiset.insert(2);
    test_multiset.insert(3);
    test_multiset.insert(3);
    test_multiset.insert(3);
    EXPECT_EQ(5, test_multiset.size());
  }

  TEST(TestMultiSet, TestIterator)
  {
    mystl::multiset<int> test_multiset;
    test_multiset.insert(1);
    test_multiset.insert(2);
    test_multiset.insert(3);
    test_multiset.insert(3);
    test_multiset.insert(3);
    int num[] = {1, 2, 3, 3, 3};
    int index = 0;

    mystl::multiset<int>::iterator iter;
    for(iter = test_multiset.begin(); iter != test_multiset.end(); ++iter)
    {
      EXPECT_EQ(num[index++], *iter);
    }
  }
/*
  TEST(TestMultiSet, TestFind)
  {
    mystl::multiset<int> test_multiset;
    test_multiset.insert(1);
    test_multiset.insert(2);
    test_multiset.insert(3);
    test_multiset.insert(3);
    test_multiset.insert(3);
    mystl::multiset<int>::iterator iter;
    iter = test_multiset.find(1);
    EXPECT_TRUE(iter != test_multiset.end());
    iter = test_multiset.find(2);
    EXPECT_TRUE(iter != test_multiset.end());
    iter = test_multiset.find(3);
    EXPECT_TRUE(iter != test_multiset.end());
    iter = test_multiset.find(4);
    EXPECT_FALSE(iter != test_multiset.end());
  }
*/
}
