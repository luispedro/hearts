#ifndef COMMON_NETWORK_MESSAGE_H_LPC_INCLUDE_GUARD_
#define COMMON_NETWORK_MESSAGE_H_LPC_INCLUDE_GUARD_
#include <qstring.h>
#include <qstringlist.h>
#include <iostream>
#include <cassert>

#include "tableid.h"
#include "user_status.h"

namespace Network {
class MessageConstructor;

// Messages (this isn't very clean, but this is very simple):
// The file Protocol.html as a bit more information
// hello name
// authQ method cookie
// authR cookie result
// authOK
// 
// connectTo server port
//
// TABLE MANAGEMENT:
//  USER
//     joinTable tname
//     createTable tname
//     leaveTable tname
//  SERVER
//     joinedTable tname
//     tableClose tname
//     addBot tname
//
// userStatus userName user_status
// motd message
//
// changeProtocol
// error errorType msg(english, user level)

class Message
{
	public:
		Message()
		{ }
		Message( const MessageConstructor& );
		Message( QString );

#define HANDLE_ALL_MESSAGE_TYPES \
					HANDLE( connectTo ) \
					HANDLE( createTable ) \
					HANDLE( joinTable ) \
					HANDLE( joinedTable ) \
					HANDLE( leaveTable ) \
					HANDLE( lookAt ) \
					HANDLE( tableClosed ) \
					HANDLE( hello ) \
					HANDLE( authQ ) \
					HANDLE( authR ) \
					HANDLE( authOK ) \
					HANDLE( addBot ) \
					HANDLE( userStatus ) \
					HANDLE( motd ) \
					HANDLE( changeProtocol ) \
					HANDLE( error )
#define HANDLE( x ) x,

		enum typeEnum { HANDLE_ALL_MESSAGE_TYPES tableInfo = lookAt };
#undef HANDLE

#define HANDLE_ALL_MESSAGE_ERRORS \
					HANDLE( notAuthenticated ) \
					HANDLE( authenticationFailed ) \
					HANDLE( inexistantTable ) 
#define HANDLE( x ) x,
		enum errorType { HANDLE_ALL_MESSAGE_ERRORS unknown };
#undef HANDLE

		typeEnum type() const
		{
			return type_;
		}
		table_id table() const
		{
			return this->arg( 0 );
		}

		QString arg( size_t idx ) const
		{
			return pieces_[ idx + 1 ];
		}
		QString asString() const;
		template <typename T>
		const T arg( unsigned ) const;
		unsigned numArgs() const;
	private:
		typeEnum type_;
		QStringList pieces_;
};

inline
std::ostream& operator <<( std::ostream& out, Message in )
{
	return out << in.asString().utf8();
}

Message::typeEnum fromString( QString );
QString toString( Message::typeEnum );

class MessageConstructor : private QStringList
{
	public:
		MessageConstructor& operator<< ( Message::typeEnum );
		MessageConstructor& operator<< ( QString );
		MessageConstructor& operator<< ( int number );
		MessageConstructor& operator<< ( user_status::type );
		MessageConstructor& operator<< ( Message::errorType );
		const QStringList list() const
		{
			return * this;
		}
		friend class Message;
};
inline
MessageConstructor& MessageConstructor::operator<<( QString r )
{
	if ( r.isNull() )
		static_cast<QStringList&>( *this ) << QString::fromLatin1( "[null]" );
	else
		static_cast<QStringList&>( *this ) << r;
	return *this;
}

inline
MessageConstructor& MessageConstructor::operator<<( int n )
{
	QString r = QString::number( n );
	return *this << r;
}

inline
MessageConstructor& MessageConstructor::operator<<( Message::errorType e )
{
	assert( ( *this )[ 0 ] == QString::fromLatin1( "error" ) );
#define HANDLE( x ) if ( e == Message::x ) return *this << #x;
	HANDLE_ALL_MESSAGE_ERRORS
#undef HANDLE
	assert( 0 );
	return *this;
}

template <typename T>
inline const T to( const QString& );

template <>
inline const QString to<QString>( const QString& r )
{
	return r;
}

template <>
inline const short to<short>( const QString& r )
{
	return r.toInt();
}

template <>
inline const char * const to<const char*>( const QString& r )
{
	return r.ascii();
}

template <>
inline const QCString to<QCString>( const QString& r )
{
	return r.utf8();
}

template <>
inline const user_status::type to<user_status::type>( const QString& r ) {
#define IFRET( x ) if ( r == QString::fromLatin1( #x ) ) return user_status::x;
		FOR_ALL_USER_STATUS( IFRET )
		return user_status::unknown;
#undef IFRET
}

template <>
inline const Message::errorType to<Message::errorType>( const QString& r ) {
#define HANDLE( x ) if ( r == QString::fromLatin1( #x ) ) return Message::x;
		HANDLE_ALL_MESSAGE_ERRORS
		return Message::unknown;
#undef HANDLE
}

template <typename T>
inline const T Message::arg( unsigned idx ) const
{
	QString rep = arg( idx );
	return to<T>( rep );
}



} // namespace Network 

#endif // COMMON_NETWORK_MESSAGE_H_LPC_INCLUDE_GUARD_
