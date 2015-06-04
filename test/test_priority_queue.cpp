#include "../queue"
#include <iostream>

int main()
{
  // test priority queue
  mystl::priority_queue<int> pq;
  // test push
  pq.push(1);
  pq.push(2);
  pq.push(3);
  pq.push(4);
  pq.push(5);
  // test size
  std::cout << "size = " << pq.size() << std::endl;

  return 0;
}
