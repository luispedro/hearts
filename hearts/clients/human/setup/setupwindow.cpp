#include "setupwindow.h"
#include "initialchoice.h"

#include "general/helper.h"

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
	insertPage( init, i18n( "Type of game" ), 0 );
	showPage( init );
	init->adjustSize();
	resize( QSize( 500, 180 ).expandedTo( minimumSizeHint() ) );
	setNextEnabled( init, true );
}

void SetupWindow::next()
{
	if ( SmartPage* p = dynamic_cast<SmartPage*>( currentPage() ) ) p->doNext( this );
	QWizard::next();
}

void SetupWindow::connected( int fd )
{
	assert( fd > 0 );
	emit connected_to( fd );
	this->QWizard::accept();
	this->close();
}


void SetupWindow::accept()
{
	if ( Connector* c = dynamic_cast<Connector*>( currentPage() ) ) {
			connected( c->connect() );
	} else {
			Q_ASSERT( "currentPage is not a Connector!!" && 0 );
	}
}


#include "setupwindow.moc"

