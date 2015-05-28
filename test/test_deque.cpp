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

  // test clear
  d1.clear();
  std::cout << "elements in d1 after clear(): ";
  print_elements(d1);

  // test pop_back
  for(int i = 0; i != 10; ++i)
  {
    d2.pop_back();
  }
  std::cout << "elements in d2: ";
  print_elements(d2);

  // test pop_front
  for(int i = 0; i != 10; ++i)
  {
    d2.pop_front();
  }
  std::cout << "elements in d2: ";
  print_elements(d2);

  // test erase 1
  d2.clear();
  for(int i = 0; i != 10; ++i)
  {
    d2.push_back(i);
  }
  std::cout << "elements in d2 before erase: ";
  print_elements(d2);
  mystl::deque<int, mystl::alloc, 8>::iterator iter;
  iter = d2.begin();
  d2.erase(iter);
  std::cout << "elements in d2 after erase: ";
  print_elements(d2);

  // test erase 2
  iter = d2.begin();
  for(int i = 0; i != 5; ++i)
  {
    d2.erase(++iter);
  }
  std::cout << "elements in d2 after erase: ";
  print_elements(d2);

  // test erase 3
  mystl::deque<int, mystl::alloc, 8>::iterator start = d2.begin();
  mystl::deque<int, mystl::alloc, 8>::iterator finish = d2.end();
  ++start;
  --finish;
  d2.erase(start, finish);
  std::cout << "elements in d2 after erase: ";
  print_elements(d2);

  // test erase 4
  start = d2.begin();
  finish = d2.end();
  d2.erase(start, finish);
  std::cout << "elements in d2 after erase: ";
  print_elements(d2);

  // test insert
  d2.insert(d2.end(), 1);
  d2.insert(d2.begin(), 0);
  iter = d2.begin();
  d2.insert(++iter, 2);
  std::cout << "elements in d2 after insert: ";
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
