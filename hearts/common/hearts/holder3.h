/***************************************************************************
                          holder3.h  -  description
                             -------------------
    begin                : Wed Feb 16 2000
    copyright            : (C) 2000 by Luis Pedro Coelho
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

#ifndef HOLDER3_H
#define HOLDER3_H

#include "card.h"
#include <vector>

/**This is a helper class used to pass three cards from the players to the game_manager.
  * It is actually not much more than a wrapper around a vector<Card>.
  *@author Luis Pedro Coelho
  */

class Holder3 {
        public:
        /** constructs an empty object */
                Holder3();
                ~Holder3();

        /** A predicate which is true if the card is present */
                bool contains(Card);

        /** This removes its argument from the result. If the card is not there, no action is taken. */
                void erase(Card);

        /** This returns true iff there are already three cards in the internal vector */
                bool full();

        /** This adds a card into the internal vector. It is a programming error to call this function if 
		  * full() returns true.
		  */
                void push(Card);

        /** This returns a const reference to its internal vector */
                const std::vector<Card>& vector() const;

        /** Resets the container */
                void clear();
        private: 
                std::vector<Card> cards;
};

std::ostream& operator << (std::ostream&,const Holder3&);
std::istream& operator >> (std::istream&,Holder3&);
#endif
