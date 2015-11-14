#include <gtest/gtest.h>
#include "../pair"

namespace mystl_test
{
  TEST(TestPair, TestConstructor)
  {
    mystl::pair<int, int> p1(1,1);
  }

  TEST(TestPair, TestValue)
  {
    mystl::pair<int, int> p1(1,1);
    EXPECT_EQ(1, p1.first);
    EXPECT_EQ(1, p1.second);
  }

  TEST(TestPair, TestMakePair)
  {
    mystl::pair<int, int> p1 = mystl::make_pair<int, int>(2,2);
    EXPECT_EQ(2, p1.first);
    EXPECT_EQ(2, p1.second);
  }

  TEST(TestPair, TestEqual)
  {
    mystl::pair<int, int> p1(1,1);
    mystl::pair<int, int> p2(2,2);
    EXPECT_TRUE(p1 == p1);
    EXPECT_TRUE(p2 == p2);
    EXPECT_FALSE(p1 == p2);
    EXPECT_FALSE(p2 == p1);
  }
}
