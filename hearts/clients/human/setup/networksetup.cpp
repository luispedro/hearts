#include "networksetup.h"

#include <qlistview.h>
#include <qtimer.h> // singleShot
#include <qpushbutton.h>
#include <kextsock.h>
#include <klocale.h>
#include <kmessagebox.h>
#include <klineeditdlg.h>
#include <klineedit.h>
#include <kdebug.h>

#include <unistd.h>

#include <cassert>

#include "networksetupwidget.h"
#include "exec.h"
#include "general/helper.h"
#include "communication/open_connections.h"
#include "network/constants.h"
#include "../options.h"

NetworkSetup::NetworkSetup( QWidget* parent, const char* name )
		: QWidget( parent, name ),
		widget_( new NetworkSetupWidget( this ) ),
		connection_( 0 ),
		connecting_( 0 ),
		good_( true )
{
	setMinimumSize( 150, 350 );
	openConnection( Network::Server, Network::Port );

	connect( widget_, SIGNAL( joinTable( QString ) ), connection_, SLOT( joinTable( QString ) ) );
	connect( widget_, SIGNAL( createNewTable() ), SLOT( newTable() ) );

	widget_->server->insert( Network::Server );
	widget_->port->insert( QString::number( Network::Port ) );

	//FIXME remove lines below and implement functionality:
	widget_->server->setEnabled( false );
	widget_->port->setEnabled( false );
	widget_->changeServer->setEnabled( false );
}

NetworkSetup::~NetworkSetup()
{
	LOG_PLACE_NL();
}

void NetworkSetup::openConnection( const char* server, short port )
{
	kdDebug() << "NetworkSetup::openConnection( " << server << ':' << port << " )" << endl;
	KExtendedSocket * socket = new KExtendedSocket( server, port );
	if ( socket->connect() < 0 ) {
		KMessageBox::error( this, i18n( "<qt>Error connecting to Hearts Server:<br><strong>%1</strong></qt>" )
				.arg( KExtendedSocket::strError( socket->socketStatus(), socket->systemError() ) ) );
		good_ = false;
		return;
	}
	
	kdDebug() << "NetworkSetup::NetworkSetup() fd = " << socket->fd() << endl;

	delete connection_; // possibly 0
	connection_ = new Network::UserConnection( socket, this );
	connect( connection_, SIGNAL( connectTo( const char*, short ) ), SLOT( connectTo( const char*, short ) ) );
	connect( connection_, SIGNAL( lookAt( QString, PlayerInfo, PlayerInfo, PlayerInfo, PlayerInfo ) ),
			 SLOT( lookAt( QString, PlayerInfo, PlayerInfo, PlayerInfo, PlayerInfo ) ) );
	connect( connection_, SIGNAL( startGame( short ) ),
			 SLOT( startGame( short ) ) );
	connect( connection_, SIGNAL( protocolChanged() ),
			 SLOT( protocolChanged() ) );

	QString playerName = Options::playerName( player_id::self );
	connection_->hello( playerName );
}



void NetworkSetup::newTable()
{
	KLineEditDlg l( i18n( "New table:" ), "", 0L );
	l.setCaption( i18n( "Create New Table" ) );
	//text is empty so disable ok button.
	l.enableButtonOK( false );
	if ( l.exec() == KLineEditDlg::Accepted ) connection_->createTable( l.text() );
}

void NetworkSetup::execute()
{
	LOG_PLACE_NL();
}

void NetworkSetup::connectTo( const char* ip, const short port )
{
	LOG_PLACE() << ' ' << ip << ':' << port << '\n';
	widget_->setEnabled( false );
	delete connecting_;
	connecting_ = new KProgressDialog( this, "connecting-progress", i18n( "Connecting...." ), i18n( "Connecting...." ) );
	connecting_->setAllowCancel( false );
	connecting_->setMinimumDuration( 10 );
	connecting_->show();
	delayedIp = QString::fromLatin1( ip );
	delayedPort = port;
	QTimer::singleShot( 5 * 1000, this, SLOT( delayedConnectTo() ) );
}

void NetworkSetup::delayedConnectTo()
{
	const char * const ip = delayedIp.latin1();
	const short port = delayedPort;
	int fd = open_client_connection( ip, port );
	delete connecting_;
	connecting_ = 0;
	emit connected( fd );
}

void NetworkSetup::startGame( short port )
{
	execute::server( port );
	connectTo( "127.0.0.1", port );
}

void NetworkSetup::protocolChanged()
{
	QTimer::singleShot( 5 * 1000, this, SLOT( delayedProtocolChanged() ) );
}

void NetworkSetup::delayedProtocolChanged()
{
	kdDebug() << "NetworkSetup::delayedProtocolChanged()" << endl;
	KExtendedSocket* socket = connection_->socket();
	assert( socket );
	int stat = socket->socketStatus();
	int fd = socket->fd();

	kdDebug() << KExtendedSocket::strError( socket->socketStatus(), socket->systemError() ) << " fd : " << fd << endl;
	if ( stat == KExtendedSocket::error ) {
		KMessageBox::error( 0, i18n( "<qt>Connection Error:<br><strong>$1</strong></qt>" )
				.arg( KExtendedSocket::strError( socket->socketStatus(), socket->systemError() ) ) );
	} else {
		assert( fd > 0 );
		socket->release();
		kdDebug() << "NetworkSetup::delayedProtocolChanged() writing a zero on fd " << fd << endl;
		const char c = 0;
		::write( fd, &c, 1 );
		emit connected( fd );
	}
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
