#ifndef DB_SETUP_WINDOW_H_INCLUDE_GUARD_
#define DB_SETUP_WINDOW_H_INCLUDE_GUARD_

#include <ktabctl.h>
#include <kmainwindow.h>
#include <qdialog.h>
class QLabel;

class SetupWindow : public QDialog {
	Q_OBJECT
		public:
				SetupWindow();
		private slots:
				void connected(int);
		signals:
				void connected_to(int);	

		private:
				KTabCtl* tabs;
				QLabel* intro_text;
				
				// LocalSetup* local;
				// RemoteSetup* remote;
				// ServerSetup* server;
};



#endif /* DB_SETUP_WINDOW_H_INCLUDE_GUARD_ */
