#include "types.h"

// Switches the current stream slot (lbl_8042C471) to the given one while lbl_8042C470 is 1 and
// both stream objects of lbl_8042B624 exist. If the first stream is idle (state 0) it only
// records the slot. Otherwise a playing outgoing stream (state 1) is muted (ADXT_SetOutVol -999)
// and stopped, states 2, 3 and 5 just become 6, and an incoming stream in state 6 is set to 5.
// HYPOTHESIS: 6 = fading out/stopped, 5 = resume; the state names are UNKNOWN.

struct StreamSlot {
	u8 unknown00[0x29];
	s8 state; // 0x29
	u8 unknown2A[0x38 - 0x2A];
	s32 volume; // 0x38
	u8 unknown3C[0x44 - 0x3C];
	void* adxt; // 0x44
};

extern "C" {
extern s8 lbl_8042C470;
extern s8 lbl_8042C471;
extern StreamSlot* lbl_8042B624[2];
void ADXT_SetOutVol(void* adxt, s32 volume);
}

static inline void MuteStream(StreamSlot* s)
{
	switch (s->state) {
		case 1:
		case 2:
		case 3:
		case 5:
			ADXT_SetOutVol(s->adxt, -999);
			s->volume = -999;
			s->state  = 6;
			break;
	}
}

extern "C" void fn_800CADD8(s8 slot)
{
	if (lbl_8042C470 != 1 || lbl_8042C471 == slot || lbl_8042B624[0] == NULL
	    || lbl_8042B624[1] == NULL) {
		return;
	}
	if (lbl_8042B624[0]->state == 0) {
		lbl_8042C471 = slot;
		return;
	}
	StreamSlot* from = lbl_8042B624[lbl_8042C471];
	StreamSlot* to   = lbl_8042B624[slot];
	switch (from->state) {
		case 1:
			MuteStream(from);
			break;
		case 2:
		case 3:
		case 5:
			from->state = 6;
			break;
	}
	switch (to->state) {
		case 6:
			to->state = 5;
			break;
	}
	lbl_8042C471 = slot;
}
