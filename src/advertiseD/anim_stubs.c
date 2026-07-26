#include "types.h"

// Two stubs the module's tables point at: one that does nothing and one that
// always answers zero.
//
// The translation unit runs from fn_1_A6C4 at 0xA6C4 to the end of fn_1_A6C8
// at 0xA6D8. The zero it returns is the named constant at .rodata 0x102C
// rather than a literal, so this unit emits no .rodata of its own.

extern "C" const f32 lbl_1_rodata_102C;

extern "C" void fn_1_A6C4(void) { }

extern "C" f32 fn_1_A6C8(void)
{
	return lbl_1_rodata_102C;
}
