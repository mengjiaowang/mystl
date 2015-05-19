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

#ifndef MYSTL_VECTOR_H_
#define MYSTL_VECTOR_H_

#include "mystl_alloc.h"
#include "mystl_construct.h"
#include "mystl_uninitialized.h"

namespace mystl
{
  template <class T, class Alloc = alloc>
  class vector
  {
    public:
      typedef T value_type;
      typedef value_type* pointer;
      typedef value_type* iterator;
      typedef value_type& reference;
      typedef size_t size_type;
      typedef ptrdiff_t difference_type;

    protected:
      typedef simple_alloc<value_type, Alloc> data_allocator;
      iterator start;
      iterator finish;
      iterator end_of_storage;

      void insert_aux(iterator positoin, const T& x);
      void deallocate()
      {
        if(start)
        {
          data_allocator::deallocate(start, end_of_storage - start);
        }
      }
      void fill_initialize(size_type n, const T& value)
      {
        start = allocate_and_fill(n, value);
        end_of_storage = finish;
      }

    public:
      iterator begin() {return start;}
      iterator end() {return finish;}
      size_type size()const {return size_type(end()-begin());}
      size_type capacity()const
      {
        return size_type(end_of_storage-begin());
      }
      bool empty()const {return begin()==end();}
      reference operator[](size_type n){return *(begin()+n);}

      vector(): start(0), finish(0), end_of_storage(0){}
      vector(size_type n, const T &value){fill_initialize(n, value);}
      vector(int n, const T &value){fill_initialize(n, value);}
      vector(long n, const T &value){fill_initialize(n, value);}
      explicit vector(size_type n){fill_initialize(n, T());}

      ~vector()
      {
        mystl::destroy(start, finish);
        deallocate();
      }
      reference front() {return *begin();}
      reference back() {return *(end()-1);}
      void push_back(const T &x)
      {
        if(finish != end_of_storage)
        {
          mystl::construct(finish, x);
          ++finish;
        }
        else
        {
          insert_aux(end(), x);
        }
      }
      void pop_back()
      {
        --finish;
        mystl::destroy(finish);
      }
      iterator erase(iterator position)
      {
        if(position + 1 != end())
        {
          mystl::copy(position + 1, finish, position);
        }
        --finish;
        destroy(finish);
        return position;
      }
      void resize(size_type new_size, const T &x)
      {
        if(new_size < size())
        {
          erase(begin() + new_size, end());
        }
        else
        {
          insert(end(), new_size - size(), x);
        }
      }
      void resize(size_type new_size)
      {
        resize(new_size, T());
      }
      void clear()
      {
        erase(begin(), end());
      }

    protected:
      iterator allocate_and_fill(size_type n, const T &x)
      {
        iterator result = data_allocator::allocate(n);
        mystl::uninitialized_fill_n(result, n, x);
        return result;
      }
  };
} // end of my stl

#endif
