#include "protocol.h"
#include "general/helper.h"
#include <cassert>

using namespace std;
using namespace MessageTypes;

#define PUT_ALL \
		PUT(Name)\
		PUT(Opponentname)\
		PUT(Receive)\
		PUT(Invalidmove)\
		PUT(Inform)\
		PUT(Status)\
		PUT(Points)\
		PUT(Ignored)\
		PUT(NameQuery)\
		PUT(NameReply)\
		PUT(PlayQuery)\
		PUT(PlayReply)\
		PUT(Give3Query)\
		PUT(Give3Reply)\
		PUT(Terminate)\
		PUT(Reset)\
		PUT(Unknown)

type Protocol::string2code( string str )
{
	static map<string, type> mapper;
	if ( mapper.empty() ) {
#define PUT(x) mapper[#x] = x;
		PUT_ALL
#undef PUT

	}
	map<string, type>::iterator resp = mapper.find( str );
	if ( resp == mapper.end() ) {
		LOG_PLACE() << "Unknown message: \'" << str << "\'\n";
		return Unknown;
	}
	return resp->second;
}

string Protocol::code2string( type cod )
{
	static map<type, string> mapper;
	if ( mapper.empty() ) {
#define PUT(x) mapper[x] = #x;
		PUT_ALL
#undef PUT

	}
	map<type, string>::iterator resp = mapper.find( cod );
	assert ( resp != mapper.end() );
	return resp->second;
}

string Protocol::encode( Message m )
{
	using namespace Protocol;
	string res = code2string( m.type() );
	if ( m.body() != "" ) {
		res += separator + m.body();
	}
	return res;
}

std::string Protocol::encode( std::string orig )
{
	std::string res = "\"";
	std::string::iterator first = orig.begin();
	while ( first != orig.end() ) {
		switch ( *first ) {
			case '\n':
			res += "\\n";
			break;
			case '\"':
			res += "\\\"";
			break;
			default:
			res += *first;
		}
		++first;
	}
	res += '\"';
	return res;
}

std::string Protocol::read_string( istream& in )
{
	while ( in and in.get() != '\"' )
		;
	std::string res;
	for ( char c = in.get(); c != EOF; c = in.get() ) {
		if ( c == '\"' )
			break;
		else if ( c == '\\' ) {
			c = in.get();
			switch ( c ) {
				case 'n':
				res += '\n';
				break;
				case 't':
				res += '\t';
				break;
				case '\"':
				res += '\"';
				break;
				case EOF:
				LOG_PLACE() << "Bad message";
				return res;
			}
		} else
			res += c;
	}
	return res;
}

