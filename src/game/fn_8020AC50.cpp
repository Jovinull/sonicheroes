// Calls fn_80209C48(slot, 0..15) for every active slot of the pool (see game/audio_system.h).
// Returns 0, or 0x0D000001 when the system is absent.
#include "game/audio_system.h"

extern "C" {
void fn_80209C48(PoolSlot* s, int channel);

static inline void ResetChannels(PoolSlot* s)
{
	int j;
	for (j = 0; j < 0x10; j++) {
		fn_80209C48(s, j);
	}
}

static inline void ResetPoolSlot(PoolSlot* s)
{
	PoolSystem* sys = lbl_8042CF6C;
	if (sys == 0) {
		return;
	}
	if (CheckPoolSlot(sys, s) != 0) {
		return;
	}
	ResetChannels(s);
}

int fn_8020AC50(void)
{
	int i;
	if (lbl_8042CF6C == 0) {
		return 0x0D000001;
	}
	for (i = 0; i < 8; i++) {
		ResetPoolSlot(&lbl_8042CF6C->slots[i]);
	}
	return 0;
}
}
