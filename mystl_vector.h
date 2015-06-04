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

#include <algorithm>

namespace mystl
{
  template <class T, class Alloc = alloc>
  class vector
  {
    public:
      typedef T value_type;
      typedef value_type* pointer;
      typedef const value_type* const_pointer;
      typedef value_type* iterator;
      typedef const value_type* const_iterator;
      typedef value_type& reference;
      typedef const value_type& const_reference;
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
        finish = start + n;
        end_of_storage = finish;
      }

    public:
      iterator begin() {return start;}
      const_iterator begin()const {return start;}
      iterator end() {return finish;}
      const_iterator end()const {return finish;}
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
          //TODO: change to mystl::copy
          std::copy(position + 1, finish, position);
        }
        --finish;
        destroy(finish);
        return position;
      }

      iterator erase(iterator first, iterator last)
      {
        //TODO: change to mystl::copy
        iterator i = std::copy(last, finish, first);
        destroy(i, finish);
        finish = finish - (last - first);
        return first;
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

      iterator insert(iterator position, const T &x)
      {
        size_type n = position - begin();
        if(finish != end_of_storage && position == end())
        {
          construct(position, x);
          ++finish;
        }
        else
        {
          insert_aux(position, x);
        }
        return begin() + n;
      }

      void insert(iterator position, size_type n, const T &x);

      void resize(size_type new_size) { resize(new_size, T());}
      void clear() { erase(begin(), end());}


    protected:
      iterator allocate_and_fill(size_type n, const T &x)
      {
        iterator result = data_allocator::allocate(n);
        mystl::uninitialized_fill_n(result, n, x);
        return result;
      }
  };

  template <class T, class Alloc>
  void vector<T, Alloc>::insert(iterator position, size_type n, const T &x)
  {
    if(n != 0)
    {
      if(size_type(end_of_storage - finish) >= n) // enough space
      {
        T x_copy = x;
        const size_type elems_after = finish - position;
        iterator old_finish = finish;
        if(elems_after > n)
        {
          mystl::uninitialized_copy(finish - n, finish, finish);
          finish += n;
          //TODO: change to mystl::copy_backward and mystl::fill
          std::copy_backward(position, old_finish - n, old_finish);
          std::fill(position, position + n, x_copy);
        }
        else
        {
          mystl::uninitialized_fill_n(finish - n, n - elems_after, x_copy);
          finish += n - elems_after;
          mystl::uninitialized_copy(position, old_finish, finish);
          finish += elems_after;
          std::fill(position, old_finish, x_copy);
        }
      }
      else // no enough space
      {
        const size_type old_size = size();
        const size_type len = old_size + std::max(old_size, n);
        iterator new_start = data_allocator::allocate(len);
        iterator new_finish = new_start;
        try
        {
          new_finish = mystl::uninitialized_copy(start, position, new_start);
          new_finish = mystl::uninitialized_fill_n(new_finish, n, x);
          new_finish = mystl::uninitialized_copy(position, finish, new_finish);
        }
        catch(...)
        {
          // commit or rollback
          mystl::destroy(new_start, new_finish);
          data_allocator::deallocate(new_start, len);
          throw;
        }
        mystl::destroy(start, finish);
        deallocate();
        start = new_start;
        finish = new_finish;
        end_of_storage = new_start + len;
      }
    }
  }

  template <class T, class Alloc>
  void vector<T, Alloc>::insert_aux(iterator position, const T &x)
  {
    if(finish != end_of_storage)
    {
      mystl::construct(finish, *(finish-1));
      ++finish;
      T x_copy = x;
      //TODO: change to mystl::copy_backward
      std::copy_backward(position, finish - 2, finish - 1);
      *position = x_copy;
    }
    else
    {
      const size_type old_size = size();
      const size_type len = old_size != 0 ? 2 * old_size : 1;
      iterator new_start = data_allocator::allocate(len);
      iterator new_finish = new_start;
      try
      {
        new_finish = mystl::uninitialized_copy(start, position, new_start);
        construct(new_finish, x);
        ++new_finish;
        new_finish = mystl::uninitialized_copy(position, finish, new_finish);
      }
      catch(...)
      {
        // commit or rollback
        mystl::destroy(new_start, new_finish);
        data_allocator::deallocate(new_start, len);
        throw;
      }
      mystl::destroy(begin(), end());
      deallocate();
      start = new_start;
      finish = new_finish;
      end_of_storage = new_start + len;
    }
  }

  template <class T, class Alloc>
  inline bool operator==(const mystl::vector<T, Alloc> &x, const mystl::vector<T, Alloc> &y)
  {
    return x.size() == y.size() && std::equal(x.begin(), x.end(), y.begin());
  }

  template <class T, class Alloc>
  inline bool operator!=(const mystl::vector<T, Alloc> &x, const mystl::vector<T, Alloc> &y)
  {
    return !(x == y);
  }

  template <class T, class Alloc>
  inline bool operator<(const vector<T, Alloc> &x, const vector<T, Alloc> &y)
  {
    return std::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
  }

  template <class T, class Alloc>
  inline bool operator>(const mystl::vector<T, Alloc> &x, const mystl::vector<T, Alloc> &y)
  {
    return (y < x);
  }

  template <class T, class Alloc>
  inline bool operator>=(const mystl::vector<T, Alloc> &x, const mystl::vector<T, Alloc> &y)
  {
    return !(x < y);
  }

  template <class T, class Alloc>
  inline bool operator<=(const mystl::vector<T, Alloc> &x, const mystl::vector<T, Alloc> &y)
  {
    return !(y < x);
  }

} // end of my stl

#endif
