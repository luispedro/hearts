#include "remotesetup.h"
#include "exec.h"
#include "general/widget_placement.h"
#include "communication/open_connections.h"

#include "../options.h"

#include <klocale.h>
#include <qpushbutton.h>
#include <kprocess.h>
#include <kapp.h>
#include <qlabel.h>
#include <qlineedit.h>

RemoteSetup::RemoteSetup(QWidget* p, QString n)
	:QWidget(p,n),
	 ok(new QPushButton(i18n("Go!"),this)),
	 ip_label(new QLabel(i18n("ip address of server:"),this)),
	 ip(new QLineEdit(this)),
	 name_label(new QLabel(i18n("name:"),this)),
	 name(new QLineEdit(Options::playerName(player_id::self),this))
{
	connect(ok,SIGNAL(clicked()),SLOT(execute()));
	
	ip_label->move(10,10);
	ip->move(right_of(ip_label) + 10,10);
	KConfig* c = KGlobal::config();
	KConfigGroupSaver s(c,QString::fromLatin1("remote-setup"));
	ip->setText(c->readEntry("ip-address","127.0.0.1"));
	
	name_label->move(10,below(ip_label) + 10),
	name->move(right_of(name_label) + 10, name_label->y());
	ok->move(10,below(name_label) + 10);
	setMinimumHeight(ok->y() + ok->height());
}

void RemoteSetup::execute()
{
		int fd = open_client_connection(ip->text());

		KConfig* c = KGlobal::config();
		KConfigGroupSaver s(c,QString::fromLatin1("remote-setup"));
		c->writeEntry("ip-address",ip->text());
	
		Options::savePlayerName(player_id::self,name->text());
		
		emit connected(fd);
}

