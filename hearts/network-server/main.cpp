#include <qapplication.h>
#include "server.h"
#include "general/helper.h"


int main(int argc, char** argv)
{
	QApplication app( argc, argv, false ); // no GUI
	( void )new Server( &app );
	LOG_PLACE_NL();
	return app.exec();
}


