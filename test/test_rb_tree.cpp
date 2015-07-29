#include "../mystl_rb_tree.h"
#include <iostream>
#include "../mystl_function.h"

int main()
{
  mystl::rb_tree<int, int, mystl::identity<int>, std::less<int> > tree;
  // test size
  std::cout << "size = " << tree.size() << std::endl;
  // test insert
  std::cout << "insert 10" << std::endl;
  tree.insert_unique(10);
  std::cout << "verified = " << tree.__rb_verify() << std::endl;

  std::cout << "insert 7" << std::endl;
  tree.insert_unique(7);
  std::cout << "verified = " << tree.__rb_verify() << std::endl;

  std::cout << "insert 8" << std::endl;
  tree.insert_unique(8);
  std::cout << "verified = " << tree.__rb_verify() << std::endl;

  std::cout << "insert 15" << std::endl;
  tree.insert_unique(15);
  std::cout << "verified = " << tree.__rb_verify() << std::endl;

  std::cout << "insert 5" << std::endl;
  tree.insert_unique(5);
  std::cout << "verified = " << tree.__rb_verify() << std::endl;

  std::cout << "insert 6" << std::endl;
  tree.insert_unique(6);
  std::cout << "verified = " << tree.__rb_verify() << std::endl;

  std::cout << "insert 11" << std::endl;
  tree.insert_unique(11);
  std::cout << "verified = " << tree.__rb_verify() << std::endl;

  std::cout << "insert 13" << std::endl;
  tree.insert_unique(13);
  std::cout << "verified = " << tree.__rb_verify() << std::endl;

  std::cout << "insert 12" << std::endl;
  tree.insert_unique(12);
  std::cout << "verified = " << tree.__rb_verify() << std::endl;

  // test iterator
  mystl::rb_tree<int, int, mystl::identity<int>, std::less<int> >::iterator it;
  it = tree.begin(); std::cout << *it << std::endl;
  ++it; std::cout << *it << std::endl;
  ++it; std::cout << *it << std::endl;
  ++it; std::cout << *it << std::endl;

  for(it = tree.begin(); it != tree.end(); ++it)
  {
    std::cout << *it << " ";
  }
  std::cout << std::endl;

  // test find
  it = tree.find(5);
  if(it != tree.end())
    std::cout << "5 found in the rb_tree" << std::endl;
  else
    std::cout << "5 not found in the rb_tree" << std::endl;

  it = tree.find(6);
  if(it != tree.end())
    std::cout << "6 found in the rb_tree" << std::endl;
  else
    std::cout << "6 not found in the rb_tree" << std::endl;

  it = tree.find(14);
  if(it != tree.end())
    std::cout << "14 found in the rb_tree" << std::endl;
  else
    std::cout << "14 not found in the rb_tree" << std::endl;

  return 0;
}
