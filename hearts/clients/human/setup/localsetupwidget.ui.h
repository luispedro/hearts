/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/


QString LocalSetupWidget::selfName() const
{
	return self_->text();
}




QString LocalSetupWidget::rightName() const
{
	return right_->text();
}



QString LocalSetupWidget::leftName() const
{
	return left_->text();
}



QString LocalSetupWidget::frontName() const
{
	return front_->text();
}
