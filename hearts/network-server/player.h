#ifndef PLAYER_H
#define PLAYER_H
#include <qobject.h>
#include <kextsock.h>

#include "network/tableid.h"
#include "network/playerid.h"
#include "network/connection.h"
#include "network/player_status.h"

class Table;
class Connection;
class Validator;
class Player : public Network::ServerConnection
{
		Q_OBJECT
	public:
		typedef player_id id;
		Player( QObject* parent, KExtendedSocket* );
		~Player();

		//X 		KExtendedSocket* socket() { return &socket_; }

		QString name() const
		{
			return name_;
		}

		void table( Table* t )
		{
			table_ = t;
		}
		Table* table()
		{
			return table_;
		}

	public slots:
		void get( Message );

		//X 		void write( Message );

		void playerStatus( QString name, player_status::type );
		void connectTo( const char* server, short port );
		void startGame( short port ); // FIXME HARD: We shouldn't tell people what port to use
		// they should tell us!

		void lookAt( Table* );
	signals:
		void joinTable( Player*, QString );
		void quitTable( Player*, table_id );
		void createTable( Player*, QString );

	private:
		QString name_;
		QCString cookie_;
		Table* table_;
		Validator* validator_;
};
#endif // PLAYER_H
