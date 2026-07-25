#include "types.h"

// The module's entry points.
//
// The translation unit runs from fn_7_0 at 0x0 to the end of _prolog at 0xD8.
// Three of the four names are read rather than argued: a REL header carries
// the offsets of its prolog, epilog and unresolved handler, so dtk takes them
// straight out of the module. fn_7_0 is the empty function the table at
// .data 0x10 registers, and nothing else in the module refers to it.
//
// Every stage module repeats this file with its own tables, and movieD and
// autosaveD carry the same three entry points with a shorter prolog.
//
// The tables are left to the module rather than claimed here: only this run
// reads the one at .data 0x10, but the sixteen bytes in front of it belong to
// no unit dtk can name, and the two the prolog installs are large blocks that
// nothing here would otherwise own.

extern void (*_ctors[])(void);
extern void (*_dtors[])(void);

typedef struct ModuleEntry {
	s32 id;
	void (*fn)(void);
} ModuleEntry;

// The block in the DOL the prolog hangs this module's two tables off.
typedef struct StageSlots {
	u8 unk0[0x30]; // 0x00
	void* unk30; // 0x30
	u8 unk34[0x4]; // 0x34
	void* unk38; // 0x38
} StageSlots;

extern u8 lbl_8042C1C0[];
extern StageSlots lbl_8029C310;
extern ModuleEntry lbl_7_data_10[];
extern u8 lbl_7_data_F8[];
extern u8 lbl_7_data_11D8[];
extern void fn_800421B4(void* arg0, ModuleEntry* arg1);
extern void fn_7_D22C8(void);

void fn_7_0(void)
{
}

void _unresolved(void)
{
}

void _epilog(void)
{
	void (**dtor)(void);

	dtor = _dtors;
	while (*dtor != NULL) {
		(*dtor)();
		dtor++;
	}
}

void _prolog(void)
{
	void (**ctor)(void);

	ctor = _ctors;
	while (*ctor != NULL) {
		(*ctor)();
		ctor++;
	}
	fn_800421B4(lbl_8042C1C0, lbl_7_data_10);
	lbl_8029C310.unk30 = lbl_7_data_11D8;
	lbl_8029C310.unk38 = lbl_7_data_F8;
	fn_7_D22C8();
}
