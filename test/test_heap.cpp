#include "../mystl_heap.h"
#include "../mystl_vector.h"
#include <iostream>

void print_vector(mystl::vector<int> &v);
int main()
{
  mystl::vector<int> test_heap;

  // test push_heap
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
  std::cout << "heap before push_heap: ";
  print_vector(test_heap);
  test_heap.push_back(50);
  mystl::push_heap(test_heap.begin(), test_heap.end());
  std::cout << "heap after push_heap:  ";
  print_vector(test_heap);

  // test pop_heap
  std::cout << "heap before pop_heap: ";
  print_vector(test_heap);
  mystl::pop_heap(test_heap.begin(), test_heap.end());
  test_heap.pop_back();
  std::cout << "heap after pop_heap:  ";
  print_vector(test_heap);

  // test sort_heap
  mystl::sort_heap(test_heap.begin(), test_heap.end());
  std::cout << "data after sort_heap:  ";
  print_vector(test_heap);

  // test make_heap
  mystl::make_heap(test_heap.begin(), test_heap.end());
  std::cout << "data after make_heap:  ";
  print_vector(test_heap);

  return 0;
}

void print_vector(mystl::vector<int> &v)
{
  mystl::vector<int>::iterator iter;
  for(iter = v.begin(); iter != v.end(); ++iter)
  {
    std::cout << *iter << " ";
  }
  std::cout << std::endl;
}
