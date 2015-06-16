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

#ifndef MYSTL_TREE_H_
#define MYSTL_TREE_H_

#include "memory"
#include "mystl_iterator.h"

namespace mystl
{
  typedef bool __rb_tree_color_type;
  const __rb_tree_color_type __rb_tree_red = false;
  const __rb_tree_color_type __rb_tree_black = true;

  struct __rb_tree_node_base
  {
    typedef __rb_tree_color_type color_type;
    typedef __rb_tree_node_base* base_ptr;

    color_type color;
    base_ptr parent;
    base_ptr left;
    base_ptr right;

    static base_ptr minimum(base_ptr x)
    {
      while(x->left != 0) x = x->left;
      return x;
    }

    static base_ptr maximum(base_ptr x)
    {
      while(x->right != 0) x = x->right;
      return x;
    }
  };

  template <class Value>
  struct __rb_tree_node: public __rb_tree_node_base
  {
    typedef __rb_tree_node<Value>* link_type;
    Value value_field;
  };

  struct __rb_tree_base_iterator
  {
    typedef __rb_tree_node_base::base_ptr base_ptr;
    typedef bidirectional_iterator_tag iterator_category;
    typedef ptrdiff_t difference_type;
    base_ptr node;

    void increment()
    {
      if(node->right != 0)
      {
        node = node->right;
        while(node->left != 0) node = node->left;
      }
      else
      {
        base_ptr y = node->parent;
        while(node == y->right)
        {
          node = y;
          y = y->parent;
        }
        if(node->right != y) node = y;
      }
    }

    void decrement()
    {
      if(node->color == __rb_tree_red && node->parent->parent == node)
      {
        node = node->right;
      }
      else if(node->left != 0)
      {
        base_ptr y = node->left;
        while(y->right != 0)
        {
          y = y->right;
        }
        node = y;
      }
      else
      {
        base_ptr y = node->parent;
        while(node == y->left)
        {
          node = y;
          y = y->parent;
        }
        node = y;
      }
    }
  };

  template <class Value, class Ref, class Ptr>
  struct __rb_tree_iterator: public __rb_tree_base_iterator
  {
    typedef Value valye_type;
    typedef Ref reference;
    typedef Ptr pointer;
    typedef __rb_tree_iterator<Value, Value&, Value*> iterator;
    typedef __rb_tree_iterator<Value, const Value&, const Value*> const_iterator;
    typedef __rb_tree_iterator<Value, Ref, Ptr> self;
    typedef __rb_tree_node<Value>* link_type;

    __rb_tree_iterator(){}
    __rb_tree_iterator(link_type x){node = x;}
    __rb_tree_iterator(const iterator& it){node = it.node;}

    reference operator*()const {return link_type(node)->value_field;}
    pointer operator->()const {return &(operator*());}
    self& operator++(){increment(); return *this;}
    self operator++(int)
    {
      self tmp = *this;
      increment();
      return tmp;
    }
    self& operator--(){decrement(); return *this;}
    self operator--(int)
    {
      self tmp = *this;
      decrement();
      return tmp;
    }
  };

  template <class Key, class Value, class KeyOfValue, class Compare, class Alloc = alloc>
  class rb_tree
  {
    protected:
      typedef void* void_pointer;
      typedef __rb_tree_node_base* base_ptr;
      typedef __rb_tree_node<Value> rb_tree_node;
      typedef simple_alloc<rb_tree_node, Alloc> rb_tree_node_allocator;
      typedef __rb_tree_color_type color_type;

    public:
      typedef Key key_type;
      typedef Value value_type;
      typedef value_type* pointer;
      typedef const value_type* const_pointer;
      typedef value_type& reference;
      typedef const value_type& const_reference;
      typedef rb_tree_node* link_type;
      typedef size_t size_type;
      typedef ptrdiff_t difference_type;

    protected:
      link_type get_node(){return rb_tree_node_allocator::allocate();}
      void put_node(link_type p){rb_tree_node_allocator::deallocate(p);}

      link_type create_node(const value_type &x)
      {
        link_type tmp = get_node();
        try
        {
          mystl::construct(&tmp->value_field, x);
        }
        catch(...)
        {
          // commit or rollback
          put_node(tmp);
        }
        return tmp;
      }

      link_type clone_node(link_type x)
      {
        link_type tmp = create_node(x->value_field);
        tmp->color = x->color;
        tmp->left = 0;
        tmp->right = 0;
        return tmp;
      }

      void destroy_node(link_type p)
      {
        mystl::destroy(&p->value_field);
        put_node(p);
      }
  };

} // end of namespace mystl

#endif
