/***************************************************************************
                     pointsbox.cpp  -  description
                        -------------------
begin                : Fri Dec 31 1999
copyright            : (C) 1999 by Luis Pedro Coelho
email                : luis@luispedro.org
***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "pointsbox.h"
#include "general/helper.h"

#include <qlayout.h>
#include <kdebug.h>
#include <klocale.h>

#include <algorithm>

PointsBox::PointsBox( const char* name )
		: KDialogBase( 0,
						name,
						true, // modal
						i18n( "Points Standing" ), //caption
						KDialogBase::Ok, // buttonMask
						KDialogBase::Ok, // defaultButton
						true ), // separator
		widget_( new QWidget( this ) ),
		layout_( new QGridLayout( widget_, 1, 4 ) ),
		selfLastLabel_( 0 ),
		rightLastLabel_( 0 ),
		frontLastLabel_( 0 ),
		leftLastLabel_( 0 )
{
	this->setMainWidget( widget_ );

	layout_->setAutoAdd( true );
	layout_->setRowSpacing( 0, 32 );

	layout_->setColSpacing( 0, 128 );
	layout_->setColSpacing( 1, 128 );
	layout_->setColSpacing( 2, 128 );
	layout_->setColSpacing( 3, 128 );

	selfLabel_ = new QLabel( widget_ );
	selfLabel_->setAlignment( AlignRight );
	rightLabel_ = new QLabel( widget_ );
	rightLabel_->setAlignment( AlignRight );
	frontLabel_ = new QLabel( widget_ );
	frontLabel_->setAlignment( AlignRight );
	leftLabel_ = new QLabel( widget_ );
	leftLabel_->setAlignment( AlignRight );

}

PointsBox::~PointsBox()
{}

inline
unsigned max4( unsigned a, unsigned b, unsigned c, unsigned d )
{
	using std::max;
	return max( max( a, b ),
				max( c, d ) );
}

inline
unsigned min4( unsigned a, unsigned b, unsigned c, unsigned d )
{
	using std::min;
	return min( min( a, b ),
				min( c, d ) );
}


void PointsBox::insertLine( unsigned self, unsigned right, unsigned front, unsigned left )
{
	kdDebug() << "PointsBox::insertLine( "
	<< self << ", "
	<< right << ", "
	<< front << ", "
	<< left << " )" << endl;
#define CASE( x ) \
	do { \
		if ( x ## LastLabel_ ) x ## LastLabel_->setEnabled( false ); \
		const char* format = ( x == max4( self, right, front, left ) ? \
						"<qt text=\"blue\">%1</qt>" : \
						 ( x == min4( self, right, front, left ) ? \
						   "<qt text=\"red\">%1</qt>" : \
						   "%1" ) ); \
		x ## LastLabel_ = new QLabel( QString::fromLatin1( "%1" ).arg( x ), widget_ ); \
		/* FIXME The format is a good idea, but setEnabled( false ) messes it up */ \
		x ## LastLabel_->setAlignment( AlignRight ); \
		labels_.append( x ## LastLabel_ ); \
	} while ( 0 )

	CASE( self );
	CASE( right );
	CASE( front );
	CASE( left );
}

void PointsBox::setName( player_id::type who, QString name )
{
	using namespace player_id;
	switch ( who ) {
		case self:
		selfLabel_->setText( name );
		break;
		case right:
		rightLabel_->setText( name );
		break;
		case left:
		leftLabel_->setText( name );
		break;
		case front:
		frontLabel_->setText( name );
		break;
		default:
		massert( 0 );
	}
}

/** Clears all the displayed text. */
void PointsBox::clear()
{
	labels_.setAutoDelete( true );
	labels_.clear();
}

#include "pointsbox.moc"

