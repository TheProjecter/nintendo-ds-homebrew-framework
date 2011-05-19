#ifndef E_STATES_H
#define E_STATES_H

/*
	Crabby tennis specific enum's

	The game is a little to simple to warrant a state machine
*/

namespace tennis
{
	// tennis specific object states
	enum object_states
	{
		states_inplay = 0x00000,
		states_p1serve = 0x00002,
		states_p2serve = 0x00004,
		states_beforeplay = 0x00006
	};

	// tennis specific game states
	enum game_states
	{
		sub_inplay = 0x00000,
		sub_beforeplay = 0x00002,
		sub_gameover = 0x00004,
		sub_paused = 0x00006
	};
}

#endif