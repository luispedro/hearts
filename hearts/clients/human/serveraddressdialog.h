#ifndef DB_SERVERADDRESSDIALOG_H_INCLUDE_GUARD_
#define DB_SERVERADDRESSDIALOG_H_INCLUDE_GUARD_

#include <qdialog.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qstring.h>
#include <qpushbutton.h>

class ServerAddressDialog : public QDialog {
		Q_OBJECT
		public:
				ServerAddressDialog(const QString& def, QWidget* p = 0, const char* name = 0);

		public slots:
				void connect();
		signals:
				void connected(int);
		private:

				QLabel* text;
				QLineEdit* address;
				QPushButton* connectButton;
};



#endif /* DB_SERVERADDRESSDIALOG_H_INCLUDE_GUARD_ */
