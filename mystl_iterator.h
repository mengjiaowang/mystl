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

#ifndef MYSTL_ITERATOR_H_
#define MYSTL_ITERATOR_H_

namespace mystl
{
  struct input_iterator_tag{};
  struct output_iterator_tag{};
  struct forward_iterator_tag: public input_iterator_tag{};
  struct bidirectional_iterator_tag: public forward_iterator_tag{};
  struct random_access_iterator_tag: public bidirectional_iterator_tag{};

  template <class Category, class T, class Distance = ptrdiff_t,
            class Pointer = T *, class Reference = T &>
  struct iterator
  {
    typedef Category iterator_category;
    typedef T value_type;
    typedef Distance difference_type;
    typedef Pointer pointer;
    typedef Reference reference;
  };

  template <class Iterator>
  struct iterator_traits
  {
    typedef typename Iterator::iterator_category iterator_category;
    typedef typename Iterator::value_type value_type;
    typedef typename Iterator::difference_type difference_type;
    typedef typename Iterator::pointer pointer;
    typedef typename Iterator::reference reference;
  };

  template <class T>
  struct iterator_traits<T *>
  {
    typedef random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef T * pointer;
    typedef T & reference;
  };

  template <class T>
  struct iterator_traits<const T *>
  {
    typedef random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef const T * pointer;
    typedef const T & reference;
  };

  template <class Iterator>
  inline typename iterator_traits<Iterator>::iterator_category
  iterator_cagetory(const Iterator&)
  {
    typedef typename iterator_traits<Iterator>::iterator_category category;
    return category();
  }

  template <class Iterator>
  inline typename iterator_traits<Iterator>::difference_type*
  distance_type(const Iterator&)
  {
    return static_cast<typename iterator_traits<Iterator>::difference_type*>(0);
  }

  template <class Iterator>
  inline typename iterator_traits<Iterator>::value_type*
  value_type(const Iterator&)
  {
    return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
  }

  template <class InputIterator>
  inline typename iterator_traits<InputIterator>::difference_type
  __distance(InputIterator first, InputIterator last,
      input_iterator_tag)
  {
    typename iterator_traits<InputIterator>::difference_type n = 0;
    while(first != last)
    {
      ++first; ++n;
    }
    return n;
  }

  template <class RandomAccessIterator>
  inline typename iterator_traits<RandomAccessIterator>::difference_type
  __distance(RandomAccessIterator first, RandomAccessIterator last,
      random_access_iterator_tag)
  {
    return last - first;
  }

  template <class InputIterator>
  inline typename iterator_traits<InputIterator>::difference_type
  distance(InputIterator first, InputIterator last)
  {
    typedef typename
      iterator_traits<InputIterator>::iterator_category category;
    return __distance(first, last, category());
  }

  template <class InputIterator, class Distance>
  inline void __advance(InputIterator &i, Distance n,
      input_iterator_tag)
  {
    while(n--) ++i;
  }

  template <class BidirectionalIterator, class Distance>
  inline void __advance(BidirectionalIterator &i, Distance n,
      bidirectional_iterator_tag)
  {
    if( n >= 0)
      while(n--) ++i;
    else
      while(n++) --i;
  }

  template <class RandomAccessIterator, class Distance>
  inline void __advance(RandomAccessIterator &i, Distance n,
      random_access_iterator_tag)
  {
    __advance(i, n, iterator_category(i));
  }
} // end of namespace mystl

#endif
