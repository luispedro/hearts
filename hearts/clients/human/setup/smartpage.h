#include <qwidget.h>
class SetupWindow;

class SmartPage : public QWidget 
{
	Q_OBJECT
	public:
		SmartPage( QWidget* parent, const char* name ):QWidget( parent, name ) { }
		virtual void doNext( SetupWindow * ) = 0;
};
