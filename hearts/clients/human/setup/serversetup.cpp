#include "serversetup.h"
#include "exec.h"
#include "serversetupwidget.h"
#include "general/helper.h"
#include "communication/constants.h"
#include "communication/open_connections.h"

#include "../options.h"

#include <qpushbutton.h>
#include <qcombobox.h>
#include <klocale.h>
#include <kprocess.h>
#include <kmessagebox.h>
#include <kapp.h>

#include <errno.h>
#include <string.h>

ServerSetup::ServerSetup( QWidget* parent, const char* name ) :
		QWidget( parent, name )
{
	widget_ = new ServerSetupWidget( this, "server-setup-widget" );

}

void ServerSetup::execute()
{
	execute_server();
	sleep( 1 ); // FIXME: hack

	execute( player_id::right, widget_->type1 );
	execute( player_id::front, widget_->type2 );
	execute( player_id::left, widget_->type3 );
	int fd = open_client_connection( local_address );
	if ( fd < 0 ) {
		KMessageBox::error( 0, i18n( "An error occurred:\n%1" ).arg( strerror( errno ) ) );
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

