#ifndef DB_TYPICALCLIENT_H_INCLUDE_GUARD_
#define DB_TYPICALCLIENT_H_INCLUDE_GUARD_

#include "dispatch.h"

  

class TypicalClient: public Dispatch 
{
	private:
		virtual void namereply_message(std::string);
		virtual void playreply_message(Card);
		virtual void give3reply_message(const Holder3&);


	private:
		/** This is called whenever a message which is meant to be delivered to
		 * the server is received.
		 */
		virtual void server_message(std::string) = 0;
};



#endif /* DB_TYPICALCLIENT_H_INCLUDE_GUARD_ */
