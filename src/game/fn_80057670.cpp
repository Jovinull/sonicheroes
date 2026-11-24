// Static initializer of a global task object (HYPOTHESIS; the object's class is UNKNOWN, its
// vtable is lbl_80242C18 and its destructor fn_80057700): constructs the TObject base of the
// 0x34-byte global lbl_802D636C without a parent, installs the class vtable and registers the
// object so its destructor runs at shutdown (chain node lbl_802D6360). The global objects stay in
// their current data units; the .ctors entry is written by hand, as in game/fn_80052150.cpp.
#include "types.h"

struct Global80057670 {
	u8 pad0[0x18];
	void* vtable; // 0x18
	u8 pad1C[0x34 - 0x1C];
};

extern "C" {
void __register_global_object(void* object, void* destructor, void* node);
void __ct__7TObjectFP7TObject(void* object, void* parent);
void* fn_80057700(void* p, s16 flags);

extern Global80057670 lbl_802D636C;
extern u8 lbl_802D6360[12];
extern u8 lbl_80242C18[];

void fn_80057670(void)
{
	__ct__7TObjectFP7TObject(&lbl_802D636C, NULL);
	lbl_802D636C.vtable = lbl_80242C18;
	__register_global_object(&lbl_802D636C, (void*)fn_80057700, lbl_802D6360);
}
}

__declspec(section ".ctors") void (*const fn80057670CtorEntry)(void) = fn_80057670;
