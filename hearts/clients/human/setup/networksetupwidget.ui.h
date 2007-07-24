/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/

#include <klineedit.h>

void NetworkSetupWidget::changeServer_clicked()
{
 emit serverChange( server->text() );
}

void NetworkSetupWidget::join_clicked()
{
 QListViewItem * current = tables->currentItem();
 if ( !current )
  return ;
 QString tableName = current->text( 0 );
 massert( !tableName.isNull() );
 emit joinTable( tableName );
}


void NetworkSetupWidget::newTable_clicked()
{
 emit createNewTable();
}


void NetworkSetupWidget::clearTables()
{
 tables->clear();
}


void NetworkSetupWidget::insertTable( QListViewItem * t )
{
 tables->insertItem( t );
}

void NetworkSetupWidget::server_returnPressed( const QString & )
{
 emit serverChange( server->text() );
}

void NetworkSetupWidget::activateJoin()
{
    join->setEnabled( true );
}

