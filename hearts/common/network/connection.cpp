#include "connection.h"
#include "general/helper.h"
#include <kextsock.h>

#include <errno.h>
#include <kdebug.h>

namespace Network
{

Connection::Connection( KExtendedSocket* socket, QObject* parent, const char* name )
		: QObject( parent, name ),
		socket_( socket )
{
	massert( socket_ );
	LOG_PLACE_NL();
	socket_->enableRead( true );
	socket_->setSocketFlags( KExtendedSocket::inputBufferedSocket );
	socket_->setBufferSize( 1024, 1024 );
	LOG_PLACE() << "socket_ = " << socket_ << '\n';
	connect( socket_, SIGNAL( closed( int ) ), SLOT( socketClosed( int ) ) );
	connect( socket_, SIGNAL( readyRead() ), SLOT( read() ) );
	LOG_PLACE_NL();
}

Connection::~Connection()
{
	socket_->close();
	delete socket_;
}


void Connection::close()
{
	socket_->close();
}

void Connection::get( Message )
{}

void Connection::read()
{
	char buffer[ 1024 ];
	buffer[ 0 ] = '\0';
	//X 	LOG_PLACE_NL();
	socket_->peekBlock( buffer, sizeof( buffer ) );
	LOG_PLACE() << " available = " << socket_->bytesAvailable() << ", peeked = \'" << buffer << "\'." << std::endl;
	while ( socket_->canReadLine() ) {
		socket_->readLine( buffer, sizeof( buffer ) );
		buffer[strlen(buffer)-1] = '\0'; // Remove the newline!
		LOG_PLACE() << ", read = \"" << buffer << "\"." << std::endl;
		Message m( QString::fromUtf8( buffer ) );
		get( m );
		emit received( m );
	}
}

void Connection::write( Message m )
{
	LOG_PLACE() << " Writing: '" << m << "'\n";
	QCString data = m.asString().utf8();
	socket_->writeBlock( data, data.size() );
	socket_->writeBlock( "\n", 1 );
}


void Connection::changeProtocol()
{
	MessageConstructor m;
	m << Message::changeProtocol;
	write( m );
}

void Connection::socketClosed( int status )
{
	
	kdDebug() << "Connection::socketClosed()" << endl;
	if ( status & KExtendedSocket::involuntary )
		emit connectionError( "socket closed by remote peer", ECONNRESET );
}

UserConnection::UserConnection( KExtendedSocket* connection, QObject* parent, const char* name )
		: Connection( connection, parent, name )
{
	LOG_PLACE_NL();
}

void UserConnection::createTable( QString name )
{
	MessageConstructor m;
	m << Message::createTable << name;
	write( m );
}

void UserConnection::joinTable( QString name )
{
	MessageConstructor m;
	m << Message::joinTable << name;
	write( m );
}

void UserConnection::hello( QString name )
{
	MessageConstructor m;
	m << Message::hello << name;
	write( m );
}

void UserConnection::authR( QCString cookie, QCString result )
{
	LOG_PLACE() << "authR -" << cookie << "- -" << result << "-" << '\n';
	write( MessageConstructor() << Message::authR << cookie << result );
}

void UserConnection::leaveTable()
{
	MessageConstructor m;
	write( m << Message::leaveTable );
}

void UserConnection::get( Message m )
{
	LOG_PLACE() << "Got message: " << m << '\n';
	switch ( m.type() ) {
		case Message::connectTo:
			emit connectTo( m.arg<const char*>( 0 ), m.arg<short>( 1 ) );
			return ;
		case Message::tableInfo:
			LOG_PLACE() << "numArgs(): " << m.numArgs() << "\n";
			emit lookAt( m.arg<QString>( 0 ),
					 m.numArgs() >= 1 ? m.arg<QString>( 1 ) : QString::null,
					 m.numArgs() >= 2 ? m.arg<QString>( 2 ) : QString::null,
					 m.numArgs() >= 3 ? m.arg<QString>( 3 ) : QString::null,
					 m.numArgs() >= 4 ? m.arg<QString>( 4 ) : QString::null );
			return ;
		case Message::changeProtocol:
			emit protocolChanged();
			return ;
		case Message::userStatus:
			emit userStatus( m.arg<QString>( 0 ), m.arg<user_status::type>( 1 ) );
			return;
		case Message::motd:
			emit motd( m.arg<QString>( 0 ) );
			return;
		case Message::authQ:
			emit authQ( m.arg<QCString>( 0 ), m.arg<QCString>( 1 ) );
			return;
		case Message::error:
			emit error( m.arg<Message::errorType>( 0 ), m.arg<QString>( 1 ) );
			return;
	}
	LOG_PLACE() << "Unknown message: " << m << '\n';
}

ServerConnection::ServerConnection( KExtendedSocket* socket, QObject* parent, const char* name )
		: Connection( socket, parent, name )
{}

void ServerConnection::connectTo( const char* server, short port )
{
	MessageConstructor m;
	m << server << port;
	write( m );
}

void ServerConnection::lookAt( QString table, QString p1, QString p2, QString p3, QString p4 )
{
	MessageConstructor m;
	m << Message::lookAt << table << p1 << p2 << p3 << p4;
	write( m );
}

void ServerConnection::motd( const QString& message ) {
	write( MessageConstructor() << Message::motd << message );
}

void ServerConnection::authQ( QCString method, QCString cookie )
{
	MessageConstructor m;
	write( m << Message::authQ << method << cookie );
}

void ServerConnection::get( Message m )
{
	LOG_PLACE() << "Got message: " << m << '\n';
	switch ( m.type() ) {
		case Message::createTable:
			emit createTable( this, m.arg<QString>( 0 ) );
			return ;
		case Message::joinTable:
			emit joinTable( this, m.arg<QString>( 0 ) );
			return ;
		case Message::hello:
			emit hello( this, m.arg<QString>( 0 ) );
			return ;
		case Message::leaveTable:
			emit leaveTable( this );
			return ;
		case Message::changeProtocol:
			emit protocolChanged();
			return ;
	}
	LOG_PLACE() << "Unknown message: " << m << '\n';
}

} // namespace Network

#include "connection.moc"


