// Opens a world-side module for one engine instance (HYPOTHESIS: a RenderWare module Open
// routine): records the globals offset, creates the shared 0xC-byte free list lbl_8042BD10 for the
// first instance (returning null when that fails), then marks the module globals active and
// fills its byte table with the default values. Counts the instance and returns it. Names are
// UNKNOWN.
// NonMatching: retail stores the globals offset before reading the instance count and re-reads
// lbl_8042BD10 right after storing the new free list (the store-then-reload pattern of the other
// RenderWare Open routines, fn_801971B0 and fn_801A1B84); this source forwards both values, so
// the stream is one instruction shorter. C mode, TU-local definitions, an assignment expression,
// volatile and optimizer flags do not reproduce it.
#include "game/rw_engine.h"

#define MODULE_801556E0_GLOBALS ((u8*)lbl_8042C9A4 + lbl_8042C900.globalsOffset)

extern "C" {
extern RwModuleInfo lbl_8042C900;
extern RwFreeList* lbl_8042BD10;
// HYPOTHESIS: RwFreeListCreate(entrySize, entriesPerBlock, alignment).
RwFreeList* RwFreeListCreate(s32 entrySize, s32 entriesPerBlock, s32 alignment);

void* fn_801556E0(void* instance, s32 offset, s32 size)
{
	lbl_8042C900.globalsOffset = offset;
	if (lbl_8042C900.numInstances == 0) {
		lbl_8042BD10 = RwFreeListCreate(0xC, 0x32, 4);
		if (lbl_8042BD10 == 0) {
			if (lbl_8042BD10 != 0) {
				RwFreeListDestroy(lbl_8042BD10);
				lbl_8042BD10 = 0;
			}
			return 0;
		}
	}
	*(u16*)MODULE_801556E0_GLOBALS = 1;
	lbl_8042C900.numInstances++;
	MODULE_801556E0_GLOBALS[0x8]  = 3;
	MODULE_801556E0_GLOBALS[0x9]  = 4;
	MODULE_801556E0_GLOBALS[0xA]  = 5;
	MODULE_801556E0_GLOBALS[0xC]  = 1;
	MODULE_801556E0_GLOBALS[0x10] = 2;
	MODULE_801556E0_GLOBALS[0x18] = 6;
	MODULE_801556E0_GLOBALS[0x28] = 4;
	MODULE_801556E0_GLOBALS[0x29] = 8;
	MODULE_801556E0_GLOBALS[0x2A] = 0;
	MODULE_801556E0_GLOBALS[0x2B] = 1;
	MODULE_801556E0_GLOBALS[0x2C] = 2;
	MODULE_801556E0_GLOBALS[0x2D] = 0x10;
	return instance;
}
}
