#ifndef LPC_INIFILE_H1094411175_INCLUDE_GUARD_
#define LPC_INIFILE_H1094411175_INCLUDE_GUARD_

#include <string>
#include <iostream>
#include <map>

struct optionsDescrition {
	static const unsigned maxOptions = 64;
	const char* name;
	const char* options[ maxOptions ];
};

class INIFile {
	public:
		INIFile( std::istream& in, const optionsDescrition* options );
		std::string get( std::string group, std::string name ) const;
	private:
		void parseLine( std::string line, std::string group, const optionsDescrition* info, unsigned count );

		std::map<std::string, std::map<std::string, std::string> > parsed_;
};



#endif /* LPC_INIFILE_H1094411175_INCLUDE_GUARD_ */
