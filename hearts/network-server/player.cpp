#include "player.h"
#include "table.h"
#include "network/connection.h"
#include "surevalidator.h"
#include <general/helper.h>

Player::Player(QObject* parent, KExtendedSocket* socket )
		:ServerConnection( socket, parent ),
		 table_( 0 ),
		 validator_( new SureValidator )
{
		LOG_PLACE_NL();
}

Player::~Player()
{
	delete validator_;
}

void Player::get( Message m )
{
	switch ( m.type() )
	{
		case Message::joinTable:
			emit joinTable( m.table() );
			break;
		case Message::leaveTable:
			emit quitTable( m.table() );
			break;
		case Message::hello:
			name_ = m.arg<QString>( 0 );
			if ( !validator_->validate( name_, m.arg<QString>( 1 ) ) ) {
				// TODO sendError( "Invalid password/username" );
				delete this;
			}
			break;
		case Message::createTable:
			emit createTable( m.table() );
			break;
		default:
			LOG_PLACE() << " Unrecognised message = " << m << std::endl;
	}
}

void Player::connectTo( const char* server, short port )
{
	MessageConstructor m;
	m << Message::connectTo << server << port;
	write( m );
}

void Player::startGame( short port )
{
	MessageConstructor m;
	m << Message::startGame << port;
	write( m );
}

void Player::lookAt( Table* table )
{
	MessageConstructor m;
	m << Message::tableInfo << table->name();
	for ( int i = 0; i != 4; ++i )
	{
		if ( table->player( i ) ) m << table->player( i )->name();
		else m << QString::fromLatin1( "[null]" );
	}
	write( m );
}

#include "player.moc"

