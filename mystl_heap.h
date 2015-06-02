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

#ifndef MYSTL_HEAP_H_
#define MYSTL_HEAP_H_

#include "mystl_iterator.h"

namespace mystl
{
  template <class RandomAccessIterator, class Distance, class T>
  void __push_heap(RandomAccessIterator first, Distance holeIndex,
      Distance topIndex, T value)
  {
    Distance parent = (holeIndex - 1) / 2;
    while((holeIndex > topIndex) && (*(first + parent) < value))
    {
      *(first + holeIndex) = *(first + parent);
      holeIndex = parent;
      parent = (holeIndex - 1) / 2;
    }
    *(first + holeIndex) = value;
  }

  template <class RandomAccessIterator, class Distance, class T>
  inline void __push_heap_aux(RandomAccessIterator first,
      RandomAccessIterator last, Distance*, T*)
  {
    __push_heap(first, Distance((last - first) - 1), Distance(0), T(*(last - 1)));
  }

  template <class RandomAccessIterator>
  inline void push_heap(RandomAccessIterator first, RandomAccessIterator last)
  {
    __push_heap_aux(first, last, distance_type(first), value_type(first));
  }

  template <class RandomAccessIterator, class Distance, class T>
  void __adjust_heap(RandomAccessIterator first, Distance holeIndex,
      Distance len, T value)
  {
    Distance topIndex = holeIndex;
    Distance secondChild = 2 * holeIndex + 2; // right child
    while(secondChild < len)
    {
      if(*(first + secondChild) < *(first + (secondChild - 1)))
      {
        --secondChild;
      }
      // percolate down
      *(first + holeIndex) = *(first + secondChild);
      holeIndex = secondChild;
      secondChild = 2 * (secondChild + 1);
    }
    if(secondChild == len)
    {
      // percolate down
      *(first + holeIndex) = *(first + (secondChild - 1));
      holeIndex = secondChild - 1;
    }
    __push_heap(first, holeIndex, topIndex, value);
  }

  template <class RandomAccessIterator, class Distance, class T>
  void __pop_heap(RandomAccessIterator first,
                  RandomAccessIterator last,
                  RandomAccessIterator result,
                  T value, Distance*)
  {
    *result = *first;
    __adjust_heap(first, Distance(0), Distance(last - first), value);
  }

  template <class RandomAccessIterator, class T>
  inline void __pop_heap_aux(RandomAccessIterator first, RandomAccessIterator last,
      T*)
  {
    __pop_heap(first, last - 1, last - 1, T(*(last - 1)), distance_type(first));
  }

  template <class RandomAccessIterator>
  inline void pop_heap(RandomAccessIterator first, RandomAccessIterator last)
  {
    __pop_heap_aux(first, last, value_type(first));
  }

  template <class RandomAccessIterator>
  void sort_heap(RandomAccessIterator first, RandomAccessIterator last)
  {
    while(last - first > 1)
    {
      pop_heap(first, last--);
    }
  }

  template <class RandomAccessIterator, class T, class Distance>
  void __make_heap(RandomAccessIterator first, RandomAccessIterator last,
      T*, Distance*)
  {
    if(last - first < 2) return;
    Distance len = last - first;
    Distance parent = (len - 2) / 2;
    while(true)
    {
      __adjust_heap(first, parent, len, T(*(first + parent)));
      if(parent == 0) return;
      --parent;
    }
  }

  template <class RandomAccessIterator>
  inline void make_heap(RandomAccessIterator first, RandomAccessIterator last)
  {
    __make_heap(first, last, value_type(first), distance_type(first));
  }

}// end of namespace mystl

#endif
