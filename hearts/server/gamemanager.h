#ifndef DB_GAMEMANAGER_H_INCLUDE_GUARD_
#define DB_GAMEMANAGER_H_INCLUDE_GUARD_

#include "player.h"
#include "table.h"

#include "hearts/player_id.h"
#include "hearts/player_status.h"
#include "hearts/card.h"
#include "general/auto_init.h"
#include "general/circular_iterator.h"

#include <set>
#include <vector>

/** This manages the game state.
  * Some terminology:
  *		- Move: one player plays one card
  * 	- Hand: four moves in which each player plays one card
  *		- Game: thirteen hands. A Game starts when all the cards are distributed and ends when the players run
  * run out of cards.
  *		- Match: several games until one player reaches a maximum number of points.
  */

class GameManager {
	public:
	/** This is going to stay a typedef for Player::playedby_t, so you can count on that. Of course, whether right et al make 
		sense as names is a complicated question, but it is sometimes usefull. At other times, just don't think of what 
		they mean as words.
	  */
		typedef player_id::type player_id_type;

		GameManager();
		~GameManager();

	/** This registers a player. It is a post-contructor.
		I used to do this in the constructor, which meant the constructor took four parameters. It was somewhat confusing, so I changed
		it to this.

		This may only be called if the object has just been constructed, but can_start_game() is still false, i.e. you haven't called it
		yet with four different ids.
		
		If you call it twice with the same id, it will just forget the old registering.
	*/
		void register_player(Player&,player_id_type);
		
	/** Sets everyone's points to zero. 
		Currently, you shouldn't call it if there is a game going on.
		This might change in the future or I'll add a new function to interrupt games.
	  */
		void reset_match();
		
	/** Getter method. */
		unsigned points(player_id_type) const;

	/** This starts a game. 
		Note that it runs alone, provided that players reply to their queries.
		Can only be called if can_start_game() is true.
	 */
		void start_game();

	/** This registers an object to call back on when a game is over.
		The object must have an accessible operator() and be copyable. A function pointer is an example.
	  */
		template <typename T>
		void register_game_over_callback(const T& callb_obj)
		{
			game_over_callback = new functor0<T>(callb_obj);
		}

	private:

	// Get the information from the players:
		class Receiver;

		friend class Receiver;

		void play_reply(player_id_type,const Card&);
		void give3_reply(player_id_type,const Holder3&);
		
	// Member data:
		struct Player_Control {
			explicit Player_Control(Player* pl = 0):player(pl)  { }
			Player* player;
			auto_init<unsigned> points;
			std::set<Card> hand;
			std::set<Card> gotten;
		};

		typedef std::vector<Player_Control> control_cont_type;
		control_cont_type players;

		typedef circular_iterator<std::vector<Player_Control>::iterator> circler;
		circler to_move;

	/** These are the cards that the players have given. It only makes sense when current_state == WaitGive3 and
	  * some players have already replied
	  */
		typedef std::vector< std::vector<Card> > given_cont_type;
		given_cont_type given_cards;

		enum State { 
				Init, // we are waiting for players to register
				Idle, // players have registered, waiting for start_game()
				WaitGive3, // waiting for players to give cards
				WaitPlay // waiting for players to play
		};
		State current_state;

		struct functor0_base {
			virtual void operator()() = 0;
		};
		template <typename T>
		struct functor0 : functor0_base {
			functor0(const T& o):obj(o) { }
	
			virtual void operator()()
				{	obj(); }
			private:
				T obj;
		};
		
		functor0_base* game_over_callback;
		auto_init<unsigned> number_games;
		auto_init<bool,false> hearts_been_played;
		Table table;
	
		// These are implementation functions. 

		/** Starts the first hand of a game. */
		void start_first_hand();
		/** Distributes cards before a game. */
		void give_cards();
		/** Distributes the cards that the players have given */
		void distribute_cards();
		/** Asks the players to give cards before a game (if necessary). */
		bool ask_for_cards();
		/** Warns all the other players about a move to be made. */
		void warn_about_move(Card);
		/** Calls current_status(s) on every player */
		void status_every_player(player_status::type);
		/** Cleans things up */
		void hand_end();
		/** At the end of a game, assigns the points to the players. */
		void assign_points();
		/** This validates a move from the to_move player. If it is valid, returns null, else returns an
			error message. */
		const char* validate(const Card&) const;
		/** Prepares for a new game. */
		void reset_game_data();
		/** Returns whether the player has a suite. */
		bool has_suite(const Player_Control&,Card::suit_t) const;

		enum {
			   	unknown_error,	
				dont_have_card, 
				play_two, 
				no_points,
				no_hearts,
			   	must_assist_clubs, 
				must_assist_hearts, 
				must_assist_spades, 
				must_assist_diamonds 
		};
		static unsigned suit_to_enum(Card::suit_t);

		static const char* error_msgs[];

};



class GameManager::Receiver : public Player::Receiver {
	public:
		Receiver(GameManager& p,player_id::type i)
			:parent(p),
			 id(i)
		{
		}

		virtual void play_reply(Card c)
		{
			parent.play_reply(id,c);
		}

		virtual void give_reply(const Holder3& h)
		{
			parent.give3_reply(id,h);
		}

	private:
		GameManager& parent;
		const player_id::type id;
};

/** @return maximum number of points a player has */
unsigned most_points(const GameManager&);
/** @return the id of the player with the minimum points */
player_id::type winner(const GameManager&);
						



#endif /* DB_GAMEMANAGER_H_INCLUDE_GUARD_ */
