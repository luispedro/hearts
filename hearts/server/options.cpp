/***************************************************************************
                     options.cpp  -  description
                        -------------------
begin                : Fri Feb 18 2000
copyright            : (C) 2000 by Luis Pedro Coelho
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

#include "options.h"
#include "general/helper.h"
#include "id_to_fd.h"
#include <getopt.h>

const unsigned defaultMaxPoints = 99;

Options* Options::singleton = 0;

namespace
{
Options* single;
}

Options::Options()
		: wait_zero_( false ),
		daemon_( false )
{}

const Options* &options = const_cast<const Options*&>( single );

unsigned Options::maxPoints() const
{
	return defaultMaxPoints;
}

const Options* Options::appOptions()
{
	return singleton;
}

Options* Options::unconstAppOptions()
{
	return singleton;
}

extern char *optarg;
void Options::init( int argc , char** argv )
{
	single = new Options;
	// copy & paste from man:getopt
	enum { fds = 1, tport, uport, wait_zero, daemon };
	static const struct option long_options[] = {
				{ "fds", 1, 0, fds },
				{ "tcp-port", 1, 0, tport },
				{ "unix-port", 1, 0, uport },
				{ "wait-zero", 0, 0, wait_zero },
				{ "daemon", 0, 0, daemon },
				{ 0, 0, 0, 0 }
			};
	int option_index = 0;
	int res;
	while ( ( res = getopt_long( argc, argv, "", long_options, &option_index ) ) > 0 ) {
		char * cur = optarg;
		switch ( res ) {
			case fds: {
				LOG_PLACE() << " Going to decode " << cur << '\n';
				for ( int i = 0; i != 4; ++i ) {
					if ( !cur || !*cur || all_registered() )
						break;
					const char* const oldcur = cur;
					int fd = strtol( cur, &cur, 10 );
					if ( cur == oldcur ) {
						std::cerr << "Error decoding argument for --fds\n";
						break;
					}
					LOG_PLACE() << " fd[ " << i << " ] = " << fd << '\n';
					if ( fd ) register_fd( player_id::all_players[ i ], fd );
					if ( *cur ) ++ cur;
				}
			}
			break;
			case tport: {
				const char* const oldcur = cur;
				int port = strtol( cur, &cur, 10 );
				if ( cur != oldcur ) single->tcp_port_ = port;
				else std::cerr << "Error decoding port number (was given \'" << oldcur << "\')\n";
			}
			break;
			case uport: {
				single->unix_address_ = cur;
			}
			break;
			case wait_zero:
			single->wait_zero_ = true;
			break;
			case daemon:
			single->daemon_ = true;
			break;
			default:
			LOG_PLACE_NL();
		}
	}
}

