#include "options.h"

#include <getopt.h>
#include <iostream>
#include <cassert>

namespace
{
	Options* singleton;
}

const Options* &options = const_cast<const Options*&>( singleton );

Options::Options()
		:daemon_( false )
		
{
}

extern char* optarg;

void Options::init( int argc, char** argv )
{
	assert( !singleton );
	singleton = new Options;

	enum { daemon = 1, logfile, pidfile };
	static const struct option long_options[] = {
			{ "daemon", 0, 0, daemon },
			{ "deamon", 0, 0, daemon },
			{ "logfile", 1, 0, logfile },
			{ "pidfile", 1, 0, pidfile },
			{ 0, 0, 0, 0 }
	};

	int option_index = 0;
	int res;
	while ( ( res = getopt_long( argc, argv, "", long_options, &option_index ) ) > 0 ) {
		const char* cur = optarg;
		switch ( res ) {
			case daemon:
				singleton->daemon_ = true;
				break;
			case logfile:
				singleton->logFile_ = std::string( cur );
				break;
			case pidfile:
				singleton->pidFile_ = std::string( cur );
				break;
			default:
				std::cerr << "Strange return from getopt (" << char( res ) << ")\n";
		}
	}
}


