/***************************************************************************
                     main.cpp  -  description
                        -------------------
begin                : Qui Jul 20 20:14:12 WEST 2000
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "server.h"
#include "options.h"
#include "open.h"
#include "id_to_fd.h"

#include <cstring> // strerror
#include <cstdlib> // srand
#include <ctime> // time()
#include <cerrno> // errno

#include <unistd.h> // daemon


int main( int argc, char **argv )
{
	Options::init( argc, argv );
	std::srand( time( 0 ) );
	if ( options->daemon() ) {
		if ( daemon( 0, 0 ) < 0 ) {
			std::cerr << "Error in daemon(): " << strerror( errno ) << ".\n";
		}
	}

	if ( !all_registered() )
		open_connections();
	Server serv;
	return serv.exec();
}

