#include "types.h"

// The module's entry points.
//
// The translation unit runs from fn_17_0 at 0x0 to the end of _prolog at 0xB4.
// The names of three of the four are read rather than argued: a REL header
// carries the offsets of its prolog, epilog and unresolved handler, so dtk
// takes them straight out of the module. fn_17_0 is the empty function the
// table at .data 0x10 registers, which is the same shape autosaveD uses, and
// nothing in the module refers to it except that table.
//
// The end is the first cut where no data crosses, and the three functions
// after it are a different cluster: two more empty stubs and then real code
// that takes arguments and works on a structure none of these touch.
//
// The .data table is left to the module rather than claimed here. Only this
// run reads it, but the sixteen bytes in front of it belong to no unit dtk can
// name, and claiming the table without them would put this file's .data ahead
// of data that has to stay where it is.

extern void (*_ctors[])(void);
extern void (*_dtors[])(void);

typedef struct ModuleEntry {
	s32 id;
	void (*fn)(void);
} ModuleEntry;

extern u8 lbl_8042C1C0[];
extern ModuleEntry lbl_17_data_10[];
extern void fn_800421B4(void* arg0, ModuleEntry* arg1);

void fn_17_0(void) { }

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
	fn_800421B4(lbl_8042C1C0, lbl_17_data_10);
}
