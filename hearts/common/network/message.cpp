#include "message.h"
#include <general/helper.h>

Message::typeEnum fromString( QString s )
{
#define HANDLE( t ) LOG_PLACE() << " - \'" << s.ascii() << "\' == " << #t << std::endl; if ( s == #t ) return Message::t;
	HANDLE_ALL_MESSAGE_TYPES;
#undef HANDLE
	// we should not get here
	return Message::typeEnum( -1 ); //FIXME
}

QString toString( Message::typeEnum t )
{
#define HANDLE( x ) if ( t == Message::x ) return #x;
	HANDLE_ALL_MESSAGE_TYPES;
	return "unknown_type"; //FIXME
#undef HANDLE
}

MessageConstructor& MessageConstructor::operator << ( Message::typeEnum t )
{
	return static_cast<MessageConstructor&>( *this << toString( t ) );
}

MessageConstructor& MessageConstructor::operator << ( player_status::type s ) 
{
	using namespace player_status;
#define HANDLE( c ) case c: return *this << #c;
	switch ( s ) {
		FOR_ALL_PLAYER_STATUS( HANDLE )
		default: return *this;
#undef HANDLE
	}
}


Message::Message( const MessageConstructor& c )
		: type_( fromString( c.first() ) ),
		pieces_( c.list() )
{}

Message::Message( QString rep )
		: pieces_( QStringList::split( QString::fromLatin1( " " ), rep ) )
{
	pieces_.gres( "\\_"," " );
	pieces_.gres( "\\\\","\\" );
	LOG_PLACE() << " Message::Message(" << rep.utf8() << ")" << std::endl;
	type_ = fromString( *pieces_.at( 0 ) );
}

QString Message::asString() const
{
	QStringList copy = pieces_;
	copy.gres( "\\","\\\\" );
	copy.gres( " ","\\_" );
	return copy.join( QString::fromLatin1( " " ) );
}

unsigned Message::numArgs() const
{
	return pieces_.size() - 1;
}

