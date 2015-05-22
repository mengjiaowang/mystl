#include "../list"
#include <iostream>

void print_list_element(mystl::list<int> &li);
int main()
{
  mystl::list<int> li;
  // test empty
  std::cout << "empty = " << li.empty() << std::endl;

  // test push_back
  li.push_back(1);
  li.push_back(2);
  li.push_back(3);
  std::cout << "empty = " << li.empty() << std::endl;

  // test front and back
  std::cout << "front = " << li.front() << std::endl;
  std::cout << "back = " << li.back() << std::endl;

  // test iterator++
  mystl::list<int>::iterator iter = li.begin();
  std::cout << "iterator = " << *(++iter) << std::endl;

  // test insert
  li.insert(iter, 4);
  print_list_element(li);

  // test push_front
  li.push_front(0);
  std::cout << "front = " << li.front() << std::endl;

  // test pop_front
  li.pop_front();
  std::cout << "front = " << li.front() << std::endl;

  // test pop_back
  li.pop_back();
  std::cout << "back = " << li.back() << std::endl;

  // test erase
  iter = li.begin();
  ++iter;
  li.erase(iter);
  print_list_element(li);

  // test remove
  li.push_back(2);
  li.remove(2);
  print_list_element(li);

  // test unique
  li.push_back(1);
  li.push_back(2);
  li.push_back(2);
  li.push_back(3);
  print_list_element(li);
  li.unique();
  print_list_element(li);

  // test clear
  li.clear();
  print_list_element(li);

  // test splice
  mystl::list<int> li1, li2;
  li1.push_back(1);
  li1.push_back(2);
  li1.push_back(3);
  li2.push_back(1);
  li2.push_back(2);
  li2.push_back(3);
  li1.splice(li1.end(), li2);
  print_list_element(li1);

  return 0;
}

void print_list_element(mystl::list<int> &li)
{
  mystl::list<int>::iterator iter;
  std::cout << "list elements: [ ";
  for(iter = li.begin(); iter != li.end(); ++iter)
  {
    std:: cout << *(iter) << " ";
  }
  std::cout << "]" << std::endl;
}
