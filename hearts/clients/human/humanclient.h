#ifndef DB_HUMANCLIENT_H_INCLUDE_GUARD_
#define DB_HUMANCLIENT_H_INCLUDE_GUARD_

#include <kmainwindow.h>

#include "communication/connection.h"
#include "humaninterface.h"
#include "qtconnection.h"
#include "pointsbox.h"
#include "hearts/card.h"

#include <vector>

class SetupWindow;

class HumanClient : public KMainWindow {
		Q_OBJECT
	public:
		HumanClient();

	private slots:
			void namequery();
			void connectionError(QString);
			void status(player_status::type);
			void inform(player_id::type,Card);
			void points(unsigned,unsigned,unsigned,unsigned);
			void invalidMove(QString);
			void terminate(QString);

			void clearTable();
			void updateNames();
			void connected_to_server(int);

			void showSetup();

	private:
			SetupWindow* setup_;
			PointsBox* pointsWindow;
			HumanInterface* interface;
			QtConnection* connection;
			player_id::type winner;
};


#endif /* DB_HUMANCLIENT_H_INCLUDE_GUARD_ */
