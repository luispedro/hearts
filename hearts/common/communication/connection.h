#ifndef DB_CONNECTION_H_INCLUDE_GUARD_
#define DB_CONNECTION_H_INCLUDE_GUARD_

#include "message.h"

/** @short A class which handles two way communication between a client and a server or a server and a client.
 * This class exports a pollfd so that the user can multiplex on it. The usual implementation is that when poll_success is
 * called, the object tries to read as much as it can and then puts it on a message queue. message_available() then returns
 * !queue.empty() and get_message() returns queue.get_top_and_pop().
 */

class pollfd;

class Connection
{
	public:
		virtual ~Connection()
		{ }

		/** This fills up arg so that it can be used to call poll().
		  * This only needs to be called once.
		  * Remember that the object retains a reference (pointer) to the pollfd object, so do not delete it.
		  */
		virtual void register_pollfd( pollfd& arg ) = 0;

		/** This should be called whenever a poll() with a previously filled pollfd returns success.
		  * @param events The pollfd on which poll() was called. It is assumed that
		  *  events.revents != 0. Notice that this also an out parameter: The 
		     *  connection may decide to change the events on which it is polling. This
		  *  could happen if for example, the application decides that it wants to
		  *  write on the file descriptor and sets POLLOUT and waits so that it 
		  *  never blocks.
		 	  */
		virtual void poll_success() = 0;

		/** This asks whether the next call to get_message will work.
		 * Note that the fact that a poll succeeded <em>does not</em> mean that 
		 * a complete message is available. There is also the possibility that 
		 * a poll success refers to two new messages.
		 */
		virtual bool message_available() const = 0;

		/** This gets a message from the internal buffer. It is a programmer error
		  * to call this if !message_available().
		  */
		virtual Message get_message() = 0;

		/** This sets the up the message to be written. Note that the message
		  * may not be written immediately. Typically, a connection will set up
		  * queue of bytes to write, set POLLOUT on its pollfd and then when it 
		  * succeeds, it will do the actual write.
		  */
		virtual void write( Message ) = 0;
};




#endif /* DB_CONNECTION_H_INCLUDE_GUARD_ */
