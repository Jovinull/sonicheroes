#include "types.h"

// Order follows the original binary, which for this compiler is source order.

// Registration table for the single code fragment this game loads. Both
// entry points here share it, which is why they have to sit in one
// translation unit. The canonical Metrowerks file name for this unit is not
// confirmed yet; "fragment" is descriptive of what the two functions do.
//
// Not linked yet. __unregister_fragment matches byte for byte, but
// __register_fragment is one instruction away: the original schedules the
// store of imagebase ahead of materialising the constant 1 for the valid
// flag, and the scheduler will not reorder those two independent instructions
// that way from any source form tried so far (12 of 13 instructions match).
// Marked NonMatching so the source is measured without being linked, leaving
// main.dol byte identical.
typedef struct {
	void* imagebase;
	void* r13;
	s32 valid;
} FragmentInfo;

static FragmentInfo fragmentinfo[1];

void __unregister_fragment(s32 index)
{
	FragmentInfo* info;

	if (index < 0)
		return;
	if (index >= 1)
		return;

	info            = &fragmentinfo[index];
	info->imagebase = 0;
	info->r13       = 0;
	info->valid     = 0;
}

s32 __register_fragment(void* imagebase, void* r13)
{
	if (fragmentinfo[0].valid == 0) {
		fragmentinfo[0].imagebase = imagebase;
		fragmentinfo[0].r13       = r13;
		fragmentinfo[0].valid     = 1;
		return 0;
	}
	return -1;
}
