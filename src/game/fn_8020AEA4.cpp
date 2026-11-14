// Validates a pool slot (see game/audio_system.h) and passes fn_802099B0 the colour packed from the
// three bytes at rgb and the alpha byte a (0xRRGGBBAA). Returns 0, the validation error, or
// 0x0D000001 when the system is absent.
#include "game/audio_system.h"

extern "C" {
void fn_802099B0(PoolSlot* s, unsigned int rgba);

int fn_8020AEA4(PoolSlot* s, unsigned char* rgb, unsigned char a)
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
	fn_802099B0(s, (rgb[0] << 24) | (rgb[1] << 16) | (rgb[2] << 8) | a);
	return 0;
}
}
