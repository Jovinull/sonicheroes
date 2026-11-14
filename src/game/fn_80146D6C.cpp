// Cleans up the module tracked by lbl_8042BCE0: frees its buffer (+0x10 of the globals, clearing it
// and the words at +0x14 and +0xC), then, if the container lbl_8042C850 is still in the module's
// container list (head at +0x0, containers linked at +0x8), destroys it through fn_8014705C and
// forgets it. Names are UNKNOWN. Always returns 1.
#include "game/rw_engine.h"

struct Container80146D6C {
	RwLinkList entries; // 0x0
	RwLLLink link;      // 0x8
};

extern "C" {
extern RwModuleInfo lbl_8042BCE0;
extern Container80146D6C* lbl_8042C850;
void fn_8014705C(Container80146D6C* container);
}

#define GLOBALS80146D6C ((u8*)lbl_8042C9A4 + lbl_8042BCE0.globalsOffset)

extern "C" {
s32 fn_80146D6C(void)
{
	if (*(void**)(GLOBALS80146D6C + 0x10) != 0) {
		lbl_8042C9A4->rwfree(*(void**)(GLOBALS80146D6C + 0x10));
		*(void**)(GLOBALS80146D6C + 0x10) = 0;
		*(void**)(GLOBALS80146D6C + 0x14) = 0;
		*(void**)(GLOBALS80146D6C + 0xC)  = 0;
	}
	{
		RwLLLink* cur;
		RwLLLink* end = (RwLLLink*)GLOBALS80146D6C;
		cur           = end->next;
		while (cur != end) {
			if ((Container80146D6C*)((u8*)cur - 0x8) == lbl_8042C850) {
				fn_8014705C(lbl_8042C850);
				lbl_8042C850 = 0;
				break;
			}
			cur = cur->next;
		}
	}
	return 1;
}
}
