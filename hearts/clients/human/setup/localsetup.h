#ifndef DB_LOCALSETUP_H_INCLUDE_GUARD_
#define DB_LOCALSETUP_H_INCLUDE_GUARD_

#include <qwidget.h>
#include <qstring.h>
#include <qpushbutton.h>

class QLabel;
class QLineEdit;
class LocalSetupWidget;

class LocalSetup : public QWidget {
		Q_OBJECT
		public:
		LocalSetup(QWidget* parent, const char* name = "");
		
		private slots:
			/** This setups a local games and execs a server */
				void execute();
			/** @internal */
				void execute2();

		signals:
				void connected(int);
		
	
	private:
		LocalSetupWidget* widget_;
};
		


#endif /* DB_LOCALSETUP_H_INCLUDE_GUARD_ */
