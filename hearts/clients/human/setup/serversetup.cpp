#include "serversetup.h"
#include "playersetup.h"
#include "exec.h"
#include "general/widget_placement.h"
#include "general/helper.h"
#include "communication/constants.h"
#include "communication/open_connections.h"

#include <klocale.h>
#include <kprocess.h>
#include <kapp.h>

ServerSetup::ServerSetup(QWidget* parent, const char* name):
	QWidget(parent,name),
	self(new QLabel(i18n("Type of first player: Local player"),this)),
	right(new PlayerSetup(player_id::right,this)),
	front(new PlayerSetup(player_id::front,this)),
	left(new PlayerSetup(player_id::left, this)),
	go(new QPushButton(i18n("Go!"),this,"server-execute"))
{
	connect(go,SIGNAL(clicked()),SLOT(execute()));
	
	self->move(10,10);
	//adjust_size(self);
	right->move(10,below(self) + 10);
	//adjust_size(right);
	front->move(10,below(right) + 10);
	//adjust_size(front);
	left->move(10,below(front) + 10);
	//adjust_size(left);
	
	go->move(10,below(left) + 20);
	adjust_size(go);
	setMinimumHeight(below(go) + 10);

}

void ServerSetup::execute()
{
		execute_server();
		sleep(1); // FIXME: hack
		right->execute();
		front->execute();
		left->execute();
		int fd = open_client_connection(local_address);
		emit connected(fd);
}


