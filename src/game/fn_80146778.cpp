// Attaches the plugin with ID 0x12C: after fn_80146BF8 succeeds, clears the 0x90-byte table
// lbl_803EC3F8 and registers 0x18 bytes of engine globals with the open/close callbacks
// fn_80145F94/fn_80145FD4, keeping the offset in lbl_8042BCE0. Returns 1 when everything succeeds.
#include "game/rw_engine.h"
#include "MSL_C/string.h"

#define PLUGIN_ID_80146778 0x12C

extern "C" {
extern RwModuleInfo lbl_8042BCE0;
extern u8 lbl_803EC3F8[0x90];
s32 RwEngineRegisterPlugin(
    s32 size, u32 pluginID, void* (*open)(void*, s32, s32), void* (*close)(void*, s32, s32));
s32 fn_80146BF8(void);
void* fn_80145F94(void* instance, s32 offset, s32 size);
void* fn_80145FD4(void* instance, s32 offset, s32 size);

s32 fn_80146778(void)
{
	s32 offset;
	if (fn_80146BF8() == 0) {
		return 0;
	}
	memset(lbl_803EC3F8, 0, sizeof(lbl_803EC3F8));
	offset = RwEngineRegisterPlugin(0x18, PLUGIN_ID_80146778, fn_80145F94, fn_80145FD4);
	{
		s32 ok                     = (offset >= 0) ? 1 : 0;
		lbl_8042BCE0.globalsOffset = offset;
		return ok;
	}
}
}
