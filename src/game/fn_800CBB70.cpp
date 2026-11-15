// Stops the second main sound stream (lbl_8042B624[1]; the reset of fn_800CC1C4); unless
// lbl_8042C470 is 1, a first stream in state 6 then goes back to state 5. HYPOTHESIS: ending a
// jingle that interrupted the music; the roles are UNKNOWN.
#include "types.h"

struct Attached800CBB70 {
	s8 state; // 0x0
	u8 pad1[7];
	void* handle; // 0x8
};

struct Stream800CBB70 {
	u8 pad0[0x18];
	void* vtable; // 0x18
	u8 pad1C[0x28 - 0x1C];
	s8 slot;  // 0x28
	s8 state; // 0x29
	u8 pad2A;
	u8 flags; // 0x2B (bit 0: paused)
	u8 pad2C[0x44 - 0x2C];
	void* player; // 0x44 (ADXT handle)
	u8 pad48[4];
	Attached800CBB70* attached; // 0x4C
};

extern "C" {
extern Stream800CBB70* lbl_8042B624[2];
extern s8 lbl_8042C470;
void ADXT_Stop(void* handle);
void ADXT_Pause(void* handle, s32 on);
void ADXT_ResetEntry(void* handle);
}

// Same reset as in fn_800CC1C4.
static inline void StopStream(Stream800CBB70* s)
{
	Attached800CBB70* attached;

	ADXT_Stop(s->player);
	ADXT_Pause(s->player, 0);
	attached = s->attached;
	if (attached != NULL) {
		ADXT_ResetEntry(attached->handle);
		attached->state = -1;
	}
	s->state = 0;
	s->flags &= ~1;
}

extern "C" void fn_800CBB70(void)
{
	Stream800CBB70* first  = lbl_8042B624[0];
	Stream800CBB70* second = lbl_8042B624[1];

	if (second != NULL) {
		if (lbl_8042C470 == 1) {
			StopStream(second);
		} else {
			StopStream(second);
			if (first != NULL) {
				switch (first->state) {
					case 6:
						first->state = 5;
						break;
				}
			}
		}
	}
}
