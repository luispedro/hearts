#ifndef DB_CIRCULAR_ITERATOR_H_INCLUDE_GUARD_
#define DB_CIRCULAR_ITERATOR_H_INCLUDE_GUARD_

/***************************************************************************
                          circular_iterator.h  -  description
                             -------------------
    begin                : Fri Dec 17 1999
    copyright            : Public Domain
    created by         :  Luis Pedro Coelho
    email                : luis.coelho@netc.pt
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 * This code is public domain. Do with it what you wish.
 *
 *  This implements a circular iterator. It takes a range at its constructor so that you
 * can always increment it and it will circle around.
 *
 *  It is not a complete implementation, since there are some functions missing, but it has been
 * working for me.
 *                                                                         *
 ***************************************************************************/

 #include <iterator>
 #include <algorithm>
 #include "helper.h"

 template <typename It>
 class circular_iterator
 /** should be      : public iterator<typename iterator_traits<It>::value_type>
   * but it gave me errors
   */
 {
        public:

                typedef typename std::iterator_traits<It>::value_type value_type;
                typedef typename std::iterator_traits<It>::difference_type difference_type;
                typedef typename std::iterator_traits<It>::iterator_category iterator_category;
                typedef typename std::iterator_traits<It>::pointer pointer;
                typedef typename std::iterator_traits<It>::reference reference;
       
                circular_iterator(const It& it, const It& fir, const It& las):cur(it),first(fir),last(las) {  }
                template <typename Cont>
                        circular_iterator(const It& it,const Cont& c): cur(it),first(c.begin()),last(c.end()) {  }
                circular_iterator() { }
                circular_iterator(const circular_iterator&);

                value_type& operator * () const;
                It& operator -> ();
                const It& operator -> () const;

                circular_iterator& operator ++ ();
                circular_iterator operator ++ (int);

                circular_iterator& operator -- ();
                circular_iterator operator -- (int);

               circular_iterator& operator += (difference_type);

                difference_type operator - (const circular_iterator& other) const;

                bool operator == (const circular_iterator&) const;

        private:

                It cur;
                It first;
                It last;
};

template <typename It>
inline circular_iterator<It>::circular_iterator(const circular_iterator<It>& other)
       :cur(other.cur),
        first(other.first),
        last(other.last)
{
       ;
}

template <typename It>
inline circular_iterator<It>::value_type& circular_iterator<It>::operator * () const
{
      return *cur;
}

template <typename It>
inline circular_iterator<It>& circular_iterator<It>::operator ++ ()
{
       ++cur;
       if (cur == last) cur = first;
       return *this;
}

template <typename It>
inline circular_iterator<It> circular_iterator<It>::operator ++ (int)
{
       circular_iterator tmp(*this);
       ++(*this);
       return tmp;
}

template <typename It>
inline It& circular_iterator<It>::operator ->()
{
       return cur;
}

template <typename It>
inline const It& circular_iterator<It>::operator ->() const
{
       return cur;
}

template <typename It>
inline circular_iterator<It>& circular_iterator<It>::operator -- ()
{
       if (cur == first) cur = last;
       --cur; // this must be done whether you have set cur to last or not
       return *this;
}

template <typename It>
inline circular_iterator<It> circular_iterator<It>::operator -- (int)
{
       circular_iterator tmp(*this);
       ++(*this);
       return tmp;
}

template <typename It>
inline circular_iterator<It>& circular_iterator<It>::operator += (circular_iterator<It>::difference_type n)
{
        n %= last - first; // put it in range
        circular_iterator::difference_type d = last - cur;
        if ( d > n)
        {
                cur += n;
                return *this;
        }
        cur = first + (n - d); // going backwards
        return *this;
}

template <typename It>
inline circular_iterator<It> operator+(circular_iterator<It> res, circular_iterator<It>::difference_type d)
{
        res += d;
        return res;
}

template <typename It>
inline bool circular_iterator<It>::operator == (const circular_iterator<It>& other) const
{
        return (cur == other.cur) && (first == other.first) && (last == other.last);
}


template <typename  It>
inline bool operator != (circular_iterator<It>& a, const circular_iterator<It>& b) 
{
	return !(a == b);
}

template <typename It>
inline typename circular_iterator<It>::difference_type
        circular_iterator<It>::operator - (const circular_iterator<It>& other) const
{
        massert (this->first == other.first);
        massert (this->last == other.last);
        if (this->cur < other.cur) return (this->last - this->cur) + (other.cur - other.first);
        return this->cur - other.cur;
}


template <typename It, typename Func>
inline Func for_each(circular_iterator<It> last, Func f)
{
        f(*last);
        circular_iterator<It> first = last;
        ++first;
        return for_each(first,last,f);
}

#endif /* DB_CIRCULAR_ITERATOR_H_INCLUDE_GUARD_ */
