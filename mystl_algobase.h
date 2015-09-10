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

  template <class InputIterator, class OutputIterator>
  inline OutputIterator __copy(InputIterator first, InputIterator last,
      OutputIterator result, input_iterator_tag)
  {
    for(; first != last; ++result, ++first)
    {
      *result = *first;
    }
    return result;
  }

  template <class RandomAccessIterator, class OutputIterator, class Distance>
  inline OutputIterator __copy_d(RandomAccessIterator first, RandomAccessIterator last,
      OutputIterator result, Distance*)
  {
    for(Distance n = last - first; n > 0; --n, ++result, ++first)
    {
      *result = *first;
    }
    return result;
  }

  template <class RandomAccessIterator, class OutputIterator, class Distance>
  inline OutputIterator __copy(RandomAccessIterator first, RandomAccessIterator last,
      OutputIterator result, random_access_iterator_tag)
  {
    return __copy_d(first, last, result, distance_type(first));
  }

  template <class InputIterator, class OutputIterator>
  struct __copy_dispatch
  {
    OutputIterator operator()(InputIterator first, InputIterator last,
        OutputIterator result)
    {
      return __copy(first, last, result, iterator_category(first));
    }
  };

#ifdef __STL_CLASS_PARTIAL_SPECIALIZATION
  template <class T>
  inline T* __copy_t(const T* first, const T* last, T* result, __true_type)
  {
    memmove(result, first, sizeof(T)*(last - first));
    return result + (last - first);
  }

  template <class T>
  inline T* __copy_t(const T* first, const T* last, T* result, __false_type)
  {
    return __copy_d(first, last, result, (ptrdiff_t*)0);
  }

  template <class T>
  struct __copy_dispatch<T*, T*>
  {
    T* operator()(T* first, T* last, T* result)
    {
      typedef typename __type_traits<T>::has_trivial_assignment_operator t;
      return __copy_t(first, last, result, t());
    }
  };

  template <class T>
  struct __copy_dispatch<const T*, T*>
  {
    T* operator()(const T* first, const T* last, T* result)
    {
      typedef typename __type_traits<T>::has_trivial_assignment_operator t;
      return __copy_t(first, last, result, t());
    }
  };
#endif

  template <class InputIterator, class OutputIterator>
  inline OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result)
  {
    return __copy_dispatch<InputIterator, OutputIterator>()(first, last, result);
  }

  inline char* copy(const char* first, const char* last, char* result)
  {
    memmove(result, first, last - first);
    return result + (last - first);
  }

  inline wchar_t* copy(const wchar_t* first, const wchar_t* last, wchar_t* result)
  {
    memmove(result, first, sizeof(wchar_t) * (last - first));
    return result + (last - first);
  }

  template <class BidirectionalIterator1, class BidirectionalIterator2>
  inline BidirectionalIterator2 __copy_backward(
      BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 result)
  {
    while(first != last) *--result = *--last;
    return result;
  }

  template <class BidirectionalIterator1, class BidirectionalIterator2>
  struct __copy_backward_dispatch
  {
    BidirectionalIterator2 operator()(BidirectionalIterator1 first,
        BidirectionalIterator1 last, BidirectionalIterator2 result)
    {
      return __copy_backward(first, last, result);
    }
  };

#ifdef __STL_CLASS_PARTIAL_SPECIALIZATION
  template <class T>
  inline T* __copy_backward_t(const T* first, const T* last, T* result, __true_type)
  {
    const ptrdiff_t N = last - first;
    memmove(result - N, first, sizeof(T)*N);
    return result - N;
  }

  template <class T>
  inline T* __copy_backward_t(const T* first, const T* last, T* result, __false_type)
  {
    return __copy_backward(first, last, result);
  }

  template <class T>
  struct __copy_backward_dispatch<T*, T*>
  {
    T* operator()(T* first, T* last, T* result)
    {
      typedef typename __type_traits<T>::has_trivial_assignment_operator t;
      return __copy_backward_t(first, last, result, t());
    }
  };

  template <class T>
  struct __copy_backward_dispatch<const T*, T*>
  {
    T* operator()(const T* first, const T* last, T* result)
    {
      typedef typename __type_traits<T>::has_trivial_assignment_operator t;
      return __copy_backward_t(first, last, result, t());
    }
  };

#endif

  template <class BidirectionalIterator1, class BidirectionalIterator2>
  inline BidirectionalIterator2 copy_backward(BidirectionalIterator1 first,
      BidirectionalIterator1 last, BidirectionalIterator2 result)
  {
    return __copy_backward_dispatch<BidirectionalIterator1, BidirectionalIterator2>()(
        first, last, result);
  }

  template <class InputIterator, class Size, class OutputIterator>
  mystl::pair<InputIterator, OutputIterator> __copy_n(InputIterator first, Size count,
      OutputIterator result, input_iterator_tag)
  {
    for(; count > 0; --count, ++first, ++result) *result = *first;
    return mystl::pair<InputIterator, OutputIterator>(first, result);
  }

  template <class RandomAccessIterator, class Size, class OutputIterator>
  inline mystl::pair<RandomAccessIterator, OutputIterator>
  __copy_n(RandomAccessIterator first, Size count, OutputIterator result, random_access_iterator_tag)
  {
    RandomAccessIterator last = first + count;
    return mystl::pair<RandomAccessIterator, OutputIterator>(last, mystl::copy(first, last, result));
  }

  template <class InputIterator, class Size, class OutputIterator>
  inline mystl::pair<InputIterator, OutputIterator>
  copy_n(InputIterator first, Size count, OutputIterator result)
  {
    return __copy_n(first, count, result, iterator_category(first));
  }

  template <class ForwardIterator, class T>
  void fill(ForwardIterator first, ForwardIterator last, const T& value)
  {
    for(; first != last; ++first) *first = value;
  }

  template <class OutputIterator, class Size, class T>
  OutputIterator fill_n(OutputIterator first, Size n, const T& value)
  {
    for(; n > 0; --n, ++first) *first = value;
    return first;
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
