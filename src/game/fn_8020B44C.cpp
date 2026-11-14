// Allocates the first inactive pool handle (see game/handle_pool.h): clears it, marks it active
// and stores it through out. Returns 0, 0x07000101 when all 0x40 are in use, or 0x0D000001 when
// the system is absent.
#include "game/handle_pool.h"

extern "C" {
void* memset(void* dst, int value, unsigned long size);

int fn_8020B44C(PoolHandle** out)
{
	PoolSystem* sys = lbl_8042CF6C;
	PoolHandle* h;
	int i;
	if (sys == 0) {
		return 0x0D000001;
	}
	h = sys->handles;
	for (i = 0; i < 0x40; i++, h++) {
		if (h->active == 0) {
			goto found;
		}
	}
	return 0x07000101;
found:
	memset(h, 0, sizeof(PoolHandle));
	h->active = 1;
	*out      = h;
	return 0;
}
}
