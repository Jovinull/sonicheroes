#include "types.h"

// e2000ObjectClearSlots, which e2000ObjectUnload runs first, in stage13D and
// stage26D: both of the E-2000's four-slot tables are cleared, slot by slot.

extern "C" s32 e2000ObjectSlotsA[4];
extern "C" s32 e2000ObjectSlotsB[4];

extern "C" void e2000ObjectClearSlots(void)
{
	for (int i = 0; i < 4; i++) {
		e2000ObjectSlotsB[i] = 0;
		e2000ObjectSlotsA[i] = 0;
	}
}
