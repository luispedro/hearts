#include "options.h"

namespace
{
std::string name_ = "LP Lapin";
bool zero_ = false;
}

std::string Options::name()
{
	return name_;
}

bool Options::send_zero()
{
	return zero_;
}

void Options::parse_args( char* argv[] )
{
	for ( unsigned i = 0; argv[ i ]; ++i ) {
		if ( std::string( argv[ i ] ) == "--playername" ) {
			if ( argv[ i + 1 ] )
				name_ = argv[ i + 1 ];
		}
		if ( std::string( argv[ i ] ) == "--zero" ) {
			zero_ = true;
		}
	}
}

