#include "initialchoice.h"
#include "localsetup.h"
#include "remotesetup.h"
#include "serversetup.h"
#include "networksetup.h"

#include "setupwindow.h"
#include "general/helper.h"
#include "general/widget_placement.h"
#include "initialchoicewidget.h"


#include <qradiobutton.h>

	InitialChoice::InitialChoice(QWidget* parent, const char* name)
		:SmartPage( parent, name )
{
	LOG_PLACE_NL();
	widget_ = new InitialChoiceWidget( this );
	widget_->radioPrivate->setEnabled( false );
	LOG_PLACE_NL();
	widget_->adjustSize();
	widget_->move( 0,0 );
	widget_->show();
}
void InitialChoice::doNext( SetupWindow* parent ) 
{
	switch ( 0 )
	{
		case 0 : // InitialChoice::AgainstComputer:
			{
				LOG_PLACE_NL();
				LocalSetup* setup = new LocalSetup( parent );
				parent->addPage( setup, "FIXME" );
				parent->setFinishEnabled( setup, true );
				parent->showPage( setup );
				connect( parent, SIGNAL( execute() ), setup, SLOT( execute() ) );
				connect( setup, SIGNAL( connected( int ) ),parent,SLOT( connected( int ) ) );
				return;
			}
		case 1: // InitialChoice::Public:
			{
				LOG_PLACE_NL();
				NetworkSetup* setup = new NetworkSetup( parent );
				parent->addPage( setup, "FIXME!!" );
				parent->setFinishEnabled( setup, true );
				parent->showPage( setup );
				connect( parent, SIGNAL( execute() ), setup, SLOT( execute() ) );
				connect( setup, SIGNAL( connected( int ) ),parent,SLOT( connected( int ) ) );
				return;
			}
		case 2: // InitialChoice::Private:
			{
				// TODO
				LOG_PLACE() << "TODO\n\n\nTODO\n\n\n\n";
				return;
			}
		default:
			massert( 0 );
	}
}

#include "initialchoice.moc"
