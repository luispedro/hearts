/***************************************************************************
                     Deck.cc  -  description
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

#include "deck.h"
#include "general/helper.h"
#include <stdlib.h>
#include <algorithm>
#include <strstream>
#include "general/random_shuffle.h"

using namespace std;


void fullDeck( Deck& res )
{
	res.clear();
	res.reserve( 52 );

	for ( int i = 0; i < 4; ++i ) {
		for ( int j = 0; j < 13; ++j ) {
			res.push_back( Card( static_cast<Card::suit_t>( i ), static_cast<Card::value_t>( j ) ) );
		}
	}
}
Deck fullDeck()
{
	Deck res;
	fullDeck( res );
	return res;
}

void randomDeck( Deck& res )
{
	fullDeck( res );
	workaround::random_shuffle( res.begin(), res.end() );
}


Deck randomDeck()
{
	Deck res;
	randomDeck( res );
	return res;
}

Deck string2deck( string str )
{
	LOG_PLACE() << " with str = " << str << ".\n";
	istrstream in( str.c_str() );
	Deck res;
	Card buf;
	while ( in >> buf ) {
		res.push_back( buf );
	}
	return res;
}

string deck2string( const Deck& deck )
{

	const size_t len = 4 * deck.size() + 1;
	char buf[ len ];
	ostrstream out( buf, sizeof( buf ) );

	Deck::const_iterator first = deck.begin();
	Deck::const_iterator last = deck.end();
	while ( first != last ) {
		out << *first << ' ';
		++first;
	}
	out << ends;
	return string( buf );
}

