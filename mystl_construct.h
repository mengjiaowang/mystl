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

#ifndef MYSTL_CONSTRUCT_H_
#define MYSTL_CONSTRUCT_H_

#include <new>

namespace mystl
{
  template <class T1, class T2>
  inline void construct(T1 *p, const T2 &value)
  {
    new ((void *)p) T1(value); // placement new
  }

  template <class T1>
  inline void construct(T1 *p)
  {
    new ((void *)p) T1();
  }

  template <class T1>
  inline void destroy(T1 *pointer)
  {
    pointer->~T();
  }

  template <class ForwardIterator>
  inline void destroy(ForwardIterator first, ForwardIterator last)
  {
    destroy(first, last, value_type(first));
  }

  template <class ForwardIterator, class T>
  inline void destroy(ForwardIterator first, ForwardIterator last, T*)
  {
    typedef typename __type_traits<T>::has_trivial_destructor trivial_destructor;
    __destroy_aux(first, last, trivial_destructor());
  }

  template <class ForwardIterator>
  inline void __destroy_aux(ForwardIterator first,
      ForwardIterator last, std::__false_type)
  {
    for(; first != last; ++first)
    {
      destroy(&*first);
    }
  }

  template <class ForwardIterator>
  inline void __destroy_aux(ForwardIterator, ForwardIterator, std::__true_type)
  {
  }

  inline void destroy(char*, char*) {}
  inline void destroy(int*, int*) {}
  inline void destroy(long*, long*) {}
  inline void destroy(float*, float*) {}
  inline void destroy(double*, double*) {}

  #ifdef __STL_HAS_WCHAR_T
  inline void destroy(wchar_t*, wchar_t*) {}
  #endif /* __STL_HAS_WCHAR_T */

} // end of namespace mystl

#endif
