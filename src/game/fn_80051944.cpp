// Runs the callback of the current entry of the current team record (lbl_802B908C[lbl_8042C1FC],
// entry index +0x8C, record at +0x90 of the third 0x114-byte array at +0x1140) with
// lbl_802C218C and the record, and counts the call (+0x8 of the record). The roles are UNKNOWN
// (see fn_8004E564 for the same arrays).
#include "types.h"

struct Callback80051944;

typedef void (*Callback80051944Fn)(void* context, Callback80051944* record);

struct Callback80051944 {
	u8 pad0[0x8];
	s32 calls;                   // 0x8
	Callback80051944Fn callback; // 0xC
};

struct Entry80051944 {
	u8 pad0[0x8C];
	s32 current;             // 0x8C (used in entry 0 only)
	Callback80051944 record; // 0x90
	u8 pad0A0[0x114 - 0xA0];
};

struct Team80051944 {
	Entry80051944 entries[16]; // 0x0 (extent UNKNOWN)
	Entry80051944 entries2[8]; // 0x1140 (extent UNKNOWN)
	u8 pad19E0[0x2324 - 0x19E0];
};

extern "C" {
extern Team80051944 lbl_802B908C[];
extern s32 lbl_8042C1FC;
extern u8 lbl_802C218C[];

void fn_80051944(void)
{
	Callback80051944* record = &lbl_802B908C[lbl_8042C1FC]
	                                .entries2[lbl_802B908C[lbl_8042C1FC].entries[0].current]
	                                .record;

	if (record->callback != NULL) {
		record->callback(lbl_802C218C, record);
		record->calls++;
	}
}
}
