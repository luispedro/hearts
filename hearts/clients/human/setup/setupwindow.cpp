#include "setupwindow.h"
#include "initialchoice.h"

#include "general/helper.h"
#include "general/widget_placement.h"

#include <klocale.h>
#include <qlabel.h>

#include <cstdlib>
#include <algorithm>
#include <cassert>
#include <unistd.h>

namespace
{
const char* intro = I18N_NOOP( "Please choose whether you would like to play a local game or a network.\n"
							   "If you want to play a network game, one player must deal cards while others\n"
							   "connect to it." );
}


SetupWindow::SetupWindow()
		: QWizard( 0, "setup-window" )
		//, intro_text(new QLabel(i18n(intro),this))
{
	LOG_PLACE_NL();
	InitialChoice* init = new InitialChoice( this );
	addPage( init, QString::fromLatin1( i18n( "Type of game" ) ) );
	showPage( init );
	init->adjustSize();
	resize( QSize( 600, 480 ).expandedTo( minimumSizeHint() ) );

	init->show();
	nothing = new QWidget( this );
	addPage( nothing, QString::fromLatin1( "Bug if you see this" ) );
	setNextEnabled( init, true );
}

void SetupWindow::next()
{
	if ( nothing ) {
		removePage( nothing );
		delete nothing;
		nothing = 0;
	}
	static_cast<SmartPage*>( currentPage() ) ->doNext( this );
}

void SetupWindow::connected( int fd )
{
	assert( fd > 0 );
	emit connected_to( fd );
	this->QWizard::accept();
	this->close();
	//this->accept();
	//X 	deleteLater();
}


void SetupWindow::accept()
{
	emit execute();
	QWizard::accept();
}


#include "setupwindow.moc"

