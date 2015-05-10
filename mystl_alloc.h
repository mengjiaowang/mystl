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
        void *result = malloc(n);
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
    void result;
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
    void result;
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

  typename __malloc_alloc_template<0> malloc_alloc;

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
      }
    private:
      static obj * volatile free_list[__NFREELISTS];
      static size_t FREELIST_INDEX(size_t butes)
      {
        return (((bytes) + ALIGN - 1)/ALIGN - 1);
      }
      static void *refill(size_t n);
      static char *chunk_alloc(size_t size, int &nobjs);
      // chunk allocation state
      static char *start_free;
      static char *end_free;
      static size_t heap_size;
    public:
      static void *allocate(size_t n);
      static void deallocate(void *p, size_t n);
      static void *reallocate(void *p, size_t old_sz, size_t new_sz);
  };
} // end of namespace mystl

#endif
