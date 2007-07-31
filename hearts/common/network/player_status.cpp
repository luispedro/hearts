#include "player_status.h"
#include <string>

namespace Network {
std::ostream& operator << ( std::ostream& out, user_status::type s ) {
		switch ( s ) {
#define CASE( x ) case user_status::x: return out << #x;
				FOR_ALL_USER_STATUS( CASE );
#undef CASE
				default:
					std::cerr << "Unknonwn user_status (" << static_cast<int>( s ) << ")\n";
					return out << "(unknown)";
		}
}
std::istream& operator >> ( std::istream& in, user_status::type& s ) {
		std::string str;
		in >> str;
#define CASE( x ) if ( str == #x ) { s = user_status::x; return in; }
		FOR_ALL_USER_STATUS( CASE )
		in.setstate( std::ios::failbit );
		return in;
}

} // namespace Network

