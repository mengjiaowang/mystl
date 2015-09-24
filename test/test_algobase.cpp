#include "../mystl_algobase.h"
#include "../vector"
#include <iostream>

int main()
{
  mystl::vector<int> a;
  a.push_back(0);
  a.push_back(1);
  a.push_back(2);
  a.push_back(3);

  // test swap
  mystl::vector<int>::iterator iter1, iter2;
  iter2 = a.begin();
  iter1 = iter2++;
  std::cout << *iter1 << " and " << *iter2 << std::endl;
  mystl::swap(iter1, iter2);
  std::cout << *iter1 << " and " << *iter2 << std::endl;
  mystl::swap(iter1, iter2);
  std::cout << *iter1 << " and " << *iter2 << std::endl;

  // test min and max
  int result;
  result = mystl::min(a[2], a[3]);
  std::cout << a[2] << " and " << a[3] << " min:" << result << std::endl;
  result = mystl::max(a[2], a[3]);
  std::cout << a[2] << " and " << a[3] << " max:" << result << std::endl;

  // test equal
  mystl::vector<int> b;
  b.push_back(0);
  b.push_back(1);
  b.push_back(2);
  b.push_back(4);
  std::cout << "equal: " << mystl::equal(a.begin(), a.end(), a.begin()) << std::endl;
  std::cout << "equal: " << mystl::equal(a.begin(), a.end(), b.begin()) << std::endl;
  std::cout << "equal: " << mystl::equal(b.begin(), b.end(), a.begin()) << std::endl;

  // test mismatch
  mystl::pair<mystl::vector<int>::iterator, mystl::vector<int>::iterator>
    mismatch_result = mystl::mismatch(a.begin(), a.end(), b.begin());
  std::cout << "mismatch: " << *mismatch_result.first << " " << *mismatch_result.second
    << std::endl;

  // test lexicographical_compare
  std::cout << "lexicographical_compare: " << mystl::lexicographical_compare(a.begin(), a.end(),
      b.begin(), b.end()) << std::endl;
  std::cout << "lexicographical_compare: " << mystl::lexicographical_compare(b.begin(), b.end(),
      a.begin(), a.end()) << std::endl;

  // test copy
  char chr1[6] = "hello";
  char chr2[6] = "xxxxx";
  mystl::copy(chr1, chr1+6, chr2);
  std::cout << "chr1: " << chr1 << std::endl << "chr2: " << chr2 << std::endl;

  // test copy_backward
  char chr3[6] = "xxxxx";
  mystl::copy_backward(chr1, chr1+6, chr3+6);
  std::cout << "chr1: " << chr1 << std::endl << "chr3: " << chr3 << std::endl;

  return 0;
}
