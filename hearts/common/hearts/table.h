#ifndef DB_TABLE_H_INCLUDE_GUARD_
#define DB_TABLE_H_INCLUDE_GUARD_

/***************************************************************************
                          table.h  -  description
                             -------------------
    begin                : Sun Dec 19 1999
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
 #include "card.h"
 #include "general/helper.h"

class Table
{
	public:

		Table();

		const std::vector<Card>& state() const throw();
		void add_play( Card );
		void add( Card );
		void reset();

		Card::suit_t push() const throw();
		bool empty() const throw();

		bool full() const throw();

	private:
		std::vector<Card> played;
};

/** Used to be a member, isn't anymore. */
unsigned winner( const Table& ) throw();

inline Table::Table()
{
	played.reserve( 4 );
}

inline const std::vector<Card>& Table::state() const throw()
{
	return played;
}

inline Card::suit_t Table::push() const throw()
{
	return played.front().suit();
}

inline bool Table::full() const throw()
{
	return played.size() == 4;
}

inline void Table::add_play( Card n )
{
	massert( played.size() < 4 );
	played.push_back( n );
}

inline void Table::add
	( Card n )
{
	massert( played.size() < 4 );
	played.push_back( n );
}

inline void Table::reset()
{
	played.clear();
}

inline bool Table::empty() const throw()
{
	return played.empty();
}

#include "deck.h"

inline std::string table2string( const Table& t )
{
	return deck2string( t.state() );
}

inline Table string2table( std::string str )
{
	Table res;
	Deck tmp = string2deck( str );
	Deck::iterator first = tmp.begin();
	Deck::iterator last = tmp.end();
	while ( first != last ) {
		res.add_play( *first );
		++first;
	}
	return res;
}

#endif /* DB_TABLE_H_INCLUDE_GUARD_ */
