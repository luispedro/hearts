#include "options.h"

#include <getopt.h>
#include <iostream>
#include <cassert>
#include <memory>
#include <fstream>

namespace
{
	Options* singleton;
}

const Options* &options = const_cast<const Options*&>( singleton );



optionsDescrition heartsdOptions[] = {
	{ "database", { "host", "username", "password", "database", 0 } },
	{ "misc", { "pidfile", "logfile", "motdfile", 0 } },
	{ 0, {} }
};

Options::Options( std::istream& in )
	:daemon_( false ),
	 parsed_( in, heartsdOptions )
{
}

extern char* optarg;


template<unsigned N, typename T>
unsigned numelems( T ( & )[ N ] ) { return N; }

std::auto_ptr<std::ifstream> findConfFile() {
	const char* locations[] = { "/etc/heartsconf", "/etc/hearts.conf", "/etc/hearts/conf" };

	for ( const char** iter = locations; iter != locations + numelems( locations ); ++iter ) {
		std::auto_ptr<std::ifstream> res( new std::ifstream( *iter ) );
		if ( *res ) return res;
	}
	return std::auto_ptr<std::ifstream>( 0 );
}

void Options::init( int argc, char** argv )
{
	assert( !singleton );

	enum { daemon = 1, conffile };
	static const struct option long_options[] = {
			{ "daemon", 0, 0, daemon },
			{ "deamon", 0, 0, daemon },
			{ "conffile", 1, 0, conffile },
			{ 0, 0, 0, 0 }
	};

	int option_index = 0;
	int res;
	std::string confname;
	while ( ( res = getopt_long( argc, argv, "", long_options, &option_index ) ) > 0 ) {
		switch ( res ) {
			case daemon:
				singleton->daemon_ = true;
				break;
			case conffile: 
				confname = optarg;
				break;
			default:
				std::cerr << "Strange return from getopt (" << char( res ) << ")\n";
		}
	}

	std::auto_ptr<std::ifstream> conf;

	if ( confname.empty() ) {
		conf = findConfFile();
	} else {
		conf.reset( new std::ifstream( confname.c_str() ) );
		if ( !*conf ) {
			std::cerr << "Unable to open configuration file \'" << confname.c_str() << "\'\n";
			exit( 1 );
		}
	}
	if ( conf.get() ) {
		singleton = new Options( *conf );
	} else {
		std::cerr << "Configuration file not found!\n";
		exit( 1 );
	}
}

