#include <kapp.h>
#include "humanclient.h"
#include "config.h"
#include "general/helper.h"
#include <kcmdlineargs.h>
#include <kaboutdata.h>
#include <klocale.h>
#include "communication/open_connections.h"
#include "communication/constants.h"

namespace {
		KCmdLineOptions app_options [] = {
			{ 0, 0, 0 }
	};
}

int main(int argc, char* argv[])
{
		LOG_PLACE_NL();
		KAboutData aboutData( "hearts", I18N_NOOP("Hearts, a card game"),
		                VERSION, "Hearts game for the KDE", KAboutData::License_GPL,
		                "(c) 2001, Luis Pedro Coelho", I18N_NOOP("Hearts - a card game"), "http://hearts.sf.net/", "luis_pedro@netcabo.pt");
		aboutData.addAuthor("Luis Pedro Coelho",0, "luis_pedro@netcabo.pt");
		KCmdLineArgs::init( argc, argv, &aboutData );
//		KCmdLineArgs::addCmdLineOptions(app_options);
		KApplication::addCmdLineOptions();
		KApplication app;
		HumanClient* main_win = new HumanClient;
		main_win->show();
//		main_win->setCaption(i18n("hearts card game"));
		LOG_PLACE_NL();
		return app.exec();
}

