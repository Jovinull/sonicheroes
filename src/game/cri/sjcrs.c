#include "types.h"

// CRI SJ critical-section nesting. This complete TU is the two-function run
// at 0x80220544..0x802205DC and its exclusive eight-byte BSS state.
// MATCHING: both functions and the complete BSS block are byte-exact.

u32 OSDisableInterrupts(void);
void OSRestoreInterrupts(u32 enabled);

static volatile s32 lbl_80422C10;
static u32 lbl_80422C14;

void fn_80220544(void)
{
	lbl_80422C10--;
	if (lbl_80422C10 == 0) {
		OSRestoreInterrupts(lbl_80422C14);
	}
}

void fn_80220590(void)
{
	if (lbl_80422C10 == 0) {
		lbl_80422C14 = OSDisableInterrupts();
	}
	lbl_80422C10++;
}
