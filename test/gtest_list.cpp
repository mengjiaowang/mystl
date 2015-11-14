#include <gtest/gtest.h>
#include "../list"

namespace mystl_test
{
  TEST(TestList, TestConstructor)
  {
    mystl::list<int> li;
    EXPECT_TRUE(li.empty());
  }

  TEST(TestList, TestPushBackAndPopBack)
  {
    mystl::list<int> li;
    li.push_back(1);
    li.push_back(2);
    li.push_back(3);
    EXPECT_EQ(3, li.size());
    li.pop_back();
    li.pop_back();
    li.pop_back();
    EXPECT_EQ(0, li.size());
  }

  TEST(TestList, TestFrontAndBack)
  {
    mystl::list<int> li;
    li.push_back(1);
    li.push_back(2);
    li.push_back(3);
    EXPECT_EQ(1, li.front());
    EXPECT_EQ(3, li.back());
  }

  TEST(TestList, TestIterator)
  {
    mystl::list<int> li;
    li.push_back(1);
    li.push_back(2);
    li.push_back(3);

    mystl::list<int>::iterator iter = li.begin();
    EXPECT_EQ(1, *iter); ++iter;
    EXPECT_EQ(2, *iter); ++iter;
    EXPECT_EQ(3, *iter); ++iter;
  }

  TEST(TestList, TestInsert)
  {
    mystl::list<int> li;
    li.push_back(1);

    mystl::list<int>::iterator iter = li.begin();
    li.insert(iter, 0);
    EXPECT_EQ(1, *iter); --iter;
    EXPECT_EQ(0, *iter); --iter;
  }

  TEST(TestList, TestPushFrontAndPopFront)
  {
    mystl::list<int> li;
    li.push_back(1);
    li.push_back(2);
    li.push_back(3);
    li.push_front(0);
    EXPECT_EQ(0, li.front());
    li.pop_front();
    EXPECT_EQ(1, li.front());
  }

  TEST(TestList, TestErase)
  {
    mystl::list<int> li;
    li.push_back(1);
    li.push_back(2);
    li.push_back(3);
    mystl::list<int>::iterator iter = li.begin();
    li.erase(iter);
    EXPECT_EQ(2, li.size());
    iter = li.begin();
    EXPECT_EQ(2, *iter); ++iter;
    EXPECT_EQ(3, *iter); ++iter;
  }

  TEST(TestList, TestRemove)
  {
    mystl::list<int> li;
    li.push_back(1);
    li.push_back(2);
    li.push_back(3);
    mystl::list<int>::iterator iter = li.begin();
    li.remove(1);
    EXPECT_EQ(2, li.size());
    iter = li.begin();
    EXPECT_EQ(2, *iter); ++iter;
    EXPECT_EQ(3, *iter); ++iter;
  }

  TEST(TestList, TestClear)
  {
    mystl::list<int> li;
    li.push_back(1);
    li.push_back(2);
    li.push_back(3);
    li.clear();
    EXPECT_EQ(0, li.size());
  }

  TEST(TestList, TestUnique)
  {
    mystl::list<int> li;
    li.push_back(1);
    li.push_back(1);
    li.push_back(2);
    li.push_back(2);
    li.push_back(3);
    li.push_back(3);
    EXPECT_EQ(6, li.size());
    li.unique();
    EXPECT_EQ(3, li.size());
    mystl::list<int>::iterator iter = li.begin();
    EXPECT_EQ(1, *iter); ++iter;
    EXPECT_EQ(2, *iter); ++iter;
    EXPECT_EQ(3, *iter); ++iter;
  }

  TEST(TestList, TestSplice)
  {
    mystl::list<int> li1, li2;
    li1.push_back(1);
    li1.push_back(1);
    li1.push_back(2);
    li2.push_back(2);
    li2.push_back(3);
    li2.push_back(3);
    li1.splice(li1.end(), li2);
    EXPECT_EQ(6, li1.size());
    mystl::list<int>::iterator iter = li1.begin();
    EXPECT_EQ(1, *iter); ++iter;
    EXPECT_EQ(1, *iter); ++iter;
    EXPECT_EQ(2, *iter); ++iter;
    EXPECT_EQ(2, *iter); ++iter;
    EXPECT_EQ(3, *iter); ++iter;
    EXPECT_EQ(3, *iter); ++iter;
  }
}
