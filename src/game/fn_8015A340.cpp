// Renders object through the callback at +0x18 of its plugin data (at the offset lbl_8042C918).
// When that succeeds and the plugin data holds a sub-object (+0xC), fn_8015AE10 processes it and
// the driver's front-to-back render hint is set from whether the sub-object's +0xC word is 1.
// Plugin and field names are UNKNOWN. Returns the object, or null when the render callback fails.
#include "game/rw_engine.h"

struct Sub8015A340 {
	u8 pad0[0xC];
	s32 fC; // 0xC
};

struct Ext8015A340 {
	u8 pad0[0xC];
	Sub8015A340* sub; // 0xC
	u8 pad10[0x18 - 0x10];
	void* (*render)(void* object); // 0x18
};

extern "C" {
extern s32 lbl_8042C918;
void fn_8015AE10(Sub8015A340* sub, void* object);

void* fn_8015A340(void* object)
{
	Ext8015A340* ext = (Ext8015A340*)((u8*)object + lbl_8042C918);
	if (ext->render(object) != 0) {
		Sub8015A340* sub = ext->sub;
		if (sub != 0) {
			RwStandardFunc hint = lbl_8042C9A4->stdFunc[rwSTANDARDHINTRENDERF2B];
			fn_8015AE10(sub, object);
			hint(0, 0, (sub->fC == 1) ? 1 : 0);
		}
		return object;
	}
	return 0;
}
}
