#ifndef LPC_OPTIONS_H1094411175_INCLUDE_GUARD_
#define LPC_OPTIONS_H1094411175_INCLUDE_GUARD_

#include "inifile.h"
#include <string>

struct Options {
	Options( std::istream& );
	bool daemon() const { return daemon_; }
	std::string pidFile() const { return parsed_.get( "misc", "pidfile" ); }
	std::string logFile() const { return parsed_.get( "misc", "logfile" ); }
	std::string motdFile() const { return parsed_.get( "misc", "motdfile" ); }


	std::string databaseDb() const { return parsed_.get( "database", "database" ); }
	std::string databaseHost() const { return parsed_.get( "database", "host" ); }
	std::string databaseUser() const { return parsed_.get( "database", "user" ); }
	std::string databasePassword() const { return parsed_.get( "database", "password" ); }
	
	static void init( int argc, char** argv );

	private:

	bool daemon_;
	INIFile parsed_;
};


extern const Options* &options;



#endif /* LPC_OPTIONS_H1094411175_INCLUDE_GUARD_ */
