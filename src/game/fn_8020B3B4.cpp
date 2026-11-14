// Validates a pool handle (see game/audio_system.h), then stores its four parameters and marks it
// as having no channel. Returns 0, the validation error, or 0x0D000001 when the system is absent.
#include "game/audio_system.h"

extern "C" {
int fn_8020B3B4(PoolHandle* h, int a, int b, int c, int d)
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
	h->param4  = a;
	h->channel = -1;
	h->param8  = b;
	h->paramC  = c;
	h->param10 = d;
	return 0;
}
}
