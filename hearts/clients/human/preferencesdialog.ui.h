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

#include "options.h"

void PreferencesDialog::init()
{
    using namespace Options;
    selfName->setText(playerName(player_id::self));
    rightName->setText(playerName(player_id::right));
    frontName->setText(playerName(player_id::front));
    leftName->setText(playerName(player_id::left));

    const Account& n = getNetwork();
    server->setText( n.host() );
    username->setText( n.login() );
    password->setText( n.password() );
}




void PreferencesDialog::saveback()
{
    using namespace Options;
#define SAVE( x ) savePlayerName( player_id::x, x ## Name->text() )
    SAVE(self);
    SAVE(right);
    SAVE(front);
    SAVE(left);

    Account& n = getNetwork();
    n.saveHost( server->text() );
    n.saveLogin( username->text() );
    n.savePassword( password->text().utf8() );
}


void PreferencesDialog::accept()
{
    saveback();
    this->QDialog::accept();
}
