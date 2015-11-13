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

#ifndef MYSTL_FUNCTION_H_
#define MYSTL_FUNCTION_H_

#include <functional>

namespace mystl
{

  template <class Arg, class Result>
  struct unary_function
  {
    typedef Arg argument_type;
    typedef Result result_type;
  };

  template <class Arg1, class Arg2, class Result>
  struct binary_function
  {
    typedef Arg1 first_argument_type;
    typedef Arg2 second_argument_type;
    typedef Result result_type;
  };

  template <class T>
  struct plus: public binary_function<T, T, T>
  {
    T operator()(const T& x, const T& y) const {return x + y;}
  };

  template <class T>
  struct minus: public binary_function<T, T, T>
  {
    T operator()(const T& x, const T& y) const {return x - y;}
  };

  template <class T>
  struct multiplies : public binary_function<T, T, T>
  {
    T operator()(const T& x, const T& y) const { return x * y;}
  };

  template <class T>
  struct devide: public binary_function<T, T, T>
  {
    T operator()(const T& x, const T& y) const { return x / y;}
  };

  template <class T> inline T identity_element(mystl::multiplies<T>) { return T(1);}
  template <class T> inline T identity_element(mystl::plus<T>) { return T(0);}

  template <class T>
  struct modulus: public binary_function<T, T, T>
  {
    T operator()(const T& x, const T& y) {return x % y;}
  };

  template <class T>
  struct negate: public unary_function<T, T>
  {
    T operator()(const T& x) const {return -x;}
  };

  template <class T>
  struct equal_to: public binary_function<T, T, bool>
  {
    T operator()(const T& x, const T& y) {return x == y;}
  };

  template <class T>
  struct not_equal_to: public binary_function<T, T, bool>
  {
    T operator()(const T& x, const T& y) {return x != y;}
  };

  template <class T>
  struct greater: public binary_function<T, T, bool>
  {
    T operator()(const T& x, const T& y) {return x > y;}
  };

  template <class T>
  struct less: public binary_function<T, T, bool>
  {
    T operator()(const T& x, const T& y) {return x < y;}
  };

  template <class T>
  struct greater_equal: public binary_function<T, T, bool>
  {
    T operator()(const T& x, const T& y) {return x >= y;}
  };

  template <class T>
  struct less_equal: public binary_function<T, T, bool>
  {
    T operator()(const T& x, const T& y) {return x <= y;}
  };

  template <class T>
  struct logical_and: public binary_function<T, T, bool>
  {
    T operator()(const T& x, const T& y) {return x && y;}
  };

  template <class T>
  struct logical_or: public binary_function<T, T, bool>
  {
    T operator()(const T& x, const T& y) {return x || y;}
  };

  template <class T>
  struct logical_not: public unary_function<T, bool>
  {
    T operator()(const T& x) {return !x;}
  };

  template <class Predicate>
  class unary_negate: public unary_function<typename Predicate::argument_type, bool>
  {
    protected:
      Predicate pred;
    public:
      explicit unary_negate(const Predicate &x): pred(x) {}
      bool operator()(const typename Predicate::argument_type &x) const
      {
        return !pred(x);
      }
  };

  template <class Predicate>
  inline unary_negate<Predicate> no1(const Predicate &pred)
  {
    return unary_negate<Predicate>(pred);
  }

  template <class Predicate>
  class binary_negate: public binary_function<typename Predicate::argument_type,
    typename Predicate::argument_type, bool>
  {
    protected:
      Predicate pred;
    public:
      explicit binary_negate(const Predicate &x): pred(x) {}
      bool operator()(const typename Predicate::argument_type &x,
          const typename Predicate::argument_type &y) const
      {
        return !pred(x, y);
      }
  };

  template <class Predicate>
  inline binary_negate<Predicate> no1(const Predicate &pred)
  {
    return binary_negate<Predicate>(pred);
  }

  template <class T>
  struct identity: public unary_function<T, T>
  {
    const T& operator()(const T& x) const {return x;}
  };

  template <class Pair>
  struct select1st : public unary_function<Pair, typename Pair::first_type>
  {
    const typename Pair::first_type& operator()(const Pair& x) const
    {
      return x.first;
    };
  };

} // end of namespace mystl

#endif
