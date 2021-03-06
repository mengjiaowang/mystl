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

#ifndef MYSTL_RB_TREE_H_
#define MYSTL_RB_TREE_H_

#include "memory"
#include "mystl_iterator.h"
#include "mystl_pair.h"

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
    typedef Value value_type;
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

  inline bool operator==(const __rb_tree_base_iterator &x,
      const __rb_tree_base_iterator &y)
  {
    return x.node == y.node;
  }

  inline bool operator!=(const __rb_tree_base_iterator &x,
      const __rb_tree_base_iterator &y)
  {
    return x.node != y.node;
  }

  inline void __rb_tree_rotate_left(__rb_tree_node_base *x,
      __rb_tree_node_base *&root)
  {
    __rb_tree_node_base *y = x->right;
    x->right = y->left;
    if(y->left != 0)
      y->left->parent = x;
    y->parent = x->parent;
    if(x == root)
      root = y;
    else if(x == x->parent->left)
      x->parent->left = y;
    else
      x->parent->right = y;
    y->left = x;
    x->parent = y;
    root->parent->parent = root;
  }

  inline void __rb_tree_rotate_right(__rb_tree_node_base *x,
      __rb_tree_node_base *&root)
  {
    __rb_tree_node_base *y = x->left;
    x->left = y->right;
    if(y->right != 0)
      y->right->parent = x;
    y->parent = x->parent;
    if(x == root)
      root = y;
    else if(x == x->parent->right)
      x->parent->right = y;
    else
      x->parent->left = y;
    y->right = x;
    x->parent = y;
    root->parent->parent = root;
  }

  inline void __rb_tree_rebalance(__rb_tree_node_base *x, __rb_tree_node_base *root)
  {
    x->color = __rb_tree_red;
    while(x != root && x->parent->color == __rb_tree_red)
    {
      if(x->parent == x->parent->parent->left)
      {
        __rb_tree_node_base *y = x->parent->parent->right;
        if(y && y->color == __rb_tree_red)
        {
          x->parent->color = __rb_tree_black;
          y->color = __rb_tree_black;
          x->parent->parent->color = __rb_tree_red;
          x = x->parent->parent;
        }
        else
        {
          if(x == x->parent->right)
          {
            x = x->parent;
            __rb_tree_rotate_left(x, root);
          }
          x->parent->color = __rb_tree_black;
          x->parent->parent->color = __rb_tree_red;
          __rb_tree_rotate_right(x->parent->parent, root);
        }
      }
      else
      {
        __rb_tree_node_base *y = x->parent->parent->left;
        if(y && y->color == __rb_tree_red)
        {
          x->parent->color = __rb_tree_black;
          y->color = __rb_tree_black;
          x->parent->parent->color = __rb_tree_red;
          x = x->parent->parent;
        }
        else
        {
          if(x == x->parent->left)
          {
            x = x->parent;
            __rb_tree_rotate_right(x, root);
          }
          x->parent->color = __rb_tree_black;
          x->parent->parent->color = __rb_tree_red;
          __rb_tree_rotate_left(x->parent->parent, root);
        }
      }
    }
    root->color = __rb_tree_black;
  }

  inline __rb_tree_node_base* __rb_tree_rebalance_for_erase(
      __rb_tree_node_base* z,
      __rb_tree_node_base*& root,
      __rb_tree_node_base*& leftmost,
      __rb_tree_node_base*& rightmost)
  {
    __rb_tree_node_base* y = z;
    __rb_tree_node_base* x = 0;
    __rb_tree_node_base* x_parent = 0;

    if(y->left == 0) x = y->right;
    else
    {
      if(y->right == 0) x = y->left;
      else
      {
        y = y->left;
        while(y->left != 0) y = y->left;
        x = y->right;
      }
    }
    if(y != z)
    {
      z->left->parent = y;
      y->left = z->left;
      if(y != z->right)
      {
        x_parent = y->parent;
        if(x) x->parent = y->parent;
        y->parent->left = x;
        y->right = z->right;
        z->right->parent = y;
      }
      else x_parent = y;
      if(root == z) root = y;
      else if(z->parent->left == z)
        z->parent->left = y;
      else
        z->parent->right = y;
      y->parent = z->parent;
      mystl::swap(y->color, z->color);
      y = z;
    }
    else
    {
      x_parent = y->parent;
      if(x) x->parent = y->parent;
      if(root == z) root = x;
      else
      {
        if(z->parent->left == z)
          z->parent->left = x;
        else
          z->parent->right = x;
      }
      if(leftmost == z)
      {
        if(z->right == 0)
          leftmost = z->parent;
        else
          leftmost = __rb_tree_node_base::minimum(x);
      }
    }

    if(y->color != __rb_tree_red)
    {
      while(x != root && (x == 0 || x->color == __rb_tree_black))
      {
        if(x == x_parent->left)
        {
          __rb_tree_node_base* w = x_parent->right;
          if(w->color == __rb_tree_red)
          {
            w->color = __rb_tree_black;
            x_parent->color = __rb_tree_red;
            __rb_tree_rotate_left(x_parent, root);
            w = x_parent->right;
          }
          if((w->right == 0 || w->left->color == __rb_tree_black) &&
             (w->right == 0 || w->right->color == __rb_tree_black))
          {
            w->color = __rb_tree_red;
            x = x_parent;
            x_parent = x_parent->parent;
          }
          else
          {
            if(w->right == 0 || w->right->color == __rb_tree_black)
            {
              if(w->left) w->left->color = __rb_tree_black;
                w->color = __rb_tree_red;
              __rb_tree_rotate_right(w, root);
              w = x_parent->right;
            }
            w->color = x_parent->color;
            x_parent->color = __rb_tree_black;
            if(w->right) w->right->color = __rb_tree_black;
            __rb_tree_rotate_left(x_parent, root);
            break;
          }
        }
        else
        {
          __rb_tree_node_base* w = x_parent->left;
          if(w->color == __rb_tree_red)
          {
            w->color = __rb_tree_black;
            x_parent->color = __rb_tree_red;
            __rb_tree_rotate_right(x_parent, root);
            w = x_parent->left;
          }
          if((w->right == 0 || w->right->color == __rb_tree_black) &&
             (w->left == 0 || w->left->color == __rb_tree_black))
          {
            w->color = __rb_tree_red;
            x = x_parent;
            x_parent = x_parent->parent;
          }
          else
          {
            if(w->left == 0 || w->left->color == __rb_tree_black)
            {
              if(w->right) w->right->color = __rb_tree_black;
              w->color = __rb_tree_red;
              __rb_tree_rotate_left(w, root);
              w = x_parent->left;
            }
            w->color = x_parent->color;
            x_parent->color = __rb_tree_black;
            if(w->left) w->left->color = __rb_tree_black;
            __rb_tree_rotate_right(x_parent, root);
            break;
          }
        }
      }
      if(x) x->color = __rb_tree_black;
    }
    return y;
  }

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

    protected:
      size_type node_count;
      link_type header;
      Compare key_compare;

      link_type& root() const {return (link_type&)header->parent;}
      link_type& leftmost() const {return (link_type&)header->left;}
      link_type& rightmost() const {return (link_type&)header->right;}

      static link_type& left(link_type x) {return (link_type&)(x->left);}
      static link_type& right(link_type x) {return (link_type&)(x->right);}
      static link_type& parent(link_type x) {return (link_type&)(x->parent);}
      static reference value(link_type x) {return x->value_field;}
      static const Key& key(link_type x) {return KeyOfValue()(value(x));}
      static color_type& color(link_type x) {return (color_type&)(x->color);}

      static link_type& left(base_ptr x) {return (link_type&)(x->left);}
      static link_type& right(base_ptr x) {return (link_type&)(x->right);}
      static link_type& parent(base_ptr x) {return (link_type&)(x->parent);}
      static reference value(base_ptr x) {return ((link_type)x)->value_field;}
      static const Key& key(base_ptr x) {return KeyOfValue()(value(link_type(x)));}
      static color_type& color(base_ptr x) {return (color_type&)(link_type(x)->color);}

      static link_type minimum(link_type x)
      {
        return (link_type) __rb_tree_node_base::minimum(x);
      }

      static link_type maximum(link_type x)
      {
        return (link_type) __rb_tree_node_base::maximum(x);
      }

    public:
      typedef __rb_tree_iterator<value_type, reference, pointer> iterator;
      typedef __rb_tree_iterator<value_type, const_reference, const_pointer> const_iterator;

    private:
      iterator __insert(base_ptr x, base_ptr y, const value_type &v);
      link_type __copy(link_type x, link_type p);
      void __erase(link_type x);
      void init()
      {
        header = get_node();
        color(header) = __rb_tree_red;
        root() = 0;
        leftmost() = header;
        rightmost() = header;
      }


    public:
      rb_tree(const Compare &comp = Compare())
      :node_count(0), key_compare(comp)
      {
        init();
      }

      ~rb_tree()
      {
        clear();
        put_node(header);
      }

      rb_tree(const rb_tree<Key, Value, KeyOfValue, Compare, Alloc> &x)
        :node_count(0), key_compare(x.key_compare)
      {
        header = get_node();
        color(header) = __rb_tree_red;
        if(x.root() == 0)
        {
          root() = 0;
          leftmost() = header;
          rightmost() = header;
        }
        else
        {
          try
          {
            root() = __copy(x.root(), header);
            leftmost() = minimum(root());
            rightmost() = maimum(root());
          }
          catch(...)
          {
            put_node(header);
          }
        }
        node_count = x.node_count;
      }

      rb_tree<Key, Value, KeyOfValue, Compare, Alloc>& operator=(
          const rb_tree<Key, Value, KeyOfValue, Compare, Alloc> &x);

    public:
      Compare key_comp() const {return key_compare;}
      iterator begin() {return leftmost();}
      const_iterator begin() const {return leftmost();}
      iterator end() {return header;}
      const_iterator end() const {return header;}
      bool empty() const {return node_count == 0;}
      size_type size() const {return node_count;}
      size_type max_size() const {return size_type(-1);}
      iterator find(const Key &k);
      const_iterator find(const Key &k) const;

    public:
      mystl::pair<iterator, bool> insert_unique(const value_type &x);
      iterator insert_equal(const value_type &x);

      template <class InputIterator>
      void insert_unique(InputIterator first, InputIterator last);

      void erase(iterator position);
      size_type erase(const key_type &x);
      void erase(iterator first, iterator last);
      void erase(const key_type *first, const key_type *last);

      void clear()
      {
        if(node_count != 0)
        {
          __erase(root());
          leftmost() = header;
          root() = 0;
          rightmost() = header;
          node_count = 0;
        }
      }

    public:
      bool __rb_verify() const;
  };

  template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
  typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator
  rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::insert_equal(const Value &v)
  {
    link_type y = header;
    link_type x = root();
    while(x != 0)
    {
      y = x;
      x = key_compare(KeyOfValue()(v), key(x)) ? left(x) : right(x);
    }
    return __insert(x, y, v);
  }

  template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
  mystl::pair<typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator, bool>
  rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::insert_unique(const Value &v)
  {
    link_type y = header;
    link_type x = root();
    bool comp = true;
    while(x != 0)
    {
      y = x;
      comp = key_compare(KeyOfValue()(v), key(x));
      x = comp ? left(x) : right(x);
    }
    iterator j = iterator(y);
    if(comp)
    {
      if(j == begin()) return mystl::pair<iterator, bool>(__insert(x, y, v), true);
      else --j;
    }
    if(key_compare(key(j.node), KeyOfValue()(v)))
    {
      return mystl::pair<iterator, bool>(__insert(x, y, v), true);
    }
    return mystl::pair<iterator, bool>(j, false);
  }

  template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
  template <class InputIterator>
  void rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::insert_unique(
      InputIterator first, InputIterator last)
  {
    for(; first != last; ++first)
    {
      insert_unique(*first);
    }
  }

  template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
  typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator
  rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::
  __insert(base_ptr x_, base_ptr y_, const Value &v)
  {
    link_type x = (link_type) x_;
    link_type y = (link_type) y_;
    link_type z;

    if(y == header || x != 0 || key_compare(KeyOfValue()(v), key(y)))
    {
      z = create_node(v);
      left(y) = z;
      if(y == header)
      {
        root() = z;
        rightmost() = z;
      }
      else if (y == leftmost())
      {
        leftmost() = z;
      }
    }
    else
    {
      z = create_node(v);
      right(y) = z;
      if(y == rightmost())
      {
        rightmost() = z;
      }
    }
    parent(z) = y;
    left(z) = 0;
    right(z) = 0;
    __rb_tree_rebalance(z, header->parent);
    ++node_count;
    return iterator(z);
  }

  template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
  inline void rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::erase(iterator position)
  {
    link_type y = (link_type) __rb_tree_rebalance_for_erase(position.node,
        header->parent, header->left, header->right);
    destroy(y);
    --node_count;
  }

  template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
  bool rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::__rb_verify() const
  {
    if(node_count == 0 || begin() == end())
    {
      return node_count == 0 && begin() == end() &&
        header->left == header && header->right == header;
    }
    //int len = __black_count(leftmost(), root());
    for(const_iterator it = begin(); it != end(); ++it)
    {
      link_type x = (link_type) it.node;
      link_type L = left(x);
      link_type R = right(x);

      if(x->color == __rb_tree_red)
      {
        if((L && L->color == __rb_tree_red) || (R && R->color == __rb_tree_red))
          return false;
      }

      if(L && key_compare(key(x), key(L))) return false;
      if(R && key_compare(key(R), key(x))) return false;

      //if(!L && !R && __black_count(x, root()) != len) return false;
    }

    if(leftmost() != __rb_tree_node_base::minimum(root())) return false;
    if(rightmost() != __rb_tree_node_base::maximum(root())) return false;

    return true;
  }

  template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
  typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator
  rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::find(const Key &k)
  {
    link_type y = header;
    link_type x = root();
    while(x != 0)
    {
      if(!key_compare(key(x),k))
      {
        y = x;
        x = left(x);
      }
      else
      {
        x = right(x);
      }
    }
    iterator j = iterator(y);
    return (j == end() || key_compare(k, key(j.node))) ? end() : j;
  }

  template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
  typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::const_iterator
  rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::find(const Key &k) const
  {
    link_type y = header;
    link_type x = root();
    while(x != 0)
    {
      if(!key_compare(key(x),k))
      {
        y = x;
        x = left(x);
      }
      else
      {
        x = right(x);
      }
    }
    const_iterator j = iterator(y);
    return (j == end() || key_compare(k, key(j.node))) ? end() : j;
  }

  template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
  typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::link_type
  rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::__copy(link_type x, link_type p)
  {
    link_type top = clone_node(x);
    top->parent = p;
    try
    {
      if(x->right)
      {
        top->right = __copy(right(x), top);
      }
      p = top;
      x = left(x);

      while(x != 0)
      {
        link_type y = clone_node(x);
        p->left = y;
        y->parent = p;
        if(x->right)
        {
          y->right = __copy(right(x), y);
        }
        p = y;
        x = left(x);
      }
    }
    catch(...)
    {
      __eraes(top);
    }
    return top;
  }


  template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
  void rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::__erase(link_type x)
  {
    // eraes without rebalancing
    while(x != 0)
    {
      __erase(right(x));
      link_type y = left(x);
      destroy_node(x);
      x = y;
    }
  }

} // end of namespace mystl

#endif
