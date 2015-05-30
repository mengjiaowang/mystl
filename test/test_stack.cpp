#include "../stack"
#include "../list"
#include <iostream>

int main()
{
  mystl::stack<int> s;
  // test push back
  s.push(1);
  s.push(2);
  s.push(3);
  std::cout << "size = " << s.size() << std::endl;

  // test pop
  std::cout << "s.pop() = " << s.top() << std::endl; s.pop();
  std::cout << "s.pop() = " << s.top() << std::endl; s.pop();
  std::cout << "s.pop() = " << s.top() << std::endl; s.pop();
  std::cout << "size = " << s.size() << std::endl;

  // use mystl::list as the container for stack
  mystl::stack<int, mystl::list<int> > sl;
  // test push back
  sl.push(1);
  sl.push(2);
  sl.push(3);
  std::cout << "size = " << s.size() << std::endl;

  // test pop
  std::cout << "s.pop() = " << sl.top() << std::endl; sl.pop();
  std::cout << "s.pop() = " << sl.top() << std::endl; sl.pop();
  std::cout << "s.pop() = " << sl.top() << std::endl; sl.pop();
  std::cout << "size = " << sl.size() << std::endl;


  return 0;
}
