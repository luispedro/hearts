/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/

#include "network/player_status.h"
#include <qstring.h>

void OnlinePlayersWidget::addPlayer( QString name, player_status::type s )
{
	int idx = table->numRows();
    table->setNumRows( idx + 1 );
    table->setText( idx, 0, name);
    table->setText( idx, 1, i18n( "Online"));
}


void OnlinePlayersWidget::setStatus( QString name, player_status::type s )
{

}
