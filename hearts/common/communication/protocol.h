#ifndef DB_PROTOCOL_H_INCLUDE_GUARD_
#define DB_PROTOCOL_H_INCLUDE_GUARD_

#include <string>
#include <iostream>
#include "message.h"

namespace Protocol {
	const char terminator[] = "\n";
	const char separator = '\t';
	std::string encode(std::string);
	std::string read_string(std::istream&);
	std::string encode(Message);
	
	MessageTypes::type string2code(std::string);
	std::string code2string(MessageTypes::type);
	/** transforms a message into a string not including a terminator */
	inline std::string encode_no_term(Message m) { return encode(m); }
	/** transforms a message into a string including a terminator */
	inline std::string encode_term(Message m) { return encode(m) + terminator; }

}


#endif /* DB_PROTOCOL_H_INCLUDE_GUARD_ */
