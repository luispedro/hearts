#include <qapplication.h>
#include "server.h"
#include "general/helper.h"

#include <errno.h>
#include <unistd.h>
#include <iostream>
#include <string>

int main(int argc, char** argv)
{
	if ( argc > 1 && std::string( argv[ 1 ] ) == "--daemon" ) {
		if ( daemon( 0, 0 ) < 0 ) {
			std::cerr << "Daemon call failed: " << strerror( errno ) << ".\n";
			return 1;
		}
	}
	QApplication app( argc, argv, false ); // no GUI
	( void )new Server( &app );
	LOG_PLACE_NL();
	return app.exec();
}


