#include "inifile.h"
#include <string>
#include <iostream>

using namespace std;

namespace { 
	void cleanup( std::string& line ) {
		std::string copy = line;
		unsigned begin = 0;
		while ( begin != line.size() && isspace( line[ begin ] ) ) ++begin;

		bool inQuote = false;
		unsigned end;
		for ( end = begin; end != line.size(); ++end ) {
			if ( line[ end ] == '\"' ) {
				inQuote = !inQuote;
			} else if ( line[ end ] == '#' && !inQuote ) {
				break;
			} else if ( line[ end ] == '\\' ) {
				++end; // ignore next character
				if ( end == line.size() ) {
					std::cerr << "Error parsing file: \\ character "
						"at the end of line (sorry, not supported)\n";
					break;
				}
			}
		}
		while ( end > begin && isspace( line[ end - 1 ] ) ) --end;
		line.assign( line, begin, end - begin );
		//std::cerr << "cleanup(\'" << copy << "\') = \'" << line << "\'\n";
	}
	string parseValue( string value ) {
		return value;
	}
	bool parseGroupName( string line, string& group )
	{
		if ( line[ 0 ] != '[' ) return false;
		if ( line[ line.size() - 1 ] != ']' ) return false;

		group.assign( line, 1, line.size() - 2 );
		return true;
	}


}

void INIFile::parseLine( string line, string group, const optionsDescrition* info, unsigned count ) {
	unsigned equals = line.find( '=' );
	if ( equals == string::npos ) {
		std::cerr << "Could not parse line " << count << ", ignoring.\n";
		return;
	}

	string name( line, 0, equals );

	if ( info ) {
		for ( const char* const * possible = info->options; true ; ++possible ) {
			if ( !*possible ) {
				std::cerr << "Option name \'" << name << "\' in line " << count << " (group = " << group << " ) unknown, ignoring.\n";
				return;
			}
			if ( name == *possible ) break;
		}
	}

	//std::cerr << group << '.' << name << '=' << string( line, equals + 1, string::npos ) << '\n';

	parsed_[ group ][ name ] = parseValue( string( line, equals + 1, string::npos ) );
}

INIFile::INIFile( std::istream& in, const optionsDescrition* options )
{
	unsigned count = 0;
	string line;
	const optionsDescrition* current = 0;
	bool inside = false;

	string group;
	while ( getline( in, line ) ) {
		++count;
		cleanup( line );
		if ( line.empty() ) continue;
		if ( parseGroupName( line, group ) ) {
			inside = true;
			if ( options ) {
				for ( current = options; current->name; ++current ) {
					if ( group == current->name ) break;
				}
				if ( !current->name ) {
					std::cerr << "Unknown group name \'" << group
						<< "\' in line " << count << ", ignoring.\n";
					inside = false;
				}
			}
		} else if ( inside ) {
			parseLine( line, group, current, count );
		}
	}
}

std::string INIFile::get( std::string group, std::string name ) const {
	std::map<std::string, std::map<std::string, std::string> >::const_iterator one
		= parsed_.find( group );
	if ( one == parsed_.end() ) return "";

	std::map<std::string, std::string>::const_iterator two = one->second.find( name );
	if ( two == one->second.end() ) return "";
	return two->second;
}

#ifdef TEST_INIFILE

#include <fstream>

int main() {
	optionsDescrition options[] = {
		{ "test", { "one", "two", "three", 0 } },
		{ "other", { "um", "dois", "três", 0 } },
		{ 0, { 0 } }
	};

	
	std::ifstream in( "test.ini" );
	if ( in ) {
		INIFile file( in, options );

		std::cout << "test/one = \'" << file.get( "test", "one" ) << '\'' << std::endl;
		std::cout << "test/two = \'" << file.get( "test", "two" ) << '\'' << std::endl;
		std::cout << "test/three = \'" << file.get( "test", "three" ) << '\'' << std::endl;
		std::cout << "test/one = \'" << file.get( "test", "one" ) << '\'' << std::endl;
		
		std::cout << "other/um = \'" << file.get( "other", "um" ) << '\'' << std::endl;
		std::cout << "other/dois = \'" << file.get( "other", "dois" ) << '\'' << std::endl;
		std::cout << "other/três = \'" << file.get( "other", "três" ) << '\'' << std::endl;
		std::cout << "other/um = \'" << file.get( "other", "um" ) << '\'' << std::endl;

		std::cout << "other/ummm = \'" << file.get( "other", "ummm" ) << '\'' << std::endl;
		std::cout << "none/um = \'" << file.get( "none", "um" ) << '\'' << std::endl;


	} else {
		std::cerr << "Error opening file\n";
		return 1;
	}
	return 0;
}

#endif

