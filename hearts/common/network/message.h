#ifndef MESSAGE_H
#define MESSAGE_H
#include <qstring.h>
#include <qstringlist.h>
#include <iostream>

#include "tableid.h"
#include "player_status.h"

class MessageConstructor;

// Messages (this isn't very clean, but this is very simple):
// The file Protocol.html as a bit more information
// startGame port  // FIXME
// connectTo server port
// joinTable table
// createTable name
// leaveTable name
// hello name
// changeProtocol

class Message
{
	public:
		Message()
		{ }
		Message( const MessageConstructor& );
		Message( QString );

#define HANDLE_ALL_MESSAGE_TYPES \
					HANDLE( startGame ) \
					HANDLE( connectTo ) \
					HANDLE( createTable ) \
					HANDLE( joinTable ) \
					HANDLE( leaveTable ) \
					HANDLE( hello ) \
					HANDLE( auth ) \
					HANDLE( lookAt ) \
					HANDLE( playerStatus ) \
					HANDLE( changeProtocol )
#define HANDLE( x ) x,

		enum typeEnum { HANDLE_ALL_MESSAGE_TYPES tableInfo = lookAt };
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
		MessageConstructor& operator<< ( player_status::type );
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

template <typename T>
inline const T Message::arg( size_t idx ) const
{
	QString rep = arg( idx );
	return to<T>( rep );
}





#endif // MESSAGE_H
