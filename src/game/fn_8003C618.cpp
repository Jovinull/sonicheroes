#include "types.h"
#include "game/effect/eff_bomb.h"

// C_COLLI's constructor (__ct__7C_COLLIFv): an empty collision with no hits
// and no shapes, full strength and vitality, owned by no character.

C_COLLI::C_COLLI()
{
	info         = NULL;
	flag         = 0;
	nbHit        = 0;
	nbInfo       = 0;
	strength     = 1;
	vitality     = 1;
	character_id = NO_CHARACTER_ID;
}
