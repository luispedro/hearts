#include "humanclient.h"
#include "options.h"
#include "general/helper.h"
#include "communication/open_connections.h"
#include "setup/setupwindow.h"

#include <strstream>
#include <iomanip>

#include <qtimer.h>
#include <qsignalmapper.h>
#include <qmessagebox.h>
#include <kmessagebox.h>
#include <kapplication.h>
#include <kdebug.h>


HumanClient::HumanClient()
	:pointsWindow(new PointsBox(i18n("points"))),
	interface(new HumanInterface(this,"human-interface")),
	connection(new QtConnection(this,"client-connection"))

{
	QSignalMapper* mPlay = new QSignalMapper(this);
	QSignalMapper* mGive = new QSignalMapper(this);
	mPlay->setMapping(connection,i18n("This is your turn to play"));
	mGive->setMapping(connection,i18n("Give three cards to your opponent"));

	connect(connection,SIGNAL(play()),interface,SLOT(play()));
	connect(connection,SIGNAL(give3()),interface,SLOT(choose3()));
	connect(connection,SIGNAL(inform(player_id::type,Card)),interface,SLOT(setCard(player_id::type,Card)));
	connect(connection,SIGNAL(inform(player_id::type,Card)),SLOT(inform(player_id::type,Card)));
	connect(connection,SIGNAL(receive(Card)),interface, SLOT(addCard(Card)));

	connect(connection,SIGNAL(points(unsigned,unsigned,unsigned,unsigned)),
			SLOT(points(unsigned,unsigned,unsigned,unsigned)));

	connect(connection,SIGNAL(invalidmove(QString)),SLOT(invalidMove(QString)));

	connect(connection,SIGNAL(opponentname(player_id::type,QString)),interface,SLOT(setName(player_id::type,QString)));
	connect(connection,SIGNAL(opponentname(player_id::type,QString)),pointsWindow,SLOT(setName(player_id::type,QString)));
	pointsWindow->setName(player_id::self,Options::playerName(player_id::self));

	connect(connection,SIGNAL(play()),mPlay,SLOT(map()));
	connect(mPlay,SIGNAL(mapped(const QString&)),interface,SLOT(setStatus(const QString&)));

	connect(connection,SIGNAL(give3()),mGive,SLOT(map()));
	connect(mGive,SIGNAL(mapped(const QString&)),interface,SLOT(setStatus(const QString&)));


	connect(connection,SIGNAL(namequery()),SLOT(namequery()));
	connect(connection,SIGNAL(error(QString)),SLOT(connectionError(QString)));
	connect(connection,SIGNAL(status(player_status::type)),SLOT(status(player_status::type)));

	connect(connection,SIGNAL(terminate(QString)),SLOT(terminate(QString)));

	connect(interface,SIGNAL(chose(const Holder3&)),connection,SLOT(give3(const Holder3&)));
	connect(interface,SIGNAL(played(Card)),connection,SLOT(play(Card)));


	setMinimumWidth(interface->width());
	setMinimumHeight(interface->height());

	updateNames();

	LOG_PLACE_NL();
	setup_ = new SetupWindow;
	connect(setup_,SIGNAL(connected_to(int)),SLOT(connected_to_server(int)));
	QTimer::singleShot( 0, this, SLOT( showSetup() ) );
}

void HumanClient::showSetup()
{
	int res = setup_->exec();
	if ( res == QWizard::Rejected ) {
		kdDebug() << "HumanClient::showSetup() exiting..." << endl;
		QTimer::singleShot( 0, kapp, SLOT( quit() ) );
	}
}

void HumanClient::connected_to_server(int fd)
{
	massert( connection );
	massert( fd > 0 );
	connection->set_fd(fd);
	updateNames(); // FIXME: This shouldn't work like this 
	// Further Note: WTF does this do?
}

void HumanClient::updateNames()
{
#define UPDATE(x) interface->setName(player_id::x,Options::playerName(player_id::x))
	UPDATE(self);
	UPDATE(right);
	UPDATE(front);
	UPDATE(left);
#undef UPDATE
}


void HumanClient::namequery()
{
	connection->name(Options::playerName(player_id::self));
}

void HumanClient::connectionError(QString m)
{
	//cerr << m.toLocal8bit() << ".\n";
	abort();
}

void HumanClient::status(player_status::type s)
{
	LOG_PLACE() << " handling status " << s << ".\n";
	using namespace player_status;
	using namespace player_id;
	bool clear = true;
	switch (s)
	{
		case hand_over_self_win:
			winner = player_id::self;
			break;
		case hand_over_right_win:
			winner = player_id::right;
			break;
		case hand_over_front_win:
			winner = player_id::front;
			break;
		case hand_over_left_win:
			winner = player_id::left;
			break;
		case game_over:
			clear = false;
			break;
	}
	if (clear)
	{
		// This is to allow time for the user to look at the cards without them being taken away.
		// Also we can't allow any new info to come in or it could ruin the display
		connection->disable();
		QTimer::singleShot(500,this,SLOT(clearTable())); 
		QTimer::singleShot(950,connection,SLOT(enable()));
	}
}


void HumanClient::clearTable()
{
	interface->clearTable(winner);
}

void HumanClient::terminate(QString)
{
	LOG_PLACE_NL();
	connection->close();
	KMessageBox::information(this,i18n("Game over"));
	(new SetupWindow)->show();
}


void HumanClient::inform(player_id::type who,Card c)
{
	if (who == player_id::self)
	{
		interface->removeCard(c);
	}
}

void HumanClient::points(unsigned self, unsigned right, unsigned front, unsigned left)
{
	pointsWindow->insertLine( self, right, front, left );
	pointsWindow->show();
}

void HumanClient::invalidMove(QString reason)
{
	LOG_PLACE() << " invalid move: " << reason << ".\n";
	QMessageBox::warning(this,i18n("Invalid Move"),i18n(reason),i18n("Ok"));
	interface->play();
}

#include "humanclient.moc"
