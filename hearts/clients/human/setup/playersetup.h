#ifndef DB_PLAYERSETUP_H_INCLUDE_GUARD_
#define DB_PLAYERSETUP_H_INCLUDE_GUARD_

#include <qcombobox.h>
#include <qlabel.h>

#include "hearts/player_id.h"

#include "serversetup.h"


class ServerSetup::PlayerSetup : public QWidget { 
	Q_OBJECT 
		public:
				PlayerSetup(player_id::type, QWidget* parent, const char* name = "player-setup");

		public slots:
				
				void execute();

		private slots:
				void optionsClicked();
			
	private:
		QLabel* label;
		QComboBox* choice;
		QPushButton* options;
		player_id::type whoami;
};



#endif /* DB_PLAYERSETUP_H_INCLUDE_GUARD_ */
