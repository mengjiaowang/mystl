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

#ifndef MYSTL_HASH_SET_H_
#define MYSTL_HASH_SET_H_

#include "mystl_function.h"
#include "mystl_alloc.h"
#include "mystl_hashtable.h"
#include "mystl_pair.h"

namespace mystl
{
  template <class Value,
            class HashFcn = mystl::hash<Value>,
            class EqualKey = mystl::equal_to<Value>,
            class Alloc = alloc>
  class hash_set
  {
    private:
      typedef mystl::hashtable<Value, Value, HashFcn, mystl::identity<Value>, EqualKey, Alloc> ht;
      ht rep;

    public:
      typedef typename ht::key_type key_type;
      typedef typename ht::value_type value_type;
      typedef typename ht::hasher hasher;
      typedef typename ht::key_equal key_equal;

      typedef typename ht::size_type size_type;
      typedef typename ht::difference_type difference_type;
      typedef typename ht::const_pointer pointer;
      typedef typename ht::const_pointer const_pointer;
      typedef typename ht::const_reference reference;
      typedef typename ht::const_reference const_reference;

      typedef typename ht::const_iterator iterator;
      typedef typename ht::const_iterator const_iterator;

      hasher hash_funct() const {return rep.hash_funct();}
      key_equal key_eq() const {return rep.key_eq();}

    public:
      // constructor
      hash_set(): rep(100, hasher(), key_equal()) {}
      explicit hash_set(size_type n): rep(n, hasher(), key_equal()) {}
      hash_set(size_type n, const hasher &hf): rep(n, hf, key_equal()) {}
      hash_set(size_type n, const hasher &hf, const key_equal &eql): rep(n, hf, eql) {}

      template <class InputIterator>
      hash_set(InputIterator first, InputIterator last): rep(100, hasher(), key_equal())
      {
        rep.insert(first, last);
      }

      template <class InputIterator>
      hash_set(InputIterator first, InputIterator last, size_type n)
      : rep(n, hasher(), key_equal())
      {
        rep.insert(first, last);
      }

      template <class InputIterator>
      hash_set(InputIterator first, InputIterator last, size_type n,
          const hasher &hf): rep(n, hf, key_equal())
      {
        rep.insert(first, last);
      }

      template <class InputIterator>
      hash_set(InputIterator first, InputIterator last, size_type n,
          const hasher &hf, const key_equal &eql): rep(n, hf, eql)
      {
        rep.insert(first, last);
      }

    public:

      size_type size() const {return rep.size();}
      size_type max_size() const {return rep.max_size();}
      bool empty() const {return rep.empty();}
      void swap(hash_set &hs) {rep.swap(hs.rep);}
      friend bool operator==__STL_NULL_TMPL_ARGS (const hash_set &,
          const hash_set&);
      iterator begin() const {return rep.begin();}
      iterator end() const {return rep.end();}

    public:
      mystl::pair<iterator, bool> insert(const value_type &obj)
      {
        mystl::pair<typename ht::iterator, bool> p = rep.insert_unique(obj);
        return mystl::pair<iterator, bool> (p.first, p.second);
      }

      template <class InputIterator>
      void insert(InputIterator first, InputIterator last)
      {
        rep.insert(first, last);
      }

      iterator find(const key_type &key) const
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
        rep.eraes(first, last);
      }

      void clear()
      {
        rep.clear();
      }

    public:

      void resize(size_type hint)
      {
        rep.resize(hint);
      }

      size_type bucket_count() const
      {
        return rep.bucket_count();
      }

      size_type max_bucket_count() const
      {
        return rep.max_bucket_count();
      }
  };

  template <class Value, class HashFcn, class EqualKey, class Alloc>
  inline bool operator==(const hash_set<Value, HashFcn, EqualKey, Alloc> &hs1,
      const hash_set<Value, HashFcn, EqualKey, Alloc> &hs2)
  {
    return hs1.rep == hs2.rep;
  }
} // end of namespace mystl

#endif
