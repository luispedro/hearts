#ifndef NETWORKSETUP_H
#define NETWORKSETUP_H

#include <qwidget.h>
#include "network/connection.h"

class NetworkSetupWidget;

using Network::PlayerInfo;

class NetworkSetup : public QWidget {
		Q_OBJECT
	public:
		NetworkSetup(QWidget* p, const char* name = "network-setup");
		~NetworkSetup();

		bool good() const { return good_; }
	signals:
		void connected(int);
	public slots:
		void execute();
		void newTable();
//X 		void joinTable();

	private slots:
		void lookAt( QString, PlayerInfo, PlayerInfo, PlayerInfo, PlayerInfo );
		void startGame( short );
		void connectTo( const char*, short );
		void delayedConnectTo();
		void protocolChanged();
		void delayedProtocolChanged();
	private:
		NetworkSetupWidget* widget_;
		Network::UserConnection* connection_;
		QString delayedIp;
		short delayedPort;
		bool good_;
};



#endif // NETWORKSETUP_H
