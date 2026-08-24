#include "types.h"

// fn_8005F794 is two instructions -- `li r3, 0x20` followed by `blr` -- at 0x8005F794.
//
// The bounds are the function's own range and nothing more. dtk already gives
// this function an object of its own, because every one of its neighbours in
// this stretch is its own auto object too, so that split carries no
// translation-unit information. What can be said is narrower and is the reason
// the carve is safe: the function references no data at all -- no .rodata, no
// .sdata, no .bss, no .sbss -- so pulling it into its own unit cannot separate
// a static from its users the way it would for a function that owns state.
// Nothing here argues that the original file started or ended at this address.
//
// So this stays a recorded range, not a claimed boundary. When the surrounding
// translation unit is identified, fold this back into it and delete the unit.

extern "C" s32 fn_8005F794(void)
{
	return 0x20;
}
