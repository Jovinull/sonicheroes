// Attaches the plugin with ID 0x11E (HYPOTHESIS: a frame plugin's ...PluginAttach): registers its
// engine open/close callbacks, an 8-byte frame extension (offset kept in lbl_8042C828) with its
// constructor/destructor/copy callbacks, and the frame stream callbacks. Returns 1 when every
// registration succeeds.
#include "types.h"

#define PLUGIN_ID_8013ECE0 0x11E

typedef void* (*Callback8013ECE0)(void*, s32, s32);

extern "C" {
extern s32 lbl_8042C828;
s32 RwEngineRegisterPlugin(
    s32 size, u32 pluginID, void* (*open)(void*, s32, s32), void* (*close)(void*, s32, s32));
// HYPOTHESIS: RwFrameRegisterPlugin and RwFrameRegisterPluginStream.
s32 fn_8019EEC0(s32 size, u32 pluginID, Callback8013ECE0 ctor, Callback8013ECE0 dtor,
    void* (*copy)(void*, void*, s32, s32));
s32 fn_8019A1DC(u32 pluginID, void* read, void* write, void* getSize);
void* fn_8013E5A8(void* instance, s32 offset, s32 size);
void* fn_8013E688(void* instance, s32 offset, s32 size);
void* fn_8013E6D8(void* object, s32 offset, s32 size);
void* fn_8013E6F4(void* object, s32 offset, s32 size);
void* fn_8013E78C(void* dst, void* src, s32 offset, s32 size);
void fn_8013EA38(void);
void fn_8013E87C(void);
void fn_8013EC7C(void);

s32 fn_8013ECE0(void)
{
	if (RwEngineRegisterPlugin(0, PLUGIN_ID_8013ECE0, fn_8013E5A8, fn_8013E688) < 0) {
		return 0;
	}
	lbl_8042C828 = fn_8019EEC0(8, PLUGIN_ID_8013ECE0, fn_8013E6D8, fn_8013E6F4, fn_8013E78C);
	s32 stream   = fn_8019A1DC(
	    PLUGIN_ID_8013ECE0, (void*)fn_8013EA38, (void*)fn_8013E87C, (void*)fn_8013EC7C);
	s32 result = 0;
	if (stream >= 0) {
		if (lbl_8042C828 >= 0) {
			result = 1;
		}
	}
	return result;
}
}
