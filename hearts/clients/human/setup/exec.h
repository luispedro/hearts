#ifndef DB_EXEC_H_INCLUDE_GUARD_
#define DB_EXEC_H_INCLUDE_GUARD_

#include <qstring.h>

namespace execute {
		void server( const int fds[ 4 ] );
		bool server( short );
		int computerClient( QString name );
		QString generateLocalAddress();
}
namespace unix {
		void coe( int );
		void uncoe( int );
}

#endif /* DB_EXEC_H_INCLUDE_GUARD_ */
