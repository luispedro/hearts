/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you want to add, delete, or rename functions or slots, use
** Qt Designer to update this file, preserving your code.
**
** You should not define a constructor or destructor in this file.
** Instead, write your code in functions called init() and destroy().
** These will automatically be called by the form's constructor and
** destructor.
*****************************************************************************/



#include "exec.h"
#include "options.h"
#include "hearts/player_id.h"
#include "communication/open_connections.h"

#include <kmessagebox.h>
#include <kconfig.h>

#include <string.h> // strerror
#include <errno.h>  // errno
#include <unistd.h>
#include <sys/socket.h>

void PrivateGameDialog::next()
{
    if (currentPage() == initialChoice) {
	bool isServer = radioServer->isChecked();
	setAppropriate(page(1), !isServer);
	setAppropriate(page(2), isServer);
	setFinishEnabled(page(1), true);
	setFinishEnabled(page(2), true);
    }
    QWizard::next();
}


void PrivateGameDialog::accept()
{
    if (currentPage() == dealCards) {
	enum { client, server };
	enum { computerplayer, remoteplayer };
	int pipe[ 2 ];
	if ( socketpair( AF_LOCAL, SOCK_STREAM, PF_LOCAL, pipe ) < 0 ) {
		KMessageBox::error( 0, i18n( "<qt>Error: [socketpair failed]</qt>" ) );
	}
	unix::coe( pipe[ server ] );
	unix::coe( pipe[ client ] );

	int fds[ 4 ] = { 0, 0, 0, 0 };
	fds[ 0 ] = pipe[ server ];
	if ( type1->currentItem() == computerplayer ) fds[ 1 ] = execute::computerClient( Options::playerName( player_id::right ) );
	if ( type2->currentItem() == computerplayer ) fds[ 2 ] = execute::computerClient( Options::playerName( player_id::front ) );
	if ( type3->currentItem() == computerplayer ) fds[ 3 ] = execute::computerClient( Options::playerName( player_id::left ) );

	int stat = fork();
	if ( stat < 0 ) {
		KMessageBox::error( 0, i18n( "<qt>Error: [fork failed]</qt>" ) );
	} else if ( stat > 0 ) {
		for ( int i = 0; i != 4; ++i ) ::close( fds[ i ] );
		char c = 0;
		if ( ::write( pipe[ client ], &c, 1 ) < 0 ) {
			KMessageBox::error( 0, i18n( "<qt>Error establishing connection:<nobr><strong>%1</strong></nobr></qt>" )
							.arg( strerror( errno ) ) );
		}
		Options::savePlayerName( player_id::self, selfName->text() );
		emit connected_to( pipe[ client ] );
	} else {
		::close( pipe[ client ] );
		if ( fds[ 1 ] < 0 || 
			fds[ 2 ] < 0 ||
			fds[ 3 ] < 0 ) {
			::close( pipe[ server ] );
			exit( 1 );
		}
		execute::server( fds );
		exit( 1 );
	}

    } else {
	int fd = open_client_connection( address->text() );

	KConfig* c = KGlobal::config();
	KConfigGroupSaver s( c, QString::fromLatin1( "remote-setup" ) );
	c->writeEntry( "ip-address", address->text() );

	Options::savePlayerName( player_id::self, selfName->text() );

	char t = 0;
	if ( fd < 0 || ::write( fd, &t, 1 ) < 0 ) {
		KMessageBox::error( 0, i18n( "<qt>Error opening connection:<nobr><strong>%1</strong></nobr></qt>" )
				.arg( strerror( errno ) ) );
	}
	emit connected_to( fd );
    }
    QWizard::accept();
}
