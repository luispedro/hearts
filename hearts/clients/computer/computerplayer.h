#ifndef DB_COMPUTERPLAYER_H1053544106_INCLUDE_GUARD_
#define DB_COMPUTERPLAYER_H1053544106_INCLUDE_GUARD_

#include "communication/typicalclient.h"
#include "communication/fdconnection.h"
#include "computerplayerbase.h"
#include <sys/poll.h>
#include <vector>

class ComputerPlayer : public TypicalClient
{
	public:
		ComputerPlayer( int fd );
		std::vector<pollfd>& get_pollfd()
		{
			return pfd_;
		}
		void poll_success();


	private:
		ComputerPlayerBase* player_;
		FDConnection* connection_;
		std::vector<pollfd> pfd_;

	private:

		virtual void playquery_message();
		virtual void give3query_message( player_id::type );
		virtual void receive_message( Card );
		virtual void inform_message( player_id::type, Card );
		virtual void opponentname_message( player_id::type, std::string )
		{ }
		virtual void ignore_message( Message )
		{ }
		virtual void terminate_message( std::string )
		{ }
		virtual void invalidmove_message( std::string )
		{ }
		virtual void status_message( player_status::type );
		virtual void points_message( unsigned, unsigned, unsigned, unsigned )
		{ }
		virtual void bad_message( Message )
		{ }
		virtual void server_message( std::string )
		{ }
		virtual void namequery_message();
};



#endif /* DB_COMPUTERPLAYER_H1053544106_INCLUDE_GUARD_ */
