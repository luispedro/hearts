#ifndef DB_EXEC_H_INCLUDE_GUARD_
#define DB_EXEC_H_INCLUDE_GUARD_

#include <qstring.h>

namespace execute {
	void server( const int fds[ 4 ] );
	bool server( short );
	int computerClient( QString name );
	QString generateLocalAddress();
	int start_new_private_game( QString s, QString r, QString f, QString l );
}
#undef unix // FreeBSD seems to define unix
namespace unix {
	// Unset the close-on-exec flag on the filedescriptor
	void coe( int fd );
	void uncoe( int fd );
}

#endif /* DB_EXEC_H_INCLUDE_GUARD_ */
