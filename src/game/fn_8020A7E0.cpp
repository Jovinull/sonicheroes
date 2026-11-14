// Validates a pool slot (see game/handle_pool.h) and passes it to fn_8020B5E8. Returns 0, the
// validation error, or 0x0D000001 when the system is absent.
#include "game/handle_pool.h"

extern "C" {
void fn_8020B5E8(PoolSlot* s);

int fn_8020A7E0(PoolSlot* s)
{
	PoolSystem* sys = lbl_8042CF6C;
	int err;
	if (sys == 0) {
		return 0x0D000001;
	}
	err = CheckPoolSlot(sys, s);
	if (err != 0) {
		return err;
	}
	fn_8020B5E8(s);
	return 0;
}
}
