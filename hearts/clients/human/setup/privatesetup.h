#ifndef DB_PRIVATESETUP_H1080679200_INCLUDE_GUARD_
#define DB_PRIVATESETUP_H1080679200_INCLUDE_GUARD_

#include <qwidget.h>

#include "clientorserverwidget.h"
#include "setupwindow.h"
#include "smartpage.h"

class RemoteSetup;
class ServerSetup;

class PrivateSetup : public SmartPage
{
		Q_OBJECT
	public:
		PrivateSetup( SetupWindow* parent, const char* name = "private-cos-setup" );
	
		void doNext( SetupWindow* );
		void init( SetupWindow* );
	public slots:
		void execute();

	private:
		ClientOrServerWidget* widget_;

		RemoteSetup* remote_;
		ServerSetup* server_;
};





#endif /* DB_PRIVATESETUP_H1080679200_INCLUDE_GUARD_ */
