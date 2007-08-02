#ifndef HEARTS_CLIENTS_HUMAN_TUE_JUL_31_17_49_53_EDT_2007_INCLUDE_GUARD_
#define HEARTS_CLIENTS_HUMAN_TUE_JUL_31_17_49_53_EDT_2007_INCLUDE_GUARD_

#include "network/message.h"
#include "network/connection.h"

#include <qobject.h>

class NetworkDialog;
class NetworkManager : public QObject {
	Q_OBJECT
	NetworkManager(const NetworkManager&);
	NetworkManager& operator = (const NetworkManager&);
	public:
		NetworkManager( NetworkDialog* dialog, Network::UserConnection*, QObject* parent, const char* name = "network-manager" );
		~NetworkManager();

	signals:
		void connected_to(int);

	private slots:
		void userStatus( QString u, user_status::type tp);
		void error(Network::Message::errorType, const QString& );
		void doAuthentication( const QCString&, const QCString& );
		void protocolChanged();
	private:
		NetworkDialog* dialog_;
		Network::UserConnection* networkconnection_;
		bool forceauthentication_;
};

#endif // HEARTS_CLIENTS_HUMAN_TUE_JUL_31_17_49_53_EDT_2007_INCLUDE_GUARD_
