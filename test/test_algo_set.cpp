#include "../algorithm"
#include "../set"
#include <iostream>

template <class T>
struct display
{
  void operator()(const T&x)
  {
    std::cout << x << " ";
  }
};

int main()
{
  int ia1[6] = {1, 3, 5, 7, 9, 11};
  int ia2[6] = {1, 2, 3, 5, 8, 13};

  mystl::set<int> S1(ia1, ia1+6);
  mystl::set<int> S2(ia2, ia2+6);

  // test set_union
  mystl::set_union(S1.begin(), S1.end(), S2.begin(), S2.end(),
      std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

  // test set_intersection
  mystl::set_intersection(S1.begin(), S1.end(), S2.begin(), S2.end(),
      std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

  // test set_difference
  mystl::set_difference(S1.begin(), S1.end(), S2.begin(), S2.end(),
      std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

  // test set_symmetric_difference
  mystl::set_symmetric_difference(S1.begin(), S1.end(), S2.begin(), S2.end(),
      std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

}
