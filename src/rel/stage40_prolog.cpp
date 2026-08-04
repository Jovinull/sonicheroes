#include "types.h"

// stage40D was built from a later revision of the otherwise shared stage
// module prolog. Its initializer calls the two slot setters supplied by
// o_sample.cpp instead of storing the pointers directly.

extern "C" {

extern void (*_ctors[])(void);
extern void (*_dtors[])(void);

typedef struct ModuleEntry {
	s32 id;
	void (*function)(void);
} ModuleEntry;

typedef struct StageSlots {
	u8 data[0x3C];
} StageSlots;

extern u8 lbl_8042C1C0[];
extern StageSlots lbl_8029C310;
extern ModuleEntry stage40ModuleTable[];
extern u8 stage40SlotA[];
extern u8 stage40SlotB[];

extern void fn_800421B4(void* context, ModuleEntry* table);
extern void setSampleWord30(StageSlots* slots, void* value);
extern void setSampleWord38(StageSlots* slots, void* value);
extern void stage40Init(void);

void stage40Dummy(void) { }

void _unresolved(void) { }

void _epilog(void)
{
	void (**destructor)(void);

	destructor = _dtors;
	while (*destructor != 0) {
		(*destructor)();
		destructor++;
	}
}

void _prolog(void)
{
	void (**constructor)(void);

	constructor = _ctors;
	while (*constructor != 0) {
		(*constructor)();
		constructor++;
	}

	fn_800421B4(lbl_8042C1C0, stage40ModuleTable);
	setSampleWord30(&lbl_8029C310, stage40SlotA);
	setSampleWord38(&lbl_8029C310, stage40SlotB);
	stage40Init();
}
}
