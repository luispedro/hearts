#include "player_status.h"
#include <string>

std::ostream& operator << ( std::ostream& out, player_status::type s ) {
		switch ( s ) {
#define CASE( x ) case player_status::x: return out << #x;
				FOR_ALL_PLAYER_STATUS( CASE );
#undef CASE
				default:
					std::cerr << "Unknonwn player_status (" << static_cast<int>( s ) << ")\n";
					return out << "(unknown)";
		}
}
std::istream& operator >> ( std::istream& in, player_status::type& s ) {
		std::string str;
		in >> str;
#define CASE( x ) if ( str == #x ) { s = player_status::x; return in; }
		FOR_ALL_PLAYER_STATUS( CASE )
		in.setstate( std::ios::failbit );
		return in;
}

