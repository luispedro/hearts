#ifndef DB_SETUP_WINDOW_H_INCLUDE_GUARD_
#define DB_SETUP_WINDOW_H_INCLUDE_GUARD_

#include <ktabctl.h>
#include <kmainwindow.h>
#include <qwizard.h>
class QLabel;

class SetupWindow : public QWizard {
	Q_OBJECT
		public:
				SetupWindow();
		private:
				void next();
		private slots:
				void connected(int);
		signals:
				void connected_to(int);	
};



#endif /* DB_SETUP_WINDOW_H_INCLUDE_GUARD_ */
