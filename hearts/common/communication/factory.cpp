#include <strstream>
#include "factory.h"
#include "general/helper.h"
#include "protocol.h"

using namespace Protocol;
using namespace MessageTypes;
using namespace std;

#define INIT \
	char buffer[1024]; \
	std::ostrstream out(buffer,sizeof(buffer));

#define END(type) \
	out << std::ends;\
	return Message(MessageTypes::type,buffer);

#define JUST_RET(Space, Name,type)	\
	 Message Space::Name() \
	{	return Message(MessageTypes::type); }


namespace Factory
{
Message Common::terminate( std::string msg )
{
	return Message( Terminate, encode( msg ) );
}

Message Common::ignored( Message m )
{
	return Message( Ignored, encode_no_term( m ) );
}



Message Server::opponentname( std::string name, player_id::type who )
{
	INIT
	out << who << separator << encode( name );
	END( Opponentname )
}

Message Server::receive( Card c )
{
	INIT
	out << c;
	END( Receive )
}



Message Server::status( player_status::type stat )
{
	INIT
	out << stat;
	END( Status )
}

Message Server::points( unsigned self, unsigned rigth, unsigned front, unsigned left )
{
	INIT
	out << self << separator << rigth << separator << front << separator << left;
	END( Points )
}

JUST_RET( Server, give3query, Give3Query )
JUST_RET( Server, playquery, PlayQuery )

Message Server::invalidplay( std::string reason )
{
	INIT
	out << encode( reason );
	END( Invalidmove )
}

Message Server::inform( Card c, player_id::type who )
{
	INIT
	out << who << separator << c;
	END( Inform )
}

JUST_RET( Server, namequery, NameQuery )

Message Client::give3reply( Holder3 cards )
{
	INIT
	LOG_PLACE() << " size = " << cards.vector().size() << ".\n";
	out << cards;
	LOG_PLACE_NL();
	END( Give3Reply )
}

Message Client::playreply( Card c )
{
	INIT
	out << c;
	END( PlayReply )
}


Message Client::namereply( std::string str )
{
	return Message( NameReply, encode( str ) );
}

}




