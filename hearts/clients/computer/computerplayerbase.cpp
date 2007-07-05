/***************************************************************************
                     computerplayerbase.cpp  -  description
                        -------------------
begin                : Tue Oct 10 2000
copyright            : (C) 2000 by Luis Pedro Coelho
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

#include "computerplayerbase.h"
#include "general/min_time.h"
#include "hearts/cards.h"

#include <iterator>


void ComputerPlayerBase::inform( const Card c, const player_id::type from )
{
	LOG_PLACE() << ' ' << from << " played " << c << ".\n";
	table_.add( c );
	if ( c == Cards::spadesQueen ) {
		queenOut_ = true;
	}
	if ( c.suit() == Card::hearts ) {
		if ( doingItAll() == none ) {
			switch ( from ) {
#define CASE(x) \
                                        case player_id::x: \
                                                whoDoingItAll = x;\
                                                break;

				CASE( self )
				CASE( right )
				CASE( left )
				CASE( front )
				default:
				massert( 0 );
			}
		} else if ( doingItAll() != static_cast<ComputerPlayerBase::doingItAll_t>( static_cast<int>( from ) ) ) { // the cast works because of the way ComputerPlayerBase::doingItAll_t is defined
			whoDoingItAll = impossible;
		}
	}
	if ( table_.state().size() == 1 ) {
		push_ = c.suit();
		++suitInfo[ c.suit() ].played;
	} else {
		if ( push() != c.suit() )
			suitInfo[ c.suit() ].skipped = true;
	}
	if ( from == player_id::self ) {
		if ( std::find_if( handBegin(), handEnd(), OfSuite( c.suit() ) ) == handEnd() )
			suitInfo[ c.suit() ].hasIt = false;
	}
	if ( c.suit() == Card::spades and c.value() >= Card::king and from == player_id::self ) {
		hasHighSpades_ = false;
		if ( std::find( handBegin(), handEnd(), Cards::spadesKing ) != handEnd() or
				std::find( handBegin(), handEnd(), Cards::spadesAce ) != handEnd() ) {
			hasHighSpades_ = true;
		}
	}
	if ( table_.full() ) {
		if ( std::count_if( handBegin(), handEnd(), not1( OfSuite( c.suit() ) ) ) == 3 ) {
			suitInfo[ c.suit() ].skippedAll = true;
		}
		handIsOver();
	}
}

void ComputerPlayerBase::hand_end()
{
	LOG_PLACE_NL();
	table_.reset();
}


Card ComputerPlayerBase::play()
{
#ifndef DEBUG
	MinTime m( 650 * 1000 );
#endif

	handIterator resIter;
	if ( table_.state().empty() ) {
		resIter = playStart();
	} else if ( std::find_if ( hand.begin(), hand.end(), OfSuite( table_.state().front().suit() ) ) != hand.end() ) {
		resIter = playAssist();
	} else {
		resIter = playNotAssist();
	}
	massert ( resIter >= handBegin() and resIter < handEnd() );
	return remove( resIter );
}

/** If !suitHasIt(s) return handEnd() else return highestCardOf(s) */
ComputerPlayerBase::handIterator ComputerPlayerBase::highestOf( Card::suit_t s ) const
{
	LOG_PLACE() << ", this = " << this << " looking for: " << s << ".\n";
	if ( !suitHasIt( s ) ) {
		LOG_PLACE() << " doesn't have " << s << "," << hand.size() << ".\n";
		return handEnd();
	}
	//        std::sort(const_cast<Card*>(hand.begin()),const_cast<Card*>(hand.end()));
	// remember the order in which the vector is: by suits and then by values.
	handIterator res = std::find_if( handBegin(), handEnd(), OfSuite( s ) );
	//        std::copy(handBegin(),handEnd(),ostream_iterator<Card>(std::cerr,","));
	//        std::cerr << std::endl;
	massert( res != handEnd() );
	while ( ( res + 1 ) != handEnd() and ( res + 1 ) ->suit() == s )
		++res;
	LOG_PLACE() << " found " << *res << ".\n";
	return res;
}

/**  */
void ComputerPlayerBase::reset()
{
	table_.reset();
	hand.clear();
	queenOut_.reset();
	hasQueen_.reset();
	heartsPlayed_.reset();
	hasHighSpades_.reset();
	whoDoingItAll.reset();
	// push_ doesn't matter
	const Card::suit_t suits[] = {
									 Card::hearts, Card::spades, Card::clubs, Card::diamonds
								 };
	for ( const Card::suit_t * s = suits; s != suits + 4; ++s ) {
		suitInfo[ *s ].reset();
	}
}

Holder3 ComputerPlayerBase::give()
{
	Holder3 res;
	while ( !res.full() ) {
		res.push( remove
					  ( this->giveOne() ) );
	}
	return res;
}

ComputerPlayerBase::doingItAll_t ComputerPlayerBase::doingItAll() const
{
	return whoDoingItAll;
}

void ComputerPlayerBase::receive( Card c )
{
	suitInfo[ c.suit() ].hasIt = true;
	if ( c == Card( Card::spades, Card::queen ) )
		hasQueen_ = true;
	if ( ( c.suit() == Card::spades ) and ( c.value() == Card::ace or c.value() == Card::king ) ) {
		hasHighSpades_ = true;
	}
	hand.insert( std::lower_bound( hand.begin(), hand.end(), c ), c );
	assertInvariants();
}

/** This removes the card pointed by its arg, which must not be handEnd().
It makes sure that the invariants are maintained. */
Card ComputerPlayerBase::remove
	( handIterator p )
{
	massert ( p >= handBegin() and p < handEnd() );
	Card res = *p;
	hand.erase( hand.begin() + ( p - hand.begin() ) );
	//hand.erase(const_cast<vector<Card>::iterator>(p));
	if ( res.suit() == Card::spades ) {
		if ( res.value() == Card::queen )
			hasQueen_ = false;
		if ( res.value() >= Card::king ) {
			hasHighSpades_ = ( std::find( handBegin(), handEnd(), Card( Card::spades, Card::king ) ) != handEnd() or
							   std::find( handBegin(), handEnd(), Card( Card::spades, Card::ace ) ) != handEnd() );
		}
	}
	suitInfo[ res.suit() ].hasIt = std::find_if( handBegin(), handEnd(), OfSuite( res.suit() ) ) != handEnd();
	return res;
}
/** This tries to check as many facts as possible. */
void ComputerPlayerBase::assertInvariants()
{
	Card::suit_t suits[] = { Card::spades, Card::hearts, Card::diamonds, Card::clubs};
	for ( Card::suit_t * suit = suits; suit != suits + 4; ++suit ) {
		if ( suitInfo[ *suit ].hasIt and std::find_if( handBegin(), handEnd(), OfSuite( *suit ) ) == handEnd() ) {
			LOG_PLACE() << " suitInfo says we've got " << *suit << " but hand = ";
			std::copy( handBegin(), handEnd(), std::ostream_iterator<Card>( std::cerr, " " ) );
			massert( 0 );
		} else if ( !suitInfo[ *suit ].hasIt and std::find_if( handBegin(), handEnd(), OfSuite( *suit ) ) != handEnd() ) {
			LOG_PLACE() << " suitInfo says we haven't got " << *suit << " but hand = ";
			std::copy( handBegin(), handEnd(), std::ostream_iterator<Card>( std::cerr, " " ) );
			massert( 0 );
		}
	}
	if ( hasHighSpades() ) {
		massert( std::find( handBegin(), handEnd(), Card( Card::spades, Card::king ) ) != handEnd() or
				 std::find( handBegin(), handEnd(), Card( Card::spades, Card::ace ) ) != handEnd() );
	}
	if ( hasQueen() ) {
		massert( std::find( handBegin(), handEnd(), Card( Card::spades, Card::queen ) ) != handEnd() );
	}
	std::vector<Card> tmp = hand;
	std::sort( tmp.begin(), tmp.end() );
	massert( tmp == hand );
}

Card ComputerPlayerBase::winningCardOnTable() const {
	Card res = table_.state().front();
	for (std::vector<Card>::const_iterator first = table_.state().begin(), past = table_.state().end(); first != past; ++first) {
		if (first->suit() == push() && first->value() > res.value()) res = *first;
	}
	return res;
}
