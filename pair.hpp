#pragma once
// clang-format off
#include <iostream>

template <class T, class P> struct pair 
{
  T first;
  P second;

  pair() {}

  pair(T &&t, P &&p) ;

  static pair make_pair(const T &t, const P &p);

  pair &operator=(const pair &left_pair);
  bool operator<=(const pair &left_pair) const;
  bool operator>=(const pair &left_pair) const;
  bool operator<(const pair &left_pair) const;
  bool operator>(const pair &left_pair) const;
  bool operator==(const pair &left_pair) const;
};

template <class T, class P>
pair<T, P> pair<T, P>::make_pair(const T &t, const P &p) 
{
  pair m_pair;
  m_pair.first = t;
  m_pair.second = p;
  return m_pair;
}

template <class T, class P> pair<T, P>::pair(T &&t, P &&p) 
{
  this->first = t;
  this->second = p;
}

template <class T, class P>
pair<T, P> &pair<T, P>::operator=(const pair &left_pair) 
{
  this->first = left_pair.first;
  this->second = left_pair.second;
  return *this;
}

template <class T, class P> bool pair<T, P>::operator<=(const pair &left_pair) const
{
  if (this->first <= left_pair.first) 
  {
    return true;
  } 
  return false;
  
}

template <class T, class P> bool pair<T, P>::operator>=(const pair &left_pair) const
{
  if (this->first >= left_pair.first) 
  {
    return true;
  } 
  return false;
}

template <class T, class P> bool pair<T, P>::operator<(const pair &left_pair) const
{
  if (this->first < left_pair.first) 
  {
    return true;
  } 
  return false;
}

template <class T, class P> bool pair<T, P>::operator>(const pair &left_pair) const
{
  if (this->first > left_pair.first) 
  {
    return true;
  } 
  return false;
}

template <class T, class P> bool pair<T, P>::operator==(const pair &left_pair) const
{
  if (this->first == left_pair.first) 
  {
    return true;
  } 
  return false;
}
