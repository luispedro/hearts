#include <qapplication.h>
#include "server.h"
#include "options.h"
#include "general/helper.h"

#include <errno.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>

void write_pid_file()
{
	std::ofstream pidf( options->logFile().c_str() );
	pidf << getpid() << std::endl;
	if ( !pidf ) {
		std::cerr << "Error writing pid file" << std::endl;
	}
}

int main( int argc, char** argv )
{
	Options::init( argc, argv );
	if ( options->daemon() ) {
		if ( daemon( 0, 0 ) < 0 ) {
			std::cerr << "Daemon call failed: " << strerror( errno ) << ".\n";
			return 1;
		}
	}
	write_pid_file();
	QApplication app( argc, argv, false ); // no GUI
	( void ) new Server( &app );
	LOG_PLACE_NL();
	return app.exec();
}


