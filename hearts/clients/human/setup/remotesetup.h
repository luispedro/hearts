#ifndef DB_REMOTESETUP_H_INCLUDE_GUARD_
#define DB_REMOTESETUP_H_INCLUDE_GUARD_

#include <qwidget.h>
class RemoteSetupWidget;


class RemoteSetup : public QWidget
{
		Q_OBJECT
	public:
		RemoteSetup( QWidget* parent, const char* name = "remote-setup" );
	signals:
		void connected( int );
	public slots:
		void execute();
	private:
		RemoteSetupWidget* widget_;
};



#endif /* DB_REMOTESETUP_H_INCLUDE_GUARD_ */
