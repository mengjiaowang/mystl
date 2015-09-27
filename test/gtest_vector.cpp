#include <gtest/gtest.h>
#include "../vector"

namespace mystl_test
{
  TEST(TestVector, TestIntConstructor)
  {
    mystl::vector<int> v1;
    EXPECT_EQ(0, v1.size());

    mystl::vector<int> v2(2, 10);
    EXPECT_EQ(10, v2[0]);
    EXPECT_EQ(10, v2[1]);
    EXPECT_EQ(2, v2.size());
  }

  TEST(TestVector, TestDoubleConstructor)
  {
    mystl::vector<double> v1;
    EXPECT_EQ(0, v1.size());

    mystl::vector<double> v2(2, 1/3);
    EXPECT_DOUBLE_EQ(1/3, v2[0]);
    EXPECT_DOUBLE_EQ(1/3, v2[1]);
    EXPECT_EQ(2, v2.size());
  }

  class TestObject
  {
    public:
      TestObject(): data(0){}
      TestObject(int data): data(data){}
      TestObject(const TestObject &obj)
      {
        this->data = obj.data;
      }
      bool operator==(const TestObject &obj)
      {
        return obj.data == this->data;
      }
      int data;
  };

  TEST(TestVector, TestObjectConstructor)
  {
    mystl::vector<TestObject> v1;
    EXPECT_EQ(0, v1.size());

    TestObject obj(10);
    mystl::vector<TestObject> v2(2, obj);
    EXPECT_TRUE(obj == v2[0]);
    EXPECT_TRUE(obj ==  v2[1]);
    EXPECT_EQ(2, v2.size());
  }

  TEST(TestVector, DISABLED_TestNestedVectorConstructor)
  {
    mystl::vector<mystl::vector<int> > v1;
    EXPECT_EQ(0, v1.size());

    mystl::vector<int> v(2,10);
    mystl::vector<mystl::vector<int> > v2(2, v);
    EXPECT_EQ(2, v2.size());
  }

  TEST(TestVector, TestPopBackInt)
  {
    mystl::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    EXPECT_EQ(3, v.size());
    EXPECT_EQ(1, v[0]);
    EXPECT_EQ(2, v[1]);
    EXPECT_EQ(3, v[2]);
  }

  TEST(TestVector, TestPopBackObject)
  {
    mystl::vector<TestObject> v;
    TestObject obj1(1), obj2(2), obj3(3);
    v.push_back(obj1);
    v.push_back(obj2);
    v.push_back(obj3);

    EXPECT_EQ(3, v.size());
    EXPECT_TRUE(obj1 == v[0]);
    EXPECT_TRUE(obj2 == v[1]);
    EXPECT_TRUE(obj3 == v[2]);
  }

  TEST(TestVector, TestDoubleEmpty)
  {
    mystl::vector<double> v;
    EXPECT_TRUE(v.empty());
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    EXPECT_FALSE(v.empty());
  }

  TEST(TestVector, TestIntFrontAndBack)
  {
    mystl::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    EXPECT_EQ(1, v.front());
    EXPECT_EQ(3, v.back());
  }

  TEST(TestVector, TestObjectFrontAndBack)
  {
    mystl::vector<TestObject> v;
    TestObject obj1(1), obj2(2), obj3(3);
    v.push_back(obj1);
    v.push_back(obj2);
    v.push_back(obj3);

    EXPECT_TRUE(obj1 == v.front());
    EXPECT_TRUE(obj3 == v.back());
  }

  TEST(TestVector, TestIntResize)
  {
    mystl::vector<int> v;
    EXPECT_EQ(0, v.size());
    v.resize(10);
    EXPECT_EQ(10, v.size());
    v.resize(1);
    EXPECT_EQ(1, v.size());
  }

  TEST(TestVector, TestObjectResize)
  {
    mystl::vector<TestObject> v;
    EXPECT_EQ(0, v.size());
    v.resize(10);
    EXPECT_EQ(10, v.size());
    v.resize(1);
    EXPECT_EQ(1, v.size());
  }

  TEST(TestVector, TestClear)
  {
    mystl::vector<TestObject> v;
    TestObject obj1(1), obj2(2), obj3(3);
    EXPECT_TRUE(v.empty());
    v.push_back(obj1);
    v.push_back(obj2);
    v.push_back(obj3);
    EXPECT_FALSE(v.empty());
    v.clear();
    EXPECT_TRUE(v.empty());
  }

  TEST(TestVector, TestReserve)
  {
    mystl::vector<TestObject> v;
    EXPECT_EQ(0, v.size());
    v.reserve(10);
    EXPECT_EQ(0, v.size());
    EXPECT_EQ(10, v.capacity());

    TestObject obj1(1), obj2(2), obj3(3);
    v.push_back(obj1);
    v.push_back(obj2);
    v.push_back(obj3);

    EXPECT_EQ(3, v.size());
    EXPECT_EQ(10, v.capacity());
  }

  TEST(TestVector, TestCompare)
  {
    mystl::vector<int> v1(3,9), v2(3,9), v3(3,10), v4(3,10);
    EXPECT_TRUE(v1 == v2);
    EXPECT_TRUE(v3 == v4);
    EXPECT_FALSE(v1 != v2);
    EXPECT_FALSE(v3 != v4);
    EXPECT_FALSE(v1 == v3);
    EXPECT_FALSE(v2 == v4);
    EXPECT_TRUE(v1 < v3);
    EXPECT_FALSE(v1 > v3);
    EXPECT_FALSE(v3 < v1);
  }

  TEST(TestVector, TestSwap)
  {
    mystl::vector<int> v1(3,9), v2(4,10);
    EXPECT_EQ(3, v1.size());
    EXPECT_EQ(4, v2.size());
    v1.swap(v2);
    EXPECT_EQ(4, v1.size());
    EXPECT_EQ(3, v2.size());
  }

}// end of namespace
