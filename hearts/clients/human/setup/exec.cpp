#include "exec.h"
#include "general/helper.h"
#include "communication/constants.h"

#include <kprocess.h>
#include <qstring.h>
#include <qstringlist.h>

#include "communication/constants.h"


std::ostream& operator<<(  std::ostream& s, const QValueList<QCString>& l )
{
	QValueList<QCString>::const_iterator it = l.begin();
	for (  ; it != l.end(); ++it )
		s << '\"' << ( *it ) << "\" "; 
	return s;
}


bool execute_server()
{
	return execute_server( Communication::Port );
}

bool execute_server( short port )
{
	KProcess p;
	p << "heartsserver" 
		<< "--tcp_port" << QString::number( port ) 
		<< "--unix_port" << local_address
		<< "--wait-zero";

	LOG_PLACE() << '!' << p.args() << "!\n";
	return p.start(KProcess::DontCare);
}


bool execute_computer_client(QString name)
{
	KProcess p;
	p << "heartscomputerclient"
		<< "--playername" << name
		<< "--address" << local_address
		<< "--zero";
	LOG_PLACE() << '!' << p.args() << "!\n";
	return p.start(KProcess::DontCare);
}


