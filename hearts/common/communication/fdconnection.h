#ifndef DB_FDCONNECTION_H_INCLUDE_GUARD_
#define DB_FDCONNECTION_H_INCLUDE_GUARD_

#include "connection.h"
#include "translator.h"

#include <queue>
#include <vector>

class FDConnection : public Connection
{
	public:
		FDConnection( int fd );
		virtual void register_pollfd( pollfd& );
		virtual void poll_success();
		virtual bool message_available() const;
		virtual Message get_message();
		virtual void write( Message );
		int fd()
		{
			return fd_;
		}
	private:
		int fd_;
		Translator in_buffer_;
		std::vector<char> out_buffer_;
		pollfd* pfd_;
};



#endif /* DB_FDCONNECTION_H_INCLUDE_GUARD_ */
