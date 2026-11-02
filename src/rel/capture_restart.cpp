#include "types.h"

// The capture enemy's restart (captureRestart here), the same in the seven
// stage modules that carry the capture: it takes its placement again
// (captureInitFromPlacement) and poses its frames (captureUpdateFrame); both
// are left as assembly.

typedef struct Capture Capture;

extern "C" void captureInitFromPlacement(Capture* object);
extern "C" void captureUpdateFrame(Capture* object);

extern "C" void captureRestart(Capture* object)
{
	captureInitFromPlacement(object);
	captureUpdateFrame(object);
}
