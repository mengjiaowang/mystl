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

#ifndef DEFALLOC_H_
#define DEFALLOC_H_

#include <new>
#include <cstddef>
#include <cstdlib>
#include <limits>
#include <iostream>

namespace mystl
{
  template <class T>
  inline T* allocate(ptrdiff_t size, T*)
  {
    std::set_new_handler(0);
    T* tmp = (T*)(::operator new((size_t)(size*sizeof(T))));
    if(tmp == 0)
    {
      std::cerr << "out of memory!" << std::endl;
      exit(1);
    }
    return tmp;
  }

  template <class T>
  inline void deallocate(T* buffer)
  {
    ::operator delete(buffer);
  }

  template <class T>
  class allocator
  {
    public:
      typedef T value_type;
      typedef T* pointer;
      typedef const T* const_pointer;
      typedef T& reference;
      typedef const T& const_reference;
      typedef size_t size_type;
      typedef ptrdiff_t difference_type;

      pointer allocate(size_type n)
      {
        return mystl::allocate((difference_type)n, (pointer)0);
      }

      void deallocate(pointer p)
      {
        mystl::deallocate(p);
      }

      pointer address(reference x)
      {
        return (pointer)&x;
      }

      const_pointer const_address(const_reference x)
      {
        return (const_pointer)&x;
      }

      size_type init_page_size()
      {
        return mystl::max(size_type(1), size_type(4096/sizeof(T)));
      }

      size_type max_size()
      {
        return mystl::max(size_type(1), size_type(UINT_MAX/sizeof(T)));
      }
  };

  // specialization
  template<>
  class allocator<void>
  {
    public:
      typedef void* pointer;
  };
} // end of namespace mystl

#endif

