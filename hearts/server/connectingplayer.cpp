#include "connectingplayer.h"
#include "communication/factory.h"
#include "general/helper.h"

#include "id_to_fd.h"
#include "server.h"
#include "options.h"
#include <unistd.h>

ConnectingPlayer::ConnectingPlayer( player_id::type id, Server* s )
		: FDConnection( id_to_fd( id ) ),
		server( s )
{
	LOG_PLACE_NL();
	if ( options->wait_zero() ) {
		char c = 1;
		LOG_PLACE() << "Waiting for a zero.\n";
		while ( ::read( id_to_fd( id ), &c , 1 ) > 0 && c )
			LOG_PLACE() << "?\n";
		LOG_PLACE() << "Received zero. We can start.\n";
	}
}

void ConnectingPlayer::play()
{
	write( Factory::Server::playquery() );
}

void ConnectingPlayer::give()
{
	write( Factory::Server::give3query() );
}

void ConnectingPlayer::receive( Card c )
{
	write( Factory::Server::receive( c ) );
}

void ConnectingPlayer::invalidPlay( std::string reason )
{
	write( Factory::Server::invalidplay( reason ) );
}

void ConnectingPlayer::inform( Card c, player_id::type who )
{
	write( Factory::Server::inform( c, who ) );
}

void ConnectingPlayer::currentStatus( player_status::type s )
{
	write( Factory::Server::status( s ) );
}

void ConnectingPlayer::points( unsigned sP, unsigned rP, unsigned fP, unsigned lP )
{
	write( Factory::Server::points( sP, rP, fP, lP ) );
}

void ConnectingPlayer::namequery()
{
	write( Factory::Server::namequery() );
}

void ConnectingPlayer::opponentname( player_id::type who, std::string name )
{
	write( Factory::Server::opponentname( name, who ) );
}

void ConnectingPlayer::matchOver()
{
	write( Factory::Common::terminate( "Game Over" ) );
}

void ConnectingPlayer::playreply_message( Card c )
{
	receiver->play_reply( c );
}

void ConnectingPlayer::give3reply_message( const Holder3& h )
{
	receiver->give_reply( h );
}

void ConnectingPlayer::ignore_message( Message )
{}

void ConnectingPlayer::wrong_message( std::string m )
{
	std::cerr << "Got a wrong message: " << m << std::endl;
}

void ConnectingPlayer::terminate_message( std::string r )
{
	std::cerr << "Got a terminate message: " << r << std::endl;
}

void ConnectingPlayer::bad_message( Message )
{
	std::cerr << "Got a bad message.\n";
}

void ConnectingPlayer::namereply_message( std::string name )
{
	if ( server )
		server->name( this, name );
}

