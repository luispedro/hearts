#include "initialchoice.h"
#include "localsetup.h"
#include "remotesetup.h"
#include "serversetup.h"
#include "networksetup.h"

#include "setupwindow.h"
#include "general/helper.h"
#include "general/widget_placement.h"
#include "initialchoicewidget.h"

#include <cassert>

#include <qradiobutton.h>
#include <klocale.h>

InitialChoice::InitialChoice( SetupWindow* parent, const char* name )
		: SmartPage( parent, name )
{
	LOG_PLACE_NL();
	widget_ = new InitialChoiceWidget( this );
	widget_->radioPrivate->setEnabled( false );

#define MAKE( memvar, Class )                                                         \
	memvar = new Class( parent );                                                 \
	memvar->hide();                                                               

	MAKE( localsetup_, LocalSetup );
	MAKE( networksetup_, NetworkSetup );

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
			LOG_PLACE() << "parent has " << parent->pageCount() << " pages.\n";

#define PUT_REMOVE( goingIn, nameIn, goingOut )                                             \
				assert( goingOut );                                 \
				assert( goingIn );                                  \
				disconnect( parent, SIGNAL( execute() ), goingOut, SLOT( execute() ) );            \
				disconnect( goingOut, SIGNAL( connected( int ) ),parent,SLOT( connected( int ) ) ); \
				connect( parent, SIGNAL( execute() ), goingIn, SLOT( execute() ) );            \
				connect( goingIn, SIGNAL( connected( int ) ),parent,SLOT( connected( int ) ) ); \
				parent->removePage( goingOut );                     \
				parent->addPage( goingIn, nameIn );                \
				parent->setFinishEnabled( goingIn, true );          \
				parent->setBackEnabled( goingIn, true );            \
				parent->setNextEnabled( goingIn, false );           \
				parent->showPage( goingIn );                        \
				return;

			PUT_REMOVE( localsetup_, i18n( "Configure players" ), networksetup_ );
		}
		case 1:      // InitialChoice::Public:
		{
			PUT_REMOVE( networksetup_, i18n( "Choose a table" ), localsetup_ );
		}
		case 2:      // InitialChoice::Private:
		{
			// TODO
			LOG_PLACE() << "TODO\n\n\nTODO\n\n\n\n";
			return ;
		}
		default:
		massert( 0 );
	}
}

#include "initialchoice.moc"

