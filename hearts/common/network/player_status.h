#ifndef LPC_PLAYER_STATUS_H1082312546_INCLUDE_GUARD_
#define LPC_PLAYER_STATUS_H1082312546_INCLUDE_GUARD_

#include <iostream>

#define FOR_ALL_PLAYER_STATUS( F ) \
		F( online ) \
		F( playing ) \
		F( waiting ) \
		F( logout )
		

namespace player_status {
		enum type {
#define ARG_COMMA( x ) x,
				FOR_ALL_PLAYER_STATUS( ARG_COMMA )
				unknown
#undef ARG_COMMA
		};
}

std::ostream& operator << ( std::ostream&, player_status::type );
std::istream& operator >> ( std::istream&, player_status::type& );



#endif /* LPC_PLAYER_STATUS_H1082312546_INCLUDE_GUARD_ */
