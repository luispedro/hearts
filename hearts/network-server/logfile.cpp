#include "logfile.h"
#include "options.h"
#include <cassert>
#include <fstream>
#include <time.h>


namespace {
	std::ofstream* output = 0;
	void delete_output() { delete output; }
}

std::ostream& logfile() {
	if ( !output ) {
			output = new std::ofstream( options->logFile().c_str() );
			assert( output );
			assert( *output );
	}
	time_t now = time( 0 );
	return *output << "[ " << ctime( &now ) << " ]: ";
}


