// TObjFlyerCollision's SetColliParameter, SetParameter and ResetVariable, out
// of line: the copies each module keeps although the constructor inlines them
// (no caller; force_active). They are in game/obj_flyer_collision.h.

#define FLYER_COL_INLINE
#include "game/obj_flyer_collision.h"
