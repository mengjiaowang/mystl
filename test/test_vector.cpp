#include "../vector"
#include <iostream>

int main()
{
  // test constructor
  mystl::vector<int> v(2,10);
  std::cout << "size = " << v.size() << " capacity = " << v.capacity() << std::endl;
  std::cout << "v[0] = " << v[0] << " v[1] = " << v[1] << std::endl;

  // test pop_back() and operator[]
  v.pop_back();
  std::cout << "size = " << v.size() << " capacity = " << v.capacity() << std::endl;
  std::cout << "v[0] = " << v[0] << std::endl;

  // test push_back() and operator[]
  v.push_back(9);
  std::cout << "size = " << v.size() << " capacity = " << v.capacity() << std::endl;
  std::cout << "v[0] = " << v[0] << " v[1] = " << v[1] << std::endl;

  // test empty
  std::cout << "empty = " << v.empty() << std::endl;

  // test front and back
  std::cout << "front = " << v.front() << " back = " << v.back() << std::endl;

  // test resize
  v.resize(0);
  std::cout << "size = " << v.size() << std::endl;
  v.resize(4);
  std::cout << "size = " << v.size() << std::endl;

  // test clear
  v.clear();
  std::cout << "size = " << v.size() << " capacity = " << v.capacity() << std::endl;
  std::cout << "empty = " << v.empty() << std::endl;

  return 0;
}
