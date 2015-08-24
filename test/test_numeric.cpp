#include "../mystl_numeric.h"
#include "../mystl_vector.h"
#include <iostream>

int main()
{
  mystl::vector<int> iv;
  iv.push_back(1);
  iv.push_back(2);
  iv.push_back(3);
  iv.push_back(4);
  iv.push_back(5);

  // test accumulate 1
  std::cout << accumulate(iv.begin(), iv.end(), 0) << std::endl;
  std::cout << accumulate(iv.begin(), iv.end(), 0, std::minus<int>()) << std::endl;

  // test adjacent_difference
  std::ostream_iterator<int> oite(std::cout, " ");
  adjacent_difference(iv.begin(), iv.end(), oite);
  std::cout << std::endl;
  adjacent_difference(iv.begin(), iv.end(), oite, std::plus<int>());
  std::cout << std::endl;

  // test inner produce
  std::cout << inner_product(iv.begin(), iv.end(), iv.begin(), 10) << std::endl;
  std::cout << inner_product(iv.begin(), iv.end(), iv.begin(), 10,
      std::minus<int>(), std::plus<int>()) << std::endl;

  // test partial sum
  partial_sum(iv.begin(), iv.end(), oite);
  std::cout << std::endl;
  partial_sum(iv.begin(), iv.end(), oite, std::minus<int>());
  std::cout << std::endl;

  // test power
  std::cout << power(10, 3) << std::endl;
  std::cout << power(10, 3, mystl::plus<int>()) << std::endl;

  // test iota
  int n = 3;
  iota(iv.begin(), iv.end(), n);
  for(size_t i = 0; i != iv.size(); ++i)
  {
    std::cout << iv[i] << ' ';
  }
  std::cout << std::endl;

  return 0;
}
