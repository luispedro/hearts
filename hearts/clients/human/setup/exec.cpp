#include "exec.h"
#include "general/helper.h"
#include "communication/constants.h"

#include <kprocess.h>
#include <qstring.h>
#include <qstringlist.h>

#include <stdio.h>

#include <sys/types.h>
#include <sys/socket.h>

QString execute::generateLocalAddress()
{
	return QString::fromLocal8Bit( local_address ) + QString::number( getpid() );
}

std::ostream& operator<<( std::ostream& s, const QValueList<QCString>& l )
{
	QValueList<QCString>::const_iterator it = l.begin();
	for ( ; it != l.end(); ++it )
		s << '\"' << ( *it ) << "\" ";
	return s;
}


namespace execute {

bool execute_server()
{
	return execute_server( Communication::Port );
}

bool execute_server( short port )
{
	KProcess p;
	p << "heartsserver"
	<< "--tcp-port" << QString::number( port )
	<< "--unix-port" << generateLocalAddress()
	<< "--wait-zero";

	LOG_PLACE() << " !" << p.args() << "!\n";
	return p.start( KProcess::DontCare );
}

bool execute_server( bool tcp, bool local )
{
#warning execute_server( bool, bool ) not implemented

	execute_server( 0 );
}

bool execute_computer_client( QString name )
{
	KProcess p;
	p << "heartscomputerclient"
	<< "--playername" << name
	<< "--address" << generateLocalAddress()
	<< "--zero";
	LOG_PLACE() << '!' << p.args() << "!\n";
	return p.start( KProcess::DontCare );
}


}

void execute::server( const int fds[ 4 ] ) {
	char buffer[ 32 ];
	if ( snprintf( buffer, sizeof( buffer ), "%d,%d,%d,%d", fds[ 0 ], fds[ 1 ], fds[ 2 ], fds[ 3 ] ) > 0) {
			execlp( "heartsserver", "heartsserver", "--fds", buffer, ( const char* )0 );
	}
	exit( 1 ); // An error occurred
}


int execute::computerClient( QString name )
{
	int pipe[2];
	if ( socketpair( AF_LOCAL, SOCK_STREAM, PF_LOCAL, pipe ) < 0 ) return -1;
	KProcess p;
	p << "heartscomputerclient"
			<< "--playername" << name
			<< "--fd" << QString::number( pipe[0] )
			<< "--zero";
	LOG_PLACE() << '!' << p.args() << "!\n";
	LOG_PLACE() << " FDs: " << pipe[ 0 ] << " <-> " << pipe[ 1 ] << "\n";
	if ( !p.start( KProcess::DontCare ) ) return -1;
	close( pipe[0] );
	return pipe[1];
}

