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

#ifndef MYSTL_ALGOBASE_H_
#define MYSTL_ALGOBASE_H_

#include "mystl_config.h"
#include "mystl_pair.h"
#include "type_traits.h"
#include "mystl_iterator.h"
#include <string.h>

namespace mystl
{
  template <class ForwardIterator1, class ForwardIterator2, class T>
  inline void __iter_swap(ForwardIterator1 a, ForwardIterator2 b, T*)
  {
    T tmp = *a;
    *a = *b;
    *b = tmp;
  }

  template <class ForwardIterator1, class ForwardIterator2>
  inline void iter_swap(ForwardIterator1 a, ForwardIterator2 b)
  {
    __iter_swap(a, b, value_type(a));
  }

  template <class T>
  inline void swap(T& a, T& b)
  {
    T tmp = a;
    a = b;
    b = tmp;
  }

#undef min
#undef max

  template <class T>
  inline const T& min(const T& a, const T& b)
  {
    return b < a ? b : a;
  }

  template <class T>
  inline const T& max(const T&a, const T& b)
  {
    return a < b ? b : a;
  }

  template <class T, class Compare>
  inline const T& min(const T& a, const T& b, Compare comp)
  {
    return comp(a, b)? b : a;
  }

  template <class T, class Compare>
  inline const T& max(const T& a, const T& b, Compare comp)
  {
    return comp(b, a)? b : a;
  }

  template <class InputIterator1, class InputIterator2>
  mystl::pair<InputIterator1, InputIterator2> mismatch(InputIterator1 first1,
      InputIterator1 last1, InputIterator2 first2)
  {
    while(first1 != last1 && *first1 == *first2)
    {
      ++first1;
      ++first2;
    }
    return mystl::pair<InputIterator1, InputIterator2> (first1, first2);
  }

  template <class InputIterator1, class InputIterator2, class BinaryPredicate>
  mystl::pair<InputIterator1, InputIterator2> mismatch(InputIterator1 first1,
      InputIterator1 last1, InputIterator2 first2, BinaryPredicate binary_pred)
  {
    while(first1 != last1 && binary_pred(*first1,  *first2))
    {
      ++first1;
      ++first2;
    }
    return mystl::pair<InputIterator1, InputIterator2> (first1, first2);
  }

  template <class InputIterator1, class InputIterator2>
  inline bool equal(InputIterator1 first1, InputIterator1 last1,
      InputIterator2 first2)
  {
    for(; first1 != last1; ++first1, ++first2)
    {
      if(*first1 != *first2) return false;
    }
    return true;
  }

  template <class InputIterator1, class InputIterator2, class BinaryPredicate>
  inline bool equal(InputIterator1 first1, InputIterator1 last1,
      InputIterator2 first2, BinaryPredicate binary_pred)
  {
    for(; first1 != last1; ++first1, ++first2)
    {
      if(binary_pred(*first1, *first2)) return false;
    }
    return true;
  }

  template <class InputIterator1, class InputIterator2>
  inline bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
      InputIterator2 first2, InputIterator2 last2)
  {
    for(; first1 != last1 && first2 != last2; ++first1, ++first2)
    {
      if(*first1 < *first2) return true;
      if(*first2 < *first1) return false;
    }
    return first1 == last1 && first2 != last2;
  }

  template <class InputIterator1, class InputIterator2, class Compare>
  inline bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
      InputIterator2 first2, InputIterator2 last2, Compare comp)
  {
    for(; first1 != last1 && first2 != last2; ++first1, ++first2)
    {
      if(comp(*first1, *first2)) return true;
      if(comp(*first2, *first1)) return false;
    }
    return first1 == last1 && first2 != last2;
  }

  inline bool lexicographical_compare(const unsigned char* first1,
      const unsigned char* last1,
      const unsigned char* first2,
      const unsigned char* last2)
  {
    const size_t len1 = last1 - first1;
    const size_t len2 = last2 - first2;
    const int result = memcmp(first1, first2, min(len1, len2));
    return result != 0 ? result < 0 : len1 < len2;
  }

} // end of namespace mystl

#endif