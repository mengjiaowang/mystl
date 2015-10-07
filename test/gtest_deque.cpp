#include <gtest/gtest.h>
#include "../vector"
#include "../deque"

namespace mystl_test
{

  TEST(TestDeque, TestConstructors)
  {
    mystl::deque<int, mystl::alloc, 8> d1;
    mystl::deque<int, mystl::alloc, 8> d2(10, 1);
    EXPECT_EQ(0, d1.size());
    mystl::deque<int, mystl::alloc, 8>::iterator iter;
    for(iter = d2.begin(); iter != d2.end(); ++iter)
    {
      EXPECT_EQ(1, *iter);
    }
  }

  TEST(TestDeque, TestPushBack)
  {
    mystl::deque<int, mystl::alloc, 8> d1;
    for(int i = 0; i != 10; ++i)
    {
      d1.push_back(10);
    }

    mystl::deque<int, mystl::alloc, 8>::iterator iter;
    for(iter = d1.begin(); iter != d1.end(); ++iter)
    {
      EXPECT_EQ(10, *iter);
    }
  }

  TEST(TestDeque, TestPushFront)
  {
    mystl::deque<int, mystl::alloc, 8> d1;
    for(int i = 0; i != 10; ++i)
    {
      d1.push_front(10);
    }

    mystl::deque<int, mystl::alloc, 8>::iterator iter;
    for(iter = d1.begin(); iter != d1.end(); ++iter)
    {
      EXPECT_EQ(10, *iter);
    }
  }

  TEST(TestDeque, TestClear)
  {
    mystl::deque<int, mystl::alloc, 8> d1;
    EXPECT_EQ(0, d1.size());
    for(int i = 0; i != 10; ++i)
    {
      d1.push_front(10);
    }
    EXPECT_EQ(10, d1.size());

    mystl::deque<int, mystl::alloc, 8>::iterator iter;
    for(iter = d1.begin(); iter != d1.end(); ++iter)
    {
      EXPECT_EQ(10, *iter);
    }
    d1.clear();
    EXPECT_EQ(0, d1.size());
  }

  TEST(TestDeque, TestPopBack)
  {
    mystl::deque<int, mystl::alloc, 8> d1;
    for(int i = 0; i != 10; ++i)
    {
      d1.push_front(i);
    }
    EXPECT_EQ(10, d1.size());

    mystl::deque<int, mystl::alloc, 8>::iterator iter;
    int index = 9;
    for(iter = d1.begin(); iter != d1.end(); ++iter)
    {
      EXPECT_EQ(index--, *iter);
    }

    for(int i = 0; i != 5; ++i)
    {
      d1.pop_back();
    }

    EXPECT_EQ(5, d1.size());
    index = 9;
    for(iter = d1.begin(); iter != d1.end(); ++iter)
    {
      EXPECT_EQ(index--, *iter);
    }
  }

  TEST(TestDeque, TestPopFront)
  {
    mystl::deque<int, mystl::alloc, 8> d1;
    for(int i = 0; i != 10; ++i)
    {
      d1.push_front(i);
    }
    EXPECT_EQ(10, d1.size());

    mystl::deque<int, mystl::alloc, 8>::iterator iter;
    int index = 9;
    for(iter = d1.begin(); iter != d1.end(); ++iter)
    {
      EXPECT_EQ(index--, *iter);
    }

    for(int i = 0; i != 5; ++i)
    {
      d1.pop_front();
    }

    EXPECT_EQ(5, d1.size());
    index = 4;
    for(iter = d1.begin(); iter != d1.end(); ++iter)
    {
      EXPECT_EQ(index--, *iter);
    }
  }

  TEST(TestDeque, TestErase1)
  {
    mystl::deque<int, mystl::alloc, 8> d1;
    for(int i = 0; i != 10; ++i)
    {
      d1.push_back(i);
    }
    mystl::deque<int, mystl::alloc, 8>::iterator iter;
    iter = d1.begin();
    d1.erase(iter);

    int index = 1;
    for(iter = d1.begin(); iter != d1.end(); ++iter)
    {
      EXPECT_EQ(index++, *iter);
    }
  }

  TEST(TestDeque, TestErase2)
  {
    mystl::deque<int, mystl::alloc, 8> d1;
    for(int i = 0; i != 10; ++i)
    {
      d1.push_back(i);
    }
    mystl::deque<int, mystl::alloc, 8>::iterator iter;
    iter = d1.begin();
    for(int i = 0; i != 5; ++i)
    {
      d1.erase(iter);
      ++iter;
    }

    int index = 5;
    for(iter = d1.begin(); iter != d1.end(); ++iter)
    {
      EXPECT_EQ(index++, *iter);
    }
  }

  TEST(TestDeque, TestErase3)
  {
    mystl::deque<int, mystl::alloc, 8> d1;
    for(int i = 0; i != 10; ++i)
    {
      d1.push_back(i);
    }
    mystl::deque<int, mystl::alloc, 8>::iterator iter1, iter2;
    iter1 = d1.begin();
    iter2 = d1.end();
    d1.erase(iter1, iter2);

    EXPECT_EQ(0, d1.size());
  }

  TEST(TestDeque, TestErase4)
  {
    mystl::deque<int, mystl::alloc, 8> d1;
    for(int i = 0; i != 10; ++i)
    {
      d1.push_back(i);
    }
    mystl::deque<int, mystl::alloc, 8>::iterator iter, iter1, iter2;
    iter1 = d1.begin();
    iter2 = d1.begin() + 5;
    d1.erase(iter1, iter2);

    EXPECT_EQ(5, d1.size());
    int index = 5;
    for(iter = d1.begin(); iter != d1.end(); ++iter)
    {
      EXPECT_EQ(index++, *iter);
    }
  }

  TEST(TestDeque, TestInsert)
  {
    mystl::deque<int, mystl::alloc, 8> d1;
    for(int i = 0; i != 10; ++i)
    {
      d1.push_back(i);
    }
    EXPECT_EQ(10, d1.size());
    d1.insert(d1.end(), 10);
    d1.insert(d1.end(), 11);
    d1.insert(d1.end(), 12);
    d1.insert(d1.end(), 13);
    d1.insert(d1.end(), 14);
    EXPECT_EQ(15, d1.size());

    mystl::deque<int, mystl::alloc, 8>::iterator iter;
    int index = 0;
    for(iter = d1.begin(); iter != d1.end(); ++iter)
    {
      EXPECT_EQ(index++, *iter);
    }
  }
}
