#include "player.h"
#include "table.h"
#include "network/connection.h"
#include "network/authentication.h"
#include <general/helper.h>

#include "database.h"
#include "validator.h"

Player::Player( QObject* parent, KExtendedSocket* socket )
		: ServerConnection( socket, parent ),
		table_( 0 ),
		validator_( new AuthenticationValidator<repeatedMD5Authenticator, VeryStupidDatabase> )
{
	LOG_PLACE_NL();
}

Player::~Player()
{
	delete validator_;
}

void Player::get( Message m )
{
	switch ( m.type() ) {
		case Message::joinTable:
			emit joinTable( this, m.table() );
			break;
		case Message::leaveTable:
			emit quitTable( this, m.table() );
			break;
		case Message::hello:
			name_ = m.arg<QString>( 0 );
			cookie_ = validator_->cookie();
			auth( validator_->id(), cookie_ );
		break;
			case Message::auth:
			if ( !validator_->validate( name_, cookie_, m.arg<QCString>( 1 ) ) ) {
				// TODO sendError( "Invalid password/username" );
				delete this;
			}
			break;
		case Message::createTable:
			emit createTable( this, m.table() );
			break;
		default:
			//ServerConnection::get( m );
			LOG_PLACE() << " Unrecognised message = " << m << std::endl;
	}
}

void Player::playerStatus( QString p, player_status::type s )
{
	MessageConstructor m;
	m << Message::playerStatus << p << s;
	write( m );
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
	for ( int i = 0; i != 4; ++i ) {
		if ( table->player( i ) )
			m << table->player( i ) ->name();
		else
			m << QString::fromLatin1( "[null]" );
	}
	write( m );
}

#include "player.moc"

