#include "setupwindow.h"
#include "localsetup.h"
#include "remotesetup.h"
#include "serversetup.h"
#include "networksetup.h"

#include "general/helper.h"
#include "general/widget_placement.h"

#include <klocale.h>
#include <qlabel.h>

#include <cstdlib>
#include <algorithm>

namespace {
		const char* intro = I18N_NOOP("Please choose whether you would like to play a local game or a network.\n"
							"If you want to play a network game, one player must deal cards while others\n"
							"connect to it.");
}


SetupWindow::SetupWindow()
	:tabs(new KTabCtl(this,"main-tab")),
	 intro_text(new QLabel(i18n(intro),this))
{
		LocalSetup* local = new LocalSetup(tabs);
		RemoteSetup* remote = new RemoteSetup(tabs);
		ServerSetup* server = new ServerSetup(tabs);
		NetworkSetup* network = new NetworkSetup(tabs);
		intro_text->move(10,10);
		adjust_size(intro_text);

		tabs->move(10,below(intro_text) + 10);
		
		tabs->addTab(network,i18n("Play on a game network"));
		tabs->addTab(remote,i18n("Connect to a private game"));
		tabs->addTab(server,i18n("Deal cards for a private game"));
		tabs->addTab(local,i18n("Play against the computer"));

//X 		adjust_size( local );
//X 		adjust_size( remote );
//X 		adjust_size( server );
//X 		adjust_size( network );
//X 		adjust_size( tabs );
		
		tabs->setMinimumSize( 250, 350 );

		setMinimumSize(std::max(intro_text->width() + 20, tabs->width() + 20),
						below(tabs) + 10);

		connect(local,SIGNAL(connected(int)),SLOT(connected(int)));
		connect(remote,SIGNAL(connected(int)),SLOT(connected(int)));
		connect(server,SIGNAL(connected(int)),SLOT(connected(int)));
		connect(network,SIGNAL(connected(int)),SLOT(connected(int)));
		LOG_PLACE_NL();
}

void SetupWindow::connected(int fd)
{
		emit connected_to(fd);
		this->close();
//X 		deleteLater();
}


#include "setupwindow.moc"

