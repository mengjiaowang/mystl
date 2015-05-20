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

#ifndef MYSTL_UNINITIALIZED_H_
#define MYSTL_UNINITIALIZED_H_

#include "mystl_construct.h"
#include "mystl_iterator.h"
#include "type_traits.h"

// will be removed
#include <algorithm>
#include <cstring>

namespace mystl
{
  // uninitialized_fill_n
  template <class ForwardIterator, class Size, class T>
  inline ForwardIterator
  __uninitialized_fill_n_aux(ForwardIterator first, Size n,
      const T &x, __true_type)
  {
    //TODO:change to mystl::fill_n
    return std::fill_n(first, n, x);
  }

  template <class ForwardIterator, class Size, class T>
  inline ForwardIterator
  __uninitialized_fill_n_aux(ForwardIterator first, Size n,
      const T &x, __false_type)
  {
    // TODO:: add exception handling to fit C++ standards
    ForwardIterator cur = first;
    for( ;n > 0; --n, ++cur)
    {
      construct(&*cur, x);
    }
    return cur;
  }

  template <class ForwardIterator, class Size, class T, class T1>
  inline ForwardIterator __uninitialized_fill_n(ForwardIterator first,
      Size n, const T &x, T1*)
  {
    typedef typename __type_traits<T1>::is_POD_type is_POD;
    return mystl::__uninitialized_fill_n_aux(first, n, x, is_POD());
  }

  template <class ForwardIterator, class Size, class T>
  inline ForwardIterator uninitialized_fill_n(ForwardIterator first,
      Size n, const T &x)
  {
    return mystl::__uninitialized_fill_n(first, n, x, value_type(first));
  }

  // uninitialized_copy
  template <class InputIterator, class ForwardIterator>
  inline ForwardIterator __uninitialized_copy_aux(InputIterator first,
      InputIterator last, ForwardIterator result, __true_type)
  {
    // TODO: change to mystl::copy
    return std::copy(first, last, result);
  }

  template <class InputIterator, class ForwardIterator>
  inline ForwardIterator __uninitialized_copy_aux(InputIterator first,
      InputIterator last, ForwardIterator result, __false_type)
  {
    // TODO: add exception handling to fit C++ standards
    ForwardIterator cur = result;
    for(; first != last; ++first, ++cur)
    {
      mystl::construct(&*cur, *first);
    }
    return cur;
  }

  template <class InputIterator, class ForwardIterator, class T1>
  inline ForwardIterator __uninitialized_copy(InputIterator first,
      InputIterator last, ForwardIterator result, T1*)
  {
    typedef typename __type_traits<T1>::is_POD_type is_POD;
    return mystl::__uninitialized_copy_aux(first, last, result, is_POD());
  }

  template <class InputIterator, class ForwardIterator>
  inline ForwardIterator uninitialized_copy(InputIterator first,
      InputIterator last, ForwardIterator result)
  {
    return mystl::__uninitialized_copy(first, last, result, value_type(result));
  }

  inline char *uninitialized_copy(const char *first, const char *last,
      char *result)
  {
    //TODO: will be changed to mystl::memmove
    std::memmove(result, first, last - first);
    return result + (last - first);
  }

  inline wchar_t *uninitialized_copy(const wchar_t *first, const wchar_t *last,
      wchar_t *result)
  {
    std::memmove(result, first, sizeof(wchar_t)*(last - first));
    return result + (last - first);
  }

  // uninitialized_fill
  template <class ForwardIterator, class T>
  inline void __uninitialized_fill_aux(ForwardIterator first,
      ForwardIterator last, const T &x, __true_type)
  {
    fill(first, last, x);
  }

  template <class ForwardIterator, class T>
  inline void __uninitialized_fill_aux(ForwardIterator first,
      ForwardIterator last, const T &x, __false_type)
  {
    // TODO:: add exception handling to fit C++ standards
    ForwardIterator cur = first;
    for( ; cur != last; ++cur)
    {
      construct(&*cur, x);
    }
  }

  template <class ForwardIterator, class T, class T1>
  inline void __uninitialized_fill(ForwardIterator first, ForwardIterator last,
      const T &x, T1*)
  {
    typedef typename __type_traits<T1>::is_POD_type is_POD();
    __uninitialized_fill_aux(first, last, x, is_POD());
  }

  template <class ForwardIterator, class T>
  inline void uninitialized_fill(ForwardIterator first, ForwardIterator last,
      const T &x)
  {
    __uninitialized_fill(first, last, x, value_type(first));
  }

} // end of namespace mystl

#endif
