// TObjCaptureCollision's TDisp (empty) and Exec, which only raises the kill
// bit when the volume is out of range or due to be killed (CheckKill, whose
// answer is made a 0 or 1 before the test, as the original does). The class is
// shared through capture_collision_class.inc.

#define CAPTURE_COLLISION_CTOR inline
#define CAPTURE_EDIT_FIRST
#include "src/rel/capture_collision_class.inc"

void TObjCaptureCollision::TDisp() { }

void TObjCaptureCollision::Exec()
{
	if (CheckKill()) {
		Signal |= 1;
	}
}
