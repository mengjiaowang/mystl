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
  public:
    void push_back(const value_type &t)
    {
      if(finish.cur != finish.last - 1)
      {
        mystl::construct(finish.cur, t);
        ++finish.cur;
      }
      else
      {
        push_back_aux(t);
      }
    }

    void push_front(const value_type &t)
    {
      if(start.cur != start.first)
      {
        mystl::construct(start.cur - 1, t);
        --start.cur;
      }
      else
      {
        push_front_aux(t);
      }
    }

  private:
    void fill_initialize(size_type n, const value_type &value);
    void create_map_and_node(size_type number_elements);
    static size_t buffer_size(){return __deque_buf_size(BufSiz, sizeof(T));}
    void push_back_aux(const value_type &t);
    void push_front_aux(const value_type &t);
    void reserve_map_at_back(size_type nodes_to_add = 1)
    {
      if(nodes_to_add + 1 > map_size - (finish.node - map))
      {
        reallocate_map(nodes_to_add, false);
      }
    }
    void reserve_map_at_front(size_type nodes_to_add = 1)
    {
      if(nodes_to_add > start.node - map)
      {
        reallocate_map(nodes_to_add, true);
      }
    }
    void reallocate_map(size_type nodes_to_add, bool add_at_front);
    static size_type initial_map_size() {return 8;}
    pointer allocate_node()
    {
      return data_allocator::allocate(buffer_size());
    }
    void deallocate_node(pointer n)
    {
      data_allocator::deallocate(n, buffer_size());
    }

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
void deque<T, Alloc, BufSize>::create_map_and_node(size_type num_elements)
{
  size_type num_nodes = num_elements / buffer_size() + 1;
  // TODO: will be changed to mystl::max
  map_size = std::max(initial_map_size(), num_nodes + 2);
  map = map_allocator::allocate(map_size);
  map_pointer nstart = map + (map_size - num_nodes) / 2;
  map_pointer nfinish = nstart + num_nodes - 1;
  map_pointer cur;
  try
  {
    for(cur = nstart; cur <= nfinish; ++cur)
    {
      *cur = allocate_node();
    }
  }
  catch(...)
  {
    // commit or rollback
  }
  start.set_node(nstart);
  finish.set_node(nfinish);
  start.cur = start.first;
  finish.cur = finish.first + num_elements % buffer_size();
}

template <class T, class Alloc, size_t BufSize>
void deque<T, Alloc, BufSize>::push_back_aux(const value_type &t)
{
  value_type t_copy = t;
  reserve_map_at_back();
  *(finish.node + 1) = allocate_node();
  try
  {
    mystl::construct(finish.cur, t_copy);
    finish.set_node(finish.node + 1);
    finish.cur = finish.first;
  }
  catch(...)
  {
    // commit or rollback
  }
}

template <class T, class Alloc, size_t BufSize>
void deque<T, Alloc, BufSize>::push_front_aux(const value_type &t)
{
  value_type t_copy = t;
  reserve_map_at_front();
  *(start.node - 1) = allocate_node();
  try
  {
    set_node(start.node - 1);
    start.cur = start.last - 1;
    mystl::construct(start.cur, t_copy);
  }
  catch(...)
  {
    // commit or rollback
    start.set_node(start.node + 1);
    start.cur = start.first;
    deallocate_node(*(start.node - 1));
    throw;
  }
}

template <class T, class Alloc, size_t BufSize>
void deque<T, Alloc, BufSize>::reallocate_map(size_type nodes_to_add, bool add_at_front)
{
  size_type old_num_nodes = finish.node - start.node + 1;
  size_type new_num_nodes = old_num_nodes + nodes_to_add;
  map_pointer new_nstart;
  if(map_size > 2 * new_num_nodes)
  {
    new_nstart = map + (map_size - new_num_nodes) / 2
      + (add_at_front ? nodes_to_add : 0);
    if(new_nstart < start.node)
    {
      // TODO: will be changed to mystl::copy
      std::copy(start.node, finish.node + 1, new_nstart);
    }
    else
    {
      // TODO: will be changed to mystl::copy_backward
      std::copy_backward(start.node, finish.node + 1, new_nstart + old_num_nodes);
    }
  }
  else
  {
    // TODO: will be changed to mystl::max
    size_type new_map_size = map_size + std::max(map_size, nodes_to_add) + 2;
    size_type new_map = map_allocator::allocate(new_map_size);
    new_nstart = new_map + (new_map_size - new_num_nodes) / 2
      + (add_at_front ? nodes_to_add : 0);
    // TODO: will be changed to mystl::copy
    std::copy(start.node, finish.node + 1, new_nstart);
    map_allocator::deallocate(map);
    map = new_map;
    map_size = new_map_size;
  }
  start.set_node(new_nstart);
  finish.set_node(new_nstart + old_num_nodes - 1);
}

} // end of namespace stl

#endif
