#include <gtest/gtest.h>
#include "../mystl_rb_tree.h"
#include "../mystl_function.h"

namespace mystl_test
{
  TEST(TestRBTree, TestConstructor)
  {
    mystl::rb_tree<int, int, mystl::identity<int>, std::less<int> > tree;
    EXPECT_EQ(0, tree.size());
  }

  TEST(TestRBTree, TestInsert)
  {
    mystl::rb_tree<int, int, mystl::identity<int>, std::less<int> > tree;
    tree.insert_unique(10);
    EXPECT_TRUE(tree.__rb_verify());
    tree.insert_unique(7);
    tree.insert_unique(8);
    tree.insert_unique(15);
    tree.insert_unique(5);
    tree.insert_unique(6);
    EXPECT_TRUE(tree.__rb_verify());
    tree.insert_unique(11);
    tree.insert_unique(13);
    tree.insert_unique(12);
    EXPECT_TRUE(tree.__rb_verify());
  }

  TEST(TestRBTree, TestIterator)
  {
    mystl::rb_tree<int, int, mystl::identity<int>, std::less<int> > tree;
    tree.insert_unique(10);
    tree.insert_unique(7);
    tree.insert_unique(8);
    tree.insert_unique(15);
    tree.insert_unique(5);
    tree.insert_unique(6);
    tree.insert_unique(11);
    tree.insert_unique(13);
    tree.insert_unique(12);
    mystl::rb_tree<int, int, mystl::identity<int>, std::less<int> >::iterator iter;
    int res [] = {5,6,7,8,10,11,12,13,15};
    int index = 0;
    for(iter = tree.begin(); iter != tree.end(); ++iter)
    {
      EXPECT_EQ(res[index++], *iter);
    }
  }

  TEST(TestRBTree, TestFind)
  {
    mystl::rb_tree<int, int, mystl::identity<int>, std::less<int> > tree;
    tree.insert_unique(10);
    tree.insert_unique(7);
    tree.insert_unique(8);
    tree.insert_unique(15);
    tree.insert_unique(5);
    tree.insert_unique(6);
    tree.insert_unique(11);
    tree.insert_unique(13);
    tree.insert_unique(12);
    mystl::rb_tree<int, int, mystl::identity<int>, std::less<int> >::iterator iter;
    iter = tree.find(5);
    EXPECT_TRUE(iter != tree.end());
    iter = tree.find(6);
    EXPECT_TRUE(iter != tree.end());
    iter = tree.find(15);
    EXPECT_TRUE(iter != tree.end());
    iter = tree.find(150);
    EXPECT_FALSE(iter != tree.end());
  }

  TEST(TestRBTree, TestErase)
  {
    mystl::rb_tree<int, int, mystl::identity<int>, std::less<int> > tree;
    tree.insert_unique(10);
    tree.insert_unique(7);
    tree.insert_unique(8);
    tree.insert_unique(15);
    tree.insert_unique(5);
    tree.insert_unique(6);
    tree.insert_unique(11);
    tree.insert_unique(13);
    tree.insert_unique(12);
    mystl::rb_tree<int, int, mystl::identity<int>, std::less<int> >::iterator iter;
    iter = tree.begin();
    tree.erase(iter);
    EXPECT_TRUE(tree.__rb_verify());
    EXPECT_EQ(8, tree.size());

    int res [] = {6,7,8,10,11,12,13,15};
    int index = 0;
    for(iter = tree.begin(); iter != tree.end(); ++iter)
    {
      EXPECT_EQ(res[index++], *iter);
    }
  }
}
