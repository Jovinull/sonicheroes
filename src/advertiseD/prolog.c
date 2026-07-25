#include "types.h"

// The module's entry points.
//
// The translation unit runs from fn_1_8808 at 0x8808 to the end of _prolog at
// 0x88C4. Three of the four names are read rather than argued: a REL header
// carries the offsets of its prolog, epilog and unresolved handler, so dtk
// takes them straight out of the module. fn_1_8808 is the empty function the
// table at .data 0x29F0 registers, and nothing else in the module refers to
// it.
//
// Every other module repeats this file. This one differs in two places: the
// epilog tears something down before it walks the destructors, and the prolog
// has a second call after registering. Both go to functions just in front of
// this run, so neither is a table this file owns.
//
// The table is left to the module rather than claimed here. Only this run
// reads it, but it sits inside a much larger block of .data that nothing else
// here would own.

extern void (*_ctors[])(void);
extern void (*_dtors[])(void);

typedef struct ModuleEntry {
	s32 id;
	void (*fn)(void);
} ModuleEntry;

extern u8 lbl_8042C1C0[];
extern ModuleEntry lbl_1_data_29F0[];
extern void fn_800421B4(void* arg0, ModuleEntry* arg1);
extern void fn_1_86C8(void);
extern void fn_1_8740(void);

void fn_1_8808(void) { }

void _unresolved(void) { }

void _epilog(void)
{
	void (**dtor)(void);

	fn_1_86C8();
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
	fn_800421B4(lbl_8042C1C0, lbl_1_data_29F0);
	fn_1_8740();
}
