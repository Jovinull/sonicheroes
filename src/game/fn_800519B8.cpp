// Runs the callback of the current team's record selected by fn_8004E608 (0x114-byte entries of
// lbl_802B908C[lbl_8042C1FC], record at +0x90 of each) with lbl_802C218C, counting the call, and
// then, unless the game mode byte +0x18 of lbl_8042C180 is 2, calls fn_80136258 and, when
// fn_80134728 agrees, fn_8004DB3C(arg, 1). The roles are UNKNOWN (see fn_80051944).
#include "types.h"

struct Record800519B8;

struct Record800519B8 {
	u8 pad0[0x8];
	s32 calls;                                               // 0x8
	void (*callback)(void* context, Record800519B8* record); // 0xC
};

struct Entry800519B8 {
	u8 pad0[0x90];
	Record800519B8 record; // 0x90
	u8 padA0[0x114 - 0xA0];
};

struct Team800519B8 {
	Entry800519B8 entries[32]; // extent UNKNOWN
	u8 pad2280[0x2324 - 0x2280];
};

struct Mode800519B8 {
	u8 pad0[0x18];
	s8 mode; // 0x18
};

extern "C" {
extern Team800519B8 lbl_802B908C[];
extern s32 lbl_8042C1FC;
extern u8 lbl_802C218C[];
extern Mode800519B8* lbl_8042C180;
s32 fn_8004E608(void);
void fn_80136258(void);
s32 fn_80134728(void);
void fn_8004DB3C(void* arg, s32 value);

void fn_800519B8(void* arg)
{
	s32 index              = fn_8004E608();
	Record800519B8* record = &lbl_802B908C[lbl_8042C1FC].entries[index].record;

	if (record->callback != NULL) {
		record->callback(lbl_802C218C, record);
		record->calls++;
	}
	if (lbl_8042C180->mode != 2) {
		fn_80136258();
		if (fn_80134728() != 0) {
			fn_8004DB3C(arg, 1);
		}
	}
}
}
