#ifndef DB_SERVERSETUP_H_INCLUDE_GUARD_
#define DB_SERVERSETUP_H_INCLUDE_GUARD_

#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>


class ServerSetup : public QWidget {
	Q_OBJECT

	public:
		ServerSetup(QWidget* parent, const char* name = "server-setup");

	signals:
		void connected(int);

	public slots:

		void execute();

		class PlayerSetup;
	
	private:

	
		QLabel* self;
		PlayerSetup* right;
		PlayerSetup* front;
		PlayerSetup* left;
		QPushButton* go;
};


#endif /* DB_SERVERSETUP_H_INCLUDE_GUARD_ */
