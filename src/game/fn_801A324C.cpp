// Appends the mipmap-level suffix ("m" followed by the level as one hexadecimal digit) to a
// texture name and, when present, to its mask name; levels outside 1..15 leave both unchanged.
// Always returns 1 (HYPOTHESIS: RenderWare default mipmap-name callback; installed by the code
// around 0x801A52D0).
#include "game/rw_engine.h"

extern "C" {
// Hexadecimal digit table (17-byte string in .rodata, owned by another unit).
extern const char lbl_8023C8D8[];

s32 fn_801A324C(char* name, char* maskName, u8 mipLevel)
{
	char suffix[3];
	// Integer flag: the retail code tests a full word here, not a C++ bool byte.
	s32 validLevel = 0;

	suffix[0] = 'm';
	if (mipLevel > 0 && mipLevel < 16) {
		validLevel = 1;
	}
	suffix[1] = validLevel ? lbl_8023C8D8[mipLevel] : 0;
	suffix[2] = 0;
	if (suffix[1]) {
		lbl_8042C9A4->rwstrcat(name, suffix);
		if (maskName && maskName[0]) {
			lbl_8042C9A4->rwstrcat(maskName, suffix);
		}
	}
	return 1;
}
}
