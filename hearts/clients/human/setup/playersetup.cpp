#include "playersetup.h"
#include "exec.h"

#include "general/widget_placement.h"
#include "general/helper.h"

#include "../options.h"

#include <kprocess.h>
#include <klocale.h>
#include <kmessagebox.h>
#include <qpushbutton.h>
#include <algorithm>

namespace {
		QString pl2text(player_id::type who)
		{
				LOG_PLACE_NL();
				using namespace player_id;
				switch (who)
				{
						case right:	return i18n("Type of second player");
						case front: return i18n("Type of third player");
						case left: 	return i18n("Type of fourth player");
						default: massert(0);
				}
		}
}

ServerSetup::PlayerSetup::PlayerSetup(player_id::type who,QWidget* parent, const char* name)
		:QWidget(parent,name),
		 label(new QLabel(pl2text(who),this)),
		 choice(new QComboBox(this)),
		 options(new QPushButton(i18n("Options"),this)),
		 whoami(who)
{
		LOG_PLACE_NL();
		label->move(10,10);
		adjust_size(label);
		
		unsigned combo_x = right_of(label) + 10;
		combo_x = std::min<unsigned>(combo_x,250);
		choice->move(combo_x,10);
		
		choice->insertItem(i18n("computer player"));
		choice->insertItem(i18n("remote human player"));
		adjust_size(choice);

		options->move(right_of(choice) + 10, 10);
		connect(options,SIGNAL(clicked()),SLOT(optionsClicked()));
		
		
		setMinimumWidth(right_of(options));
		setMinimumHeight(10 + std::max(label->height(), choice->height()));
		LOG_PLACE_NL();
}

void ServerSetup::PlayerSetup::optionsClicked()
{
		enum { comp, remote };
		if (choice->currentItem() == comp)
		{
				KMessageBox::sorry(this,i18n("Not yet implemented"));
				/*
				* ComputerPlayerOptions* opt = new ComputerPlayerOptions(whoami);
				* opt->show();
				* opt->exec();
				*/
		}
		else if (choice->currentItem() == remote)
		{
				
				 KMessageBox::sorry(this,i18n("There are no options available for remote players"));

		}
}

void ServerSetup::PlayerSetup::execute()
{
		enum { comp, remote, local };
		if (choice->currentItem() == comp)
		{
				
				execute_computer_client(QString(Options::playerName(whoami)));
		} 
		else if (choice->currentItem() == local) 
		{
				// what the fuck are we doing here ????
				massert(0);
				//execute_human_client(QString("127.0.0.1"),QString("Tomate"));
		}
		else 
		{
				; // remote player, do nothing
		}
}

#include "playersetup.moc"

