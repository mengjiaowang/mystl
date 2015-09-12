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

#ifndef MYSTL_ALGO_H_
#define MYSTL_ALGO_H_

#include "mystl_algobase.h"
#include "set"

namespace mystl
{
  template <class InputIterator1, class InputIterator2, class OutputIterator>
  OutputIterator set_union(InputIterator1 first1, InputIterator1 last1,
      InputIterator2 first2, InputIterator2 last2, OutputIterator result)
  {
    while(first1 != last1 && first2 != last2)
    {
      if(*first1 < *first2)
      {
        *result = *first1;
        ++first1;
      }
      else if(*first2 < *first1)
      {
        *result = *first2;
        ++first2;
      }
      else
      {
        *result = *first1;
        ++first1;
        ++first2;
      }
      ++result;
    }
    return mystl::copy(first2, last2, mystl::copy(first1, last1, result));
  }

  template <class InputIterator1, class InputIterator2, class OutputIterator,
            class Compare>
  OutputIterator set_union(InputIterator1 first1, InputIterator1 last1,
      InputIterator2 first2, InputIterator2 last2, OutputIterator result,
      Compare comp)
  {
    while(first1 != last1 && first2 != last2)
    {
      if(comp(*first1, *first2))
      {
        *result = *first1;
        ++first1;
      }
      else if(comp(*first2, *first1))
      {
        *result = *first2;
        ++first2;
      }
      else
      {
        *result = *first1;
        ++first1;
        ++first2;
      }
      ++result;
    }
    return mystl::copy(first2, last2, mystl::copy(first1, last1, result));
  }

  template <class InputIterator1, class InputIterator2, class OutputIterator>
  OutputIterator set_intersection(InputIterator1 first1, InputIterator1 last1,
      InputIterator2 first2, InputIterator2 last2, OutputIterator result)
  {
    while(first1 != last1 && first2 != last2)
    {
      if(*first1 < *first2)
      {
        ++first1;
      }
      else if(*first2 < *first1)
      {
        ++first2;
      }
      else
      {
        *result = *first1;
        ++first1;
        ++first2;
      }
    }
    return result;
  }

  template <class InputIterator1, class InputIterator2, class OutputIterator,
            class Compare>
  OutputIterator set_intersection(InputIterator1 first1, InputIterator1 last1,
      InputIterator2 first2, InputIterator2 last2, OutputIterator result, Compare comp)
  {
    while(first1 != last1 && first2 != last2)
    {
      if(comp(*first1, *first2))
      {
        ++first1;
      }
      else if(comp(*first2, *first1))
      {
        ++first2;
      }
      else
      {
        *result = *first1;
        ++first1;
        ++first2;
      }
    }
    return result;
  }

  template <class InputIterator1, class InputIterator2, class OutputIterator>
  OutputIterator set_difference(InputIterator1 first1, InputIterator1 last1,
      InputIterator2 first2, InputIterator2 last2, OutputIterator result)
  {
    while(first1 != last1 && first2 != last2)
    {
      if(*first1 < *first2)
      {
        *result = *first1;
        ++first1;
        ++result;
      }
      else if(*first2 < *first1)
      {
        ++first2;
      }
      else
      {
        ++first1;
        ++first2;
      }
    }
    return mystl::copy(first1, last1, result);
  }

  template <class InputIterator1, class InputIterator2, class OutputIterator,
            class Compare>
  OutputIterator set_difference(InputIterator1 first1, InputIterator1 last1,
      InputIterator2 first2, InputIterator2 last2, OutputIterator result,
      Compare comp)
  {
    while(first1 != last1 && first2 != last2)
    {
      if(comp(*first1, *first2))
      {
        *result = *first1;
        ++first1;
        ++result;
      }
      else if(comp(*first2, *first1))
      {
        ++first2;
      }
      else
      {
        ++first1;
        ++first2;
      }
    }
    return mystl::copy(first1, last1, result);
  }

  template <class InputIterator1, class InputIterator2, class OutputIterator>
  OutputIterator set_symmetric_difference(InputIterator1 first1, InputIterator1 last1,
      InputIterator2 first2, InputIterator2 last2, OutputIterator result)
  {
    while(first1 != last1 && first2 != last2)
    {
      if(*first1 < *first2)
      {
        *result = *first1;
        ++first1;
        ++result;
      }
      else if(*first2 < *first1)
      {
        *result = *first2;
        ++first2;
        ++result;
      }
      else
      {
        ++first1;
        ++first2;
      }
    }
    return mystl::copy(first1, last1, mystl::copy(first2, last2, result));
  }

  template <class InputIterator1, class InputIterator2, class OutputIterator,
            class Compare>
  OutputIterator set_symmetric_difference(InputIterator1 first1, InputIterator1 last1,
      InputIterator2 first2, InputIterator2 last2, OutputIterator result, Compare comp)
  {
    while(first1 != last1 && first2 != last2)
    {
      if(comp(*first1, *first2))
      {
        *result = *first1;
        ++first1;
        ++result;
      }
      else if(comp(*first2, *first1))
      {
        *result = *first2;
        ++first2;
        ++result;
      }
      else
      {
        ++first1;
        ++first2;
      }
    }
    return mystl::copy(first1, last1, mystl::copy(first2, last2, result));
  }

}

#endif
