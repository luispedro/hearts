#include "networkmanager.h"
#include "networkdialog.h"
#include "options.h"
#include "general/helper.h"
#include "network/connection.h"
#include "network/authentication.h"

#include <qlabel.h>
#include <kmessagebox.h>
#include <klocale.h>
#include <kextsock.h>
#include <kio/passdlg.h>

NetworkManager::NetworkManager( NetworkDialog* dialog, Network::UserConnection* c, QObject* parent, const char* name):
	QObject(parent,name),
	dialog_(dialog),
	networkconnection_(c),
	forceauthentication_(false)
{
	connect( networkconnection_, SIGNAL( protocolChanged() ), SLOT( protocolChanged() ) );
	connect( networkconnection_, SIGNAL( authQ( const QCString&, const QCString& ) ),
			SLOT( doAuthentication( const QCString&, const QCString& ) ) );
	connect( networkconnection_, SIGNAL( error( Network::Message::errorType, const QString& ) ),
			SLOT( error( Network::Message::errorType, const QString& ) ) );

	connect( networkconnection_, SIGNAL( lookAt( QString, QString, QString, QString, QString ) ),
			 dialog_, SLOT( lookAt( QString, QString, QString, QString, QString ) ) );
	connect( networkconnection_, SIGNAL( motd( const QString& ) ),
			dialog_->motd, SLOT( setText( const QString& ) ) );

	connect( networkconnection_, SIGNAL( userStatus( QString, user_status::type ) ),
	 		SLOT( userStatus( QString, user_status::type ) ) );
	connect( dialog_, SIGNAL( newTable( QString ) ), networkconnection_, SLOT( createTable( QString ) ) );
	connect( dialog_, SIGNAL( joinTable( QString ) ), networkconnection_, SLOT( joinTable( QString ) ) );

}

NetworkManager::~NetworkManager()
{
	delete networkconnection_;
}

void NetworkManager::doAuthentication(const QCString& method, const QCString& cookie)
{
	LOG_PLACE() << " cookie: -" << cookie << "-\n";
	Network::repeatedMD5Authenticator authenticator;
	if ( method != authenticator.id() ) {
		KMessageBox::error( dialog_, QString::null,
			i18n( "Unkown authentication method: '%1'.\nThis is probably a version mismatch between your installed version of hearts and the network server.\nPlease consider upgrading your version of hearts." ) );
		return;
	}
	Options::Account& network = Options::getNetwork();
	QCString password = network.password();
	if ( password.isNull() || forceauthentication_ ) {
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
		forceauthentication_ = false;
	}
	char* result;
	LOG_PLACE() << "PASSWORD: \'" << password << "\'\n";
	authenticator.generate( password, cookie, &result );
	networkconnection_->authR( cookie, result );
	free( result );
	LOG_PLACE_NL();
}

void NetworkManager::error(Network::Message::errorType e, const QString& msg)
{
	KMessageBox::error(0, i18n("<qt>Error from server:<strong>%1</strong></qt>" ).arg(msg));
}

void NetworkManager::userStatus(QString u, user_status::type t)
{
	dialog_->userStatus(u,int(t));
}

void NetworkManager::protocolChanged()
{
	LOG_PLACE_NL();
	KExtendedSocket* socket = networkconnection_->socket();
	assert( socket );
	int stat = socket->socketStatus();
	int fd = socket->fd();

	if ( stat == KExtendedSocket::error ) {
		KMessageBox::error( 0, i18n( "<qt>Connection Error:<br><strong>%1</strong></qt>" )
				.arg( KExtendedSocket::strError( socket->socketStatus(), socket->systemError() ) ) );
	} else {
		assert( fd > 0 );
		socket->release();
		LOG_PLACE()  << " writing a zero on fd " << fd << '\n';
		const char c = 0;
		::write( fd, &c, 1 );
		emit connected_to( fd );
	}
}

