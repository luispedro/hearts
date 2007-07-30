#include "exec.h"
#include "general/helper.h"
#include "communication/constants.h"

#include <kprocess.h>
#include <qstring.h>
#include <qstringlist.h>

#include <stdio.h> // snprintf

#include <sys/types.h> // socketpair
#include <sys/socket.h> // socketpair
#include <fcntl.h> // uncoe

QString execute::generateLocalAddress()
{
	return QString::fromLocal8Bit( Communication::local_address ) + QString::number( getpid() );
}

std::ostream& operator<<( std::ostream& s, const QValueList<QCString>& l )
{
	QValueList<QCString>::const_iterator it = l.begin();
	for ( ; it != l.end(); ++it )
		s << '\"' << ( *it ) << "\" ";
	return s;
}


bool execute::server( short port )
{
	KProcess p;
	p << "heartsserver"
	<< "--daemon"
	<< "--tcp-port" << QString::number( port )
	<< "--unix-port" << generateLocalAddress()
	<< "--wait-zero";

	LOG_PLACE() << " !" << p.args() << "!\n";
	return p.start( KProcess::DontCare );
}

/* On the close-on-exec flag
 * 
 * We need to stop the AI player from having a copy of each others pipes, so we set
 * close-on-exec on each flag.
 *
 * Then, just before we exec the server, we unset it.
 */
void unix::coe( int fd ) {
	fcntl( fd, F_SETFD, ( fcntl( fd, F_GETFD ) | FD_CLOEXEC ) );
}
void unix::uncoe( int fd ) {
	fcntl( fd, F_SETFD, ( fcntl( fd, F_GETFD ) & ~FD_CLOEXEC ) );
}

using namespace unix;

void execute::server( const int fds[ 4 ] ) {
	char buffer[ 32 ];
	char port[ 32 ];
	bool tcp = false;
	for ( int i = 0; i != 4; ++i ) {
		if ( fds[ i ] ) uncoe( fds[ i ] );
		else tcp = true;
	}
	if ( snprintf( buffer, sizeof( buffer ), "%d,%d,%d,%d", fds[ 0 ], fds[ 1 ], fds[ 2 ], fds[ 3 ] ) > 0) {
		if ( tcp ) {
			if ( snprintf( port, sizeof( port ), "%d", Communication::tcp_port ) > 0 ) {
				execlp( "heartsserver",
					"heartsserver",
					"--daemon",
					"--fds",
					buffer,
					"--tcp-port",
					port,
					"--wait-zero",
					static_cast<const char*>( 0 )
					);
			}
		} else {
			execlp( "heartsserver",
				"heartsserver",
				"--daemon",
				"--fds",
				buffer,
				"--wait-zero",
				( const char* )0 );
		}	
	}
	LOG_PLACE_NL();
	exit( 1 ); // An error occurred
}


int execute::computerClient( QString n )
{
	enum { client, server };
	int pipe[2];
	if ( socketpair( AF_LOCAL, SOCK_STREAM, PF_LOCAL, pipe ) < 0 ) return -1;

	char name[ 64 ];
	strncpy( name, n.utf8(), sizeof( name ) );
	char fd[ 8 ];
	snprintf( fd, sizeof( fd ), "%d", pipe[ client ] );
	
	int stat = fork();
	if ( stat < 0 ) return -1;
	if ( stat > 0 ) {
		::close( pipe[ client ] );
		return pipe[ server ];
	} else {
		close( pipe[ server ] );
		execlp( "heartscomputerclient",
						"heartscomputerclient",
						"--playername",
						name,
						"--fd",
						fd,
						"--zero",
						static_cast<const char*>( 0 ) );
		exit( 1 );
	}
	close( pipe[ client ] );
	return pipe[ server ];
}

int execute::start_new_private_game( QString self, QString right, QString front, QString left) 
{
	LOG_PLACE_NL();
	enum { client, server };
	int pipe[2];
	int stat;
	if ( socketpair( AF_LOCAL, SOCK_STREAM, PF_LOCAL, pipe ) < 0 ) {
		goto error;
	}
	stat = fork();
	if ( stat < 0 ) goto error;
	if ( stat > 0 ) {
		::close( pipe[ server ] );
		char c = 0;
		::write( pipe[ client ], &c, 1);
		return pipe[ client ];
	} else {
		::close( pipe[ client ] );

		int fds[ 4 ];
		fds[ 0 ] = pipe[ server ];
		fds[ 1 ] = execute::computerClient( right );
		fds[ 2 ] = execute::computerClient( front );
		fds[ 3 ] = execute::computerClient( left );
		if ( fds[ 1 ] < 0 ||
			fds[ 2 ] < 0 ||
			fds[ 3 ] < 0 ) {
			::close( pipe[ server ] );
			exit( 1 );
		}
		execute::server( fds );
		return 0;
	}
error:
	LOG_PLACE_NL();
	return 0;
}	
