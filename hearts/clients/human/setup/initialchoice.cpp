#include "initialchoice.h"
#include "localsetup.h"
#include "networksetup.h"
#include "privatesetup.h"

#include "setupwindow.h"
#include "general/helper.h"
#include "initialchoicewidget.h"

#include <cassert>

#include <qradiobutton.h>
#include <klocale.h>

InitialChoice::InitialChoice( SetupWindow* parent, const char* name )
		: SmartPage( parent, name )
{
	LOG_PLACE_NL();
	widget_ = new InitialChoiceWidget( this );

#define MAKE( memvar, Class, name )               \
	memvar = new Class( parent );       \
	parent->addPage( memvar, i18n( name ) ); \
	parent->setBackEnabled( memvar, true ); \
	parent->setAppropriate( memvar, false );

	MAKE( localsetup_, LocalSetup, "Configure Players" );
	parent->setFinishEnabled( localsetup_, true );
	parent->setNextEnabled( localsetup_, false );

	MAKE( networksetup_, NetworkSetup, "Choose a table" );
	parent->setFinishEnabled( networksetup_, false );
	parent->setNextEnabled( networksetup_, false );
	connect( networksetup_, SIGNAL( connected( int ) ), parent, SLOT( connected( int ) ) );

	MAKE( privatesetup_, PrivateSetup, "Deal or join" );
	parent->setFinishEnabled( privatesetup_, false );

	
	widget_->radioNetwork->setEnabled( networksetup_->good() );

	LOG_PLACE_NL();
	widget_->adjustSize();
	widget_->move( 0, 0 );
	widget_->show();
}


void InitialChoice::doNext( SetupWindow* parent )
{
	assert( parent );
	switch ( widget_->option() ) {
		case 0 :      // InitialChoice::AgainstComputer:
		{
#define PUT_REMOVE( goingIn, goingOut0, goingOut1 )                                             \
				parent->setAppropriate( goingOut0, false );		\
				parent->setAppropriate( goingOut1, false );     \
				parent->setAppropriate( goingIn, true );

			PUT_REMOVE( localsetup_,  networksetup_, privatesetup_ );
			parent->setNextEnabled( localsetup_, false );
			break;
		}
		case 1:      // InitialChoice::Public:
		{
			PUT_REMOVE( networksetup_, localsetup_, privatesetup_ );
			parent->setNextEnabled( networksetup_, false );
			break;
		}
		case 2:      // InitialChoice::Private:
		{
			PUT_REMOVE( privatesetup_, localsetup_, networksetup_ );
			parent->setNextEnabled( privatesetup_, true );
			return ;
		}
		default:
		massert( 0 );
	}
}

#include "initialchoice.moc"

