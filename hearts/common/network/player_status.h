#ifndef LPC_PLAYER_STATUS_H1082312546_INCLUDE_GUARD_
#define LPC_PLAYER_STATUS_H1082312546_INCLUDE_GUARD_

#include <iostream>

#define FOR_ALL_USER_STATUS( F ) \
		F( online ) \
		F( playing ) \
		F( waiting ) \
		F( logout )
		

namespace user_status {
		enum type {
#define ARG_COMMA( x ) x,
				FOR_ALL_USER_STATUS( ARG_COMMA )
				unknown
#undef ARG_COMMA
		};
}

std::ostream& operator << ( std::ostream&, user_status::type );
std::istream& operator >> ( std::istream&, user_status::type& );



#endif /* LPC_PLAYER_STATUS_H1082312546_INCLUDE_GUARD_ */
