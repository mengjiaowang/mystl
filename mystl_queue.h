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

#ifndef MYSTL_QUEUE_H_
#define MYSTL_QUEUE_H_

#include "deque"
#include "mystl_config.h"

namespace mystl
{
  template <class T, class Sequence = mystl::deque<T> >
  class queue
  {
    friend bool operator== __STL_NULL_TMPL_ARGS(const queue &x, const queue &y);
    friend bool operator<  __STL_NULL_TMPL_ARGS(const queue &x, const queue &y);

    public:
      typedef typename Sequence::value_type value_type;
      typedef typename Sequence::size_type size_type;
      typedef typename Sequence::reference reference;
      typedef typename Sequence::const_reference const_reference;

    protected:
      Sequence c;

    public:
      bool empty() {return c.empty();}
      size_type size() const {return c.size();}
      reference front() {return c.front();}
      const_reference front() const {return c.front();}
      reference back() {return c.back();}
      const_reference back() const {return c.back();}
      void push(const value_type &x) {c.push_back(x);}
      void pop() {c.pop_front();}
  };

  template <class T, class Sequence>
  bool operator==(const queue<T, Sequence> &x, const queue<T, Sequence> &y)
  {
    return x.c == y.c;
  }

  template <class T, class Sequence>
  bool operator<(const queue<T, Sequence> &x, const queue<T, Sequence> &y)
  {
    return x.c < y.c;
  }
} // end of namespace mystl

#endif
