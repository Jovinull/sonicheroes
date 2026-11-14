// Per-update step of the audio system (see game/audio_system.h). A nested call only counts itself
// in `skipped`; otherwise the update records the time, refreshes f10/f0C, runs every slot (the
// fn_8020BA04/fn_802096B0 pair only while bit 31 of the slot word is set), refreshes f10/f0C again
// and leaves. The nesting count is changed with interrupts disabled.
#include "game/audio_system.h"

extern "C" {
#include "dolphin/os.h"

int fn_80206F04(void);
int fn_80208C38(void);
void fn_8020BA04(PoolSlot* s);
void fn_802096B0(PoolSlot* s);
void fn_802092A8(PoolSlot* s);
void fn_8020917C(PoolSlot* s);
void fn_802093D4(PoolSlot* s);
void fn_80209318(PoolSlot* s);
void fn_80206578(PoolListNode** list);

void fn_80209EC4(void)
{
	BOOL enabled;
	int i;
	if (lbl_8042CF6C == 0 || lbl_8042CF6C->f00 == 0) {
		return;
	}
	enabled = OSDisableInterrupts();
	lbl_8042CF6C->lock++;
	OSRestoreInterrupts(enabled);
	if (lbl_8042CF6C->lock != 1) {
		lbl_8042CF6C->skipped++;
		enabled = OSDisableInterrupts();
		lbl_8042CF6C->lock--;
		OSRestoreInterrupts(enabled);
		return;
	}
	lbl_8042CF6C->prevTime = lbl_8042CF6C->time;
	lbl_8042CF6C->time     = OSGetTime();
	lbl_8042CF6C->f10      = fn_80206F04();
	lbl_8042CF6C->f0C      = fn_80208C38();
	for (i = 0; i < 8; i++) {
		if (lbl_8042CF6C->slots[i].active & 0x80000000) {
			fn_8020BA04(&lbl_8042CF6C->slots[i]);
			fn_802096B0(&lbl_8042CF6C->slots[i]);
		}
		fn_802092A8(&lbl_8042CF6C->slots[i]);
		fn_8020917C(&lbl_8042CF6C->slots[i]);
		fn_802093D4(&lbl_8042CF6C->slots[i]);
		fn_80209318(&lbl_8042CF6C->slots[i]);
		fn_80206578(&lbl_8042CF6C->slots[i].objects);
	}
	lbl_8042CF6C->f10 = fn_80206F04();
	lbl_8042CF6C->f0C = fn_80208C38();
	enabled           = OSDisableInterrupts();
	lbl_8042CF6C->lock--;
	OSRestoreInterrupts(enabled);
}
}
