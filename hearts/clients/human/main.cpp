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
			KCmdLineLastOption
	};
}

int test_pointsbox()
{
		PointsBox* box = new PointsBox;
		box->setName( player_id::self, "luis" );
		box->setName( player_id::right, "right" );
		box->setName( player_id::front, "front" );
		box->setName( player_id::left, "left" );
		box->insertLine( 1, 2 ,3 ,4 );
		box->insertLine( 12, 22 ,23 ,24 );
		box->insertLine( 212,222 ,243 ,224 );
		box->exec();
		box->insertLine( 12,22 ,243 ,24 );
		box->insertLine( 212,22 ,23 ,224 );
		box->exec();

		box->clear();

		box->insertLine( 8, 8, 8, 8 );
		box->insertLine( 81, 82, 83, 84 );
		box->insertLine( 88, 87, 86, 85 );
		box->exec();

		box->insertLine( 8, 8, 8, 8 );
		box->insertLine( 81, 82, 83, 84 );
		box->insertLine( 88, 87, 86, 85 );
		box->exec();

		box->insertLine( 8, 8, 8, 8 );
		box->insertLine( 81, 82, 83, 84 );
		box->insertLine( 88, 87, 86, 85 );
		box->exec();
		box->clear();

		box->insertLine( 8, 8, 8, 8 );
		box->insertLine( 81, 82, 83, 84 );
		box->insertLine( 88, 87, 86, 85 );
		box->exec();
		box->clear();

		box->insertLine( 8, 8, 8, 8 );
		box->insertLine( 81, 82, 83, 84 );
		box->insertLine( 88, 87, 86, 85 );
		box->exec();
		box->clear();

		box->insertLine( 8, 8, 8, 8 );
		box->insertLine( 81, 82, 83, 84 );
		box->insertLine( 88, 87, 86, 85 );
		box->insertLine( 88, 87, 86, 85 );
		box->insertLine( 88, 87, 86, 85 );
		box->insertLine( 88, 87, 86, 85 );
		box->insertLine( 88, 87, 86, 85 );
		box->insertLine( 88, 87, 86, 85 );
		box->insertLine( 88, 87, 86, 85 );
		box->insertLine( 88, 87, 86, 85 );
		box->insertLine( 88, 87, 86, 85 );
		box->insertLine( 88, 87, 86, 85 );
		box->insertLine( 88, 87, 86, 85 );
		box->insertLine( 88, 87, 86, 85 );
		box->insertLine( 88, 87, 86, 85 );
		box->insertLine( 88, 87, 86, 85 );
		box->insertLine( 88, 87, 86, 85 );
		box->insertLine( 88, 87, 86, 85 );
		box->insertLine( 88, 87, 86, 85 );
		box->insertLine( 88, 87, 86, 85 );
		box->insertLine( 88, 87, 86, 85 );
		box->insertLine( 88, 87, 86, 85 );
		box->insertLine( 88, 87, 86, 85 );
		box->insertLine( 88, 87, 86, 85 );
		box->insertLine( 88, 87, 86, 85 );
		box->insertLine( 88, 87, 86, 85 );
		box->insertLine( 88, 87, 86, 85 );
		box->insertLine( 88, 87, 86, 85 );
		box->insertLine( 88, 87, 86, 85 );
		box->insertLine( 88, 87, 86, 85 );
		box->insertLine( 88, 87, 86, 85 );
		box->insertLine( 88, 87, 86, 85 );
		box->insertLine( 88, 87, 86, 85 );
		box->insertLine( 88, 87, 86, 85 );
		box->insertLine( 88, 87, 86, 85 );
		box->insertLine( 88, 87, 86, 85 );
		return box->exec();
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

