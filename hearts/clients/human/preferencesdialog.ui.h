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
    selfName->setText(Options::playerName(player_id::self));
    rightName->setText(Options::playerName(player_id::right));
    frontName->setText(Options::playerName(player_id::front));
    leftName->setText(Options::playerName(player_id::left));
}




void PreferencesDialog::saveback()
{
    using namespace Options;
#define SAVE( x ) savePlayerName( player_id::x, x ## Name->text() )
    SAVE(self);
    SAVE(right);
    SAVE(front);
    SAVE(left);
}


void PreferencesDialog::accept()
{
    saveback();
    this->QDialog::accept();
}
