#include <qapplication.h>
#include "server.h"
#include "options.h"
#include "general/helper.h"
#include "logfile.h"

#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <iostream>
#include <fstream>
#include <string>

void write_pid_file()
{
	std::ofstream pidf( options->pidFile().c_str() );
	pidf << getpid() << std::endl;
	if ( !pidf ) {
		std::cerr << "Error writing pid file [" << options->pidFile() << ']' << std::endl;
	}
}

void reopenlog( int ) { reopenlog(); }

void install_sighandlers() {
	struct sigaction info;
	std::memset( &info, 0, sizeof( info ) );
	info.sa_handler = &reopenlog;
	sigemptyset( &info.sa_mask );
	info.sa_flags = SA_RESTART;
	
	sigaction( SIGHUP, &info, 0 );
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

	install_sighandlers();
	write_pid_file();
	QApplication app( argc, argv, false ); // no GUI
	( void ) new Server( &app );
	LOG_PLACE_NL();
	return app.exec();
}


