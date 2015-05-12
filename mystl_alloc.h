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

#ifndef MYSTL_ALLOC_H_
#define MYSTL_ALLOC_H_

#ifndef __THROW_BAD_ALLOC
  #include <new>
  #define __THROW_BAD_ALLOC throw std::bad_alloc()
#endif

#include <cstddef>
#include <cstdlib>
#include <limits>

namespace mystl
{
  template <int inst>
  class __malloc_alloc_template
  {
    private:
      // oom: out of memory
      static void *oom_malloc(size_t);
      static void *oom_realloc(void*, size_t);
      static void (* __malloc_alloc_oom_handler)();

    public:
      static void *allocate(size_t n)
      {
        void *result = std::malloc(n);
        if(result == 0) result = oom_malloc(n);
        return result;
      }

      static void deallocate(void *p, size_t /* n */)
      {
        free(p);
      }

      static void *reallocate(void *p, size_t /* old size */, size_t new_sz /* new size */)
      {
        void *result = realloc(p, new_sz);
        if(result == 0) result = oom_realloc(p, new_sz);
        return result;
      }

      static void (*set_malloc_handler(void (*f)()))()
      {
        void (*old)() = __malloc_alloc_oom_handler;
        __malloc_alloc_oom_handler = f;
        return old;
      }
  };

  // malloc_alloc out-of-memory handling
  template <int inst>
  void (*__malloc_alloc_template<inst>::__malloc_alloc_oom_handler)() = 0;

  template <int inst>
  void *__malloc_alloc_template<inst>::oom_malloc(size_t n)
  {
    void (*my_malloc_handler)();
    void *result;
    for(;;)
    {
      my_malloc_handler = __malloc_alloc_oom_handler;
      if(my_malloc_handler == 0)
      {
        __THROW_BAD_ALLOC;
      }
      (*my_malloc_handler)();
      result = malloc(n);
      if(result) return result;
    }
  }

  template <int inst>
  void *__malloc_alloc_template<inst>::oom_realloc(void *p, size_t n)
  {
    void (*my_malloc_handler)();
    void *result;
    for(;;)
    {
      my_malloc_handler = __malloc_alloc_oom_handler;
      if(my_malloc_handler == 0)
      {
        __THROW_BAD_ALLOC;
      }
      (*my_malloc_handler)();
      result = realloc(p, n);
      if(result) return result;
    }
  }

  typedef __malloc_alloc_template<0> malloc_alloc;

  // default allocator - implemented with free list

  enum {__ALIGN = 8};
  enum {__MAX_BYTES = 128};
  enum {__NFREELISTS = 16};

  template <bool threads, int inst>
  class __default_alloc_template
  {
    private:
      static size_t ROUND_UP(size_t bytes)
      {
        return(((bytes) + __ALIGN - 1) &~ (__ALIGN - 1));
      }
    private:
      union obj
      {
        union obj* free_list_link;
        char client_data[1];
      };
    private:
      static obj * volatile free_list[__NFREELISTS];
      static size_t FREELIST_INDEX(size_t bytes)
      {
        return (((bytes) + __ALIGN - 1)/__ALIGN - 1);
      }
      static void *refill(size_t n);
      static char *chunk_alloc(size_t size, int &nobjs);
      // chunk allocation state
      static char *start_free;
      static char *end_free;
      static size_t heap_size;
    public:
      static void *allocate(size_t n)
      {
        if(n > (size_t) __MAX_BYTES)
        {
          return malloc_alloc::allocate(n);
        }
        obj * volatile * my_free_list;
        obj * result;
        my_free_list = free_list + FREELIST_INDEX(n);
        result = *my_free_list;
        if(result == 0)
        {
          void *r = refill(ROUND_UP(n));
          return r;
        }
        *my_free_list = result->free_list_link;
        return result;
      }

      static void deallocate(void *p, size_t n)
      {
        if(n > (size_t) __MAX_BYTES)
        {
          malloc_alloc::deallocate(p ,n);
          return;
        }
        obj *q = (obj *)p;
        obj * volatile * my_free_list;
        my_free_list = free_list + FREELIST_INDEX(n);
        q->free_list_link = *my_free_list;
        *my_free_list = q;
      }

      static void *reallocate(void *p, size_t old_sz, size_t new_sz);
  };

  template<bool threads, int inst>
  char *__default_alloc_template<threads, inst>::start_free = 0;

  template<bool threads, int inst>
  char *__default_alloc_template<threads, inst>::end_free = 0;

  template<bool threads, int inst>
  char *__default_alloc_template<threads, inst>::heap_free = 0;

  template<bool threads, int inst>
  __default_alloc_template<thread, inst>::obj * volatile
  __default_alloc_template<thread, inst>::free_list[__NFREELISTS] =
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,};

  template<bool threads, int inst>
  void *__default_alloc_template<threads, inst>::refill(size_t n)
  {
    int nobjs = 20;
    char *chunk = chunk_alloc(n, objs);
    obj *volatile *my_free_list;
    obj *result;
    obj *current_obj, *next_obj;
    int i;

    if( nobjs == 1)
    {
      return chunk;
    }
    my_free_list = free_list + FREELIST_INDEX(n);
    result = (obj*)chunk;
    *my_free_list = next_obj = (obj*)(chunk + n);
    for(i = 1;; ++i)
    {
      current_obj = next_obj;
      next_obj = (obj*)((char*)next_obj + n);
      if(nobjs - 1 == i)
      {
        current_obj->free_list_link = 0;
        break;
      }
      else
      {
        current_obj->free_list_link = next_obj;
      }
    }
    return result;
  }

  template<bool threads, int inst>
  char * __default_alloc_template<threads, inst>::
  chunk_alloc(size_t size, int& nobjs)
  {
    char *result;
    size_t total_bytes = size * nobjs;
    size_t bytes_left = end_free - start_free;

    if(bytes_left >= total_bytes)
    {
      result = start_free;
      start_free += total_bytes;
      return result;
    }
    else if(bytes_left >= size)
    {
      nobjs = bytes_left/size;
      total_bytes = size * nobjs;
      result = start_free;
      start_free += total_bytes;
      return result;
    }
    else
    {
      size_t bytes_to_get = 2 * total_bytes + ROUND_UP(heap_size >> 4);
      if(bytes_left > 0)
      {
        obj * volatile *my_free_list =
          free_list + FREELIST_INDEX(bytes_left);
        ((obj *)start_free)->free_list_link = *my_free_list;
        *my_free_list = (obj *) start_free;
      }
      start_free = (char *)malloc(bytes_to_get);
      if(start_free == 0)
      {
        int i;
        obj * volatile *my_free_list, *p;
        for(i = size; i <= __MAX_BYTES; i += __ALIGN)
        {
          my_free_list = free_list + FREELIST_INDEX(i);
          p = *my_free_list;
          if(p != 0)
          {
            *my_free_list = p->free_list_link;
            start_free = (char *)p;
            end_free = start_free + i;
            return chunk_alloc(size, nobjs);
          }
        }
        end_free = 0;
        start_free = (char *) malloc_alloc::allocate(bytes_to_get);
      }
      heap_size += bytes_to_get;
      end_free = start_free + byte_to_get;
      return chunk_alloc(size, nobjs);
    }
  }

} // end of namespace mystl

#endif
