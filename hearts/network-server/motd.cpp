#include "motd.h"
#include "options.h"
#include <fstream>

namespace {
	const char* msgstring = 0;
	void initMessage() {
		if ( msgstring ) return;
		if ( options->motdFile() != "" ) {
			std::ifstream fin( options->motdFile().c_str() );
			std::string buffer;
			if ( std::getline( fin, buffer ) ) {
				msgstring = strdup( buffer.c_str() );
			}
		}
		if ( !msgstring ) msgstring = "<qt>Welcome to <b>hearts.luispedro.org</b>.</qt>";
	}
}

const char* MotD::message() {
	if ( !msgstring ) initMessage();
	return msgstring;
}

