#include "player_status.h"
#include <iostream>
#include <cassert>
#include <string>

#define ALL_CASES \
	CASE(wait_left)\
	CASE(wait_front)\
	CASE(wait_right)\
	CASE(game_over)\
	CASE(hand_over_self_win)\
	CASE(hand_over_right_win)\
	CASE(hand_over_front_win)\
	CASE(hand_over_left_win)

ostream& player_status::operator << (ostream& out, player_status::type s)
{
		switch (s)
		{
#define CASE(x) case player_status::x: out << #x; return out;
				ALL_CASES
#undef CASE
		}
		assert(0);
		return out;
}

istream& player_status::operator >> (istream& in, player_status::type& s)
{
		std::string str;
		in >> str;
#define CASE(x) else if (str == #x) { s = player_status::x; return in; }
		if (0);
		ALL_CASES
#undef CASE
		assert(0);
		return in;
}
