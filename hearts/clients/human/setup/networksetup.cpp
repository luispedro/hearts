#include "networksetup.h"

#include <qlistview.h>
#include <qtimer.h>
#include <qpushbutton.h>
#include <kextsock.h>
#include <klocale.h>
#include <kmessagebox.h>
#include <klineeditdlg.h>
#include <klineedit.h>

#include <string.h>
#include <errno.h>
#include <unistd.h>

#include "networksetupwidget.h"
#include "exec.h"
#include "general/widget_placement.h"
#include "general/helper.h"
#include "communication/open_connections.h"
#include "network/constants.h"
#include "../options.h"

NetworkSetup::NetworkSetup( QWidget* parent, const char* name )
		: QWidget( parent, name ),
		widget_( new NetworkSetupWidget( this ) ),
		connection_( 0 ),
		good_( true )
{
	KExtendedSocket * socket = new KExtendedSocket( Network::Server, Network::Port );
	if ( socket->connect() < 0 ) {
		KMessageBox::error( this, i18n( "Error connecting to Hearts Server: %1" ).arg( strerror( errno ) ) );
		good_ = false;
	}
	connection_ = new Network::UserConnection( socket, this );
	setMinimumSize( 150, 350 );
	connect( widget_, SIGNAL( joinTable( QString ) ), connection_, SLOT( joinTable( QString ) ) );
	connect( widget_, SIGNAL( createNewTable() ), SLOT( newTable() ) );

	connect( connection_, SIGNAL( connectTo( const char*, short ) ), SLOT( connectTo( const char*, short ) ) );
	connect( connection_, SIGNAL( lookAt( QString, PlayerInfo, PlayerInfo, PlayerInfo, PlayerInfo ) ),
			 SLOT( lookAt( QString, PlayerInfo, PlayerInfo, PlayerInfo, PlayerInfo ) ) );
	connect( connection_, SIGNAL( startGame( short ) ),
			 SLOT( startGame( short ) ) );
	connect( connection_, SIGNAL( protocolChanged() ),
			 SLOT( protocolChanged() ) );

	QString playerName = Options::playerName( player_id::self );
#ifdef DEBUG

	playerName += QString::fromLatin1( "%1" );
	playerName.arg( getpid() );
#endif

	connection_->hello( playerName );
	widget_->connectingBox->hide();
	widget_->server->insert( Network::Server );
	widget_->port->insert( QString::fromLatin1( "%1" ).arg( Network::Port ) );

	//FIXME remove lines below and implement functionality:
	widget_->server->setEnabled( false );
	widget_->port->setEnabled( false );
	widget_->changeServer->setEnabled( false );
}

NetworkSetup::~NetworkSetup()
{
	LOG_PLACE_NL();
}


void NetworkSetup::newTable()
{
	KLineEditDlg l( i18n( "New table:" ), "", 0L );
	l.setCaption( i18n( "Create New Table" ) );
	//text is empty so disable ok button.
	l.enableButtonOK( false );
	l.exec();

	connection_->createTable( l.text() );
}

void NetworkSetup::execute()
{
	LOG_PLACE_NL();
}

void NetworkSetup::connectTo( const char* ip, const short port )
{
	LOG_PLACE() << ' ' << ip << ':' << port << '\n';
	widget_->setEnabled( false );
	widget_->connectingBox->setEnabled( true );
	widget_->connectingBox->show();
	delayedIp = QString::fromLatin1( ip );
	delayedPort = port;
	QTimer::singleShot( 5 * 1000, this, SLOT( delayedConnectTo() ) );
}

void NetworkSetup::delayedConnectTo()
{
	const char * const ip = delayedIp.latin1();
	const short port = delayedPort;
	int fd = open_client_connection( ip, port );
	emit connected( fd );
}

void NetworkSetup::startGame( short port )
{
	execute_server( port );
	connectTo( "127.0.0.1", port );
}

void NetworkSetup::protocolChanged()
{
	QTimer::singleShot( 5 * 1000, this, SLOT( delayedProtocolChanged() ) );
}

void NetworkSetup::delayedProtocolChanged()
{
	int fd = connection_->socket() ->fd();
	connection_->socket() ->release();
	const char c = 0;
	::write( fd, &c, 1 );
	emit connected( fd );
}


void NetworkSetup::lookAt( QString table, QString p1, QString p2, QString p3, QString p4 )
{
	LOG_PLACE_NL();
	QListView* tables = widget_->tables;
	QListViewItem* tableView = tables->findItem( table, 0 );
	if ( tableView ) {
		tables->takeItem( tableView );
		delete table;
	}
	tableView = new QListViewItem( tables, table, p1, p2, p3, p4 );
	tables->insertItem( tableView );
}

#include "networksetup.moc"
