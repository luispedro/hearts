#include "exec.h"
#include <kprocess.h>
#include <qstring.h>

#include "communication/constants.h"

bool execute_server()
{
	return execute_server( Communication::Port );
}

bool execute_server( short port )
{
	KProcess p;
	p << "heartsserver" << QString::number( port );
	return p.start(KProcess::DontCare);
}


bool execute_computer_client(QString name)
{
	KProcess p;
	p << "heartscomputerclient" << "--playername" << name;
	return p.start(KProcess::DontCare);
}


