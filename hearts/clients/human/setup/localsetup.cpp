#include "localsetup.h"
#include "exec.h"

#include "general/widget_placement.h"
#include "general/setup.h"
#include "hearts/player_id.h"
#include "general/helper.h"
#include "communication/constants.h"
#include "communication/open_connections.h"

#include "../options.h"

#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <klocale.h>
#include <kapp.h>
#include <qtimer.h>
#include <kprocess.h>

#include <sys/socket.h>
#include <unistd.h>

#include <algorithm>



LocalSetup::LocalSetup(QWidget* parent, const char* name)
	:QWidget(parent,name),
	 self_message(new QLabel(i18n("Your name"),this)),
	 self_name(new QLineEdit(Options::playerName(player_id::self),this)),
	 right_message(new QLabel(i18n("Name of opponent on right"),this)),
	 right_name(new QLineEdit(Options::playerName(player_id::right),this)),
	 front_message(new QLabel(i18n("Name of opponent in front"),this)),
	 front_name(new QLineEdit(Options::playerName(player_id::front),this)),
	 left_message(new QLabel(i18n("Name of opponent on left"), this)),
	 left_name(new QLineEdit(Options::playerName(player_id::left),this)),
	 go(new QPushButton(i18n("Go!"),this))
{
	connect(go,SIGNAL(clicked()),SLOT(execute()));
	
	
	const int x = 10;
	const int padding = 10;
	
	self_message->move(x,padding);
	self_message->setMinimumSize(self_message->sizeHint());
	LOG_PLACE() << self_message->sizeHint().width() << ',' << self_message->sizeHint().height() << '\n';
	int max_x = right_of(self_message);
	
	right_message->move(x,below(self_message) + padding);
	adjust_size(right_message);
	max_x = std::max(max_x,right_of(right_message));
	
	front_message->move(x,below(right_message) + padding);
	adjust_size(front_message);
	max_x = std::max(max_x,right_of(front_message));

	left_message->move(x,below(front_message) + padding);
	adjust_size(left_message);
	max_x = std::max(max_x, right_of(left_message));

	max_x += padding;

#define ADJUST(x) x##_name->setMinimumSize(140,x##_name->height());x##_name->move(max_x,x##_message->y());

	ADJUST(self);
	ADJUST(right);
	ADJUST(front);
	ADJUST(left);
	
	go->move(x,below(left_message) + padding);

	setMinimumSize(right_of(self_name) + padding, below(go) + padding);
	LOG_PLACE() << right_of(self_name) + padding << ',' << below(go) + padding << ")\n";
	
}


void LocalSetup::execute()
{ // FIXME: add error handling
		// FIXME: the whole thing with execute2 is really "hacky"
	execute_server();
	QTimer::singleShot(1500,this,SLOT(execute2()));
}

void LocalSetup::execute2()
{
		execute_computer_client(right_name->text());
		execute_computer_client(front_name->text());
		execute_computer_client(left_name->text());
		int fd = open_client_connection(local_address); 
#define SAVE(x)  Options::savePlayerName(player_id::x,x##_name->text())

		SAVE(self);
		SAVE(right);
		SAVE(front);
		SAVE(left);

		// must be done last
		emit connected(fd);
}


#include "localsetup.moc"

