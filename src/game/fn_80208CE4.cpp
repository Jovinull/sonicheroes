// Hands out a voice entry of the audio system (see game/audio_system.h): starting after the last
// one handed out, takes the first entry that is waiting for an AX voice and gets one
// (AXAcquireVoice, priority 0x1B, callback fn_80208FF8), or the first idle entry that still owns
// a voice. The entry is marked in use with its two pause bits cleared and records a, b and c.
// Returns the entry, or null when none of the 0x40 qualifies.
#include "game/audio_system.h"

extern "C" {
extern const float lbl_8042FFDC;
void fn_80208FF8(void* voice);

static inline PoolEntry10C* FindVoiceEntry(void)
{
	int i;
	PoolEntry10C* e;
	for (i = 0; i < 0x40; i++) {
		lbl_8042CF6C->nextEntry++;
		lbl_8042CF6C->nextEntry %= 0x40;
		e = &lbl_8042CF6C->entries10C[lbl_8042CF6C->nextEntry];
		if ((e->flags & 0x80000000) && (e->flags & 0x40000000)) {
			AXVPB* voice = AXAcquireVoice(0x1B, fn_80208FF8, (u32)e);
			if (voice != 0) {
				lbl_8042CF6C->voicesAcquired++;
				e->voice = voice;
				e->flags &= ~0x40000000;
				return e;
			}
		}
		if (!(e->flags & 0x80000000) && e->voice != 0) {
			return e;
		}
	}
	return 0;
}

PoolEntry10C* fn_80208CE4(int a, int b, int c)
{
	PoolEntry10C* e = FindVoiceEntry();
	if (e != 0) {
		e->f10  = lbl_8042FFDC;
		e->f108 = a;
		e->f08  = b;
		e->f0C  = c;
		e->flags |= 0x80000000;
		e->flags &= ~1;
		e->flags &= ~2;
		e->f104 = 0;
	}
	return e;
}
}
