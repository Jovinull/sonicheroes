// TObjS03WalkWay's TDisp, which only asks OnEdit and drops the answer (the
// editor-only drawing it guarded is not in the build). The class is shared
// through s03_walk_way_class.inc.

#define S03_WALK_WAY_CTOR inline
#include "src/rel/s03_walk_way_class.inc"

void TObjS03WalkWay::TDisp()
{
	OnEdit();
}
