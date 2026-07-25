#include "types.h"

// The stage modules' entry points, written once and linked into all thirteen.
//
// Every stage module carries this run at .text 0x0 to 0xD8, byte for byte the
// same code, and differs only in which of its own symbols the four references
// resolve to. So it is one source, named in each module's splits.txt, with
// each module's symbols.txt renaming its copies to the shared names declared
// below. The Wind Waker links REL/executor.c into its rels the same way.
//
// Three of the four names are read rather than argued: a REL header carries
// the offsets of its prolog, epilog and unresolved handler, so dtk takes them
// straight out of the module. stageDummy is the empty function the module's
// table registers, and nothing else in a module refers to it.
//
// stage40D has the same four functions but does not share this file: its
// epilog reloads through the destructor pointer instead of reusing the test's
// load, and its prolog calls two setters where these do the stores inline, so
// that module was built from a different revision of the source.
//
// movieD, autosaveD and advertiseD keep their own copies: each has a prolog
// that does module specific work this one does not.

extern void (*_ctors[])(void);
extern void (*_dtors[])(void);

typedef struct ModuleEntry {
	s32 id;
	void (*fn)(void);
} ModuleEntry;

// The block in the DOL the prolog hangs the module's two tables off.
typedef struct StageSlots {
	u8 unk0[0x30]; // 0x00
	void* unk30;   // 0x30
	u8 unk34[0x4]; // 0x34
	void* unk38;   // 0x38
} StageSlots;

extern u8 lbl_8042C1C0[];
extern StageSlots lbl_8029C310;
extern void fn_800421B4(void* arg0, ModuleEntry* arg1);

// Defined by each module, renamed to these names in its own symbols.txt.
extern ModuleEntry stageModuleTable[];
extern u8 stageSlotA[];
extern u8 stageSlotB[];
extern void stageInit(void);

void stageDummy(void) { }

void _unresolved(void) { }

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
	fn_800421B4(lbl_8042C1C0, stageModuleTable);
	lbl_8029C310.unk30 = stageSlotA;
	lbl_8029C310.unk38 = stageSlotB;
	stageInit();
}
