#include <gtest/gtest.h>
#include "../vector"
#include "../algorithm"

namespace mystl_test
{
  struct even_num
  {
    bool operator()(const unsigned int num)
    {
      return !(num & 1);
    }
  };

  struct odd_num
  {
    bool operator()(const unsigned int num)
    {
      return num & 1;
    }
  };

  TEST(TestAlgorithms, TestMerge)
  {
    mystl::vector<int> m1, m2, m;
    mystl::vector<int>::iterator merged_result;
    m1.push_back(1);
    m1.push_back(3);
    m1.push_back(5);
    m2.push_back(2);
    m2.push_back(4);
    m2.push_back(6);
    m.resize(m1.size() + m2.size());
    merged_result = mystl::merge(m1.begin(), m1.end(), m2.begin(), m2.end(), m.begin());

    for(size_t i = 1; i != 7; ++i)
    {
      EXPECT_EQ((int)i, m[i-1]);
    }
  }
}// end of namespace
