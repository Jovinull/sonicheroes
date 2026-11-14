// Validates a pool slot (see game/audio_system.h) and passes it to fn_8020B8A0 with a (0..0x1F),
// b (0..0x7F) and c. Returns 0, 0x03000001 for an out-of-range a or b, the validation error, or
// 0x0D000001 when the system is absent.
#include "game/audio_system.h"

extern "C" {
void fn_8020B8A0(PoolSlot* s, int a, int b, int c);

int fn_8020AB74(PoolSlot* s, signed char a, signed char b, signed char c)
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
	if (a < 0 || a > 0x1F) {
		return 0x03000001;
	}
	if (b < 0 || b > 0x7F) {
		return 0x03000001;
	}
	fn_8020B8A0(s, a, b, c);
	return 0;
}
}
