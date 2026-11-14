// Installs aux effect `effect` (0 none, 1 standard reverb, 2 high-quality reverb, 3 chorus,
// 4 delay; others are ignored) of the audio system (see game/audio_system.h) on aux bus A (bus 0)
// or B (bus 1).
#include "game/audio_system.h"
#include "dolphin/ax.h"

typedef void (*AuxCallback80209CDC)(void*, void*);

extern "C" {
void fn_80209CDC(int bus, int effect)
{
	AuxCallback80209CDC callback;
	void* context;
	switch (effect) {
		default:
			return;
		case 0:
			callback = 0;
			context  = 0;
			break;
		case 1:
			callback = (AuxCallback80209CDC)AXFXReverbStdCallback;
			context  = &lbl_8042CF6C->reverbStd;
			break;
		case 2:
			callback = (AuxCallback80209CDC)AXFXReverbHiCallback;
			context  = &lbl_8042CF6C->reverbHi;
			break;
		case 3:
			callback = (AuxCallback80209CDC)AXFXChorusCallback;
			context  = &lbl_8042CF6C->chorus;
			break;
		case 4:
			callback = (AuxCallback80209CDC)AXFXDelayCallback;
			context  = &lbl_8042CF6C->delay;
			break;
	}
	switch (bus) {
		case 0:
			AXRegisterAuxACallback(callback, context);
			break;
		case 1:
			AXRegisterAuxBCallback(callback, context);
			break;
	}
}
}
