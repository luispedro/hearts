#include <cstdlib> // std::rand
#include <algorithm> // std::iter_swap

  // Below, it's copied from GNU C++ LIB (and therefore under the GPL 2 + instation exception),
  // except that I use std::rand() unconditionally
  //
  // The reason for the copy is:
  // http://anubis.dkuug.dk/jtc1/sc22/wg21/docs/lwg-active.html#395
  //
  //
namespace workaround {
  /**
   *  @if maint
   *  Return a random number in the range [0, n).  This function encapsulates
   *  whether we're using rand (part of the standard C library) or lrand48
   *  (not standard, but a much better choice whenever it's available).
   *
   *  XXX There is no corresponding encapsulation fn to seed the generator.
   *  @endif
  */
  template<typename Distance>
    inline Distance
    random_number(Distance n)
    {
      return std::rand() % n;
    }


  /**
   *  @brief Randomly shuffle the elements of a sequence.
   *  @param  first   A forward iterator.
   *  @param  last    A forward iterator.
   *  @return  Nothing.
   *
   *  Reorder the elements in the range @p [first,last) using a random
   *  distribution, so that every possible ordering of the sequence is
   *  equally likely.
  */
  template<typename RandomAccessIter>
    inline void
    random_shuffle(RandomAccessIter first, RandomAccessIter last)
    {
      if (first == last) return;
      for (RandomAccessIter i = first + 1; i != last; ++i)
	std::iter_swap(i,first + random_number((i - first) + 1));
    }

}

