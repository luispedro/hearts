#include "dispatch.h"
#include "protocol.h"
#include "general/helper.h"
#include <strstream>
#include <iostream>

using std::istrstream;


Dispatch::Handler Dispatch::code2handler( Message::type_t type )
{
	typedef std::map<Message::type_t, Handler> map_type;
	static map_type handlers;
	if ( handlers.empty() ) {
		using namespace MessageTypes;
		handlers[ NameQuery ] = &Dispatch::namequery_handler;
		handlers[ NameReply ] = &Dispatch::namereply_handler;
		handlers[ Opponentname ] = &Dispatch::opponentname_handler;
		handlers[ Receive ] = &Dispatch::receive_handler;
		handlers[ Invalidmove ] = &Dispatch::invalidmove_handler;
		handlers[ Inform ] = &Dispatch::inform_handler;
		handlers[ Status ] = &Dispatch::status_handler;
		handlers[ Points ] = &Dispatch::points_handler;
		handlers[ PlayQuery ] = &Dispatch::playquery_handler;
		handlers[ PlayReply ] = &Dispatch::playreply_handler;
		handlers[ Give3Query ] = &Dispatch::give3query_handler;
		handlers[ Terminate ] = &Dispatch::terminate_handler;
		//	handlers[Reset] = &Dispatch::reset_handler;
		handlers[ Give3Reply ] = &Dispatch::give3reply_handler;
		handlers[ PlayReply ] = &Dispatch::playreply_handler;

	}
	map_type::iterator resp = handlers.find( type );
	if ( resp == handlers.end() ) {
		LOG_PLACE() << "No handler for " << type << ".\n";
		return &Dispatch::error_handler;
	}
	return resp->second;
}

void Dispatch::handle( Message m )
{
	( this->*code2handler( m.type() ) ) ( m );
}

void Dispatch::points_handler( Message m )
{
	unsigned self, rigth, front, left;
	istrstream in( m.body().c_str() );
	in >> self >> rigth >> front >> left;
	if ( !in )
		bad_message( m );
	else
		points_message( self, rigth, front, left );
}

void Dispatch::opponentname_handler( Message m )
{
	player_id::type player;
	std::string name;
	istrstream in( m.body().c_str() );
	in >> player;
	name = Protocol::read_string( in );
	if ( !in )
		bad_message( m );
	else
		opponentname_message( player, name );
}

void Dispatch::ignore_handler( Message m )
{
	ignore_message( m );
}


void Dispatch::terminate_handler( Message m )
{
	terminate_message( m.body() );
}

void Dispatch::namequery_handler( Message )
{
	namequery_message();
}

void Dispatch::namereply_handler( Message m )
{
	std::string name;
	istrstream in( m.body().c_str() );
	name = Protocol::read_string( in );
	if ( !in )
		bad_message( m );
	else
		namereply_message( name );
}

void Dispatch::playquery_handler( Message )
{
	playquery_message();
}

void Dispatch::playreply_handler( Message m )
{
	Card c;
	istrstream in( m.body().c_str() );
	in >> c;
	if ( !in )
		bad_message( m );
	else
		( playreply_message( c ) );
}

void Dispatch::inform_handler( Message m )
{
	LOG_PLACE() << Protocol::encode( m ) << ".\n";
	player_id::type who;
	Card what;
	istrstream in( m.body().c_str() );
	in >> who >> what;
	if ( !in )
		bad_message( m );
	else
		inform_message( who, what );
}

void Dispatch::invalidmove_handler( Message m )
{
	istrstream in( m.body().c_str() );
	invalidmove_message( Protocol::read_string( in ) );
}

void Dispatch::status_handler( Message m )
{
	istrstream in( m.body().c_str() );
	player_status::type stat;
	in >> stat;
	if ( !in )
		bad_message( m );
	else
		status_message( stat );
}

void Dispatch::receive_handler( Message m )
{
	Card c;
	istrstream in( m.body().c_str() );
	in >> c;
	if ( !in )
		bad_message( m );
	else
		receive_message( c );
}

void Dispatch::give3query_handler( Message )
{
	give3query_message();
}

void Dispatch::give3reply_handler( Message m )
{
	Holder3 hold;
	istrstream in( m.body().c_str() );
	in >> hold;
	LOG_PLACE() << ' ' << hold << ".\n";
	if ( !in )
		bad_message( m );
	else
		give3reply_message( hold );
}


void Dispatch::error_handler( Message m )
{
	bad_message( m );
}

