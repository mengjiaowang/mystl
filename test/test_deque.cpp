#include "../mystl_deque.h"
#include "../mystl_alloc.h"
#include <iostream>

void print_elements(mystl::deque<int, mystl::alloc, 8> &d);
int main()
{
  // test constructors
  mystl::deque<int, mystl::alloc, 8> d1;
  mystl::deque<int, mystl::alloc, 8> d2(10,1);

  // test iterator
  std::cout << "elements in d1: ";
  print_elements(d1);
  std::cout << "elements in d2: ";
  print_elements(d2);

  // test push_back
  for(int i = 0; i != 10; ++i)
  {
    d1.push_back(i);
    d2.push_back(i);
  }
  std::cout << "elements in d1: ";
  print_elements(d1);
  std::cout << "elements in d2: ";
  print_elements(d2);

  // test push_front
  for(int i = 0; i != 10; ++i)
  {
    d1.push_front(i);
    d2.push_front(i);
  }
  std::cout << "elements in d1: ";
  print_elements(d1);
  std::cout << "elements in d2: ";
  print_elements(d2);

  return 0;
}

void print_elements(mystl::deque<int, mystl::alloc, 8> &d)
{
  mystl::deque<int, mystl::alloc, 8>::iterator iter;
  for(iter = d.begin(); iter != d.end(); ++iter)
  {
    std::cout << *iter << " ";
  }
  std::cout << std::endl;
}
