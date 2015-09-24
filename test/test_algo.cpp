#include "../mystl_algo.h"
#include "../vector"
#include "../list"
#include <iostream>
#include <list>

void print(mystl::vector<int> &v)
{
  mystl::vector<int>::iterator iter;
  for(iter = v.begin(); iter != v.end(); ++iter)
  {
    std::cout << *iter << " ";
  }
  std::cout << std::endl;
}

void print(mystl::list<int> &v)
{
  mystl::list<int>::iterator iter;
  for(iter = v.begin(); iter != v.end(); ++iter)
  {
    std::cout << *iter << " ";
  }
  std::cout << std::endl;
}

struct even_num
{
  bool operator()(const unsigned int num)
  {
    return !(num & 1);
  }
};

struct odd_num
{
  bool operator()(const unsigned int num)
  {
    return num & 1;
  }
};

int main()
{
  // test merge
  mystl::vector<int> m1, m2, m;
  mystl::vector<int>::iterator merged_result;
  m1.push_back(1);
  m1.push_back(3);
  m1.push_back(5);
  m2.push_back(2);
  m2.push_back(4);
  m2.push_back(6);
  m.resize(m1.size() + m2.size());
  merged_result = mystl::merge(m1.begin(), m1.end(), m2.begin(), m2.end(), m.begin());
  print(m1);
  print(m2);
  print(m);

  // test merge 2
  merged_result = mystl::merge(m1.begin(), m1.end(), m2.begin(), m2.end(), m.begin(), std::less<int>());
  print(m);

  // test partition
  mystl::partition(m.begin(), m.end(), even_num());
  print(m);

  // test partition
  mystl::partition(m.begin(), m.end(), odd_num());
  print(m);

  // test reverse for vector
  mystl::reverse(m1.begin(), m1.end());
  print(m1);

  // test reverse for list
  /*
  mystl::list<int> li;
  li.push_back(1);
  li.push_back(2);
  li.push_back(3);

  mystl::reverse(li.begin(), li.end());
  print(li);
  */
  return 0;
}
