#ifndef NETWORKCONNECTION_H
#define NETWORKCONNECTION_H
class NetworkConnection : public QObject 
{
	public:
		NetworkConnection( const char* server, short port, QObject* parent, const char * name = "network-connection" );

	public slots:
		void connectTo( const char* , short );
		void connectionError( QString errorStr, int errno );
		void serverError( QString errorStr );

	private:
		KExtendedSocket* socket_;
};

#endif // NETWORKCONNECTION_H
