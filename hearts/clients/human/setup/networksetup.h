#ifndef NETWORKSETUP_H
#define NETWORKSETUP_H

#include <qwidget.h>
#include <kprogress.h>
#include "network/connection.h"
#include "setupwindow.h"

class NetworkSetupWidget;
class OnlinePlayersDialog;

using Network::PlayerInfo;

class NetworkSetup : public QWidget
{
		Q_OBJECT
	public:
		NetworkSetup( QWidget* p, const char* name = "network-setup" );
		~NetworkSetup();

		bool good() const
		{
			return good_;
		}
	signals:
		void connected( int );
	public slots:
		void newTable();
		//X 		void joinTable();

	private slots:
		void reconnect();
		void lookAt( QString, PlayerInfo, PlayerInfo, PlayerInfo, PlayerInfo );
		void startGame( short );
		void connectTo( const char*, short );
		void delayedConnectTo();
		void protocolChanged();
		void delayedProtocolChanged();
		void playerStatus( QString, player_status::type );

		void error( Message::errorType, const QString& msg );
		
		void doAuthentication( const QCString& method, const QCString& cookie );
	private:

		bool openConnection( const char* host, short port );
		void resetGUI( const char* );

		NetworkSetupWidget* widget_;
		OnlinePlayersDialog* online_;
		Network::UserConnection* connection_;
		KProgressDialog* connecting_;
		QString delayedIp;
		short delayedPort;
		bool good_;
		bool force_;
};

#endif // NETWORKSETUP_H

