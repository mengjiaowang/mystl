#include "../mystl_deque.h"
#include "../mystl_alloc.h"
#include <iostream>

int main()
{
  mystl::deque<int, mystl::alloc, 8> d1;
  mystl::deque<int, mystl::alloc, 8> d2(10,0);
  return 0;
}
