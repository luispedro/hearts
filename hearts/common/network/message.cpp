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
}

MessageConstructor& MessageConstructor::operator << ( Message::typeEnum t )
{
		return static_cast<MessageConstructor&>( *this << toString( t ) );
}
Message::Message( const MessageConstructor& c )
		:type_( fromString( c.first() ) ),
		 pieces_( c.list() )
{
}

Message::Message( QString rep )
		:pieces_( QStringList::split( " ", rep ) )
{
		LOG_PLACE() << " Message::Message(" << rep.utf8() << ")" << std::endl;
		type_ = fromString( *pieces_.at( 0 ) );
}

QString Message::asString() const
{
		return pieces_.join( QString::fromLatin1( " " ) );
}

unsigned Message::numArgs() const 
{
	return pieces_.size();
}

