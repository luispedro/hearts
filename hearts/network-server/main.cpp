#include <qapplication.h>
#include "server.h"
#include "general/helper.h"

#include <errno.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>

void write_pid_file()
{
	std::ofstream pidf( "/var/run/hearts.pid" );
	pidf << getpid() << std::endl;
	if ( !pidf ) {
		std::cerr << "Error writing pid file" << std::endl;
	}
}

int main(int argc, char** argv)
{
	if ( argc > 1 && std::string( argv[ 1 ] ) == "--deamon" ) {
		std::cerr << "\"--deamon\" should have been spelt \"--daemon\", but I will let it pass (just this time)." << std::endl;
		std::strcpy( argv[ 1 ], "--daemon" );
	}
	if ( argc > 1 && std::string( argv[ 1 ] ) == "--daemon" ) {
		if ( daemon( 0, 0 ) < 0 ) {
			std::cerr << "Daemon call failed: " << strerror( errno ) << ".\n";
			return 1;
		}
	}
	write_pid_file();
	QApplication app( argc, argv, false ); // no GUI
	( void )new Server( &app );
	LOG_PLACE_NL();
	return app.exec();
}


