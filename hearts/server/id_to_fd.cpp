#include "id_to_fd.h"
#include <cassert>
namespace
{
int fds[ 4 ] = { -1, -1, -1, -1 };
}

void register_fd( int fd )
{
	for ( int i = 0; i != 4; ++i ) {
		if ( fds[ i ] == -1 ) {
				fds[ i ] = fd;
				return;
		}
	}
	assert( 0 );
}

void register_fd( player_id::type who, int fd )
{
	fds[ who ] = fd;
}

int id_to_fd( player_id::type who )
{
	return fds[ who ];
}

bool all_registered()
{
	for ( int i = 0; i != 4; ++i )
		if ( fds[ i ] == -1 )
			return false;
	return true;
}

