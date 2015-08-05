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

#ifndef MYSTL_SET_H_
#define MYSTL_SET_H_

#include "mystl_function.h"
#include "mystl_alloc.h"
#include "mystl_rb_tree.h"
#include "mystl_pair.h"

namespace mystl
{
  // will be replaced by mystl::less<Key>
  template <class Key, class Compare = std::less<Key>, class Alloc = alloc>
  class set
  {
    public:
      typedef Key key_type;
      typedef Key value_type;
      typedef Compare key_compare;
      typedef Compare value_compare;

    private:
      typedef mystl::rb_tree<key_type, value_type, identity<value_type>,
              key_compare, Alloc> rep_type;
      rep_type t; // red-black tree

    public:
      typedef typename rep_type::const_pointer pointer;
      typedef typename rep_type::const_pointer const_pointer;
      typedef typename rep_type::const_reference reference;
      typedef typename rep_type::const_reference const_reference;
      typedef typename rep_type::const_iterator iterator;

      typedef typename rep_type::const_iterator const_iterator;
      typedef typename rep_type::size_type size_type;
      typedef typename rep_type::difference_type difference_type;

      // constructors
      set(): t(Compare()) {}

      explicit set(const Compare &comp): t(comp) {}

      template<class InputIterator>
      set(InputIterator first, InputIterator last): t(Compare())
      {
        t.insert_unique(first, last);
      }

      template<class InputIterator>
      set(InputIterator first, InputIterator last, const Compare &comp): t(comp)
      {
        t.insert_unique(first, last);
      }

      // accessors
      key_compare key_comp() const {return t.key_comp;}
      value_compare value_comp() const {return t.value_comp;}
      iterator begin() const {return t.begin();}
      iterator end() const {return t.end();}
      bool empty() const {return t.empty();}
      size_type size() const {return t.size();}
      size_type max_size() const {return t.max_size();}
      void swap(set<Key, Compare, Alloc> &x) {t.swap(x, t);}

      // insert and erase
      typedef mystl::pair<iterator, bool> pair_iterator_bool;

      mystl::pair<iterator, bool> insert(const value_type &x)
      {
        mystl::pair<typename rep_type::iterator, bool> p = t.insert_unique(x);
        return mystl::pair<iterator, bool>(p.first, p.second);
      }

      template<class InputIterator>
      void insert(InputIterator first, InputIterator last)
      {
        t.insert_unique(first, last);
      }

      // test find
      iterator find(const key_type &x) {return t.find(x);}
  };

} // end of namepsace mystl

#endif
