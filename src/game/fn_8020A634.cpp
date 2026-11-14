// Calls fn_80209A3C for every active pool slot (see game/handle_pool.h), then fn_8020A05C.
// Returns 0, or 0x0D000001 when the system is absent. The retail loop runs 0x40 times over the
// 0x1530-byte slots although the pool has eight of them; the records beyond the eighth fail the
// slot validation, so only the real slots are passed on.
#include "game/handle_pool.h"

extern "C" {
void fn_80209A3C(PoolSlot* s);
void fn_8020A05C(void);

static inline void StopPoolSlot(PoolSlot* s)
{
	PoolSystem* sys = lbl_8042CF6C;
	if (sys == 0) {
		return;
	}
	if (CheckPoolSlot(sys, s) != 0) {
		return;
	}
	fn_80209A3C(s);
}

static inline void StopPoolSlots(PoolSystem* sys)
{
	PoolSlot* s;
	int i;
	if (sys == 0) {
		return;
	}
	s = sys->slots;
	for (i = 0; i < 0x40; i++, s++) {
		StopPoolSlot(s);
	}
}

int fn_8020A634(void)
{
	PoolSystem* sys = lbl_8042CF6C;
	if (sys == 0) {
		return 0x0D000001;
	}
	StopPoolSlots(sys);
	fn_8020A05C();
	return 0;
}
}
