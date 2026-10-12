// TObjCaptureCollision::KillMyself, out of line: the copy each module keeps
// although Exec inlines it (no caller; force_active). It is in
// capture_collision_class.inc.

#define CAPTURE_COLLISION_CTOR inline
#define CAPTURE_KILL_INLINE
#include "src/rel/capture_collision_class.inc"
