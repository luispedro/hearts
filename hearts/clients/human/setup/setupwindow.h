#ifndef DB_SETUP_WINDOW_H_INCLUDE_GUARD_
#define DB_SETUP_WINDOW_H_INCLUDE_GUARD_

#include <ktabctl.h>
#include <kmainwindow.h>
#include <qwizard.h>
class QLabel;


class Connector {
		public:
				virtual int connect() = 0;
};

class SetupWindow : public QWizard
{
		Q_OBJECT
	public:
		SetupWindow();

	public slots:
		void connected( int );
	
	signals:
		void connected_to( int );
		void execute();

	private:
		void next();
		virtual void accept();
};



#endif /* DB_SETUP_WINDOW_H_INCLUDE_GUARD_ */
