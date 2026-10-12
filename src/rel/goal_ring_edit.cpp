#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// TObjGoalring::EditOnChange (the PS2 build's name): the goal ring takes no
// edits.

class TObjGoalring : public TObject, public TObjSetObj, public C_COLLI
{
public:
	// Exec comes first so that it is the key function (see rel/goal_ring_dtor.cpp).
	virtual void Exec();
	virtual void EditOnChange(SETDATA_PARAM* param);
};

void TObjGoalring::EditOnChange(SETDATA_PARAM* param) { }
