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

#ifndef MYSTL_PAIR_H_
#define MYSTL_PAIR_H_

namespace mystl
{
  template <class T1, class T2>
  struct pair
  {
    typedef T1 first_type;
    typedef T2 second_type;

    T1 first;
    T2 second;

    pair() : first(T1()), second(T2()) {}
    pair(const T1 &a, const T2 &b) : first(a), second(b) {}

    template <class U1, class U2>
    pair(const pair<U1, U2> &p) : first(p.first), second(p.second) {}
  };

  template <class T1, class T2>
  inline bool operator==(const pair<T1, T2> &x, const pair<T1, T2> &y)
  {
    return x.first == y.first && x.second == y.second;
  }

  template <class T1, class T2>
  inline bool operator < (const pair<T1, T2> &x, const pair<T1, T2> &y)
  {
    return x.first < y.first || (!(y.first < x.fist) && x.second < y.second);
  }

  template <class T1, class T2>
  pair<T1, T2> make_pair(const T1 &x, const T2 &y)
  {
    return pair<T1, T2>(x, y);
  }

} // end of namespace mystl

#endif
