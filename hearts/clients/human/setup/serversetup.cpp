#include "serversetup.h"
#include "exec.h"
#include "serversetupwidget.h"
#include "general/helper.h"
#include "communication/constants.h"
#include "communication/open_connections.h"

#include "../options.h"

#include <qpushbutton.h>
#include <qcombobox.h>
#include <qlabel.h>
#include <qlineedit.h>

#include <klocale.h>
#include <kprocess.h>
#include <kmessagebox.h>
#include <kapplication.h>

#include <errno.h>
#include <string.h>

// For hostname discovery
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

ServerSetup::ServerSetup( QWidget* parent, const char* name ) :
		QWidget( parent, name )
{
	widget_ = new ServerSetupWidget( this, "server-setup-widget" );

	widget_->selfName->setText( Options::playerName( player_id::self ) );

	connect( widget_->options1, SIGNAL( clicked() ), SLOT( optionsRight() ) );
	connect( widget_->options2, SIGNAL( clicked() ), SLOT( optionsFront() ) );
	connect( widget_->options3, SIGNAL( clicked() ), SLOT( optionsLeft() ) );


	const char* error = 0;

	char buffer[ 128 ];
	if ( !gethostname( buffer, sizeof( buffer ) ) ) {
	       if ( struct hostent* host = gethostbyname( buffer ) ) {
			widget_->message->setText( 
				i18n( "<qt>You hostname (and IP address) seem to be <nobr><strong>%1 (%2)</strong></nobr></qt>" )
					.arg( host->h_name )
					.arg( inet_ntoa( *reinterpret_cast<struct in_addr *>( host->h_addr ) ) ) );
	       } else {
		       error = hstrerror( h_errno );
	       }
	} else {
		error = strerror( errno );
	}
	if ( error ) {
		widget_->message->setText( i18n( "<qt>Error guessing host address:<nobr><strong>%1</strong></nobr></qt>" )
			.arg( error ) );
	}
}



void ServerSetup::execute()
{
	enum { client, server };
	int pipe[ 2 ];
	if ( socketpair( AF_LOCAL, SOCK_STREAM, PF_LOCAL, pipe ) < 0 ) {
			KMessageBox::error( 0, i18n( "<qt>Error: [socketpair failed]</qt>" ) );
			return;
	}
	int fds[ 4 ];
	fds[ 0 ] = pipe[ 0 ];
	fds[ 1 ] = execute( player_id::right, widget_->type1 );
	fds[ 2 ] = execute( player_id::front, widget_->type2 );
	fds[ 3 ] = execute( player_id::left, widget_->type3 );

	int stat = fork();
	if ( stat < 0 ) {
			KMessageBox::error( 0, i18n( "<qt>Error: [fork failed]</qt>" ) );
			return;
	} else if ( stat > 0 ) {
			::close( pipe[ 0 ] );
			char c = 0;
			if ( write( pipe[ 1 ], &c, 1 ) < 0 ) {
					KMessageBox::error( 0, i18n( "<qt>Error establishing connection:<nobr><strong>%1</strong></nobr></qt>" )
									.arg( strerror( errno ) ) );
			}
			Options::savePlayerName( player_id::self, widget_->selfName->text() );
			emit connected( pipe[ 1 ] );
			return;
	} else {
			::close( pipe[ 1 ] );
			if ( fds[ 1 ] < 0 || 
							fds[ 2 ] < 0 ||
							fds[ 3 ] < 0 ) {
					::close( pipe[ server ] );
					exit( 1 );
			}
			execute::server( fds );
			exit( 1 );
	}
}

void ServerSetup::optionsSelf() {
}

void ServerSetup::optionsRight() {
	options( player_id::right, widget_->type1 );
}

void ServerSetup::optionsFront() {
	options( player_id::front, widget_->type2 );
}

void ServerSetup::optionsLeft() {
	options( player_id::left, widget_->type3 );
}

void ServerSetup::options( player_id::type, QComboBox* type )
{
	enum { comp, remote };
	if ( type->currentItem() == comp ) {
		KMessageBox::sorry( this, i18n( "Not yet implemented" ) );
		/*
		* ComputerPlayerOptions* opt = new ComputerPlayerOptions( player );
		* opt->show();
		* opt->exec();
		*/
	} else if ( type->currentItem() == remote ) {

		KMessageBox::sorry( this, i18n( "There are no options available for remote players" ) );

	}
}

int ServerSetup::execute( player_id::type player, QComboBox* type ) {
	enum { comp, remote };
	if ( type->currentItem() == comp ) {
		return execute::computerClient( QString( Options::playerName( player ) ) );
	}
	return 0; // remote player, do nothing
}



#include "serversetup.moc"

