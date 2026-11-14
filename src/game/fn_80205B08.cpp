// ARQ completion callback of the audio system (see game/audio_system.h): finds the request,
// clears its busy byte and calls its completion callback, if any, with the stored argument. An
// unknown request reports lbl_8023D4FC with the file name lbl_8023D4EC and line 0xAE, then hangs.
#include "game/audio_system.h"

extern "C" {
extern char lbl_8023D4FC[];

void fn_80205B08(u32 request)
{
	int i;
	for (i = 0; i < 0x40; i++) {
		if ((u32)&lbl_8042CF6C->requests[i] == request) {
			goto found;
		}
	}
	OSReport(lbl_8023D4FC, lbl_8023D4EC, 0xAE);
	while (1) {
	}
found:
	lbl_8042CF6C->busy[i] = 0;
	if (lbl_8042CF6C->requestCallback[i] != 0) {
		lbl_8042CF6C->requestCallback[i](lbl_8042CF6C->requestCallbackArg[i]);
	}
}
}
