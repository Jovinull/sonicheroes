// TObjBobPreJumpCollision's constructor, out of line: the copy each module
// keeps although the jump's constructor inlines it (no caller; force_active).
// The constructor is in game/obj_bob_jump_collision.h.

#define BOB_PRE_JUMP_CTOR
#include "game/obj_bob_jump_collision.h"
