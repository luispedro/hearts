#ifndef DB_QTCLIENT_H_INCLUDE_GUARD_
#define DB_QTCLIENT_H_INCLUDE_GUARD_

#include "humanclientoptions.h"

#include "communication/typicalclient.h"
#include "communication/fdconnection.h"

#include <qobject.h>
#include <klocale.h>

#include <sys/poll.h> // pollfd

#include <string> // std::string
#include <cassert>
#include <memory>

class KSocket;

/** Translates between the libhearts framework and Qt's framework.
 * This is a very simple class which makes incoming messages into emited signals and takes
 *  messages via slots to turn them into outgoing messages.
 */

class QtConnection : public QObject, private TypicalClient
{
		Q_OBJECT
	public:

		QtConnection( QObject* parent = 0, const char* name = 0 );
		~QtConnection();

	public slots:

		void set_fd( int fd );
		void close();

		void disable();
		void enable();


		void play( Card );
		void give3( const Holder3& );
		void name( QString );

	signals:
		void opponentname( player_id::type, QString );
		void status( player_status::type );
		void play();
		void give3();
		void receive( Card );
		void namequery();
		void error( QString );
		void points( unsigned, unsigned, unsigned, unsigned );
		void inform( player_id::type, Card );
		void invalidmove( QString );
		void terminate( QString );

	private:
		void socket_callback( KSocket*, int );
		void update_watcher();
		void handle_messages();
	private slots:
		void read( KSocket* );
		void write( KSocket* );

	private:
		virtual void server_message( std::string )
		{
			emit error( i18n( "You got a server message!\n"
							  "Maybe there is a mistake in setup.\n\n" ) );
		}


		virtual void opponentname_message( player_id::type, std::string );
		virtual void ignore_message( Message );

		virtual void terminate_message( std::string );

		virtual void namequery_message();

		virtual void playquery_message();
		virtual void inform_message( player_id::type, Card );
		virtual void invalidmove_message( std::string reason );
		virtual void status_message( player_status::type );
		virtual void receive_message( Card );
		virtual void give3query_message();
		virtual void points_message( unsigned, unsigned, unsigned, unsigned );
		virtual void invalidMessage_message( Message )
		{
			assert( 0 );
		}

		// Error handlers:

		/** Error in decoding the message: */
		virtual void messageNotUnderstood( Message )
		{
			assert( 0 );
		}
		/** Error in handling the message */
		virtual void bad_message( Message )
		{
			assert( 0 );
		}

	private:
		FDConnection* connection;
		pollfd pfd;
		KSocket* watcher;
		bool enabled;
};




#endif /* DB_QTCLIENT_H_INCLUDE_GUARD_ */
