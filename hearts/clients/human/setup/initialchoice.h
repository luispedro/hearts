#ifndef DB_INITIALCHOICE_H_INCLUDE_GUARD_
#define DB_INITIALCHOICE_H_INCLUDE_GUARD_

#include <qwidget.h>
#include "smartpage.h"

class InitialChoiceWidget;
class LocalSetup;
class NetworkSetup;
class PrivateSetup;

class InitialChoice : public SmartPage
{
		Q_OBJECT

	public:
		InitialChoice( SetupWindow*, const char* = "initial-choice" );
	private:
		virtual void doNext( SetupWindow* );
		virtual void init( SetupWindow* ) { }
		InitialChoiceWidget* widget_;

		LocalSetup* localsetup_;
		NetworkSetup* networksetup_;
		PrivateSetup* privatesetup_;
};




#endif /* DB_INITIALCHOICE_H_INCLUDE_GUARD_ */
