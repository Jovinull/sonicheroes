// Forwards its four arguments to the optional callback stored at +0x30 of the texture module
// globals; returns null when no callback is installed. The callback's role is UNKNOWN (a
// texture-module hook).
#include "game/rw_engine.h"

typedef void* (*RwTextureHook30801A4CAC)(void* a, void* b, void* c, void* d);

extern "C" {
void* fn_801A4CAC(void* a, void* b, void* c, void* d)
{
	RwTextureHook30801A4CAC hook = *(RwTextureHook30801A4CAC*)(RW_TEXTURE_GLOBALS + 0x30);
	if (hook != 0) {
		return hook(a, b, c, d);
	}
	return 0;
}
}
