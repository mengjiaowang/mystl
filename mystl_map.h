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

#ifndef MYSTL_MAP_H_
#define MYSTL_MAP_H_

#include "mystl_function.h"
#include "mystl_alloc.h"
#include "mystl_rb_tree.h"
#include "mystl_pair.h"

namespace mystl
{
  template <class Key, class T, class Compare = mystl::less<Key>, class Alloc = alloc>
  class map
  {
    public:
      typedef Key key_type;
      typedef T data_type;
      typedef T mapped_type;
      typedef mystl::pair<const Key, T> value_type;
      typedef Compare key_compare;

      class value_compare: public mystl::binary_function<value_type, value_type, bool>
      {
        friend class map<Key, T, Compare, Alloc>;
        protected:
          Compare comp;
          value_compare(Compare c): comp(c){}
        public:
          bool operator()(const value_type &x, const value_type &y) const
          {
            return comp(x.first, y.first);
          }
      };

    private:
      typedef rb_tree<key_type, value_type,
              select1st<value_type>, key_compare, Alloc> rep_type;
      rep_type t;

    public:
        typedef typename rep_type::pointer pointer;
        typedef typename rep_type::const_pointer const_pointer;
        typedef typename rep_type::reference reference;
        typedef typename rep_type::const_reference const_reference;
        typedef typename rep_type::iterator iterator;
        typedef typename rep_type::const_iterator const_iterator;
        typedef typename rep_type::size_type size_type;
        typedef typename rep_type::difference_type difference_type;

        // allocation and deallocation
        map(): t(Compare()) {}
        explicit map(const Compare &comp): t(comp) {}
        template <class InputIterator>
        map(InputIterator first, InputIterator last)
        :t(Compare()) {t.insert_unique(first, last);}
        template <class InputIterator>
        map(InputIterator first, InputIterator last, const Compare &comp)
        :t(comp) {t.insert_unique(first, last);}

        // accessors
        key_compare key_comp() const {return t.key_comp();}
        value_compare value_comp() const {return value_compare(t.key_comp());}
        iterator begin() {return t.begin();}
        const_iterator begin() const {return t.begin();}
        iterator end() {return t.end();}
        const_iterator end() const {return t.end();}
        bool empty() {return t.empty();}
        size_type size() const {return t.size();}
        size_type max_size() const {return t.max_size();}
        T& operator[] (const key_type &k)
        {
          return (*((insert(value_type(k, T()))).first)).second;
        }

        // insert and erase
        mystl::pair<iterator, bool> insert(const value_type &x)
        {
          return t.insert_unique(x);
        }

        iterator insert(iterator position, const value_type &x)
        {
          return t.insert_unique(position, x);
        }

        template <class InputIterator>
        void insert(InputIterator first, InputIterator last)
        {
          t.insert_unique(first, last);
        }

        iterator eraes(iterator position)
        {
          t.erase(position);
        }
        void clear()
        {
          t.clear();
        }
  };
} // end of namespace mystl

#endif
