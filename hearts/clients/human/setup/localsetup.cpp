#include "localsetup.h"
#include "exec.h"

#include "general/widget_placement.h"
#include "general/setup.h"
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
#include <kapp.h>
#include <qtimer.h>
#include <kprocess.h>
#include <kmessagebox.h>

#include <sys/socket.h>
#include <unistd.h>

#include <algorithm>

LocalSetup::LocalSetup(QWidget* parent, const char* name)
	:QWidget(parent,name),
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
{ // FIXME: add error handling
		// FIXME: the whole thing with execute2 is really "hacky"
	LOG_PLACE();
	execute_server(false,true);
	QTimer::singleShot(1500,this,SLOT(execute2()));
}

void LocalSetup::execute2()
{
	LOG_PLACE();
	execute_computer_client( widget_->rightName() );
	execute_computer_client( widget_->leftName() );
	execute_computer_client( widget_->frontName() );
	int fd = open_client_connection(generateLocalAddress().local8Bit()); 
	
	if ( fd < 0 ) {
		KMessageBox::error( this, "Unable to connect to server!" );
		return;
	}

#define SAVE(x)  Options::savePlayerName( player_id::x,widget_->x##Name() ) 
	SAVE(self);
	SAVE(right);
	SAVE(front);
	SAVE(left);

	// must be done last
	emit connected(fd);
}


#include "localsetup.moc"

