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

#ifndef MYSTL_NUMERIC_H_
#define MYSTL_NUMERIC_H_

#include "mystl_iterator.h"
#include "mystl_function.h"

namespace mystl
{

template <class InputIterator, class T>
T accumulate(InputIterator first, InputIterator last, T init)
{
  for(; first != last; ++first)
  {
    init = init + *first;
  }
  return init;
}

template <class InputIterator, class T, class BinaryOperation>
T accumulate(InputIterator first, InputIterator last, T init,
    BinaryOperation binary_op)
{
  for(; first != last; ++first)
  {
    init = binary_op(init, *first);
  }
  return init;
}

template <class InputIterator, class OutputIterator, class T>
OutputIterator __adjacent_difference(InputIterator first,
    InputIterator last, OutputIterator result, T*)
{
  T value = *first;
  while(++first != last)
  {
    T tmp = *first;
    *++result = tmp - value;
    value = tmp;
  }
  return ++result;
}

template <class InputIterator, class OutputIterator>
OutputIterator adjacent_difference(InputIterator first,
    InputIterator last, OutputIterator result)
{
  if(first == last) return result;
  *result = *first;
  return __adjacent_difference(first, last, result, mystl::value_type(first));
}

template <class InputIterator, class OutputIterator, class BinaryOperation,
          class T>
OutputIterator __adjacent_difference(InputIterator first, InputIterator last,
    OutputIterator result, T*, BinaryOperation binary_op)
{
  T value = *first;
  while(++first != last)
  {
    T tmp = *first;
    *++result = binary_op(tmp, value);
    value = tmp;
  }
  return ++result;
}

template <class InputIterator, class OutputIterator, class BinaryOperation>
OutputIterator adjacent_difference(InputIterator first, InputIterator last,
    OutputIterator result, BinaryOperation binary_op)
{
  if(first == last) return result;
  *result = *first;
  return __adjacent_difference(first, last, result, mystl::value_type(first),
      binary_op);
}

template <class InputIterator1, class InputIterator2, class T>
T inner_product(InputIterator1 first1, InputIterator1 last1,
                InputIterator2 first2, T init)
{
  for(; first1 != last1; ++first1, ++first2)
  {
    init += *first1 * *first2;
  }
  return init;
}

template <class InputIterator1, class InputIterator2, class T,
          class BinaryOperation1, class BinaryOperation2>
T inner_product(InputIterator1 first1, InputIterator1 last1,
                InputIterator2 first2, T init,
                BinaryOperation1 binary_op1, BinaryOperation2 binary_op2)
{
  for(; first1 != last1; ++first1, ++first2)
  {
    init = binary_op1(init, binary_op2(*first1, *first2));
  }
  return init;
}

template <class InputIterator, class OutputIterator, class T>
OutputIterator __partial_sum(InputIterator first, InputIterator last,
    OutputIterator result, T*)
{
  T value = *first;
  while(++first != last)
  {
    value += *first;
    *++result = value;
  }
  return ++result;
}

template <class InputIterator, class OutputIterator>
OutputIterator partial_sum(InputIterator first, InputIterator last,
    OutputIterator result)
{
  if(first == last) return result;
  *result = *first;
  return __partial_sum(first, last, result, mystl::value_type(first));
}

template <class InputIterator, class OutputIterator, class T, class BinaryOperation>
OutputIterator __partial_sum(InputIterator first, InputIterator last,
    OutputIterator result, T*, BinaryOperation binary_op)
{
  T value = *first;
  while(++first != last)
  {
    value = binary_op(value, *first);
    *++result = value;
  }
  return ++result;
}

template <class InputIterator, class OutputIterator, class BinaryOperation>
OutputIterator partial_sum(InputIterator first, InputIterator last,
    OutputIterator result, BinaryOperation binary_op)
{
  if(first == last) return result;
  *result = *first;
  return __partial_sum(first, last, result, mystl::value_type(first), binary_op);
}

template <class T, class Integer, class MonoidOperation>
T power(T x, Integer n, MonoidOperation op)
{
  if(n == 0) return mystl::identity_element(op);
  else
  {
    while((n & 1) == 0)
    {
      n >>= 1;
      x = op(x, x);
    }
    T result = x;
    n >>= 1;
    while(n != 0)
    {
      x = op(x, x);
      if((n & 1) != 0) result = op(result, x);
      n >>= 1;
    }
    return result;
  }
}

template <class T, class Integer>
inline T power(T x, Integer n)
{
  return power(x, n, mystl::multiplies<T>());
}

template <class ForwardIterator, class T>
void iota(ForwardIterator first, ForwardIterator last, T value)
{
  while(first != last) *first ++ = value ++;
}

} // end of namespace mystl

#endif
