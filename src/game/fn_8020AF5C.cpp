// Packs a MIDI event for an audio pool slot (see game/audio_system.h) into the four bytes at ev:
// the status byte, the first data byte from the variable arguments and, for status classes
// 0x80, 0x90, 0xA0, 0xB0, 0xD0 and 0xE0, a second one (0 otherwise); the fourth byte is cleared.
// Returns 0, the slot validation error, or 0x0D000001 when the system is absent.
// NonMatching: 3 word diffs in the inlined va_start: retail builds the 0x03000000 gpr/fpr word in
// r4 and loads the __va_arg type afterwards, MWCC uses r5. Statement and declaration orders and the
// MSL va_start spelling did not change it.
#include "game/audio_system.h"
#include "Runtime.PPCEABI.H/__va_arg.h"

extern "C" {
int fn_8020AF5C(PoolSlot* s, unsigned char* ev, unsigned char status, ...)
{
	PoolSystem* sys = lbl_8042CF6C;
	__va_list args;
	int err;
	if (sys == 0) {
		return 0x0D000001;
	}
	err = CheckPoolSlot(sys, s);
	if (err != 0) {
		return err;
	}
	__builtin_va_info(&args);
	ev[0] = status;
	ev[1] = *(int*)__va_arg(args, 1);
	switch (status & 0xF0) {
		case 0x80:
		case 0x90:
		case 0xA0:
		case 0xB0:
		case 0xD0:
		case 0xE0:
			ev[2] = *(int*)__va_arg(args, 1);
			break;
		default:
			ev[2] = 0;
			break;
	}
	ev[3] = 0;
	return 0;
}
}
