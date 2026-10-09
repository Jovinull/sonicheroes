// captureCollisionCreate, the factory rel/capture_collision_register.cpp puts
// in the editor record for TObjCaptureCollision, in the five stage modules
// whose revision of the class inlines the whole constructor: stage05D, 07D,
// 09D, 13D and 26D. rel/e_capture_collision.cpp is the other revision, where
// ResetVariable and SetParameter stay calls.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. The object hangs off the task at lbl_8042C10C rather than
// the usual one.
//
// ResetVariable clears the position and angle, the position from the module's
// zero, and SetParameter then copies the placement's over them.

#define CAPTURE_COLLISION_CTOR inline
#include "src/rel/capture_collision_class.inc"

extern "C" void captureCollisionCreate(void)
{
	new TObjCaptureCollision(lbl_8042C10C);
}
