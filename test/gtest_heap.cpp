#include <gtest/gtest.h>
#include "../vector"
#include "../mystl_heap.h"

namespace mystl_test
{

  TEST(TestHeap, TestPushHeap)
  {
    mystl::vector<int> test_heap;

    test_heap.push_back(68);
    test_heap.push_back(31);
    test_heap.push_back(65);
    test_heap.push_back(21);
    test_heap.push_back(24);
    test_heap.push_back(32);
    test_heap.push_back(26);
    test_heap.push_back(19);
    test_heap.push_back(16);
    test_heap.push_back(13);
    test_heap.push_back(50);

    mystl::push_heap(test_heap.begin(), test_heap.end());

    int res [] = {68,50,65,21,31,32,26,19,16,13,24};

    for(unsigned int i = 0; i != test_heap.size(); ++i)
    {
      EXPECT_EQ(res[i], test_heap[i]);
    }
  }

  TEST(TestHeap, TestPopHeap)
  {
    mystl::vector<int> test_heap;

    test_heap.push_back(68);
    test_heap.push_back(31);
    test_heap.push_back(65);
    test_heap.push_back(21);
    test_heap.push_back(24);
    test_heap.push_back(32);
    test_heap.push_back(26);
    test_heap.push_back(19);
    test_heap.push_back(16);
    test_heap.push_back(13);
    test_heap.push_back(50);

    mystl::push_heap(test_heap.begin(), test_heap.end());
    mystl::pop_heap(test_heap.begin(), test_heap.end());
    test_heap.pop_back();

    int res [] = {65,50,32,21,31,24,26,19,16,13};

    for(unsigned int i = 0; i != test_heap.size(); ++i)
    {
      EXPECT_EQ(res[i], test_heap[i]);
    }
  }

  TEST(TestHeap, TestHeapSort)
  {
    mystl::vector<int> test_heap;

    test_heap.push_back(68);
    test_heap.push_back(31);
    test_heap.push_back(65);
    test_heap.push_back(21);
    test_heap.push_back(24);
    test_heap.push_back(32);
    test_heap.push_back(26);
    test_heap.push_back(19);
    test_heap.push_back(16);
    test_heap.push_back(13);
    test_heap.push_back(50);

    mystl::sort_heap(test_heap.begin(), test_heap.end());

    int res []= {13,16,19,21,24,26,31,32,50,65};
    for(unsigned int i = 0; i != test_heap.size() - 1; ++i)
    {
      EXPECT_EQ(res[i], test_heap[i]);
    }
  }
}
