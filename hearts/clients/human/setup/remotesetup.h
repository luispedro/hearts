#ifndef DB_REMOTESETUP_H_INCLUDE_GUARD_
#define DB_REMOTESETUP_H_INCLUDE_GUARD_

#include <qwidget.h>

#include "setupwindow.h"

class RemoteSetupWidget;
class RemoteSetup : public QWidget, public Connector
{
		Q_OBJECT
	public:
		RemoteSetup( QWidget* parent, const char* name = "remote-setup" );

		int connect();
	private:
		RemoteSetupWidget* widget_;
};



#endif /* DB_REMOTESETUP_H_INCLUDE_GUARD_ */
