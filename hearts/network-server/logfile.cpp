#include "logfile.h"
#include "options.h"
#include <cassert>
#include <fstream>
#include <time.h>

namespace {
	std::ofstream* output_ = 0;
	void delete_output() { delete output_; output_ = 0; }
}

std::ostream& logfile() {
	if ( !output_ ) reopenlog();
	time_t now = time( 0 );
	return *output_ << "[ " << ctime( &now ) << " ]: ";
}

void reopenlog() {
	bool atexit_installed = false;
	if ( output_ ) {
		delete output_;
		atexit_installed = true; // we had probably been called previously
	}
	output_ = new std::ofstream( options->logFile().c_str() );
	if ( !atexit_installed ) std::atexit( delete_output );
	assert( output_ );
	if ( *output_ ) {
		delete output_;
		output_ = new std::ofstream( "/dev/null" );
	}
}
