#include "types.h"

struct RuntimeCallbacks {
	u8 pad00[0x1C];
	s32 enabled;
	void (*postEvent)(s32, s32*);
};

extern "C" {
extern RuntimeCallbacks lbl_8029BB80;

void fn_8004BEDC();
void fn_80013010(void*);
void fn_80013038(void*);
}

extern "C" void fn_800122B4(void* argument)
{
	fn_8004BEDC();
	fn_80013010(argument);
}

extern "C" void fn_800122E8(void* argument)
{
	s32 event[2];
	event[0] = 0xFF;
	event[1] = 0xFF;

	if (lbl_8029BB80.enabled != 0)
		lbl_8029BB80.postEvent(20, event);
	fn_80013038(argument);
}
