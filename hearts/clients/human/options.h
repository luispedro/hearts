#include <qstring.h>

#include "hearts/player_id.h"

namespace Options
{
QString playerName( player_id::type who );
void savePlayerName( player_id::type, const QString& );

class Account {
	public:
		explicit Account( const char* );
		QString login() const;
		void saveLogin( const QString& );

		QCString password() const;
		void savePassword( const QCString& );

		QString host() const;
		void saveHost( QString );

		short port() const;
		//void savePort( short );
};

Account& getNetwork();

}


