#ifndef DB_SETUP_H_INCLUDE_GUARD_
#define DB_SETUP_H_INCLUDE_GUARD_

#include "hearts/player_id.h"
#include "helper.h"

namespace Setup
{

inline int id_to_fd( player_id::type t )
{
	using namespace player_id;
	switch ( t ) {
		case player_id::self:
		return 7;
		case player_id::right:
		return 4;
		case player_id::front:
		return 5;
		case player_id::left:
		return 6;
		default:
		massert( 0 );
	}
}
inline int client_fd()
{
	return 3;
}
}





#endif /* DB_SETUP_H_INCLUDE_GUARD_ */
