#ifndef DB_OPTIONS_H1053544106_INCLUDE_GUARD_
#define DB_OPTIONS_H1053544106_INCLUDE_GUARD_

#include <string>

namespace Options {
	std::string name();
	bool send_zero();
	void parse_args(char* argv[]);
}



#endif /* DB_OPTIONS_H1053544106_INCLUDE_GUARD_ */
