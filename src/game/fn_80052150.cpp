#include "types.h"

// The static initializer of newCameraMisc.cpp (CORROBORATED by PS2 metadata): registers the global
// TCameraMisc object _cameraMisc (lbl_8042C270) so that its destructor (fn_8005210C) runs at shutdown,
// linked through the chain node at lbl_802D5E10. The constructor is empty, so no call is emitted, as in
// __sinit_dAnim_cpp. Both objects stay in their current data units. The .ctors entry is written by hand,
// as in game/fn_8004F97C.cpp.

extern "C" {
void __register_global_object(void*, void*, void*);
void* fn_8005210C(void* p, s16 flags);

extern u8 lbl_8042C270[8];
extern u8 lbl_802D5E10[12];

void fn_80052150(void)
{
	__register_global_object(lbl_8042C270, (void*)fn_8005210C, lbl_802D5E10);
}
}

__declspec(section ".ctors") void (*const fn80052150CtorEntry)(void) = fn_80052150;
