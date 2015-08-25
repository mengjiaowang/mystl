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

#ifndef MYSTL_MULTISET_H_
#define MYSTL_MULTISET_H_

#include "mystl_function.h"
#include "mystl_alloc.h"
#include "mystl_rb_tree.h"

namespace mystl
{
  template <class Key, class Compare = mystl::less<Key>, class Alloc = mystl::alloc>
  class multiset
  {
    public:
      typedef Key key_type;
      typedef Key value_type;
      typedef Compare key_compare;
      typedef Compare value_compare;
    private:
      typedef mystl::rb_tree<key_type, value_type,
              mystl::identity<value_type>, key_compare, Alloc> rep_type;
      rep_type t; // red-black tree representing multiset
    public:
      typedef typename rep_type::const_pointer pointer;
      typedef typename rep_type::const_pointer const_pointer;
      typedef typename rep_type::const_reference reference;
      typedef typename rep_type::const_reference const_reference;
      typedef typename rep_type::const_iterator iterator;
      typedef typename rep_type::const_iterator const_iterator;
      typedef typename rep_type::size_type size_type;
      typedef typename rep_type::difference_type difference_type;

      // allocation and deallocation

      multiset() : t(Compare()) {}
      explicit multiset(const Compare &comp) : t(comp) {}

      template <class InputIterator>
      multiset(InputIterator first, InputIterator last)
        : t(Compare()) {t.insert_equal(first, last);}
      template <class InputIterator>
      multiset(InputIterator first, InputIterator last, const Compare &comp)
        : t(comp) {t.insert_equal(first, last);}

      multiset(const multiset<Key, Compare, Alloc> &x) : t(x.t) {}
      multiset<Key, Compare, Alloc> & operator=(const multiset<Key, Compare, Alloc> &x)
      {
        t = x.t;
        return *this;
      }

      // accessors
      key_compare key_comp() const {return t.key_comp();}
      value_compare value_comp() const {return t.key_comp();}
      iterator begin() const {return t.begin();}
      iterator end() const {return t.end();}
      bool empty() const {return t.empty();}
      size_type size() const {return t.size();}
      size_type max_size() const {return t.max_size();}

      // insert and erase
      iterator insert(const value_type &x)
      {
        return t.insert_equal(x);
      }

      iterator insert(iterator position, const value_type &x)
      {
        typedef typename rep_type::iterator rep_iterator;
        return t.insert_equal((rep_iterator&)position, x);
      }

      template <class InputIterator>
      void insert(InputIterator first, InputIterator last)
      {
        t.insert_equal(first, last);
      }

      void erase(iterator position)
      {
        typedef typename rep_type::iterator rep_iterator;
        t.erase((rep_iterator&)position);
      }

      size_type erase(const key_type &x)
      {
        return t.erase(x);
      }

      void erase(iterator first, iterator last)
      {
        typedef typename rep_type::iterator rep_iterator;
        t.erase((rep_iterator&) first, (rep_iterator&) last);
      }

      void clear() {t.clear();}

      // multiset operations
      iterator find(const key_type &x) const {return t.find(x);}
      size_type count(const key_type &x) const {return t.count(x);}

  };
} // end of namespace mystl

#endif
