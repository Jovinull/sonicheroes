// Attaches the plugin with ID 0x105 (HYPOTHESIS: a RenderWare toolkit plugin's ...PluginAttach):
// registers its engine open/close callbacks, a 12-byte atomic extension (offset kept in
// lbl_8042C868) and a 12-byte geometry extension (offset kept in lbl_8042C86C) with their
// constructor/destructor/copy callbacks, and the geometry stream callbacks. Returns 1 when every
// registration succeeds.
#include "types.h"

#define PLUGIN_ID_8014A90C 0x105

typedef void* (*Callback8014A90C)(void*, s32, s32);

extern "C" {
// Declared volatile as a reconstruction aid: the retail code reloads each offset after storing it
// before testing it.
extern volatile s32 lbl_8042C868;
extern volatile s32 lbl_8042C86C;
s32 RwEngineRegisterPlugin(
    s32 size, u32 pluginID, void* (*open)(void*, s32, s32), void* (*close)(void*, s32, s32));
// HYPOTHESIS: RpAtomicRegisterPlugin, RpGeometryRegisterPlugin and RpGeometryRegisterPluginStream.
s32 fn_801520D0(s32 size, u32 pluginID, Callback8014A90C ctor, Callback8014A90C dtor,
    void* (*copy)(void*, void*, s32, s32));
s32 fn_80152FDC(s32 size, u32 pluginID, Callback8014A90C ctor, Callback8014A90C dtor,
    void* (*copy)(void*, void*, s32, s32));
s32 fn_8015301C(u32 pluginID, void* read, void* write, void* getSize);
void* fn_80149E2C(void* instance, s32 offset, s32 size);
void* fn_80149E40(void* instance, s32 offset, s32 size);
void* fn_80149E54(void* object, s32 offset, s32 size);
void* fn_80149E74(void* dst, void* src, s32 offset, s32 size);
void* fn_8014A37C(void* object, s32 offset, s32 size);
void* fn_80149FD8(void* object, s32 offset, s32 size);
void* fn_8014A03C(void* dst, void* src, s32 offset, s32 size);
void fn_8014A1E4(void);
void fn_8014A0E0(void);
void fn_8014A32C(void);

s32 fn_8014A90C(void)
{
	if (RwEngineRegisterPlugin(0, PLUGIN_ID_8014A90C, fn_80149E2C, fn_80149E40) < 0) {
		return 0;
	}
	lbl_8042C868 = fn_801520D0(0xC, PLUGIN_ID_8014A90C, fn_80149E54, fn_80149E54, fn_80149E74);
	if (lbl_8042C868 < 0) {
		return 0;
	}
	lbl_8042C86C = fn_80152FDC(0xC, PLUGIN_ID_8014A90C, fn_8014A37C, fn_80149FD8, fn_8014A03C);
	if (lbl_8042C86C < 0) {
		return 0;
	}
	return (fn_8015301C(
	            PLUGIN_ID_8014A90C, (void*)fn_8014A1E4, (void*)fn_8014A0E0, (void*)fn_8014A32C)
	           >= 0)
	    ? 1
	    : 0;
}
}
