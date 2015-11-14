#include <gtest/gtest.h>
#include "../slist"

namespace mystl_test
{
  TEST(TestSlist, TestConstructor)
  {
    mystl::slist<int> sl;
    EXPECT_TRUE(sl.empty());
  }

  TEST(TestSlist, TestPushFront)
  {
    mystl::slist<int> sl;
    sl.push_front(1);
    sl.push_front(2);
    sl.push_front(3);
    sl.push_front(4);
    EXPECT_EQ(4, sl.size());
  }

  TEST(TestSlist, TestIterator)
  {
    mystl::slist<int> sl;
    sl.push_front(1);
    sl.push_front(2);
    sl.push_front(3);
    sl.push_front(4);
    mystl::slist<int>::iterator iter = sl.begin();
    EXPECT_EQ(4, *iter); ++iter;
    EXPECT_EQ(3, *iter); ++iter;
    EXPECT_EQ(2, *iter); ++iter;
    EXPECT_EQ(1, *iter); ++iter;
  }

  TEST(TestSlist, TestEraseAfter)
  {
    mystl::slist<int> sl;
    sl.push_front(1);
    sl.push_front(2);
    sl.push_front(3);
    sl.push_front(4);
    mystl::slist<int>::iterator iter = sl.begin();
    sl.erase_after(iter);
    iter = sl.begin();
    EXPECT_EQ(4, *iter); ++iter;
    EXPECT_EQ(2, *iter); ++iter;
    EXPECT_EQ(1, *iter); ++iter;
  }
}
