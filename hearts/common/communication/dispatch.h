#ifndef DB_DISPATCH_H_INCLUDE_GUARD_
#define DB_DISPATCH_H_INCLUDE_GUARD_

#include <map>
#include <memory> // auto_ptr
#include <string>

#include "message.h"
#include "hearts/player_status.h"
#include "hearts/player_id.h"
#include "hearts/card.h"
#include "hearts/holder3.h"

class Dispatch
{
	public:
		virtual ~Dispatch()
		{ }

		/** This is the main function of the class
		 * call this to dispatch the handling to the handler object
		 */
		void handle( Message );
	private:
		typedef void ( Dispatch::*Handler ) ( Message );
		Handler code2handler( Message::type_t );

		void points_handler( Message );
		void opponentname_handler( Message );
		void ignore_handler( Message );
		void terminate_handler( Message );

		void namereply_handler( Message );
		void namequery_handler( Message );

		void opponnentname_handler( Message );

		void playquery_handler( Message );
		void playreply_handler( Message );

		void inform_handler( Message );
		void invalidmove_handler( Message );
		void status_handler( Message );
		void handover_handler( Message );
		void receive_handler( Message );
		void give3query_handler( Message );
		void give3reply_handler( Message );
		void gameover_handler( Message );
		void invalidMessage_handler( Message );

		/** Error in handling the message */
		void error_handler( Message );

	private:

		/** Opponent name in utf-8 */
		virtual void opponentname_message( player_id::type, std::string ) = 0;
		virtual void ignore_message( Message ) = 0;
		virtual void terminate_message( std::string ) = 0;
		virtual void namequery_message() = 0;
		virtual void namereply_message( std::string ) = 0;
		virtual void playquery_message() = 0;
		virtual void playreply_message( Card ) = 0;
		virtual void invalidmove_message( std::string reason ) = 0;
		virtual void status_message( player_status::type ) = 0;
		virtual void receive_message( Card ) = 0;
		virtual void give3query_message() = 0;
		virtual void give3reply_message( const Holder3& ) = 0;
		virtual void points_message( unsigned, unsigned, unsigned, unsigned ) = 0;

		virtual void inform_message( player_id::type, Card ) = 0;
		/** Error in handling the message */
		virtual void bad_message( Message ) = 0;
};











#endif /* DB_DISPATCH_H_INCLUDE_GUARD_ */
