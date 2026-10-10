// TObjCaptureCollision::CreateInstance, the static factory the PS2 build names
// CreateInstance__20TObjCaptureCollisionFv: the same new-expression as
// rel/capture_collision_create.cpp, returning the object. The class is in
// capture_collision_class.inc.

#define CAPTURE_COLLISION_CTOR inline
#include "src/rel/capture_collision_class.inc"

TObjCaptureCollision* TObjCaptureCollision::CreateInstance()
{
	return new TObjCaptureCollision(lbl_8042C10C);
}
