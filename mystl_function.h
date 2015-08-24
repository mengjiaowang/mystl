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

#ifndef MYSTL_FUNCTION_H_
#define MYSTL_FUNCTION_H_

#include <functional>

namespace mystl
{
  template <class T>
  //TODO: will be changed to mystl::unary_function<T, T>
  struct multiplies : public std::binary_function<T, T, T>
  {
    T operator()(const T& x, const T& y) const { return x * y;}
  };

  template <class T>
  struct plus : public std::binary_function<T, T, T> {
    T operator()(const T& x, const T& y) const { return x + y;}
  };

  template <class T> inline T identity_element(mystl::multiplies<T>) { return T(1);}
  template <class T> inline T identity_element(mystl::plus<T>) { return T(0);}

  template <class T>
  //TODO: will be changed to mystl::unary_function<T, T>
  struct identity: public std::unary_function<T, T>
  {
    const T& operator()(const T& x) const {return x;}
  };

  template <class Pair>
  struct select1st : public std::unary_function<Pair, typename Pair::first_type>
  {
    const typename Pair::first_type& operator()(const Pair& x) const
    {
      return x.first;
    };
  };

} // end of namespace mystl

#endif
