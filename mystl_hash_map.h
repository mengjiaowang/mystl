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

#ifndef MYSTL_HASH_MAP_H_
#define MYSTL_HASH_MAP_H_

#include "mystl_function.h"
#include "mystl_alloc.h"
#include "mystl_hashtable.h"
#include "mystl_pair.h"

namespace mystl
{
  template <class Key,
            class T,
            class HashFcn = mystl::hash<Key>,
            class EqualKey = mystl::equal_to<Key>,
            class Alloc = alloc>
  class hash_map
  {
    private:
      typedef hashtable<mystl::pair<const Key, T>, Key, HashFcn,
              mystl::select1st<mystl::pair<const Key, T> >, EqualKey, Alloc> ht;
      ht rep;

    public:
      typedef typename ht::key_type key_type;
      typedef T data_type;
      typedef T mapped_type;
      typedef typename ht::value_type value_type;
      typedef typename ht::hasher hasher;
      typedef typename ht::key_equal key_equal;

      typedef typename ht::size_type size_type;
      typedef typename ht::difference_type difference_type;
      typedef typename ht::pointer pointer;
      typedef typename ht::const_pointer const_pointer;
      typedef typename ht::reference reference;
      typedef typename ht::const_reference const_reference;

      typedef typename ht::iterator iterator;
      typedef typename ht::const_iterator const_iterator;

      hasher hash_funct() const {return rep.hash_funct();}
      key_equal key_eq() const {return rep.key_eq();}

    public:
      hash_map(): rep(100, hasher(), key_equal()) {}
      explicit hash_map(size_type n): rep(n, hasher(), key_equal()) {}
      hash_map(size_type n, const hasher &hf): rep(n, hf, key_equal()) {}
      hash_map(size_type n, const hasher &hf, key_equal &eql): rep(n, hf, eql) {}

      template <class InputIterator>
      hash_map(InputIterator first, InputIterator last)
      :rep(100, hasher(), key_equal())
      {
        rep.insert_unique(first, last);
      }

      template <class InputIterator>
      hash_map(InputIterator first, InputIterator last, size_type n)
      :rep(n, hasher(), key_equal())
      {
        rep.insert_unique(first, last);
      }

      template <class InputIterator>
      hash_map(InputIterator first, InputIterator last, size_type n, const hasher& hf)
      :rep(n, hf, key_equal())
      {
        rep.insert_unique(first, last);
      }

      template <class InputIterator>
      hash_map(InputIterator first, InputIterator last, size_type n,
          const hasher& hf, const key_equal& eql)
      :rep(n, hf, eql)
      {
        rep.insert_unique(first, last);
      }

    public:
      size_type size() const {return rep.size();}
      size_type max_size() const {return rep.max_size();}
      bool empty() const {return rep.empty();}
      void swap(hash_map &hm) {rep.swap(hm.rep);}
      friend bool operator==__STL_NULL_TMPL_ARGS(const hash_map &,
          const hash_map &);

      iterator begin() {return rep.begin();}
      iterator end() {return rep.end();}
      const_iterator begin() const {return rep.begin();}
      const_iterator end() const {return rep.end();}

    public:
      mystl::pair<iterator, bool> insert(const value_type &obj)
      {
        return rep.insert_unique(obj);
      }

      template <class InputIterator>
      void insert(InputIterator first, InputIterator last)
      {
        rep.insert_unique(first, last);
      }

      iterator find(const key_type &key)
      {
        return rep.find(key);
      }

      const_iterator find(const key_type &key) const
      {
        return rep.find(key);
      }

      size_type count(const key_type &key) const
      {
        return rep.count(key);
      }

      size_type erase(const key_type &key)
      {
        return rep.erase(key);
      }

      void erase(iterator it)
      {
        rep.erase(it);
      }

      void erase(iterator first, iterator last)
      {
        rep.erase(first, last);
      }

      void clear()
      {
        rep.clear();
      }
  };

  template <class Key, class T, class HashFcn, class EqualKey, class Alloc>
  inline bool operator==(const hash_map<Key, T, HashFcn, EqualKey, Alloc> &hm1,
                         const hash_map<Key, T, HashFcn, EqualKey, Alloc> &hm2)
  {
    return hm1.rep == hm2.rep;
  }

} // end of namespace mystl

#endif
