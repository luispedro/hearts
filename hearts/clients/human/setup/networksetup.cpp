#include "networksetup.h"

#include <qlistview.h>
#include <qtimer.h> // singleShot
#include <qpushbutton.h>
#include <qlabel.h>
#include <kextsock.h>
#include <klocale.h>
#include <kmessagebox.h>
#include <klineeditdlg.h>
#include <klineedit.h>
#include <kdebug.h>
#include <kio/passdlg.h>

#include <unistd.h>

#include <cassert>

#include "networksetupwidget.h"
#include "onlineplayerdialog.h"
#include "exec.h"
#include "general/helper.h"
#include "communication/open_connections.h"
#include "network/player_status.h"
#include "network/authentication.h"
#include "../options.h"

NetworkSetup::NetworkSetup( QWidget* parent, const char* name )
		: QWidget( parent, name ),
		widget_( new NetworkSetupWidget( this ) ),
		online_( new OnlinePlayersDialog( this ) ),
		connection_( 0 ),
		connecting_( 0 ),
		good_( false ),
		force_( false )
{
	setMinimumSize( 150, 350 );

	connect( widget_, SIGNAL( createNewTable() ), SLOT( newTable() ) );
	connect( widget_, SIGNAL( serverChange() ), SLOT( reconnect() ) );

	Options::Account& network = Options::getNetwork();

	widget_->server->insert( network.host() );
	widget_->port->insert( QString::number( network.port() ) );
	online_->setModal( false );
	openConnection( network.host(), network.port() );
	resetGUI( network.host() );
}

NetworkSetup::~NetworkSetup()
{
	LOG_PLACE_NL();
}

bool NetworkSetup::openConnection( const char* server, short port )
{
	kdDebug() << "NetworkSetup::openConnection( " << server << ':' << port << " )" << endl;
	KExtendedSocket * socket = new KExtendedSocket( server, port );
	if ( socket->connect() < 0 ) {
		KMessageBox::error( this, i18n( "<qt>Error connecting to Hearts Server:<br><strong>%1</strong></qt>" )
				.arg( KExtendedSocket::strError( socket->socketStatus(), socket->systemError() ) ) );
		return false;
	} else {
		good_ = true;
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

	connect( connection_, SIGNAL( playerStatus( QString, player_status::type ) ),
			SLOT( playerStatus( QString, player_status::type ) ) );
	connect( connection_, SIGNAL( motd( const QString& ) ),
			online_, SLOT( setMotD( const QString& ) ) );
	connect( connection_, SIGNAL( authQ( const QCString&, const QCString& ) ),
			SLOT( doAuthentication( const QCString&, const QCString& ) ) );
	connect( connection_, SIGNAL( error( Message::errorType, const QString& ) ),
			SLOT( error( Message::errorType, const QString& ) ) );

	connect( widget_, SIGNAL( joinTable( QString ) ), connection_, SLOT( joinTable( QString ) ) );

	QString playerName = Options::playerName( player_id::self );
	connection_->hello( playerName );
	return true;
}

void NetworkSetup::resetGUI( const char* server )
{
	widget_->tables->clear();
	online_->clear();
	
	//widget_->join->setEnabled( good_ && widget_->join->currentItem() );


	widget_->newTable->setEnabled( good_ );
	widget_->tables->setEnabled( good_ );
	if ( good_ ) online_->show();
	else online_->hide();

	widget_->state->setText( good_ ?
			// ( loggedIn ?
			//	i18n( "<qt>State: <b>Connected to %1 as %2</b></qt>" ).arg( server ).arg( username ) :
				i18n( "<qt>State: <b>Connected to %1 as guest</b></qt>" ).arg( server ) :
			//) :
			i18n( "<qt>State: <b>Not Connected</b></qt>" ) );
}



void NetworkSetup::doAuthentication( const QCString& method, const QCString& cookie )
{
	repeatedMD5Authenticator authenticator;
	if ( method != authenticator.id() ) {
		KMessageBox::error( widget_, QString::null, i18n( "Unkown authentication method" ) );
		return;
	}
	Options::Account& network = Options::getNetwork();
	QCString password = network.password();
	if ( password.isNull() || force_ ) {
		QString user = network.login();
		QString pass = QString::fromUtf8( password );
		if ( KIO::PasswordDialog::getNameAndPassword( user, pass, 0, i18n( "Login to hearts server" ) )
				== KDialogBase::Accepted ) {
			password = pass.utf8();
			network.saveLogin( user.utf8() );
			password = pass.utf8();
			network.savePassword( password );
		} else {
			KMessageBox::error( 0, i18n( "Need username and password for login" ) );
			return;
		}
		force_ = false;
	}
	char* result;
	kdDebug() << "PASSWORD: \'" << password << '\'' << endl;
	authenticator.generate( password, cookie, &result );
	connection_->authR( cookie, result );
	free( result );
	kdDebug() << "doAuthentication() done" << endl;
}

void NetworkSetup::error( Message::errorType error, const QString& msg )
{

	kdDebug() << "Got error " << ( int )error << ": " << msg;

	switch ( error ) {
		case Message::authenticationFailed: force_ = true;
						    break;
	}
}

void NetworkSetup::newTable()
{
	KLineEditDlg l( i18n( "New Table" ), "", 0L );
	l.setCaption( i18n( "Create New Table" ) );
	//text is empty so disable ok button.
	l.enableButtonOK( false );
	if ( l.exec() == KLineEditDlg::Accepted ) connection_->createTable( l.text() );
}

void NetworkSetup::reconnect()
{
	if ( openConnection( widget_->server->text().latin1(), widget_->port->text().toInt() ) ) {
		resetGUI( widget_->server->text().latin1() );
	}
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

void NetworkSetup::playerStatus( QString p, player_status::type s )
{
		kdDebug() << "NetworkSetup::playerStatus( " << p << ")" << endl;
		online_->addPlayer( p, s );
		LOG_PLACE()<< "status: " << s << "\n";
}

#include "networksetup.moc"
