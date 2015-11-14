#include <gtest/gtest.h>
#include <iostream>
#include "../mystl_numeric.h"
#include "../vector"

namespace mystl_test
{
  TEST(TestNumeric, TestAccumulate)
  {
    mystl::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    int res = 0;
    res = mystl::accumulate(v.begin(), v.end(), 0);
    EXPECT_EQ(res, 15);
    res = mystl::accumulate(v.begin(), v.end(), 10);
    EXPECT_EQ(res, 25);
    res = mystl::accumulate(v.begin(), v.end(), 0, mystl::minus<int>());
    EXPECT_EQ(res, -15);
    res = mystl::accumulate(v.begin(), v.end(), 10, mystl::minus<int>());
    EXPECT_EQ(res, -5);
  }

  TEST(TestNumeric, DISABLED_TestAdjacentDifference)
  {
    mystl::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    std::ostream_iterator<int> oite(std::cout, " ");
    mystl::adjacent_difference(v.begin(), v.end(), oite);
    std::cout << std::endl;
    mystl::adjacent_difference(v.begin(), v.end(), oite, mystl::plus<int>());
    std::cout << std::endl;
  }

  TEST(TestNumeric, TestInnerProduct)
  {
    mystl::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    int res = 0;
    res = mystl::inner_product(v.begin(), v.end(), v.begin(), 0);
    EXPECT_EQ(55, res);
    res = mystl::inner_product(v.begin(), v.end(), v.begin(), 10);
    EXPECT_EQ(65, res);
    res = mystl::inner_product(v.begin(), v.end(), v.begin(), 10,
        mystl::plus<int>(), mystl::minus<int>());
    EXPECT_EQ(10, res);
  }

  TEST(TestNumeric, TestPower)
  {
    int res = 0;
    res = mystl::power(10, 3);
    EXPECT_EQ(1000, res);
    res = mystl::power(10, 3, mystl::plus<int>());
    EXPECT_EQ(30, res);
  }

  TEST(TestNumeric, TestIota)
  {
    mystl::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    mystl::iota(v.begin(), v.end(), 10);
    for(size_t i = 0; i != v.size(); ++i)
    {
      EXPECT_EQ(10+i, v[i]);
    }
  }
}
