#ifndef DB_LOCALSETUP_H_INCLUDE_GUARD_
#define DB_LOCALSETUP_H_INCLUDE_GUARD_

#include <qwidget.h>
#include <qstring.h>
#include <qpushbutton.h>

class QLabel;
class QLineEdit;

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
		QLabel* self_message;
		QLineEdit* self_name;
		
		QLabel* right_message;
		QLineEdit* right_name;
		
		QLabel* front_message;
		QLineEdit* front_name;

		QLabel* left_message;
		QLineEdit* left_name;

		QPushButton* go;

};
		


#endif /* DB_LOCALSETUP_H_INCLUDE_GUARD_ */
