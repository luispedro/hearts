#include "server.h"
#include "options.h"

#include "general/helper.h"
#include "connectingplayer.h"
#include "general/utilitario.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cassert>

const unsigned number_of_players = 4;
struct gameover_callback
{
	gameover_callback( Server& s ) : server( s )
	{ }
	void operator() ()
	{
		server.game_over();
	}
private:
	Server& server;
};

Server::Server()
{
	fds.resize( number_of_players );
	for ( unsigned i = 0; i != number_of_players; ++i ) {
		players.push_back( new ConnectingPlayer( player_id::all_players[ i ], this ) );
		players.back() ->register_pollfd( fds[ i ] );
		manager.register_player( *players.back(), player_id::all_players[ i ] );
	}
	manager.register_game_over_callback( gameover_callback( *this ) );
}

int Server::exec()
{
	int stat;
	LOG_PLACE() << ".\n";
	ask_names();
	manager.start_game();
	LOG_PLACE() << ".\n";
	while ( ( stat = Utility::Poll( fds, Utility::Poll_Forever ) ) > 0 ) {
		for ( unsigned i = 0; i != number_of_players; ++i ) {
			if ( fds[ i ].revents ) {
				//LOG_PLACE() << ".\n";
				players[ i ] ->poll_success();
				while ( players[ i ] ->message_available() ) {
					players[ i ] ->handle( players[ i ] ->get_message() );
				}
			}
		}
	}
	return 0;
}

void Server::advertise_points()
{
	using namespace player_id;
	std::vector<unsigned> points;
	for ( int i = 0; i != number_of_players; ++i ) points.push_back( manager.points( player_id::all_players[ i ] ) );
	LOG_PLACE() 
		<< "\n\n\n"
		<< "\n\t POINTS[ 0 ]: " << points[ 0 ] << "."
		<< "\n\t POINTS[ 1 ]: " << points[ 1 ] << "."
		<< "\n\t POINTS[ 2 ]: " << points[ 2 ] << "."
		<< "\n\t POINTS[ 3 ]: " << points[ 3 ] << "."
		<< "\n\n\n\n\n";
	circular_iterator<std::vector<unsigned>::iterator> iter( points.begin(), points.begin(), points.end() );
	for ( unsigned i = 0; i != 4; ++i ) {
		players[ i ]->points( *iter, *( iter + 1 ), *( iter + 2 ), *( iter + 3 ) );
		++iter;
	}
}

void Server::advertise_match_over()
{
	for_each( players.begin(), players.end(), mem_fun( &ConnectingPlayer::matchOver ) );
}

void Server::game_over()
{
	LOG_PLACE_NL();
	advertise_points();
	unsigned mostP = most_points( manager );
	if ( mostP > options->maxPoints() ) {
		advertise_match_over();
	} else {
		manager.start_game();
	}
}


void Server::ask_names()
{
	for ( unsigned i = 0; i != 4; ++i ) {
		players[ i ] ->namequery();
	}
}

void Server::name( ConnectingPlayer* who, std::string name )
{
	LOG_PLACE_NL();
	circular_iterator<std::vector<ConnectingPlayer*>::iterator> circler( players.begin(), players.begin(), players.end() );
	while ( *circler != who ) {
		++circler;
		assert( *circler != players.front() );
	}
	for ( int i = 1; i != 4; ++i )      // self does not matter
	{
		( *( circler + i ) ) ->opponentname( player_id::all_players[ i ], name );
	}
}



