#ifndef DB_PLAYER_ID_H_INCLUDE_GUARD_
#define DB_PLAYER_ID_H_INCLUDE_GUARD_


/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#include <iostream>

namespace player_id
{
enum type { self, right, front, left };
static const type all_players[] =
	{
		self, right, front, left
	};
}


std::istream& operator >> ( std::istream&, player_id::type& );
std::ostream& operator << ( std::ostream&, player_id::type );


#define HANDLE_ALL_PLAYER_IDS( FUNCTION ) \
	do { \
	FUNCTION( self ); \
	FUNCTION( right ); \
	FUNCTION( front ); \
	FUNCTION( left ); \
	} while ( 0 )


#endif /* DB_PLAYER_ID_H_INCLUDE_GUARD_ */

