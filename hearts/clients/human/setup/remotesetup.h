#ifndef DB_REMOTESETUP_H_INCLUDE_GUARD_
#define DB_REMOTESETUP_H_INCLUDE_GUARD_

#include <qwidget.h>
class QPushButton;
class QLabel;
class QLineEdit;

class RemoteSetup : public QWidget {
		Q_OBJECT
	public:
		RemoteSetup(QWidget* parent, QString name = "remote-setup");
	signals:
		void connected(int);
	public slots:
		void execute();
	private:
		QPushButton* 	ok;
		QLabel* 	 	ip_label;
		QLineEdit* 		ip;
		QLabel*			name_label;
		QLineEdit*		name;
};



#endif /* DB_REMOTESETUP_H_INCLUDE_GUARD_ */
