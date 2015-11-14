#include <gtest/gtest.h>
#include "../queue"

namespace mystl_test
{
  TEST(TestPriorityQueue, TestConstructor)
  {
    mystl::priority_queue<int> pq;
  }

  TEST(TestPriorityQueue, TestPush)
  {
    mystl::priority_queue<int> pq;
    pq.push(1);
    pq.push(2);
    pq.push(3);
    pq.push(4);
    pq.push(5);
    EXPECT_EQ(5, pq.size());
  }

  TEST(TestPriorityQueue, TestPop)
  {
    mystl::priority_queue<int> pq;
    pq.push(1);
    pq.push(2);
    pq.push(3);
    pq.push(4);
    pq.push(5);
    EXPECT_EQ(5, pq.top());
    pq.pop();
    EXPECT_EQ(4, pq.size());
  }
}
