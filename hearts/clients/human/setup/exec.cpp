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
namespace {
		void coe( int fd ) {
				fcntl( fd, F_SETFD, ( fcntl( fd, F_GETFD ) | FD_CLOEXEC ) );
		}
		void uncoe( int fd ) {
				fcntl( fd, F_SETFD, ( fcntl( fd, F_GETFD ) & ~FD_CLOEXEC ) );
		}
}

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
											"--fds",
											buffer,
											"--tcp-port",
											port,
											"--wait-zero",
											static_cast<const char*>( 0 )
									);
					}
			} else {
					execlp( "heartsserver", "heartsserver", "--fds", buffer, "--wait-zero", ( const char* )0 );
			}
	}
	exit( 1 ); // An error occurred
}


int execute::computerClient( QString name )
{
	enum { client, server };
	int pipe[2];
	if ( socketpair( AF_LOCAL, SOCK_STREAM, PF_LOCAL, pipe ) < 0 ) return -1;
	coe( pipe[ server ] );
	
	KProcess p;
	p << "heartscomputerclient"
			<< "--playername" << name
			<< "--fd" << QString::number( pipe[ client ] )
			<< "--zero";

	LOG_PLACE() << '!' << p.args() << "!\n";
	LOG_PLACE() << " FDs: " << pipe[ server ] << " <-> " << pipe[ client ] << "\n";

	if ( !p.start( KProcess::DontCare ) ) return -1;
	close( pipe[ client ] );
	return pipe[ server ];
}

