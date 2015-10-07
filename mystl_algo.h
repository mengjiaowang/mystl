/*
 * A self study of the book <The Annotated STL Sources - using SGI STL>
 * by Hou Jie. Feel free to use the source code, but please add the copyright
 * notice from HP.
 *
 */

/*
 *
 * Copyright (c) 1994
 * Hewlett-Packard Company
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Hewlett-Packard Company makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 *
 *
 * Copyright (c) 1996,1997
 * Silicon Graphics Computer Systems, Inc.
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Silicon Graphics makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 */

#ifndef MYSTL_ALGO_H_
#define MYSTL_ALGO_H_

#include "mystl_algobase.h"
#include "mystl_heap.h"
#include "set"

namespace mystl
{

  template <class T>
  inline const T& __median(const T&a, const T&b, const T&c)
  {
    if(a < b)
    {
      if(b < c) return b;
      else if(a < c) return c;
      else return a;
    }
    else if(a < c) return a;
    else if(b < c) return c;
    else return b;
  }

  template <class T, class Compare>
  inline const T& __median(const T&a, const T&b, const T&c, Compare comp)
  {
    if(comp(a, b))
    {
      if(comp(b, c)) return b;
      else if(comp(a, c)) return c;
      else return a;
    }
    else if(comp(a, c)) return a;
    else if(comp(b, c)) return c;
    else return b;
  }

  template <class InputIterator, class Function>
  Function for_each(InputIterator first, InputIterator last, Function f)
  {
    for(; first != last; ++first)
    {
      f(*first);
    }
    return f;
  }

  template <class InputIterator, class T>
  InputIterator find(InputIterator first, InputIterator last, const T& value)
  {
    while(first != last && *first != value) ++first;
    return first;
  }

  template <class InputIterator, class Predicate>
  InputIterator find_if(InputIterator first, InputIterator last, Predicate pred)
  {
    while(first != last && pred(*first)) ++first;
    return first;
  }

  template <class ForwardIterator>
  ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last)
  {
    if(first == last) return last;
    ForwardIterator next = first;
    while(++next != last)
    {
      if(*first == *next) return first;
    }
    return last;
  }

  template <class ForwardIterator, class BinaryPredicate>
  ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last,
      BinaryPredicate binary_pred)
  {
    if(first == last) return last;
    ForwardIterator next = first;
    while(++next != last)
    {
      if(binary_pred(*first, *next)) return first;
    }
    return last;
  }

  template <class InputIterator, class T, class Size>
  void count(InputIterator first, InputIterator last, const T& value, Size &n)
  {
    for(; first != last; ++first)
    {
      if(*first == value) ++n;
    }
  }

  template <class InputIterator, class Predicate, class Size>
  void count_if(InputIterator first, InputIterator last, Predicate pred, Size &n)
  {
    for(; first != last; ++first)
    {
      if(pred(*first)) ++n;
    }
  }

#ifdef __STL_CLASS_PARTIAL_SPECIALIZATION

  template <class InputIterator, class T>
  typename mystl::iterator_traits<InputIterator>::difference_type
  count(InputIterator first, InputIterator last, const T& value)
  {
    typename mystl::iterator_traits<InputIterator>::difference_type n = 0;
    for(; first != last; ++first)
    {
      if(*first == value) ++n;
    }
    return n;
  }

  template <class InputIterator, class Predicate>
  typename mystl::iterator_traits<InputIterator>::difference_type
  count_if(InputIterator first, InputIterator last, Predicate pred)
  {
    typename mystl::iterator_traits<InputIterator>::difference_type n = 0;
    for(; first != last; ++first)
    {
      if(pred(*first, value)) ++n;
    }
    return n;
  }

#endif /* __STL_CLASS_PARTIAL_SPECIALIZATION */

  template <class ForwardIterator, class Generator>
  void generate(ForwardIterator first, ForwardIterator last, Generator gen)
  {
    for(; first != last; ++first)
    {
      *first = gen();
    }
  }

  template <class OutputIterator, class Size, class Generator>
  OutputIterator generate_n(OutputIterator first, Size n, Generator gen)
  {
    for(; n > 0; --n, ++first)
    {
      *first = gen();
    }
    return first;
  }

  template <class InputIterator1, class InputIterator2, class OutputIterator>
  OutputIterator merge(InputIterator1 first1, InputIterator1 last1,
      InputIterator2 first2, InputIterator2 last2, OutputIterator result)
  {
    while(first1 != last1 && first2 != last2)
    {
      if(*first2 < *first1)
      {
        *result = *first2;
        ++first2;
      }
      else
      {
        *result = *first1;
        ++first1;
      }
      ++result;
    }
    return copy(first2, last2, copy(first1, last1, result));
  }

  template <class InputIterator1, class InputIterator2, class OutputIterator,
            class Compare>
  OutputIterator merge(InputIterator1 first1, InputIterator1 last1,
      InputIterator2 first2, InputIterator2 last2, OutputIterator result, Compare comp)
  {
    while(first1 != last1 && first2 != last2)
    {
      if(comp(*first2, *first1))
      {
        *result = *first2;
        ++first2;
      }
      else
      {
        *result = *first1;
        ++first1;
      }
      ++result;
    }
    return copy(first2, last2, copy(first1, last1, result));
  }

  template <class ForwardIterator>
  ForwardIterator min_element(ForwardIterator first, ForwardIterator last)
  {
    if(first == last) return first;
    ForwardIterator result = first;
    while(++first != last)
    {
      if(*first < *result) result = first;
    }
    return result;
  }

  template <class ForwardIterator, class Compare>
  ForwardIterator min_element(ForwardIterator first, ForwardIterator last, Compare comp)
  {
    if(first == last) return first;
    ForwardIterator result = first;
    while(++first != last)
    {
      if(comp(*first, *result)) result = first;
    }
    return result;
  }

  template <class BidirectionalIterator, class Predicate>
  BidirectionalIterator partition(BidirectionalIterator first,
      BidirectionalIterator last, Predicate pred)
  {
    while(true)
    {
      while(true)
      {
        if(first == last) return first;
        else if(pred(*first)) ++first;
        else break;
      }
      --last;
      while(true)
      {
        if(first == last) return first;
        else if(!pred(*last)) --last;
        else break;
      }
      mystl::iter_swap(first, last);
      ++first;
    }
  }

  template <class BidirectionalIterator>
  inline void reverse(BidirectionalIterator first, BidirectionalIterator last)
  {
    __reverse(first, last, iterator_category(first));
  }

  template <class BidirectionalIterator>
  void __reverse(BidirectionalIterator first, BidirectionalIterator last, bidirectional_iterator_tag)
  {
    while(true)
    {
      if(first == last || first == --last)
      {
        return;
      }
      else
      {
        iter_swap(first++, last);
      }
    }
  }

  template <class RandomAccessIterator>
  void __reverse(RandomAccessIterator first, RandomAccessIterator last, random_access_iterator_tag)
  {
    while(first < last) iter_swap(first++, --last);
  }

  template <class InputIterator1, class InputIterator2, class OutputIterator>
  OutputIterator set_union(InputIterator1 first1, InputIterator1 last1,
      InputIterator2 first2, InputIterator2 last2, OutputIterator result)
  {
    while(first1 != last1 && first2 != last2)
    {
      if(*first1 < *first2)
      {
        *result = *first1;
        ++first1;
      }
      else if(*first2 < *first1)
      {
        *result = *first2;
        ++first2;
      }
      else
      {
        *result = *first1;
        ++first1;
        ++first2;
      }
      ++result;
    }
    return mystl::copy(first2, last2, mystl::copy(first1, last1, result));
  }

  template <class InputIterator1, class InputIterator2, class OutputIterator,
            class Compare>
  OutputIterator set_union(InputIterator1 first1, InputIterator1 last1,
      InputIterator2 first2, InputIterator2 last2, OutputIterator result,
      Compare comp)
  {
    while(first1 != last1 && first2 != last2)
    {
      if(comp(*first1, *first2))
      {
        *result = *first1;
        ++first1;
      }
      else if(comp(*first2, *first1))
      {
        *result = *first2;
        ++first2;
      }
      else
      {
        *result = *first1;
        ++first1;
        ++first2;
      }
      ++result;
    }
    return mystl::copy(first2, last2, mystl::copy(first1, last1, result));
  }

  template <class InputIterator1, class InputIterator2, class OutputIterator>
  OutputIterator set_intersection(InputIterator1 first1, InputIterator1 last1,
      InputIterator2 first2, InputIterator2 last2, OutputIterator result)
  {
    while(first1 != last1 && first2 != last2)
    {
      if(*first1 < *first2)
      {
        ++first1;
      }
      else if(*first2 < *first1)
      {
        ++first2;
      }
      else
      {
        *result = *first1;
        ++first1;
        ++first2;
        ++result;
      }
    }
    return result;
  }

  template <class InputIterator1, class InputIterator2, class OutputIterator,
            class Compare>
  OutputIterator set_intersection(InputIterator1 first1, InputIterator1 last1,
      InputIterator2 first2, InputIterator2 last2, OutputIterator result, Compare comp)
  {
    while(first1 != last1 && first2 != last2)
    {
      if(comp(*first1, *first2))
      {
        ++first1;
      }
      else if(comp(*first2, *first1))
      {
        ++first2;
      }
      else
      {
        *result = *first1;
        ++first1;
        ++first2;
      }
    }
    return result;
  }

  template <class InputIterator1, class InputIterator2, class OutputIterator>
  OutputIterator set_difference(InputIterator1 first1, InputIterator1 last1,
      InputIterator2 first2, InputIterator2 last2, OutputIterator result)
  {
    while(first1 != last1 && first2 != last2)
    {
      if(*first1 < *first2)
      {
        *result = *first1;
        ++first1;
        ++result;
      }
      else if(*first2 < *first1)
      {
        ++first2;
      }
      else
      {
        ++first1;
        ++first2;
      }
    }
    return mystl::copy(first1, last1, result);
  }

  template <class InputIterator1, class InputIterator2, class OutputIterator,
            class Compare>
  OutputIterator set_difference(InputIterator1 first1, InputIterator1 last1,
      InputIterator2 first2, InputIterator2 last2, OutputIterator result,
      Compare comp)
  {
    while(first1 != last1 && first2 != last2)
    {
      if(comp(*first1, *first2))
      {
        *result = *first1;
        ++first1;
        ++result;
      }
      else if(comp(*first2, *first1))
      {
        ++first2;
      }
      else
      {
        ++first1;
        ++first2;
      }
    }
    return mystl::copy(first1, last1, result);
  }

  template <class InputIterator1, class InputIterator2, class OutputIterator>
  OutputIterator set_symmetric_difference(InputIterator1 first1, InputIterator1 last1,
      InputIterator2 first2, InputIterator2 last2, OutputIterator result)
  {
    while(first1 != last1 && first2 != last2)
    {
      if(*first1 < *first2)
      {
        *result = *first1;
        ++first1;
        ++result;
      }
      else if(*first2 < *first1)
      {
        *result = *first2;
        ++first2;
        ++result;
      }
      else
      {
        ++first1;
        ++first2;
      }
    }
    return mystl::copy(first1, last1, mystl::copy(first2, last2, result));
  }

  template <class InputIterator1, class InputIterator2, class OutputIterator,
            class Compare>
  OutputIterator set_symmetric_difference(InputIterator1 first1, InputIterator1 last1,
      InputIterator2 first2, InputIterator2 last2, OutputIterator result, Compare comp)
  {
    while(first1 != last1 && first2 != last2)
    {
      if(comp(*first1, *first2))
      {
        *result = *first1;
        ++first1;
        ++result;
      }
      else if(comp(*first2, *first1))
      {
        *result = *first2;
        ++first2;
        ++result;
      }
      else
      {
        ++first1;
        ++first2;
      }
    }
    return mystl::copy(first1, last1, mystl::copy(first2, last2, result));
  }

}

#endif
