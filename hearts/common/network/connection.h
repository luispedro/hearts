#ifndef CONNECTION_H
#define CONNECTION_H

#include "message.h"
#include <qobject.h>
#include <qstring.h>

class KExtendedSocket;

namespace Network
{

class Connection: public QObject
{
		Q_OBJECT
	public:
		Connection( KExtendedSocket* connection, QObject* parent, const char* name = "network-connection" );
		virtual ~Connection();

		KExtendedSocket* socket()
		{
			return socket_;
		}

	public slots:
		void write( Message );
		void read();
		void close();
		void changeProtocol();

	signals:
		void protocolChanged();
		void connectionError( const char*, int );
		void peerError( const char* );
		void received( Message );
		void eof();

	private:
		virtual void get( Message );
	private slots:

		virtual void socketClosed( int flags ); // connected to socket_::closed
	private:
		KExtendedSocket* socket_;
};

typedef QString PlayerInfo;

class UserConnection : public Connection
{
		Q_OBJECT
	public:
		UserConnection( KExtendedSocket* connection, QObject* parent, const char* name = "user-network-connection" );

	signals:
		void connectTo( const char*, short );
		void lookAt( QString, QString, QString, QString, QString );
		void userStatus( QString, user_status::type );
		void motd( const QString& );
		void authQ( const QCString&, const QCString& );
		void authOK();
		void error( Network::Message::errorType, const QString& );
		void tableClosed( const QString& );
		void joinedTable( QString );
	public slots:
		void addBot( QString );
		void hello( QString );
		void authR( QCString cookie, QCString result );
		void createTable( QString );
		void joinTable( QString );
		void leaveTable();
	private:
		void get( Message );
};

class ServerConnection : public Connection
{
		Q_OBJECT
	public:
		ServerConnection( KExtendedSocket* connection,
						  QObject* parent,
						  const char* name = "server-network-connection" );

		/**
		 * This is set automatically before calling hello( "" );
		 */
		QString userName();
		// Unlike the corresponding slots in the above class, this one includes <code>this</code>in its signals as the
		// intended usage will be to have several objects connecting to the same slot.
	signals:
		void hello( ServerConnection*, QString );
		void createTable( ServerConnection*, QString );
		void joinTable( ServerConnection*, QString );
		void leaveTable( ServerConnection* );
		void addBot( ServerConnection*, QString );
	public slots:
		void tableClosed( QString );
		void joinedTable( QString );
		void connectTo( const char*, short );
		void lookAt( QString, QString, QString, QString, QString );
		void authQ( QCString method, QCString cookie );
		void authOK();
		void motd( const QString& );

	private:
		void get( Message );
};

} // namespace Network

#endif // CONNECTION_H

