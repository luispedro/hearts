#include "remotesetup.h"
#include "exec.h"
#include "remotesetupwidget.h"
#include "communication/open_connections.h"

#include "../options.h"

#include <klocale.h>
#include <kprocess.h>
#include <kapp.h>

#include <qlineedit.h>


RemoteSetup::RemoteSetup( QWidget* p, const char* n )
	: QWidget( p, n ),
	widget_( new RemoteSetupWidget( this, "remote-setup-widget" ) )
{
}

void RemoteSetup::execute()
{
	int fd = open_client_connection( widget_->address->text() );

	KConfig* c = KGlobal::config();
	KConfigGroupSaver s( c, QString::fromLatin1( "remote-setup" ) );
	c->writeEntry( "ip-address", widget_->address->text() );

	Options::savePlayerName( player_id::self, widget_->selfName->text() );

	emit connected( fd );
}

#include "remotesetup.moc"

