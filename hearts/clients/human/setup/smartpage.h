#ifndef DB_SMARTPAGE_H1080679200_INCLUDE_GUARD_
#define DB_SMARTPAGE_H1080679200_INCLUDE_GUARD_

#include <qwidget.h>
class SetupWindow;

class SmartPage : public QWidget
{
		Q_OBJECT
	public:
		SmartPage( QWidget* parent, const char* name ) : QWidget( parent, name )
		{ }
		virtual void doNext( SetupWindow * ) = 0;
		virtual void init( SetupWindow * ) = 0;
};


#endif /* DB_SMARTPAGE_H1080679200_INCLUDE_GUARD_ */
