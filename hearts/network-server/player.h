#ifndef PLAYER_H
#define PLAYER_H
#include <qobject.h>
#include <kextsock.h>

#include "network/tableid.h"
#include "network/playerid.h"
#include "network/connection.h"

class Table;
class Connection;
class Player : public Network::ServerConnection
{
	Q_OBJECT
	public:
		typedef player_id id;
		Player(QObject* parent, KExtendedSocket* );

//X 		KExtendedSocket* socket() { return &socket_; }
		
		QString name() const { return name_; }

		void table( Table* t ) { table_ = t; }
		Table* table() { return table_; }

	public slots:
		void get( Message );

//X 		void write( Message );

		void connectTo( const char* server, short port );
		void startGame( short port ); // FIXME HARD: We shouldn't tell people what port to use
		// they should tell us!

		void lookAt( Table* );
	signals:
		void joinTable( QString );
		void quitTable( table_id );
		void createTable( QString );

	private:
		QString name_;
		Table* table_;
};
#endif // PLAYER_H
