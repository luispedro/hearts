#ifndef _HOME_LUIS_HEARTS_NETWORK_SERVER_H
#define _HOME_LUIS_HEARTS_NETWORK_SERVER_H
#include <qobject.h>
#include <kextsock.h>

class Table;
class Server : public QObject
{
	Q_OBJECT
	public:
		Server(QObject* parent);

	public slots:
		void acceptSlot();
		void tableFull( Table* );
		void createTable( QString );
		void joinTable( QString );
		void connectionError( const char*, int );

	private:
		void newConnection( int );
		void showTable( Table* );
	private:
		KExtendedSocket socket_;
};
#endif // _HOME_LUIS_HEARTS_NETWORK_SERVER_H

