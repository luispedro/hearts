#include "remotesetup.h"
#include "exec.h"
#include "remotesetupwidget.h"
#include "communication/open_connections.h"

#include "../options.h"

#include <klocale.h>
#include <kprocess.h>
#include <kconfig.h>
#include <kmessagebox.h>
#include <kapplication.h>

#include <qlineedit.h>

#include <string.h> // strerror
#include <errno.h>  // errno


RemoteSetup::RemoteSetup( QWidget* p, const char* n )
	: QWidget( p, n ),
	widget_( new RemoteSetupWidget( this, "remote-setup-widget" ) )
{
	widget_->selfName->setText( Options::playerName( player_id::self ) );
	KConfig* c = KGlobal::config();
	KConfigGroupSaver s( c, QString::fromLatin1( "remote-setup" ) );

	widget_->address->setText( c->readEntry( "ip-address" ) );
}

void RemoteSetup::execute()
{
	int fd = open_client_connection( widget_->address->text() );

	KConfig* c = KGlobal::config();
	KConfigGroupSaver s( c, QString::fromLatin1( "remote-setup" ) );
	c->writeEntry( "ip-address", widget_->address->text() );

	Options::savePlayerName( player_id::self, widget_->selfName->text() );

	char t = 0;
	if ( fd < 0 || write( fd, &t, 1 ) < 0 ) {
		KMessageBox::error( 0, i18n( "<qt>Error opening connection:<nobr><strong>%1</strong></nobr></qt>" )
				.arg( strerror( errno ) ) );
	} else {
		emit connected( fd );
	}
}

#include "remotesetup.moc"

