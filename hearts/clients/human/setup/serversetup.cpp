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
#include <klocale.h>
#include <kprocess.h>
#include <kmessagebox.h>
#include <kapp.h>

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
	execute_server();
	sleep( 1 ); // FIXME: hack
	execute( player_id::right, widget_->type1 );
	execute( player_id::front, widget_->type2 );
	execute( player_id::left, widget_->type3 );
	int fd = open_client_connection( generateLocalAddress().local8Bit() );
	if ( fd < 0 ) {
		KMessageBox::error( 0, i18n( "<qt>Error establishing connection: <nobr><strong>%1</strong></nobr></qt>" )
				.arg( strerror( errno ) ) );
	}
	char c = 0;
	if ( write( fd, &c, 1 ) < 0 ) {
		KMessageBox::error( 0, i18n( "<qt>Error establishing connection:<nobr><strong>%1</strong></nobr></qt>" )
				.arg( strerror( errno ) ) );
	}
	emit connected( fd );
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

void ServerSetup::execute( player_id::type player, QComboBox* type ) {
	enum { comp, remote };
	if ( type->currentItem() == comp ) {
		execute_computer_client( QString( Options::playerName( player ) ) );
	} else {
		; // remote player, do nothing
	}
}



#include "serversetup.moc"

