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
#include "vector"
#include "mystl_heap.h"

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

  template <class T, class Sequence = mystl::vector<T>,
            /* TODO: will be changed to mystl::less */
            class Compare = std::less<typename Sequence::value_type> >
  class priority_queue
  {
    public:
      typedef typename Sequence::value_type value_type;
      typedef typename Sequence::size_type size_type;
      typedef typename Sequence::reference reference;
      typedef typename Sequence::const_reference const_reference;
    protected:
      Sequence c;
      Compare comp;
    public:
      priority_queue():c(){}
      explicit priority_queue(const Compare &x): c(), comp(x) {}

      template <class InputIterator>
      priority_queue(InputIterator first, InputIterator last, const Compare &x)
      :c(first, last), comp(x)
      {
        mystl::make_heap(c.begin(), c.end(), x);
      }

      template <class InputIterator>
      priority_queue(InputIterator first, InputIterator last):c(first, last)
      {
        mystl::make_heap(c.begin(), c.end(), comp);
      }

      bool empty() const {return c.empty();}
      size_type size() const {return c.size();}
      const_reference top() {return c.front();}
      void push(const value_type &x)
      {
        try
        {
          c.push_back(x);
          mystl::push_heap(c.begin(), c.end(), comp);
        }
        catch(...)
        {
          c.clear();
        }
      }
      void pop()
      {
        try
        {
          mystl::pop_heap(c.begin(), c.end(), comp);
          c.pop_back();
        }
        catch(...)
        {
          c.clear();
        }
      }
  };
} // end of namespace mystl

#endif
