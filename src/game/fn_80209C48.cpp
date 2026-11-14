// Resets channel `ch` of an audio pool slot (see game/audio_system.h) to its defaults with
// interrupts disabled. lbl_804300A0 is the .sdata2 literal (float)0x88888888, declared const so
// its load may be scheduled ahead of the integer stores as in retail.
#include "game/audio_system.h"

extern "C" {
#include "dolphin/os.h"

extern const float lbl_804300A0;

void fn_80209C48(PoolSlot* s, int ch)
{
	BOOL enabled        = OSDisableInterrupts();
	s->channels[ch].f00 = 0;
	s->channels[ch].f10 = 100;
	s->channels[ch].f18 = 0x40;
	s->channels[ch].f1C = 0x2000;
	s->channels[ch].f14 = 0x7F;
	s->channels[ch].f20 = 0;
	s->channels[ch].f28 = 0;
	s->channels[ch].f24 = -1;
	s->channels[ch].f38 = 0x88888888;
	s->channels[ch].f3C = lbl_804300A0;
	s->channels[ch].f40 = lbl_804300A0;
	OSRestoreInterrupts(enabled);
}
}
