// Stops the main sound stream lbl_8042B624 (see fn_800CB84C): stops and un-pauses its ADX player
// (+0x44), resets the entry of its attached stream (+0x4C; its first byte becomes -1), clears the
// state (+0x29) and the paused bit (+0x2B bit 0) and, when the name lbl_8042B620 exists, records it
// (fn_80116D2C/fn_80116E3C on lbl_803E774C) and copies it into the stream's 0x20-byte name (+0x50).
// HYPOTHESIS: the BGM stream with its last-played name; the roles are UNKNOWN.
#include "types.h"

struct Attached800CC1C4 {
	s8 state; // 0x0
	u8 pad1[7];
	s32 handle; // 0x8
};

struct Stream800CC1C4 {
	u8 pad0[0x29];
	s8 state; // 0x29
	u8 pad2A;
	u8 flags; // 0x2B
	u8 pad2C[0x44 - 0x2C];
	s32 player; // 0x44 (ADXT handle)
	u8 pad48[4];
	Attached800CC1C4* attached; // 0x4C
	char name[0x20];            // 0x50
};

extern "C" {
extern Stream800CC1C4* lbl_8042B624;
extern char lbl_8042B620[4];
extern u8 lbl_803E774C[];
void ADXT_Stop(s32 handle);
void ADXT_Pause(s32 handle, s32 on);
void ADXT_ResetEntry(s32 handle);
void* fn_80116D2C(void* object);
void fn_80116E3C(void* record, char* name);
void* memset(void* dst, int c, unsigned long n);
char* strcpy(char* dst, const char* src);

void fn_800CC1C4(void)
{
	Stream800CC1C4* s = lbl_8042B624;

	if (s != NULL) {
		Attached800CC1C4* attached;

		ADXT_Stop(s->player);
		ADXT_Pause(s->player, 0);
		attached = s->attached;
		if (attached != NULL) {
			ADXT_ResetEntry(attached->handle);
			attached->state = -1;
		}
		s->state = 0;
		s->flags &= ~1;
		if (lbl_8042B620 != NULL) {
			fn_80116E3C(fn_80116D2C(lbl_803E774C), lbl_8042B620);
			memset(s->name, 0, sizeof(s->name));
			strcpy(s->name, lbl_8042B620);
		}
	}
}
}
