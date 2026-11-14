// Ends rendering with the plugin data of object (at the offset lbl_8042C918): clears the engine's
// current world and calls the end callback at +0x14. Plugin and object names are UNKNOWN. Returns
// the callback's result.
#include "game/rw_engine.h"

struct Ext8015A304 {
	u8 pad0[0x14];
	void* (*end)(void* object); // 0x14
};

extern "C" {
extern s32 lbl_8042C918;

void* fn_8015A304(void* object)
{
	Ext8015A304* ext       = (Ext8015A304*)((u8*)object + lbl_8042C918);
	lbl_8042C9A4->curWorld = 0;
	return ext->end(object);
}
}
