#include "humanclient.h"
#include "options.h"
#include "general/helper.h"
#include "exec.h"
#include "networkdialog.h"
#include "privategamedialog.h"
#include "preferencesdialog.h"

#include <iomanip>

#include <qtimer.h>
#include <qsignalmapper.h>
#include <qlineedit.h>
#include <qmessagebox.h>
#include <kmessagebox.h>
#include <kpopupmenu.h>
#include <kmenubar.h>
#include <kapplication.h>
#include <kaction.h>
#include <kstdaccel.h>
#include <kdebug.h>


#include <string.h> // strerror
#include <errno.h>  // errno
#include <unistd.h>

// For hostname discovery:
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


HumanClient::HumanClient()
		: pointsWindow( new PointsBox ),
		interface( new HumanInterface( this, "human-interface" ) ),
		connection( new QtConnection( this, "client-connection" ) ),
		preferences_(0)
{

	connect( connection, SIGNAL( play() ), interface, SLOT( play() ) );
	connect( connection, SIGNAL( give3( player_id::type ) ), interface, SLOT( choose3() ) );
	connect( connection, SIGNAL( inform( player_id::type, Card ) ), interface, SLOT( setCard( player_id::type, Card ) ) );
	connect( connection, SIGNAL( inform( player_id::type, Card ) ), SLOT( inform( player_id::type, Card ) ) );
	connect( connection, SIGNAL( receive( Card ) ), interface, SLOT( addCard( Card ) ) );

	connect( connection, SIGNAL( points( unsigned, unsigned, unsigned, unsigned ) ),
			 SLOT( points( unsigned, unsigned, unsigned, unsigned ) ) );

	connect( connection, SIGNAL( invalidmove( QString ) ), SLOT( invalidMove( QString ) ) );

	connect( connection, SIGNAL( opponentname( player_id::type, QString ) ),
					interface, SLOT( setName( player_id::type, QString ) ) );
	connect( connection, SIGNAL( opponentname( player_id::type, QString ) ),
					pointsWindow, SLOT( setName( player_id::type, QString ) ) );
	pointsWindow->setName( player_id::self, Options::playerName( player_id::self ) );

	connect( connection, SIGNAL( give3( player_id::type ) ), SLOT( giveStatus( player_id::type ) ) );
	connect( connection, SIGNAL( play() ), SLOT( playStatus() ) );

	connect( connection, SIGNAL( namequery() ), SLOT( namequery() ) );
	connect( connection, SIGNAL( error( QString ) ), SLOT( connectionError( QString ) ) );
	connect( connection, SIGNAL( status( player_status::type ) ), SLOT( status( player_status::type ) ) );

	connect( connection, SIGNAL( terminate( QString ) ), SLOT( terminate( QString ) ) );

	connect( interface, SIGNAL( chose( const Holder3& ) ), connection, SLOT( give3( const Holder3& ) ) );
	connect( interface, SIGNAL( played( Card ) ), connection, SLOT( play( Card ) ) );


	setFixedWidth( interface->width() );
	setMinimumHeight( interface->height() );

#define SET_NAME(x) interface->setName(player_id::x,Options::playerName(player_id::x))
	HANDLE_ALL_PLAYER_IDS( SET_NAME );
#undef SET_NAME
	
	KMenuBar* menu = menuBar();
	KPopupMenu* gamemenu = new KPopupMenu( this );

	KAction* newGameAct = new KAction(i18n("&New Game"), "gamenew",
                               KStdAccel::shortcut( KStdAccel::New ),
                               this, SLOT( newGame() ),
                               actionCollection(), "new" );


	newGameAct->plug(gamemenu);
	gamemenu->insertItem( "Hearts &network game", this, SLOT( heartsNetwork() ) );
	gamemenu->insertItem( "Private &network game", this, SLOT( privateGame() ) );
	gamemenu->insertSeparator();
	KAction* qAct = KStdAction::quit( kapp, SLOT( quit() ), actionCollection() );
	qAct->plug(gamemenu);
	menu->insertItem( i18n( "&Game" ), gamemenu );

	KPopupMenu* editmenu = new KPopupMenu(this);
	KAction* pAct = KStdAction::preferences(this, SLOT(preferencesDialog()), actionCollection());
	pAct->plug(editmenu);
	menu->insertItem(i18n("E&dit"), editmenu);

	LOG_PLACE_NL();
	QTimer::singleShot( 500, this, SLOT( newGame() ) ); 
}

void HumanClient::connected_to_server( int fd )
{
	kdDebug() << "HumanClient::connected_to_server( " << fd << " )" << endl;
	massert( connection );
	massert( fd > 0 );
	connection->set_fd( fd );
	connection->enable();
}

void HumanClient::namequery()
{
	connection->name( Options::playerName( player_id::self ) );
}

void HumanClient::connectionError( QString m )
{
	//cerr << m.toLocal8bit() << ".\n";
	abort();
}

void HumanClient::status( player_status::type s )
{
	LOG_PLACE() << " handling status " << s << ".\n";
	using namespace player_status;
	bool clear = true;
	switch ( s ) {
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
		default: return;
	}
	if ( clear ) {
		// This is to allow time for the user to look at the cards without them being taken away.
		// Also we can't allow any new info to come in or it could ruin the display
		connection->disable();
		QTimer::singleShot( 500, this, SLOT( clearTable() ) );
		QTimer::singleShot( 950, connection, SLOT( enable() ) );
	}
}


void HumanClient::clearTable()
{
	interface->clearTable( winner );
}

void HumanClient::terminate( QString )
{
	LOG_PLACE_NL();
	connection->close();
	KMessageBox::information( this, i18n( "Game Over" ) );
	QTimer::singleShot( 500, this, SLOT( newGame() ) );
}


void HumanClient::inform( player_id::type who, Card c )
{
	if ( who == player_id::self ) {
		interface->removeCard( c );
	}
}

void HumanClient::points( unsigned self, unsigned right, unsigned front, unsigned left )
{
	pointsWindow->insertLine( self, right, front, left );
	pointsWindow->exec();
}

void HumanClient::invalidMove( QString reason )
{
	LOG_PLACE() << " invalid move: " << reason << ".\n";
	QMessageBox::warning( this, i18n( "Invalid Move" ), i18n( reason ), i18n( "Ok" ) );
	interface->play();
}

void HumanClient::playStatus()
{
	interface->setStatus( i18n( "Your turn to play" ) );
}

void HumanClient::giveStatus( player_id::type whom )
{
	switch ( whom ) {
		case player_id::right:
			interface->setStatus( i18n( "Choose three cards to pass right" ) );
			break;
		case player_id::front:
			interface->setStatus( i18n( "Choose three cards to pass across" ) );
			break;
		case player_id::left:
			interface->setStatus( i18n( "Choose three cards to pass left" ) );
			break;
		default:
			kdWarning() << "BUG: giveStatus( " << static_cast<int>( whom ) << " )" << endl;
	}
}

void HumanClient::newGame()
{
	using namespace Options;
	interface->reset();
	int fd = execute::start_new_private_game( playerName( player_id::self ), playerName( player_id::right ), playerName( player_id::front ), playerName( player_id::left ) );
	if ( !fd ) {
		KMessageBox::error( this, i18n( "Problem starting a new game.\nThis is most likely an installation problem." ) );
	} else {
		connected_to_server( fd );
	}
}

void HumanClient::privateGame()
{
	interface->reset();
	PrivateGameDialog* p = new PrivateGameDialog();
	connect( p, SIGNAL( connected_to( int ) ),  SLOT( connected_to_server( int ) ) );
	p->selfName->setText( Options::playerName( player_id::self ) );
	p->selfName_2->setText( Options::playerName( player_id::self ) );

        const char* error = 0;
        char buffer[ 128 ];
        if ( !gethostname( buffer, sizeof( buffer ) ) ) {
               if ( struct hostent* host = gethostbyname( buffer ) ) {
                        p->message->setText(
                                i18n( "<qt>You hostname (and IP address) seem to be <nobr><strong>%1 (%2)</strong></nobr></qt>" )
                                        .arg( host->h_name )
                                        .arg( inet_ntoa( *reinterpret_cast<struct in_addr *>( host->h_addr ) ) ) );
               } else {
                       error = hstrerror( h_errno );
               }
        } else {
                error = strerror( errno );
        }
        if ( error ) {
                p->message->setText( i18n( "<qt>Error guessing host address:<nobr><strong>%1</strong></nobr></qt>" )
                        .arg( error ) );
        }
	p->exec();
}

void HumanClient::heartsNetwork()
{
	interface->reset();
	NetworkDialog* h = new NetworkDialog;
	h->exec();
}

void HumanClient::preferencesDialog()
{
	LOG_PLACE_NL();
	if (!preferences_) preferences_ = new PreferencesDialog(this);
	QTimer::singleShot(0, preferences_, SLOT(exec()));
}
#include "humanclient.moc"

