// TObjCaptureCollision's SetParameter and ResetVariable, out of line: the
// copies each module keeps although the constructor inlines them (no caller;
// force_active). They are in capture_collision_class.inc.

#define CAPTURE_COLLISION_CTOR inline
#define CAPTURE_PARAM_INLINE
#include "src/rel/capture_collision_class.inc"
