#include "../stack"
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

  return 0;
}
