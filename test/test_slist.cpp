#include "../slist"
#include <iostream>

void print_slist(mystl::slist<int> &sl);

int main()
{
  // test slist
  mystl::slist<int> sl;
  // test size
  std::cout << "size = " << sl.size() << std::endl;
  // test push_front
  sl.push_front(1);
  sl.push_front(2);
  sl.push_front(3);
  sl.push_front(4);
  // test iterator
  print_slist(sl);

  // test clear
  sl.clear();
  std::cout << "size = " << sl.size() << std::endl;
  return 0;
}

void print_slist(mystl::slist<int> &sl)
{
  mystl::slist<int>::iterator iter = sl.begin();
  for(; iter != sl.end(); ++iter)
  {
    std::cout << *iter << " ";
  }
  std::cout << std::endl;
}


