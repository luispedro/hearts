#include "localsetup.h"
#include "exec.h"

#include "general/widget_placement.h"
#include "hearts/player_id.h"
#include "general/helper.h"
#include "communication/constants.h"
#include "communication/open_connections.h"

#include "../options.h"

#include "localsetupwidget.h"

#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <klocale.h>
#include <kapplication.h>
#include <qtimer.h>
#include <kdebug.h>
#include <kprocess.h>
#include <kmessagebox.h>

#include <sys/socket.h>
#include <unistd.h>

#include <algorithm>

LocalSetup::LocalSetup( QWidget* parent, const char* name )
		: QWidget( parent, name ),
		widget_( new LocalSetupWidget( this, "localsetupwidget" ) )
{
#define SET_INIT( x ) setName( player_id::x, Options::playerName( player_id::x ) );
	HANDLE_ALL_PLAYER_IDS( SET_INIT );
}

void LocalSetup::setName( player_id::type who, QString name )
{
#define CASE( x ) if ( who == player_id::x ) widget_->x ## _ ->setText( name )

	HANDLE_ALL_PLAYER_IDS( CASE );
}

void LocalSetup::execute()
{
	enum { client, server };
	kdDebug() << "LocalSetup::execute()" << endl;
	int pipe[2];
	int stat;
	if ( socketpair( AF_LOCAL, SOCK_STREAM, PF_LOCAL, pipe ) < 0 ) {
			goto error;
	}

	stat = fork();
	if ( stat < 0 ) goto error;
	if ( stat > 0 ) {
#define SAVE(x)  Options::savePlayerName( player_id::x,widget_->x##Name() )
			SAVE( self );
			SAVE( right );
			SAVE( front );
			SAVE( left );
			char c = 0;
			::write( pipe[ client ], &c, 1);
			emit connected( pipe[ client ] );
	} else {
			int fds[ 4 ];
			fds[ 0 ] = pipe[ server ];
			fds[ 1 ] = execute::computerClient( widget_->rightName() );
			fds[ 2 ] = execute::computerClient( widget_->frontName() );
			fds[ 3 ] = execute::computerClient( widget_->leftName() );
			if ( fds[ 1 ] < 0 ||
							fds[ 2 ] < 0 ||
							fds[ 3 ] < 0 ) {
					::close( pipe[ server ] );
					exit( 1 );
			}
			execute::server( fds );
	}
error:
	LOG_PLACE_NL();
	// NOP
}

#include "localsetup.moc"

