#include "types.h"

// Ends the stage animation tasks (after fn_8012158C): each task pointer still set, the seven
// singles (lbl_8042C42C, C424, C41C, C414, C434, C40C, C400) and the four entries of the five
// tables lbl_803043C8 .. lbl_80304408, gets the end flag 0x1 (TObject +0x4) and is cleared.
// HYPOTHESIS: the task roles (see fn_800C0B04, fn_800C1E8C and the other animation units) are
// UNKNOWN.

struct Task800C59C4 {
	u8 pad0[0x4];
	u16 signal; // 0x4
};

extern "C" {
extern Task800C59C4* lbl_8042C42C;
extern Task800C59C4* lbl_8042C424;
extern Task800C59C4* lbl_8042C41C;
extern Task800C59C4* lbl_8042C414;
extern Task800C59C4* lbl_8042C434;
extern Task800C59C4* lbl_8042C40C;
extern Task800C59C4* lbl_8042C400;
extern Task800C59C4* lbl_803043C8[4];
extern Task800C59C4* lbl_803043D8[4];
extern Task800C59C4* lbl_803043E8[4];
extern Task800C59C4* lbl_803043F8[4];
extern Task800C59C4* lbl_80304408[4];
void fn_8012158C(void);
}

static inline void EndTask(Task800C59C4*& task)
{
	if (task != NULL) {
		task->signal |= 1;
		task = NULL;
	}
}

extern "C" void fn_800C59C4(void)
{
	fn_8012158C();
	EndTask(lbl_8042C42C);
	EndTask(lbl_8042C424);
	EndTask(lbl_8042C41C);
	EndTask(lbl_8042C414);
	EndTask(lbl_8042C434);
	EndTask(lbl_8042C40C);
	EndTask(lbl_8042C400);
	for (s32 i = 0; i < 4; i++) {
		EndTask(lbl_803043C8[i]);
		EndTask(lbl_803043D8[i]);
		EndTask(lbl_803043E8[i]);
		EndTask(lbl_803043F8[i]);
		EndTask(lbl_80304408[i]);
	}
}
