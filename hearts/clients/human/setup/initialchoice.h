#ifndef DB_INITIALCHOICE_H_INCLUDE_GUARD_
#define DB_INITIALCHOICE_H_INCLUDE_GUARD_

#include <qwidget.h>
#include "smartpage.h"
class InitialChoiceWidget;

class InitialChoice : public SmartPage {
	Q_OBJECT

	public:
		InitialChoice(QWidget*,const char* = "initial-choice");
	private:
		virtual void doNext( SetupWindow* );
		InitialChoiceWidget* widget_;
};




#endif /* DB_INITIALCHOICE_H_INCLUDE_GUARD_ */
