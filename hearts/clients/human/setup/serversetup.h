#ifndef DB_SERVERSETUP_H_INCLUDE_GUARD_
#define DB_SERVERSETUP_H_INCLUDE_GUARD_

#include <qwidget.h>

class QPushButton;
class QLabel;

class ServerSetup : public QWidget {
	Q_OBJECT

	public:
		ServerSetup(QWidget* parent, const char* name = "server-setup");

	signals:
		void connected(int);

	public slots:
		void execute();

	public:
		class PlayerSetup;

	private:


		QLabel* self;
		PlayerSetup* right;
		PlayerSetup* front;
		PlayerSetup* left;
		QPushButton* go;
};


#endif /* DB_SERVERSETUP_H_INCLUDE_GUARD_ */
