#ifndef DB_SERVER_H_INCLUDE_GUARD_
#define DB_SERVER_H_INCLUDE_GUARD_

#include "connectingplayer.h"
#include "gamemanager.h"
#include "communication/connection.h"

#include <sys/poll.h>
#include <string>

/** This class runs a hearts server.
	This contains all the objects necessary for running the program. It delegates almost all functions to these member objects.
	The only real work of this function is in the constructor, where connections are opened. All the rest is just a driver, where the 
	member objects provide everything.
  */


class Server
{
	public:
		Server();
		/** This function returns a code with similar semantics to main(). */
		int exec();

		void name( ConnectingPlayer*, std::string );

		void game_over();
		void match_over(player_id::type);
	private:

		void ask_names();
		void advertise_points();
		void advertise_match_over( player_id::type );

		std::vector<ConnectingPlayer*> players;
		std::vector< pollfd > fds;
		std::vector<std::string> playernames_;

		GameManager manager;
};



#endif /* DB_SERVER_H_INCLUDE_GUARD_ */
