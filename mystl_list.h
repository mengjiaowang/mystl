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

#ifndef MYSTL_LIST_H_
#define MYSTL_LIST_H_

#include "mystl_alloc.h"
#include "mystl_construct.h"
#include "mystl_uninitialized.h"

#include <algorithm>

namespace mystl
{
  template <class T>
  struct __list_node
  {
    typedef void * void_pointer;
    void_pointer prev;
    void_pointer next;
    T data;
  };

  template <class T, class Ref, class Ptr>
  struct __list_iterator
  {
    typedef __list_iterator<T, T&, T*> iterator;
    typedef __list_iterator<T, T&, T*> self;
    typedef bidirectional_iterator_tag iterator_category;
    typedef T value_type;
    typedef Ptr pointer;
    typedef Ref reference;
    typedef __list_node<T> * link_type;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    link_type node;

    //constructor
    __list_iterator(link_type x): node(x){}
    __list_iterator(){}
    __list_iterator(const iterator &x): node(x.node){}

    bool operator==(const self &x) const {return node == x.node;}
    bool operator!=(const self &x) const {return node != x.node;}

    reference operator*() const {return (*node).data;}
    pointer operator->() const {return &(operator*());}
    self &operator++()
    {
      node = (link_type)((*node).next);
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
      node = (link_type)((*node).prev);
      return *this;
    }
    self &operator--(int)
    {
      self tmp = *this;
      --*this;
      return tmp;
    }
  };

  template <class T, class Alloc = alloc>
  class list
  {
    public:
      typedef T value_type;
      typedef __list_iterator<T, T&, T*> iterator;
      typedef const iterator const_iterator;
      typedef T & reference;
      typedef const value_type& const_reference;
      typedef size_t size_type;
      typedef __list_node<T> * link_type;

    protected:
      typedef __list_node<T> list_node;
      typedef simple_alloc<list_node, Alloc> list_node_allocator;

      link_type get_node(){return list_node_allocator::allocate();}
      void put_node(link_type p) {list_node_allocator::deallocate(p);}
      link_type create_node(const T& x)
      {
        link_type p = get_node();
        mystl::construct(&p->data, x);
        return p;
      }
      void destroy_node(link_type p)
      {
        destroy(&p->data);
        put_node(p);
      }
      void empty_initialization()
      {
        node = get_node();
        node->next = node;
        node->prev = node;
      }
      void transfer(iterator position, iterator first, iterator last);

    public:

      iterator begin(){return (link_type)((*node).next);}
      const_iterator begin() const{return (link_type)(*node).next;}
      iterator end(){return node;}
      const_iterator end() const{return node;}
      bool empty(){return node->next == node;}
      /*
      size_type size() const
      {
        size_type result = 0;
        distance(begin(), end(), result);
        return result;
      }
      */
      reference front(){return *begin();}
      reference back(){return *(--end());}
      iterator insert(iterator position, const T& x)
      {
        link_type tmp = create_node(x);
        tmp->next = position.node;
        tmp->prev = position.node->prev;
        (link_type(position.node->prev))->next = tmp;
        position.node->prev = tmp;
        return tmp;
      }
      void push_back(const T& x){insert(end(), x);}
      void push_front(const T& x){insert(begin(), x);}
      iterator erase(iterator position)
      {
        link_type next_node = link_type(position.node->next);
        link_type prev_node = link_type(position.node->prev);
        prev_node->next = next_node;
        next_node->prev = prev_node;
        destroy_node(position.node);
        return iterator(next_node);
      }
      void pop_front(){erase(begin());}
      void pop_back()
      {
        iterator tmp = end();
        erase(--tmp);
      }
      void clear();
      void remove(const T& value);
      void unique();
      void splice(iterator position, list &x)
      {
        if(!x.empty()) transfer(position, x.begin(), x.end());
      }

    public:
      // constructor
      list(){empty_initialization();}

    protected:
      link_type node;
  };

  template <class T, class Alloc>
  void list<T, Alloc>::clear()
  {
    link_type cur = (link_type) node->next; // begin()
    while(cur != node)
    {
      link_type tmp = cur;
      cur = (link_type) cur->next;
      destroy_node(tmp);
    }
    node->next = node;
    node->prev = node;
  }

  template <class T, class Alloc>
  void list<T, Alloc>::remove(const T& value)
  {
    iterator first = begin();
    iterator last = end();
    while(first != last)
    {
      iterator next = first;
      ++next;
      if(*first == value) erase(first);
      first = next;
    }
  }

  template <class T, class Alloc>
  void list<T, Alloc>::unique()
  {
    iterator first = begin();
    iterator last = end();
    if(first == last) return; // empty list
    iterator next = first;
    while(++next != last)
    {
      if(*first == *next) erase(next);
      else first = next;
    }
  }

  template <class T, class Alloc>
  void list<T, Alloc>::transfer(iterator position, iterator first, iterator last)
  {
    if(position != last)
    {
      (*(link_type((*last.node).prev))).next = position.node;
      (*(link_type((*first.node).prev))).next = last.node;
      (*(link_type((*position.node).prev))).next = first.node;
      link_type tmp = link_type((*position.node).prev);
      (*position.node).prev = (*last.node).prev;
      (*last.node).prev = (*first.node).prev;
      (*first.node).prev = tmp;
    }
  }

} // end of namespace mystl

#endif
