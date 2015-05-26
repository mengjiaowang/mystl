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

#ifndef MYSTL_DEQUE_H_
#define MYSTL_DEQUE_H_

#include "mystl_alloc.h"
#include "mystl_construct.h"
#include "mystl_uninitialized.h"

#include <algorithm>

namespace mystl
{

inline size_t __deque_buf_size(size_t n, size_t sz)
{
  return n != 0 ? n : (sz < 512 ? size_t(512/sz) : size_t(1));
}

template <class T, class Ref, class Ptr, size_t BufSiz>
struct __deque_iterator
{
  typedef __deque_iterator<T, T&, T*, BufSiz> iterator;
  typedef __deque_iterator<T, const T&, const T*, BufSiz> const_iterator;
  static size_t buffer_size(){return __deque_buf_size(BufSiz, sizeof(T));}

  typedef random_access_iterator_tag iterator_category;
  typedef T value_type;
  typedef Ptr pointer;
  typedef Ref reference;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;
  typedef T** map_pointer;
  typedef __deque_iterator self;

  T* cur;
  T* first;
  T* last;
  map_pointer node;

  void set_node(map_pointer new_node)
  {
    node = new_node;
    first = *new_node;
    last = first + difference_type(buffer_size());
  }

  reference operator*() const{return *cur;}
  pointer operator->() const{return &(operator*());}
  difference_type operator-(const self &x) const
  {
    return difference_type(buffer_size())* (node - x.node - 1) +
      (cur - first) + (x.last - x.cur);
  }
  self operator++()
  {
    ++cur;
    if(cur == last)
    {
      set_node(node + 1);
      cur = first;
    }
    return *this;
  }
  self &operator++(int)
  {
    self tmp = *this;
    ++*this;
    return tmp;
  }
  self &operator--()
  {
    if(cur == first)
    {
      set_node(node - 1);
      cur = last;
    }
    --cur;
    return *this;
  }
  self operator--(int)
  {
    self tmp = *this;
    --*this;
    return tmp;
  }
  self &operator+=(difference_type n)
  {
    difference_type offset = n + (cur + first);
    if(offset >= 0 && offset < difference_type(buffer_size()))
    {
      cur += n;
    }
    else
    {
      difference_type node_offset = offset > 0 ?
        offset / difference_type(buffer_size()) :
        -difference_type((-offset - 1) / buffer_size()) - 1;
      set_node(node + node_offset);
      cur = first + (offset - node_offset * difference_type(buffer_size()));
    }
    return *this;
  }
  self operator+(difference_type n)
  {
    self tmp = *this;
    return tmp += n;
  }
  self operator-=(difference_type n)
  {
    return *this += -n;
  }
  self operator-(difference_type n)
  {
    self tmp = *this;
    return tmp -= n;
  }
  reference operator[](difference_type n) const
  {
    return *(*this + n);
  }
  bool operator==(const self &x) const
  {
    return cur == x.cur;
  }
  bool operator!=(const self &x) const
  {
    return !(*this==x);
  }
  bool operator<(const self &x) const
  {
    return (node == x.node) ? (cur < x.cur) : (node < x.node);
  }
};

template<class T, class Ref, class Ptr, size_t BufSiz>
inline random_access_iterator_tag
  iterator_category(const __deque_iterator<T, Ref, Ptr, BufSiz>&)
{
  return random_access_iterator_tag();
}

template<class T, class Ref, class Ptr, size_t BufSiz>
inline typename iterator_traits<T>::value_type*
value_type(const __deque_iterator<T, Ref, Ptr, BufSiz>&)
{
  return static_cast<typename iterator_traits<T>::value_type*>(0);
}

template <class T, class Alloc=alloc, size_t BufSiz = 0>
class deque
{
  public:
    typedef T value_type;
    typedef value_type* pointer;
    typedef value_type& reference;
    typedef size_t size_type;
    typedef __deque_iterator<T, T&, T*, BufSiz> iterator;
    typedef ptrdiff_t difference_type;

  protected:
    typedef pointer* map_pointer;

  protected:
    iterator start;
    iterator finish;
    map_pointer map;
    size_type map_size;

  protected:
    typedef simple_alloc<value_type, Alloc> data_allocator;
    typedef simple_alloc<pointer, Alloc> map_allocator;

  public:
    //constructor
    deque(): start(), finish(), map_size(0){}
    deque(int n, const value_type &value)
    :start(), finish(), map_size(0)
    {
      fill_initialize(n, value);
    }

  private:
    void fill_initialize(size_type n, const value_type &value);
    void create_map_and_node(size_type number_elements);
    static size_t buffer_size(){return __deque_buf_size(BufSiz, sizeof(T));}

  public:
    iterator begin(){return start;}
    iterator end(){return finish;}
    reference operator[](size_type n)
    {
      return start[difference_type(n)]; // __deque_iterator::operator[]
    }
    reference front(){return *start;}
    reference back()
    {
      iterator tmp = finish;
      --tmp; // __deque_iterator::operator--
      return *tmp; // __deque_iterator::operator*
    }
    size_type size() const{return finish-start;} // __deque_iterator::operator-
    size_type max_size() const{return size_type(-1);}
    bool empty() const{return finish==start;}
};

template <class T, class Alloc, size_t BufSize>
void deque<T, Alloc, BufSize>::fill_initialize(size_type n, const value_type &value)
{
  create_map_and_node(n);
  map_pointer cur;
  try
  {
    for(cur = start.node; cur < finish.node; ++cur)
    {
      mystl::uninitialized_fill(*cur, *cur + buffer_size(), value);
    }
    mystl::uninitialized_fill(finish.first, finish.cur, value);
  }
  catch(...)
  {
    // commit or rollback
    // TODO: add exception handling code
  }
}

template <class T, class Alloc, size_t BufSize>
void deque<T, Alloc, BufSize>::create_map_and_node(size_type n)
{
}

} // end of namespace stl

#endif
