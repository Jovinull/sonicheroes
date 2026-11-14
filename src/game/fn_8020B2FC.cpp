// Releases a pool handle (see game/handle_pool.h): after validation, an active handle with a
// channel waits until that channel's busy byte is clear, then the handle is marked inactive.
// The busy byte is read once, so the retail wait spins on the first value it sees.
#include "game/handle_pool.h"

extern "C" {
int fn_8020B2FC(PoolHandle* h)
{
	PoolSystem* sys = lbl_8042CF6C;
	int err;
	if (sys == 0) {
		return 0x0D000001;
	}
	err = CheckPoolHandle(sys, h);
	if (err != 0) {
		return err;
	}
	if (h->active != 0 && h->channel >= 0) {
		while (sys->busy[h->channel] != 0) {
		}
	}
	h->active = 0;
	return 0;
}
}
