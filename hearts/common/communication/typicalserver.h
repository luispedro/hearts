#ifndef DB_TYPICALSERVER_H_INCLUDE_GUARD_
#define DB_TYPICALSERVER_H_INCLUDE_GUARD_

#include "dispatch.h"



class TypicalServer: public Dispatch
{
	private:
		virtual void namequery_message();
		virtual void playquery_message();
		virtual void give3query_message( player_id::type );

		virtual void receive_message( Card );
		virtual void inform_message( Card, player_id::type );
		virtual void opponentname_message( player_id::type, std::string );
		virtual void invalidmove_message( std::string );
		virtual void status_message( player_status::type );
		virtual void points_message( unsigned, unsigned, unsigned, unsigned );
		virtual void inform_message( player_id::type, Card );
	private:
		/** This is called whenever a message which is meant to be delivered to
		 * the server is received.
		 */
		virtual void wrong_message( std::string ) = 0;
};



#endif /* DB_TYPICALSERVER_H_INCLUDE_GUARD_ */
