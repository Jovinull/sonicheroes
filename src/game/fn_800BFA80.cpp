// Static initializer of the three-entry table lbl_80253D20 (HYPOTHESIS; the meaning of its 12-byte
// entries is UNKNOWN): copies the entries lbl_80253CFC, lbl_80253D08 and lbl_80253D14 into it.
// The entries are copied as blocks, so the entry holds an array, not three named words. All the
// tables stay in their current .data units; the .ctors entry is written by hand, as in
// game/fn_80052150.cpp.
#include "types.h"

struct Entry800BFA80 {
	s32 v[3];
};

extern "C" {
extern Entry800BFA80 lbl_80253CFC;
extern Entry800BFA80 lbl_80253D08;
extern Entry800BFA80 lbl_80253D14;
extern Entry800BFA80 lbl_80253D20[3];

void fn_800BFA80(void)
{
	lbl_80253D20[0] = lbl_80253CFC;
	lbl_80253D20[1] = lbl_80253D08;
	lbl_80253D20[2] = lbl_80253D14;
}
}

__declspec(section ".ctors") void (*const fn800BFA80CtorEntry)(void) = fn_800BFA80;
