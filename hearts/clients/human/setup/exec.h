#ifndef DB_EXEC_H_INCLUDE_GUARD_
#define DB_EXEC_H_INCLUDE_GUARD_

#include <qstring.h>

namespace execute {
		void server( const int fds[ 4 ] );
		bool execute_server();
		bool execute_server( bool tcp, bool local );
		bool execute_server( short port );

		int computerClient( QString name );
		QString generateLocalAddress();
}

using namespace execute;

#endif /* DB_EXEC_H_INCLUDE_GUARD_ */
