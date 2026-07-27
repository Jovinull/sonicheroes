#include "types.h"

// Registration of a callback the stage code fires, and a no-op sitting next to
// it. Two tiny functions from fn_80013038 through 0x80013044, owning the word
// of .sbss at 0x8042C0D8.
//
// The bounds are pinned by the neighbours rather than argued from private
// data: task_create.c ends at 0x80013038 and dvd_status.cpp begins at
// 0x80013044 with its own extabindex entry, so this run is what lies between
// two units whose boundaries are already exact. That fixes the range but not
// the count, so whether these two functions were one translation unit or two
// is the minimal assumption rather than a proven fact.
//
// The .sbss word is assigned here because fn_8001303C is its setter. It is not
// private to this unit: fn_80112DAC also writes it, and four call sites
// between 0x80013688 and 0x80013C38 read it. Those readers are what give the
// type away, since each one null checks the word and then calls through it:
//
//   lwz r12, lbl_8042C0D8@sda21(r0)
//   cmplwi r12, 0x0
//   beq .L_800136A0
//   li r3, 0x0
//   mtctr r12
//   bctrl
//
// and fn_80112DAC stores the address of fn_80112BB0 into it. So it holds a
// function pointer, not an integer. All four call sites pass 0 as the only
// argument, so the parameter's type is a guess; that there is one argument is
// not.

extern "C" {

// Guessed name: nothing in the binary names this callback. Guessed parameter
// type, for the reason given above.
typedef void (*StateCallback)(s32);

void fn_80013038(void) { }

StateCallback lbl_8042C0D8;

void fn_8001303C(StateCallback callback)
{
	lbl_8042C0D8 = callback;
}
}
