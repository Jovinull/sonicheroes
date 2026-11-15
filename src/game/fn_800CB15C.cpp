// Stops the two sound streams of lbl_8042B634 (see fn_800CB84C): for each allocated entry, stops
// and un-pauses its ADX player (+0x3C), clears the ids at +0x2C/+0x30 and +0x2A to -1, the state
// (+0x29) to 0 and the paused bit (+0x2B bit 0).
#include "types.h"

struct Entry800CB15C {
	u8 pad0[0x29];
	s8 state;      // 0x29
	s8 unknown2A;  // 0x2A
	u8 flags;      // 0x2B (bit 0: paused)
	s32 unknown2C; // 0x2C
	s32 unknown30; // 0x30
	u8 pad34[0x3C - 0x34];
	s32 player; // 0x3C (ADXT handle)
};

extern "C" {
extern Entry800CB15C* lbl_8042B634[2];
void ADXT_Stop(s32 handle);
void ADXT_Pause(s32 handle, s32 on);

void fn_800CB15C(void)
{
	Entry800CB15C* e;
	int i;

	for (i = 0; i < 2; i++) {
		e = lbl_8042B634[i];
		if (e != NULL) {
			ADXT_Stop(e->player);
			ADXT_Pause(e->player, 0);
			e->unknown2C = -1;
			e->unknown30 = -1;
			e->unknown2A = -1;
			e->state     = 0;
			e->flags &= ~1;
		}
	}
}
}
