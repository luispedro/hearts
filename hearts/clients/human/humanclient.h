#ifndef DB_HUMANCLIENT_H_INCLUDE_GUARD_
#define DB_HUMANCLIENT_H_INCLUDE_GUARD_

#include <kmainwindow.h>

#include "communication/connection.h"
#include "humaninterface.h"
#include "qtconnection.h"
#include "pointsbox.h"
#include "hearts/card.h"

class SetupWindow;

class HumanClient : public KMainWindow
{
		Q_OBJECT
	public:
		HumanClient();

	private slots:
		void namequery();
		void connectionError( QString );
		void status( player_status::type );
		void giveStatus( player_id::type );
		void playStatus();
		void inform( player_id::type, Card );
		void points( unsigned, unsigned, unsigned, unsigned );
		void invalidMove( QString );
		void terminate( QString );

		void clearTable();
		void connected_to_server( int );

		void newGame();
		void privateGame();
		void heartsNetwork();

	private:
		SetupWindow* setup_;
		PointsBox* pointsWindow;
		HumanInterface* interface;
		QtConnection* connection;
		player_id::type winner;
};


#endif /* DB_HUMANCLIENT_H_INCLUDE_GUARD_ */
