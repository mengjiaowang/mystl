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

  // test reserve
  v.reserve(10);
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  v.push_back(4);
  std::cout << "test reserve: size = " << v.size() << " capacity = " << v.capacity() << std::endl;
  mystl::vector<int>::iterator iter = v.begin();
  for(iter = v.begin(); iter != v.end(); ++iter)
  {
    std::cout << "value: " << (*iter) << std::endl;
  }
  v.insert(v.end(), 3, 5);
  std::cout << "test reserve: size = " << v.size() << " capacity = " << v.capacity() << std::endl;
  for(iter = v.begin(); iter != v.end(); ++iter)
  {
    std::cout << "value: " << (*iter) << std::endl;
  }

  // test compare
  mystl::vector<int> v1(3,9), v2(2,10);
  std::cout << "v1 == v2: " << (v1 == v2) << std::endl;
  std::cout << "v1 != v2: " << (v1 != v2) << std::endl;
  std::cout << "v1 < v2: " << (v1 < v2) << std::endl;
  std::cout << "v1 > v2: " << (v1 > v2) << std::endl;
  std::cout << "v1 <= v2: " << (v1 <= v2) << std::endl;
  std::cout << "v1 >= v2: " << (v1 >= v2) << std::endl;

  // test swap
  std::cout << "size = " << v1.size() << " capacity = " << v1.capacity() << std::endl;
  std::cout << "size = " << v2.size() << " capacity = " << v2.capacity() << std::endl;
  v1.swap(v2);
  std::cout << "size = " << v1.size() << " capacity = " << v1.capacity() << std::endl;
  std::cout << "size = " << v2.size() << " capacity = " << v2.capacity() << std::endl;

  return 0;
}
