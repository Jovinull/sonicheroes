#include "game/setObj.h"

// The static initializer of setGen.cpp (CORROBORATED by PS2 metadata): constructs
// TObjSetGen::objTable, the 0x800-entry SETOBJ_PARAM table at lbl_802D63A0, by running
// SETOBJ_PARAM's constructor (fn_8005B8A0) on each entry. It has no destructor. The .ctors entry is
// written by hand, as in game/fn_8004F97C.cpp.

extern "C" void __construct_array(void* base, void* ctor, void* dtor, s32 size, s32 count);
extern "C" void fn_8005B8A0(SETOBJ_PARAM* param);
extern "C" SETOBJ_PARAM lbl_802D63A0[0x800];

extern "C" void fn_8005B864(void)
{
	__construct_array(lbl_802D63A0, (void*)fn_8005B8A0, 0, sizeof(SETOBJ_PARAM), 0x800);
}

__declspec(section ".ctors") void (*const fn8005B864CtorEntry)(void) = fn_8005B864;
