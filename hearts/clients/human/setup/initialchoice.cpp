#include "initialchoice.h"
#include "localsetup.h"
#include "remotesetup.h"
#include "serversetup.h"
#include "networksetup.h"

#include "setupwindow.h"
#include "general/helper.h"
#include "general/widget_placement.h"
#include "initialchoicewidget.h"

	InitialChoice::InitialChoice(QWidget* parent, const char* name)
		:SmartPage( parent, name )
{
	LOG_PLACE_NL();
	widget_ = new InitialChoiceWidget( this );
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
				LocalSetup* setup = new LocalSetup( this );
				parent->addPage( setup, "FIXME" );
				parent->setFinishEnabled( setup, true );
				return;
			}
		case 1: // InitialChoice::Public:
			{
				NetworkSetup* setup = new NetworkSetup( this );
				parent->addPage( setup, "FIXME!!" );
				parent->setFinishEnabled( setup, true );
			}
		case 2: // InitialChoice::Private:
			{
				// TODO
				return;
			}
		default:
			massert( 0 );
	}
}

