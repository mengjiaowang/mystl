#include <gtest/gtest.h>
#include "../vector"
#include "../list"
#include "../pair"
#include "../algorithm"

namespace mystl_test
{

  TEST(TestAlgorithmBase, TestSwap)
  {
    mystl::vector<int> a;
    a.push_back(0);
    a.push_back(1);
    mystl::vector<int>::iterator iter1, iter2;

    iter2 = a.begin();
    iter1 = iter2++;

    EXPECT_EQ(0, *iter1);
    EXPECT_EQ(1, *iter2);

    mystl::swap(iter1, iter2);

    EXPECT_EQ(1, *iter1);
    EXPECT_EQ(0, *iter2);

    mystl::swap(iter1, iter2);

    EXPECT_EQ(0, *iter1);
    EXPECT_EQ(1, *iter2);
  }

  TEST(TestAlgorithmBase, TestMaxAndMinInt)
  {
    int a = 0, b = 1;
    int max = mystl::max(a, b);
    int min = mystl::min(a, b);

    EXPECT_EQ(1, max);
    EXPECT_EQ(0, min);
  }

  TEST(TestAlgorithmBase, TestMaxAndMinDouble)
  {
    double a = 0, b = 1;
    double max = mystl::max(a, b);
    double min = mystl::min(a, b);

    EXPECT_DOUBLE_EQ(1, max);
    EXPECT_DOUBLE_EQ(0, min);
  }

  TEST(TestAlgorithmBase, TestEqual)
  {
    mystl::vector<int> a, b;

    a.push_back(0);
    a.push_back(1);
    a.push_back(2);
    a.push_back(4);

    b.push_back(0);
    b.push_back(1);
    b.push_back(2);
    b.push_back(4);

    EXPECT_TRUE(mystl::equal(a.begin(), a.end(), a.begin()));
    EXPECT_TRUE(mystl::equal(a.begin(), a.end(), b.begin()));
    EXPECT_TRUE(mystl::equal(b.begin(), b.end(), a.begin()));

    b.push_back(5);

    EXPECT_TRUE(mystl::equal(a.begin(), a.end(), b.begin()));

    a.push_back(6);

    EXPECT_FALSE(mystl::equal(a.begin(), a.end(), b.begin()));
    EXPECT_FALSE(mystl::equal(b.begin(), b.end(), a.begin()));
  }

  TEST(TestAlgorithmBase, TestMismatch)
  {
    mystl::vector<int> a, b;

    a.push_back(0);
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);

    b.push_back(0);
    b.push_back(1);
    b.push_back(2);
    b.push_back(4);

    mystl::pair<mystl::vector<int>::iterator, mystl::vector<int>::iterator>
    mismatch_result = mystl::mismatch(a.begin(), a.end(), b.begin());

    EXPECT_EQ(3, *mismatch_result.first);
    EXPECT_EQ(4, *mismatch_result.second);
  }

  TEST(TestAlgorithmBase, TestLexicographicalCompare)
  {
    mystl::vector<int> a, b;

    a.push_back(0);
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);

    b.push_back(0);
    b.push_back(1);
    b.push_back(2);
    b.push_back(4);

    bool result;
    result = mystl::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
    EXPECT_TRUE(result);
    result = mystl::lexicographical_compare(b.begin(), b.end(), a.begin(), a.end());
    EXPECT_FALSE(result);
    result = mystl::lexicographical_compare(a.begin(), a.end(), a.begin(), a.end());
    EXPECT_FALSE(result);
  }

  TEST(TestAlgorithmBase, TestCopy)
  {
    char chr1[6] = "hello";
    char chr2[6] = "xxxxx";
    mystl::copy(chr1, chr1+6, chr2);
    for(size_t i = 0; i != 6; ++i)
    {
      EXPECT_EQ(chr1[i], chr2[i]);
    }
  }

  TEST(TestAlgorithmBase, TestCopyBackward)
  {
    char chr1[6] = "hello";
    char chr2[6] = "xxxxx";
    mystl::copy_backward(chr1, chr1+6, chr2+6);
    for(size_t i = 0; i != 6; ++i)
    {
      EXPECT_EQ(chr1[i], chr2[i]);
    }
  }

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

  TEST(TestAlgorithms, TestPartitionEvenNumber)
  {
    mystl::vector<int> m;
    m.push_back(1);
    m.push_back(2);
    m.push_back(3);
    m.push_back(4);
    m.push_back(5);
    m.push_back(6);

    mystl::partition(m.begin(), m.end(), even_num());

    EXPECT_EQ(6, m[0]);
    EXPECT_EQ(2, m[1]);
    EXPECT_EQ(4, m[2]);
    EXPECT_EQ(3, m[3]);
    EXPECT_EQ(5, m[4]);
    EXPECT_EQ(1, m[5]);
  }

  TEST(TestAlgorithms, TestPartitionOddNumber)
  {
    mystl::vector<int> m;
    m.push_back(1);
    m.push_back(2);
    m.push_back(3);
    m.push_back(4);
    m.push_back(5);
    m.push_back(6);

    mystl::partition(m.begin(), m.end(), odd_num());

    EXPECT_EQ(1, m[0]);
    EXPECT_EQ(5, m[1]);
    EXPECT_EQ(3, m[2]);
    EXPECT_EQ(4, m[3]);
    EXPECT_EQ(2, m[4]);
    EXPECT_EQ(6, m[5]);
  }

  TEST(TestAlgorithms, TestReserveForVector)
  {
    mystl::vector<int> m;
    m.push_back(1);
    m.push_back(2);
    m.push_back(3);
    m.push_back(4);
    m.push_back(5);
    m.push_back(6);

    mystl::reverse(m.begin(), m.end());

    EXPECT_EQ(6, m[0]);
    EXPECT_EQ(5, m[1]);
    EXPECT_EQ(4, m[2]);
    EXPECT_EQ(3, m[3]);
    EXPECT_EQ(2, m[4]);
    EXPECT_EQ(1, m[5]);
  }

  TEST(TestAlgorithms, TestSetUnion)
  {
    int ia1[6] = {1, 3, 5, 7, 9, 11};
    int ia2[6] = {1, 2, 3, 5, 8, 13};
    int ia3[9] = {1, 2, 3, 5, 7, 8, 9, 11, 13};

    mystl::set<int> S1(ia1, ia1+6);
    mystl::set<int> S2(ia2, ia2+6);
    mystl::vector<int> S3(9);

    // test set_union
    mystl::set_union(S1.begin(), S1.end(), S2.begin(), S2.end(), S3.begin());

    mystl::vector<int>::iterator iter = S3.begin();
    int index = 0;
    for(iter = S3.begin(); iter !=S3.end(); ++iter)
    {
      EXPECT_EQ(ia3[index++], *iter);
    }
  }

  TEST(TestAlgorithms, TestSetIntersection)
  {
    int ia1[6] = {1, 3, 5, 7, 9, 11};
    int ia2[6] = {1, 2, 3, 5, 8, 13};
    int ia3[3] = {1, 3, 5};

    mystl::set<int> S1(ia1, ia1+6);
    mystl::set<int> S2(ia2, ia2+6);
    mystl::vector<int> S3(3);

    // test set_union
    mystl::set_intersection(S1.begin(), S1.end(), S2.begin(), S2.end(), S3.begin());

    mystl::vector<int>::iterator iter = S3.begin();
    int index = 0;
    for(iter = S3.begin(); iter !=S3.end(); ++iter)
    {
      EXPECT_EQ(ia3[index++], *iter);
    }
  }

  TEST(TestAlgorithms, TestSetDifference)
  {
    int ia1[6] = {1, 3, 5, 7, 9, 11};
    int ia2[6] = {1, 2, 3, 5, 8, 13};
    int ia3[3] = {7, 9, 11};

    mystl::set<int> S1(ia1, ia1+6);
    mystl::set<int> S2(ia2, ia2+6);
    mystl::vector<int> S3(3);

    // test set_union
    mystl::set_difference(S1.begin(), S1.end(), S2.begin(), S2.end(), S3.begin());

    mystl::vector<int>::iterator iter = S3.begin();
    int index = 0;
    for(iter = S3.begin(); iter !=S3.end(); ++iter)
    {
      EXPECT_EQ(ia3[index++], *iter);
    }
  }

  TEST(TestAlgorithms, TestSetSymmetricDifference)
  {
    int ia1[6] = {1, 3, 5, 7, 9, 11};
    int ia2[6] = {1, 2, 3, 5, 8, 13};
    int ia3[6] = {2, 7, 8, 9, 11, 13};

    mystl::set<int> S1(ia1, ia1+6);
    mystl::set<int> S2(ia2, ia2+6);
    mystl::vector<int> S3(6);

    // test set_union
    mystl::set_symmetric_difference(S1.begin(), S1.end(), S2.begin(), S2.end(), S3.begin());

    mystl::vector<int>::iterator iter = S3.begin();
    int index = 0;
    for(iter = S3.begin(); iter !=S3.end(); ++iter)
    {
      EXPECT_EQ(ia3[index++], *iter);
    }
  }

  TEST(TestSort, TestInsertionSort)
  {
    int arr [] = {3,1,2,4,6,5,9,7,8,0};
    mystl::__insertion_sort(arr, arr+10);
    for(int i = 0; i != 10; ++i)
    {
      EXPECT_EQ(i, arr[i]);
    }
  }

  TEST(TestSort, TestPartialSort1)
  {
    int arr [] = {3,1,2,4,6,5,9,7,8,0};
    mystl::partial_sort(arr, arr+10, arr+10);
    for(int i = 0; i != 10; ++i)
    {
      EXPECT_EQ(i, arr[i]);
    }
  }

  TEST(TestSort, TestPartialSort2)
  {
    int arr [] = {3,1,2,4,6,5,9,7,8,0};
    mystl::partial_sort(arr, arr+5, arr+10);
    for(int i = 0; i != 5; ++i)
    {
      EXPECT_EQ(i, arr[i]);
    }
  }

  TEST(TestSort, TestSort)
  {
    int arr [] = {3,1,2,4,6,5,9,7,8,0};
    mystl::sort(arr, arr+10);
    for(int i = 0; i != 10; ++i)
    {
      EXPECT_EQ(i, arr[i]);
    }
  }

}// end of namespace
