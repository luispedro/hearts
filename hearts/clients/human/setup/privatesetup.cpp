#include "privatesetup.h"
#include "remotesetup.h"
#include "serversetup.h"
#include "general/helper.h"

#include <klocale.h>
#include <kdebug.h>

PrivateSetup::PrivateSetup( SetupWindow* parent, const char* name )
	:SmartPage( parent, name ),
	remote_( 0 ),
	server_( 0 )
{
	widget_ = new ClientOrServerWidget( this );
}


void PrivateSetup::init( SetupWindow* parent )
{
	if ( remote_ ) return;

	remote_ = new RemoteSetup( parent );
	parent->addPage( remote_, i18n( "Connection Options" ) );
	parent->setFinishEnabled( remote_, true );
	parent->setNextEnabled( remote_, false );
	parent->setAppropriate( remote_, false );

	server_ = new ServerSetup( parent );
	parent->addPage( server_, i18n( "Dealer Options" ) );
	parent->setFinishEnabled( server_, true );
	parent->setNextEnabled( server_, false );
	parent->setAppropriate( server_, false );
}

void PrivateSetup::execute() {
}


void PrivateSetup::doNext( SetupWindow* parent ) {
	if ( widget_->isServer() ) {
		parent->setAppropriate( server_, true );
		parent->setAppropriate( remote_, false );
		parent->setNextEnabled( server_, false );
		parent->setFinishEnabled( server_, true );
	} else {
		parent->setAppropriate( server_, false );
		parent->setAppropriate( remote_, true );
		parent->setNextEnabled( remote_, false );
	}
}

