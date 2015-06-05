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

#ifndef MYSTL_SLIST_H_
#define MYSTL_SLIST_H_

#include "mystl_alloc.h"

namespace mystl
{
  struct __slist_node_base
  {
    __slist_node_base* next;
  };

  template <class T>
  struct __slist_node: public __slist_node_base
  {
    T data;
  };

  inline __slist_node_base* __slist_make_link(
      __slist_node_base *prev_node, __slist_node_base *new_node)
  {
    new_node->next = prev_node->next;
    prev_node->next = new_node;
    return new_node;
  }

  inline size_t __slist_size(__slist_node_base *node)
  {
    size_t result = 0;
    for(; node != 0; node = node->next) ++result;
    return result;
  }

  struct __slist_iterator_base
  {
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef forward_iterator_tag iterator_category;

    __slist_node_base *node;
    __slist_iterator_base(__slist_node_base *x): node(x){}

    void incr(){node = node->next;}
    bool operator==(const __slist_iterator_base &x) const
    {
      return node == x.node;
    }
    bool operator!=(const __slist_iterator_base &x) const
    {
      return node != x.node;
    }
  };

  template <class T, class Ref, class Ptr>
  struct __slist_iterator: public __slist_iterator_base
  {
    typedef __slist_iterator<T, T&, T*> iterator;
    typedef __slist_iterator<T, const T&, const T*> const_iterator;
    typedef __slist_iterator<T, Ref, Ptr> self;

    typedef T value_type;
    typedef Ptr pointer;
    typedef Ref reference;
    typedef __slist_node<T> list_node;

    __slist_iterator(list_node *x): __slist_iterator_base(x){}
    __slist_iterator(): __slist_iterator_base(0){}
    __slist_iterator(const iterator &x): __slist_iterator_base(x.node){}

    reference operator*() const {return ((list_node*)node)->data;}
    pointer operator->() const {return *(operator*());}
    self& operator++()
    {
      incr();
      return *this;
    }
    self operator++(int)
    {
      self tmp = *this;
      incr();
      return tmp;
    }
  };

  template <class T, class Alloc=alloc>
  class slist
  {
    public:
      typedef T value_type;
      typedef value_type* pointer;
      typedef const value_type* const_pointer;
      typedef value_type& reference;
      typedef const value_type& const_reference;
      typedef size_t size_type;
      typedef ptrdiff_t difference_type;
      typedef __slist_iterator<T, T&, T*> iterator;

    private:
      typedef __slist_node<T> list_node;
      typedef __slist_node_base list_node_base;
      typedef __slist_iterator_base iterator_base;
      typedef simple_alloc<list_node, alloc> list_node_allocator;

      static list_node* create_node(const value_type &x)
      {
        list_node *node = list_node_allocator::allocate();
        try
        {
          mystl::construct(&node->data, x);
          node->next = 0;
        }
        catch(...)
        {
          list_node_allocator::deallocate(node);
        }
        return node;
      }

      static void destroy_node(list_node *node)
      {
        mystl::destroy(&node->data);
        list_node_allocator::deallocate(node);
      }

    private:
      list_node_base head;

    public:
      slist() {head.next = 0;}
      ~slist() {clear();}

      iterator begin() {return iterator((list_node*)head.next);}
      iterator end() {return iterator(0);}
      size_type size() const {return __slist_size(head.next);}
      bool empty() const {return head.next == 0;}

      void swap(slist &L)
      {
        list_node_base* tmp = head.next;
        head.next = L.head.next;
        L.head.next = tmp;
      }

      reference front() {return ((list_node*)head.next)->data;}
      void push_front(const value_type &x)
      {
        __slist_make_link(&head, create_node(x));
      }
      void pop_front()
      {
        list_node *node = (list_node*)head.next;
        head.next = node->next;
        destroy_node(node);
      }
      iterator erase_after(iterator pos)
      {
        return iterator((list_node*)erase_after(pos.node));
      }
      iterator erase_after(iterator first, iterator last)
      {
        return iterator((list_node*)erase_after(first, last));
      }
      void clear(){erase_after(&head, 0);}

    private:
      list_node_base *erase_after(list_node_base *pos)
      {
        list_node *next = (list_node*)(pos->next);
        list_node_base *next_next = next->next;
        pos->next = next_next;
        destroy_node(next);
        return next_next;
      }

      list_node_base *erase_after(list_node_base *before_first,
          list_node_base *last_node)
      {
        list_node* cur = (list_node*) (before_first->next);
        while(cur != last_node)
        {
          list_node *tmp = cur;
          cur = (list_node*) cur->next;
          destroy_node(tmp);
        }
        before_first->next = last_node;
        return last_node;
      }

  };

} // end of namespace mystl

#endif
