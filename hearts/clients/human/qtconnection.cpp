#include "qtconnection.h"
#include "communication/factory.h"
#include "general/helper.h"
#include <ksock.h>
#include <unistd.h>


QtConnection::QtConnection( QObject* p, const char* n )
		: QObject( p, n ),
		connection( 0 ),
		watcher( 0 ),
		enabled( true )
{}

QtConnection::~QtConnection()
{
	LOG_PLACE_NL();
	delete connection;
	delete watcher;
}

void QtConnection::set_fd( int fd )
{
	delete connection;
	connection = new FDConnection( fd );
	delete watcher;
	watcher = new KSocket( connection->fd() );
	connection->register_pollfd( pfd );
	update_watcher();
	connect( watcher, SIGNAL( readEvent( KSocket* ) ), SLOT( read( KSocket* ) ) );
	connect( watcher, SIGNAL( writeEvent( KSocket* ) ), SLOT( write( KSocket* ) ) );
}

void QtConnection::close()
{
	LOG_PLACE_NL();
	enabled = false;
	if ( connection ) {
		::close( connection->fd() );
		delete connection;
		connection = 0;
	}
	if ( watcher ) {
		delete watcher;
		watcher = 0;
	}
}


void QtConnection::update_watcher()
{
	watcher->enableRead( pfd.events & POLLIN );
	watcher->enableWrite( pfd.events & POLLOUT );
}

void QtConnection::socket_callback( KSocket* t, const int pollconstant )
{
	( void ) t; // no "unused variable" warnings in release builds
	assert( t == watcher );
	pfd.revents = pollconstant;
	connection->poll_success();
	update_watcher();
	handle_messages();
}

void QtConnection::read( KSocket* t )
{
	LOG_PLACE() << " reading.\n";
	this->socket_callback( t, POLLIN );
}

void QtConnection::write( KSocket* t )
{
	LOG_PLACE_NL();
	this->socket_callback( t, POLLOUT );
}

void QtConnection::handle_messages()
{
	LOG_PLACE_NL();
	while ( enabled and connection->message_available() ) {
		Message m = connection->get_message();
		LOG_PLACE() << " message = " << m.type() << ".\n";
		this->handle( m );
	}
}

void QtConnection::opponentname_message( player_id::type who, std::string name )
{
	emit opponentname( who, QString::fromUtf8( name.c_str() ) );
}

void QtConnection::ignore_message( Message )
{
	//	emit error(QString::from_utf8(em));
}

void QtConnection::terminate_message( std::string em )
{
	LOG_PLACE_NL();
	emit terminate( QString::fromUtf8( em.c_str() ) );
}

void QtConnection::namequery_message()
{
	emit namequery();
}

void QtConnection::playquery_message()
{
	emit play();
}

void QtConnection::inform_message( player_id::type who, Card what )

{
	emit inform( who, what );
}

void QtConnection::invalidmove_message( std::string why )
{
	emit invalidmove( QString( why.c_str() ) );
}

void QtConnection::status_message( player_status::type s )
{
	LOG_PLACE_NL();
	emit status( s );

}

void QtConnection::receive_message( Card c )
{
	emit receive( c );
}

void QtConnection::give3query_message()
{
	emit give3();
}

void QtConnection::points_message( unsigned a, unsigned b, unsigned c, unsigned d )
{
	emit points( a, b, c, d );
}

void QtConnection::play( Card c )
{
	LOG_PLACE_NL();
	connection->write( Factory::Client::playreply( c ) );
	update_watcher();
}

void QtConnection::give3( const Holder3& h )
{
	connection->write( Factory::Client::give3reply( h ) );
	update_watcher();
}
void QtConnection::name( QString n )
{
	connection->write( Factory::Client::namereply( std::string( n.utf8() ) ) );
	update_watcher();
}


void QtConnection::disable()
{
	enabled = false;
	if ( watcher ) {
		watcher->enableRead( false );
		watcher->enableWrite( false );
	}
}

void QtConnection::enable()
{
	LOG_PLACE() << "\nconnection = " << connection << ", watcher = " << watcher << std::endl;
	enabled = true;
	if ( watcher )
		update_watcher();
	if ( connection ) {
		LOG_PLACE_NL();
		handle_messages();
	}
}

#include "qtconnection.moc"
