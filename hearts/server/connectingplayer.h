#ifndef DB_CONNECTINGPLAYER_H_INCLUDE_GUARD_
#define DB_CONNECTINGPLAYER_H_INCLUDE_GUARD_

#include "player.h"
#include "hearts/player_id.h"
#include "communication/connection.h"
#include "communication/typicalserver.h"
#include "communication/fdconnection.h"

/** @short This is a glue class between Player and Dispatch
	This is to implement a player which sits on the other end of a connection.
  */

class Server;

class ConnectingPlayer : public FDConnection, public Player, public TypicalServer
{
	public:
		ConnectingPlayer( player_id::type, Server* );

		// the player interface:
		virtual void play();
		virtual void give();
		virtual void invalidPlay( std::string );
		virtual void receive( Card );
		virtual void inform( Card, player_id::type );
		virtual void currentStatus( player_status::type );
		virtual void points( unsigned, unsigned, unsigned, unsigned );
		virtual void matchOver();
		virtual void reset()
		{
			assert( 0 );
		}

		// other communications:
		void namequery();
		void opponentname( player_id::type, std::string );


	private:
		// the Handler interface:
		virtual void playreply_message( Card );
		virtual void give3reply_message( const Holder3& );
		virtual void namereply_message( std::string );
		virtual void wrong_message( std::string );
		virtual void ignore_message( Message );
		virtual void terminate_message( std::string );
		virtual void bad_message( Message );

		Server* server;
};



#endif /* DB_CONNECTINGPLAYER_H_INCLUDE_GUARD_ */
