#include "computerplayer.h"

#include "general/helper.h"
#include "communication/factory.h"

#include "options.h"

#include "computerplayer3_2.h"
#include "computerplayer4.h"

#include <unistd.h>


ComputerPlayer::ComputerPlayer( int fd )
		: player_( new ComputerPlayer3_2 ),
		connection_( new FDConnection( fd ) ),
		pfd_( 1 )
{
	connection_->register_pollfd( pfd_[ 0 ] );
}

void ComputerPlayer::poll_success()
{
	connection_->poll_success();
	while ( connection_->message_available() ) {
		this->handle( connection_->get_message() );
	}
}


void ComputerPlayer::playquery_message()
{
	connection_->write( Factory::Client::playreply( player_->play() ) );
}

void ComputerPlayer::give3query_message( player_id::type )
{
	connection_->write( Factory::Client::give3reply( player_->give() ) );
}


void ComputerPlayer::receive_message( Card c )
{
	player_->receive( c );
}

void ComputerPlayer::inform_message( player_id::type who, Card what )
{
	player_->inform( what, who );
}

void ComputerPlayer::namequery_message()
{
	connection_->write( Factory::Client::namereply( Options::name() ) );
}


void ComputerPlayer::status_message( player_status::type s )
{
	using namespace player_status;
	switch ( s ) {
		case hand_over_self_win:
		case hand_over_right_win:
		case hand_over_front_win:
		case hand_over_left_win: {
			player_->hand_end();
			break;
		}
		case game_over: {}
		default: {
			LOG_PLACE() << s << ".\n";
		}
	}
}



