// Copies arg0 into the character buffer at lbl_803EC968+0x14C through the engine's
// rwstrcpy slot (+0xF8), then returns arg0.
#include "game/rw_engine.h"

struct Glob8016E054 {
	u8 pad[0x14C];
	char text[0x40];
};

extern "C" {
extern Glob8016E054 lbl_803EC968;

char* fn_8016E054(char* arg0)
{
	if (arg0 != 0) {
		lbl_8042C9A4->rwstrcpy((char*)&lbl_803EC968 + 0x14C, arg0);
		return arg0;
	}
	return 0;
}
}
