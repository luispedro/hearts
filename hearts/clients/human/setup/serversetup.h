#ifndef DB_SERVERSETUP_H_INCLUDE_GUARD_
#define DB_SERVERSETUP_H_INCLUDE_GUARD_

#include <qwidget.h>

#include "hearts/player_id.h"

class ServerSetupWidget;
class QComboBox;

class ServerSetup : public QWidget
{
	Q_OBJECT

	public:
		ServerSetup( QWidget* parent, const char* name = "server-setup" );

	signals:
		void connected( int );

	public slots:
		void execute();

	private slots:
		void optionsSelf();
		void optionsRight();
		void optionsFront();
		void optionsLeft();

	private:
		int execute( player_id::type, QComboBox* );
		void options( player_id::type, QComboBox* );

		ServerSetupWidget* widget_;
};


#endif /* DB_SERVERSETUP_H_INCLUDE_GUARD_ */
