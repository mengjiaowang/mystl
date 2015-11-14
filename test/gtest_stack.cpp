#include <gtest/gtest.h>
#include "../stack"
#include "../list"

namespace mystl_test
{
  TEST(TestStack, TestConstructor1)
  {
    mystl::stack<int> s;
    EXPECT_EQ(0, s.size());
  }

  TEST(TestStack, TestPush1)
  {
    mystl::stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    EXPECT_EQ(3, s.size());
  }

  TEST(TestStack, TestPop1)
  {
    mystl::stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    EXPECT_EQ(3, s.size());
    s.pop();
    EXPECT_EQ(2, s.size());
    s.pop();
    EXPECT_EQ(1, s.size());
    s.pop();
    EXPECT_EQ(0, s.size());
  }

  TEST(TestStack, TestConstructor2)
  {
    mystl::stack<int, mystl::list<int> > s;
    EXPECT_EQ(0, s.size());
  }

  TEST(TestStack, TestPush2)
  {
    mystl::stack<int, mystl::list<int> > s;
    s.push(1);
    s.push(2);
    s.push(3);
    EXPECT_EQ(3, s.size());
  }

  TEST(TestStack, TestPop2)
  {
    mystl::stack<int, mystl::list<int> > s;
    s.push(1);
    s.push(2);
    s.push(3);
    EXPECT_EQ(3, s.size());
    s.pop();
    EXPECT_EQ(2, s.size());
    s.pop();
    EXPECT_EQ(1, s.size());
    s.pop();
    EXPECT_EQ(0, s.size());
  }

}
