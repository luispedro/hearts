#include "serveraddressdialog.h"
#include "general/widget_placement.h"
#include "communication/open_connections.h"

#include <klocale.h>

#include <algorithm>


ServerAddressDialog::ServerAddressDialog(const QString& def, QWidget* p, const char* n)
		:QDialog(p,n),
		 text(new QLabel(i18n("Please enter the address of the server"),this)),
		 address(new QLineEdit(def,this)),
		 connectButton(new QPushButton(i18n("Connect"),this))
{
		text->move(10,10);
		text->resize(text->sizeHint());
		address->move(10,below(text) + 10);
		address->resize(address->sizeHint());
		connectButton->move(10, below(address) + 10);
		setMinimumSize(10 + std::max(text->width(),address->width()),below(connectButton));
		QObject::connect(connectButton,SIGNAL(clicked()),this,SLOT(connect()));
}

void ServerAddressDialog::connect()
{
	int fd = open_client_connection(address->text().latin1());
	close();
	emit connected(fd);
}

#include "serveraddressdialog.moc"
