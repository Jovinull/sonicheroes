// Runs the handler at +0x64 of the table lbl_80239A30 for the current team's record
// (lbl_802C1D1C[lbl_8042C1FC], 0x114 bytes) with lbl_802C218C, counting the call (+0x8 of the
// record); the team's busy flag (+0x4 of its 0xC-byte entry in lbl_802D5AF0) is set around it.
// Roles are UNKNOWN (see fn_80051944 for the same call through a record's own callback).
#include "types.h"

struct Record800518AC {
	u8 pad0[0x8];
	s32 calls; // 0x8
	u8 padC[0x114 - 0xC];
};

struct Flags800518AC {
	u8 pad0[4];
	s32 busy; // 0x4
	u8 pad8[4];
};

struct Handlers800518AC {
	u8 pad0[0x64];
	void (*handler)(void* context, Record800518AC* record); // 0x64
};

extern "C" {
extern Flags800518AC lbl_802D5AF0[];
extern Record800518AC lbl_802C1D1C[];
extern u8 lbl_802C218C[];
extern const Handlers800518AC lbl_80239A30;
extern s32 lbl_8042C1FC;

void fn_800518AC(void)
{
	lbl_802D5AF0[lbl_8042C1FC].busy = 1;
	lbl_80239A30.handler(lbl_802C218C, &lbl_802C1D1C[lbl_8042C1FC]);
	lbl_802C1D1C[lbl_8042C1FC].calls++;
	lbl_802D5AF0[lbl_8042C1FC].busy = 0;
}
}
