// Applies a sound output mode (0 stereo-like, 1 mono, 2 surround-like; HYPOTHESIS from the calls):
// stops the sound manager lbl_8042C388 first (fn_800B48B8), forces mode 1 when the console sound
// setting (fn_801D5B1C) is 0 and turns mode 1 into 0 when it is 1, programs the mixer
// (MIXSetSoundMode, fn_8020B540, fn_80209E58), passes the mode to fn_800CA52C and records it in
// mode switch 0x12 of lbl_8042C180. Other modes are ignored. The names are UNKNOWN.
#include "types.h"

class MODESWITCH;
enum MODESWITCH_ENUM {
	MODESWITCH_SOUND = 0x12 // HYPOTHESIS
};

class MODESWITCH
{
public:
	void SetModeSwitch(MODESWITCH_ENUM which, int value);
};

extern "C" {
extern void* lbl_8042C388;
extern MODESWITCH* lbl_8042C180;
void fn_800B48B8(void* manager);
u32 fn_801D5B1C(void);
void MIXSetSoundMode(u32 mode);
void fn_8020B540(s32 mode);
void fn_80209E58(s32 mode);
void fn_800CA52C(s32 mode);

void fn_800B41A0(s32 mode)
{
	if (lbl_8042C388 != NULL) {
		fn_800B48B8(lbl_8042C388);
	}
	if (fn_801D5B1C() == 0) {
		mode = 1;
	}
	if (fn_801D5B1C() == 1 && mode == 1) {
		mode = 0;
	}
	switch (mode) {
		case 1:
			MIXSetSoundMode(0);
			fn_8020B540(0);
			fn_80209E58(0);
			break;
		case 0:
			MIXSetSoundMode(1);
			fn_8020B540(1);
			fn_80209E58(0);
			break;
		case 2:
			MIXSetSoundMode(1);
			fn_8020B540(1);
			fn_80209E58(1);
			break;
		default:
			return;
	}
	fn_800CA52C(mode);
	if (lbl_8042C180 != NULL) {
		lbl_8042C180->SetModeSwitch(MODESWITCH_SOUND, mode);
	}
}
}
