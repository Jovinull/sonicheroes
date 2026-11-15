// Releases the eight entries of lbl_80253A34 (fn_800B7C88) and clears them, with the word +0x64 of
// lbl_8042C3AC set to lbl_8042C3BC meanwhile, inside a fn_801AD5D8/fn_801AD5D0 pair (HYPOTHESIS:
// an interrupt or lock state that is restored when it was 0). Clears +0x60 and +0x64 of
// lbl_8042C3AC afterwards. The roles are UNKNOWN.
#include "types.h"

struct State800B7BDC {
	u8 pad0[0x60];
	s32 unknown60; // 0x60
	s32 unknown64; // 0x64
};

extern "C" {
extern State800B7BDC* lbl_8042C3AC;
extern s32 lbl_8042C3BC;
extern s32 lbl_8042C3C0;
extern void* lbl_80253A34[8];
s32 fn_801AD5D8(void);
void fn_801AD5D0(s32 value);
void fn_800B7C88(void* entry);

void fn_800B7BDC(void)
{
	s32 state;
	int i;

	lbl_8042C3AC->unknown64 = lbl_8042C3BC;
	state                   = fn_801AD5D8();
	lbl_8042C3C0            = state;
	for (i = 0; i < 8; i++) {
		if (lbl_80253A34[i] != NULL) {
			fn_800B7C88(lbl_80253A34[i]);
			lbl_80253A34[i] = NULL;
		}
	}
	lbl_8042C3AC->unknown60 = 0;
	lbl_8042C3AC->unknown64 = 0;
	if (state == 0) {
		fn_801AD5D0(0);
	}
}
}
