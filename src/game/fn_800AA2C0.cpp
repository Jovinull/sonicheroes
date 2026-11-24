// Static initializer of the global sequence object lbl_80303EC8 (HYPOTHESIS; the derived class
// name is UNKNOWN, its vtable is lbl_80253164): the inlined constructor chain stores the SEQUENCE
// base vtable, then the derived one, and clears the three words at 0x1C. The class has no
// destructor to register. The object stays in its current .bss unit; the .ctors entry is written
// by hand, as in game/fn_80052150.cpp.
#include "types.h"

extern "C" {
extern u8 __vt__8SEQUENCE[];
extern u8 lbl_80253164[];
}

struct Global800AA2C0 {
	void* vtable; // 0x00
	u8 pad4[0x1C - 0x4];
	s32 f1C; // 0x1C
	s32 f20; // 0x20
	s32 f24; // 0x24
	u8 pad28[0x70 - 0x28];
};

static inline void InitSequence800AA2C0(Global800AA2C0* g)
{
	g->vtable = __vt__8SEQUENCE;
}

static inline void InitGlobal800AA2C0(Global800AA2C0* g)
{
	InitSequence800AA2C0(g);
	g->vtable = lbl_80253164;
	g->f1C    = 0;
	g->f20    = 0;
	g->f24    = 0;
}

extern "C" {
extern Global800AA2C0 lbl_80303EC8;

void fn_800AA2C0(void)
{
	InitGlobal800AA2C0(&lbl_80303EC8);
}
}

__declspec(section ".ctors") void (*const fn800AA2C0CtorEntry)(void) = fn_800AA2C0;
