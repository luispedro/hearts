/***************************************************************************
                          holder3.cpp  -  description
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

#include "holder3.h"
#include "general/helper.h"
#include <algorithm>// find

Holder3::Holder3(){
}
Holder3::~Holder3(){
}

/** This adds a card into the internal vector */
void Holder3::push(Card c)
{
        massert(cards.size() < 3);
        cards.push_back(c);
}

/** This returns true iff there are already three cards in the internal vector */
bool Holder3::full()
{
        return cards.size() == 3;
}

/** This removes its argument from the result. If the card is not there, no action is taken. */
void Holder3::erase(Card c)
{
        cards.erase(std::find(cards.begin(),cards.end(),c));
}

/** A predicate which is true iff the card is present */
bool Holder3::contains(Card c)
{
        return std::find(cards.begin(),cards.end(),c) != cards.end();
}

/** This returns a const reference to its internal vector */
const std::vector<Card>& Holder3::vector() const 
{
        return cards;
}
/** Resets the container */
void Holder3::clear(){
        cards.clear();
}

std::ostream& operator << (std::ostream& out, const Holder3& t)
{
		out << t.vector()[0] << ' ' << t.vector()[1] << ' ' << t.vector()[2];
		return out;
}

std::istream& operator >> (std::istream& in, Holder3& t)
{
		t.clear();
		while (!t.full())
		{
				Card tmp;
				in >> tmp;
				t.push(tmp);
		}
		return in;
}

