#ifndef DB_DECK_H_INCLUDE_GUARD_
#define DB_DECK_H_INCLUDE_GUARD_

/***************************************************************************
                          deck.h  -  description
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

#include <vector>
 #include <string>
 #include "card.h"

typedef std::vector<Card> Deck;

Deck fullDeck();
Deck randomDeck();

void fullDeck( Deck& );
void randomDeck( Deck& );

std::string deck2string( const Deck& );
Deck string2deck( std::string );

#endif /* DB_DECK_H_INCLUDE_GUARD_ */
