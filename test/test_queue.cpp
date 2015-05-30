#include "../queue"
#include "../list"
#include <iostream>

int main()
{
  mystl::queue<int> q;
  // test push back
  q.push(1);
  q.push(2);
  q.push(3);
  std::cout << "size = " << q.size() << std::endl;

  // test pop
  std::cout << "s.pop() = " << q.front() << std::endl; q.pop();
  std::cout << "s.pop() = " << q.front() << std::endl; q.pop();
  std::cout << "s.pop() = " << q.front() << std::endl; q.pop();
  std::cout << "size = " << q.size() << std::endl;

  // use mystl::list as the container for stack
  mystl::queue<int, mystl::list<int> > ql;
  // test push back
  ql.push(1);
  ql.push(2);
  ql.push(3);
  std::cout << "size = " << ql.size() << std::endl;

  // test pop
  std::cout << "s.pop() = " << ql.front() << std::endl; ql.pop();
  std::cout << "s.pop() = " << ql.front() << std::endl; ql.pop();
  std::cout << "s.pop() = " << ql.front() << std::endl; ql.pop();
  std::cout << "size = " << ql.size() << std::endl;

  return 0;
}
