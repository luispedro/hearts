#include "motd.h"
#include "options.h"
#include <fstream>

namespace {
	const char* message = 0;
	void initMessage() {
		if ( message ) return;
		if ( options().motdFile() != "" ) {
			std::ifstream fin( options().motdFile().c_str() );
			std::string buffer;
			if ( std::getline( fin, buffer ) ) {
				message = strdup( buffer.c_str() );
			}
		}
		if ( !message ) message = "<qt>Welcome to <b>hearts.luispedro.org</b>.</qt>";
	}
}

const char* MotD::message() {
	if ( !message ) initMessage();
	return message;
}

