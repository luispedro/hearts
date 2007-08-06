/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you want to add, delete, or rename functions or slots, use
** Qt Designer to update this file, preserving your code.
**
** You should not define a constructor or destructor in this file.
** Instead, write your code in functions called init() and destroy().
** These will automatically be called by the form's constructor and
** destructor.
*****************************************************************************/


#include "general/helper.h"
#include <klineeditdlg.h>

void NetworkDialog::newTable_clicked()
{
	KLineEditDlg l( i18n( "New Table" ), "", 0L );
	l.setCaption( i18n( "Create New Table" ) );
	//text is empty so disable ok button.
	l.enableButtonOK( false );
	if ( l.exec() == KLineEditDlg::Accepted ) emit newTable( l.text() );
}


void NetworkDialog::lookAt( QString table, QString p1, QString p2, QString p3, QString p4 )
{
	LOG_PLACE_NL();
	QListViewItem* tableView = tables->findItem( table, 0 );
	if ( tableView ) {
		tables->takeItem( tableView );
		delete table;
	}
	tableView = new QListViewItem( tables, table, p1, p2, p3, p4 );
	tables->insertItem( tableView );
}

void NetworkDialog::joinTable_clicked()
{
 QListViewItem * current = tables->currentItem();
 if ( !current ) return ;
 QString tableName = current->text( 0 );
 massert( !tableName.isNull() );
 emit joinTable( tableName );
}


void NetworkDialog::activateJoin()
{
    joinTableButton->setEnabled(true);
}

void NetworkDialog::userStatus( QString u, int st )
{
   (void)st;
 int idx = usertable->numRows();
    usertable->setNumRows( idx + 1 );
    usertable->setText( idx, 0, u);
    usertable->setText( idx, 1, i18n( "Online"));

}


void NetworkDialog::accept()
{
    this->QDialog::accept();
}
