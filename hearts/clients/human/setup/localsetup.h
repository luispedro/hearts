#ifndef DB_LOCALSETUP_H_INCLUDE_GUARD_
#define DB_LOCALSETUP_H_INCLUDE_GUARD_

#include <qwidget.h>
#include <qstring.h>
#include <qpushbutton.h>

#include "hearts/player_id.h"

class QLabel;
class QLineEdit;
class LocalSetupWidget;

class LocalSetup : public QWidget
{
		Q_OBJECT
	public:
		LocalSetup( QWidget* parent, const char* name = "" );

	public slots:
		void setName( player_id::type, QString );

	signals:
		void connected( int );

	private slots:
		/** This setups a local games and execs a server */
		void execute();

	private:
		LocalSetupWidget* widget_;
};



#endif /* DB_LOCALSETUP_H_INCLUDE_GUARD_ */
