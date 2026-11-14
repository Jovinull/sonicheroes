// Starts rendering with the plugin data of object (at the offset lbl_8042C918): makes its world
// pointer (+0xC) the engine's current world, advances the engine render frame and calls the render
// callback at +0x10. Plugin and object names are UNKNOWN. Returns the callback's result.
#include "game/rw_engine.h"

struct Ext8015A2B8 {
	u8 pad0[0xC];
	void* world;                   // 0xC
	void* (*render)(void* object); // 0x10
};

extern "C" {
extern s32 lbl_8042C918;

void* fn_8015A2B8(void* object)
{
	Ext8015A2B8* ext       = (Ext8015A2B8*)((u8*)object + lbl_8042C918);
	lbl_8042C9A4->curWorld = ext->world;
	lbl_8042C9A4->renderFrame++;
	return ext->render(object);
}
}
