#include <gtest/gtest.h>
#include "../mystl_hashtable.h"
#include "../mystl_function.h"
#include "../mystl_hash_fun.h"

namespace mystl_test
{
  TEST(TestHashtable, TestConstructor)
  {
    mystl::hashtable<int, int, mystl::hash<int>, mystl::identity<int>,
      std::equal_to<int> > test_ht(5, mystl::hash<int>(), std::equal_to<int>());
  }

  TEST(TestHashtable, TestInsertUnique)
  {
    mystl::hashtable<int, int, mystl::hash<int>, mystl::identity<int>,
      std::equal_to<int> > test_ht(5, mystl::hash<int>(), std::equal_to<int>());

    test_ht.insert_unique(1);
    test_ht.insert_unique(63);
    test_ht.insert_unique(108);

    EXPECT_EQ(3, test_ht.size());
  }

  TEST(TestHashtable, TestIterator)
  {
    mystl::hashtable<int, int, mystl::hash<int>, mystl::identity<int>,
      std::equal_to<int> > test_ht(5, mystl::hash<int>(), std::equal_to<int>());

    test_ht.insert_unique(1);
    test_ht.insert_unique(63);
    test_ht.insert_unique(108);

    mystl::hashtable<int, int, mystl::hash<int>, mystl::identity<int>,
      std::equal_to<int> >::iterator iter = test_ht.begin();

    EXPECT_EQ(1, *iter); ++iter;
    EXPECT_EQ(108, *iter); ++iter;
    EXPECT_EQ(63, *iter);
  }

  TEST(TestHashtable, TestInsertEqual)
  {
    mystl::hashtable<int, int, mystl::hash<int>, mystl::identity<int>,
      std::equal_to<int> > test_ht(5, mystl::hash<int>(), std::equal_to<int>());

    test_ht.insert_equal(1);
    test_ht.insert_equal(63);
    test_ht.insert_equal(108);
    test_ht.insert_equal(1);
    test_ht.insert_equal(63);
    test_ht.insert_equal(108);

    mystl::hashtable<int, int, mystl::hash<int>, mystl::identity<int>,
      std::equal_to<int> >::iterator iter = test_ht.begin();

    EXPECT_EQ(6, test_ht.size());
  }

  TEST(TestHashtable, TestEraseAfterInsertUnique)
  {
    mystl::hashtable<int, int, mystl::hash<int>, mystl::identity<int>,
      std::equal_to<int> > test_ht(5, mystl::hash<int>(), std::equal_to<int>());

    test_ht.insert_unique(1);
    test_ht.insert_unique(63);
    test_ht.insert_unique(108);

    test_ht.erase(1);
    test_ht.erase(63);
    EXPECT_EQ(1, test_ht.size());

    mystl::hashtable<int, int, mystl::hash<int>, mystl::identity<int>,
      std::equal_to<int> >::iterator iter = test_ht.begin();
    EXPECT_EQ(108, *iter);
  }

  TEST(TestHashtable, TestEraseAfterInsertEqual)
  {
    mystl::hashtable<int, int, mystl::hash<int>, mystl::identity<int>,
      std::equal_to<int> > test_ht(5, mystl::hash<int>(), std::equal_to<int>());

    test_ht.insert_equal(1);
    test_ht.insert_equal(63);
    test_ht.insert_equal(108);
    test_ht.insert_equal(1);
    test_ht.insert_equal(63);
    test_ht.insert_equal(108);

    test_ht.erase(1);
    test_ht.erase(63);
    EXPECT_EQ(2, test_ht.size());

    mystl::hashtable<int, int, mystl::hash<int>, mystl::identity<int>,
      std::equal_to<int> >::iterator iter = test_ht.begin();

    EXPECT_EQ(108, *iter); ++iter;
    EXPECT_EQ(108, *iter);
  }

  TEST(TestHashtable, TestFind)
  {
    mystl::hashtable<int, int, mystl::hash<int>, mystl::identity<int>,
      std::equal_to<int> > test_ht(5, mystl::hash<int>(), std::equal_to<int>());

    test_ht.insert_unique(1);
    test_ht.insert_unique(63);
    test_ht.insert_unique(108);

    mystl::hashtable<int, int, mystl::hash<int>, mystl::identity<int>,
      std::equal_to<int> >::iterator iter;

    iter = test_ht.find(1);
    EXPECT_TRUE(iter != test_ht.end());
    iter = test_ht.find(63);
    EXPECT_TRUE(iter != test_ht.end());
    iter = test_ht.find(108);
    EXPECT_TRUE(iter != test_ht.end());
    iter = test_ht.find(2);
    EXPECT_FALSE(iter != test_ht.end());
  }

  TEST(TestHashtable, TestCount1)
  {
    mystl::hashtable<int, int, mystl::hash<int>, mystl::identity<int>,
      std::equal_to<int> > test_ht(5, mystl::hash<int>(), std::equal_to<int>());

    test_ht.insert_unique(1);
    test_ht.insert_unique(63);
    test_ht.insert_unique(108);

    EXPECT_EQ(1, test_ht.count(1));
    EXPECT_EQ(1, test_ht.count(63));
    EXPECT_EQ(1, test_ht.count(108));
  }

  TEST(TestHashtable, TestCount2)
  {
    mystl::hashtable<int, int, mystl::hash<int>, mystl::identity<int>,
      std::equal_to<int> > test_ht(5, mystl::hash<int>(), std::equal_to<int>());

    test_ht.insert_unique(1);
    test_ht.insert_unique(63);
    test_ht.insert_unique(108);
    test_ht.insert_unique(1);
    test_ht.insert_unique(63);
    test_ht.insert_unique(108);

    EXPECT_EQ(1, test_ht.count(1));
    EXPECT_EQ(1, test_ht.count(63));
    EXPECT_EQ(1, test_ht.count(108));
  }

  TEST(TestHashtable, TestCount3)
  {
    mystl::hashtable<int, int, mystl::hash<int>, mystl::identity<int>,
      std::equal_to<int> > test_ht(5, mystl::hash<int>(), std::equal_to<int>());

    test_ht.insert_equal(1);
    test_ht.insert_equal(63);
    test_ht.insert_equal(108);
    test_ht.insert_equal(1);
    test_ht.insert_equal(63);
    test_ht.insert_equal(108);

    EXPECT_EQ(2, test_ht.count(1));
    EXPECT_EQ(2, test_ht.count(63));
    EXPECT_EQ(2, test_ht.count(108));
  }

} // end of namespace mystl_test
