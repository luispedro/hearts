#ifndef DB_CARD_H_INCLUDE_GUARD_
#define DB_CARD_H_INCLUDE_GUARD_

/***************************************************************************
                          Card.h  -  description
                             -------------------
    begin                : Thu Dec 16 1999
    copyright            : (C) 1999 by Luis Pedro Coelho
    email                : luis@luispedro.org
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#include <iostream>
 #include <functional>

/** A game card class with value semantics.
   *
   * @author Luis P. Coelho <luis@luispedro.org>
   */

class Card
{
	public:
		/** the possible values for the cards. */
		enum value_t { two, three, four, five, six, seven, eight, nine, ten, jack, queen, king, ace };
		/** the four suits */
		enum suit_t { spades, diamonds, clubs, hearts };

		/** constructs a card with the given suit and value */
		Card ( suit_t a, value_t b ) : s( a ), v( b )
		{
			;
		}
		/** constructs a two of spades. */
		Card() : s( spades ), v( two )
		{
			;
		}

		suit_t suit() const
		{
			return s;
		}
		value_t value() const
		{
			return v;
		}


	private:

		suit_t s;
		value_t v;
};

/** a STL like predicate type for use with card collections. It's operator () returns true if the card has the same
 * suit as the internally saved suit. */
class OfSuite : public std::unary_function<Card, bool>
{
	public:
		/** constructs an object whose operator () returns true for a Card of suit s */
		explicit OfSuite( Card::suit_t s ) : s( s )
		{ }
		/**returns true if the c has the suit passed in the constructor */
		bool operator() ( const Card c ) const
		{
			return c.suit() == s;
		}
	protected:
		const Card::suit_t s;
};

std::ostream& operator << ( std::ostream&, Card );
std::istream& operator >> ( std::istream&, Card& );
/** This is mainly helpful for debugging porpuses */
std::ostream& operator << ( std::ostream&, Card::suit_t );

/** This is based on the on the ordering of cards for the hearts game if both cards are of the same suit and
  * On an arbitrary ordering of suits if they aren't.
  */
inline bool operator < ( Card a, Card b )
{
	if ( static_cast<int>( a.suit() ) != static_cast<int>( b.suit() ) ) {
		return static_cast<int>( a.suit() ) < static_cast<int>( b.suit() );
	}
	return static_cast<int>( a.value() ) < static_cast<int>( b.value() );
}

inline bool operator == ( Card a, Card b )
{
	return a.value() == b.value() && a.suit() == b.suit();
}

inline bool operator != ( Card a, Card b )
{
	return !( a == b ) ;
}


#endif /* DB_CARD_H_INCLUDE_GUARD_ */

