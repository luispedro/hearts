#include "connection.h"
#include "general/helper.h"
#include <kextsock.h>

#include <errno.h>

namespace Network {
	
Connection::Connection(KExtendedSocket* socket, QObject* parent, const char* name )
	:QObject( parent, name ),
	socket_( socket )
{
	massert( socket_ );
	LOG_PLACE_NL();
	socket_->enableRead( true );
	socket_->setSocketFlags( KExtendedSocket::inputBufferedSocket );
	socket_->setBufferSize( 1024, 1024 );
	LOG_PLACE() << "socket_ = " << socket_ << '\n';
	connect( socket_, SIGNAL( closed( int ) ),SLOT( socketClosed( int ) ) );
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
{

}

void Connection::read()
{
	char buffer[ 1024 ];
	buffer[ 0 ] = '\0';
//X 	LOG_PLACE_NL();
	socket_->peekBlock( buffer, sizeof( buffer ) );
	LOG_PLACE() << " available = " << socket_->bytesAvailable() << ", peeked = \'" << buffer << "\'." << std::endl;
	while ( socket_->canReadLine() )
	{
		socket_->readLine( buffer, sizeof( buffer ) );
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
	if ( status & KExtendedSocket::involuntary ) emit connectionError( "socket closed by remote peer", ECONNRESET );
}

UserConnection::UserConnection( KExtendedSocket* connection, QObject* parent, const char* name )
	:Connection( connection, parent, name )
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

void UserConnection::auth( QString auth )
{
	write( MessageConstructor() << Message::auth << auth );
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
		case Message::startGame:
			emit startGame( m.arg<short>( 0 ) );
			return;
		case Message::connectTo:
			emit connectTo( m.arg<const char*>( 0 ), m.arg<short>( 1 ) );
			return;
		case Message::tableInfo:
			emit lookAt( m.arg<QString>( 0 ),
					m.numArgs() >= 1 ? m.arg<PlayerInfo>( 1 ) : QString::null,
					m.numArgs() >= 2 ? m.arg<PlayerInfo>( 2 ) : QString::null,
					m.numArgs() >= 3 ? m.arg<PlayerInfo>( 3 ) : QString::null,
					m.numArgs() >= 4 ? m.arg<PlayerInfo>( 4 ) : QString::null );
			return;
		case Message::changeProtocol:
			emit protocolChanged();
			return;
	}
	LOG_PLACE() << "Unknown message: " << m << '\n';
}

ServerConnection::ServerConnection( KExtendedSocket* socket, QObject* parent, const char* name )
	:Connection( socket, parent, name )
{
}

void ServerConnection::startGame( short port )
{
	MessageConstructor m;
	m << Message::startGame << port;
	write( m );
}

void ServerConnection::connectTo( const  char* server, short port )
{
	MessageConstructor m;
	m << server << port;
	write( m );
}

void ServerConnection::lookAt( QString table, PlayerInfo p1, PlayerInfo p2, PlayerInfo p3, PlayerInfo p4 )
{
	MessageConstructor m;
	m << Message::lookAt << table << p1 << p2 << p3 << p4;
	write( m );
}

void ServerConnection::auth( QString type )
{
	MessageConstructor m;
	write( m << Message::auth << type );
}

void ServerConnection::get( Message m )
{
	LOG_PLACE() << "Got message: " << m << '\n';
	switch ( m.type() ) {
		case Message::createTable:
			emit createTable( this, m.arg<QString>( 0 ) );
			return;
		case Message::joinTable:
			emit joinTable( this, m.arg<QString>( 0 ) );
			return;
		case Message::hello:
			emit hello( this, m.arg<QString>( 0 ) );
			return;
		case Message::leaveTable:
			emit leaveTable(this);
			return;
		case Message::changeProtocol:
			emit protocolChanged();
			return;
	}
	LOG_PLACE() << "Unknown message: " << m << '\n';
}

} // namespace Network

#include "connection.moc"


