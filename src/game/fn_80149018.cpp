// Attaches the plugin with ID 0x120 (HYPOTHESIS: a RenderWare toolkit plugin attach): registers its
// engine open/close callbacks and 4-byte material, atomic and world-sector extensions (offsets kept
// in lbl_8042C858, lbl_8042C85C and lbl_8042C860) together with their stream callbacks, then runs
// fn_80145F2C. Returns 1 when every step succeeds.
#include "types.h"

#define PLUGIN_ID_80149018 0x120
#define CB(f)              ((void*)(f))

extern "C" {
extern s32 lbl_8042C858;
extern s32 lbl_8042C85C;
extern s32 lbl_8042C860;
s32 RwEngineRegisterPlugin(s32 size, u32 pluginID, void* open, void* close);
// HYPOTHESIS: RpMaterial/RpAtomic/RpWorldSector RegisterPlugin and RegisterPluginStream.
s32 fn_801549E8(s32 size, u32 pluginID, void* ctor, void* dtor, void* copy);
s32 fn_801520D0(s32 size, u32 pluginID, void* ctor, void* dtor, void* copy);
s32 fn_80158958(s32 size, u32 pluginID, void* ctor, void* dtor, void* copy);
s32 fn_80154A28(u32 pluginID, void* read, void* write, void* getSize);
s32 fn_80152150(u32 pluginID, void* read, void* write, void* getSize);
s32 fn_80158998(u32 pluginID, void* read, void* write, void* getSize);
s32 fn_80145F2C(void);
void fn_80147998(void);
void fn_80147928(void);
void fn_80147A38(void);
void fn_80147A48(void);
void fn_80147B84(void);
void fn_801482F8(void);
void fn_80147F98(void);
void fn_80148878(void);
void fn_801489BC(void);
void fn_801489CC(void);
void fn_801489DC(void);
void fn_80148A2C(void);
void fn_801489F8(void);
void fn_80148A94(void);
void fn_80148AB4(void);
void fn_80148AC4(void);
void fn_80148AD4(void);
void fn_80148B24(void);
void fn_80148AF0(void);
void fn_80148B8C(void);

s32 fn_80149018(void)
{
	if (RwEngineRegisterPlugin(0, PLUGIN_ID_80149018, CB(fn_80147998), CB(fn_80147928)) < 0) {
		return 0;
	}
	lbl_8042C858
	    = fn_801549E8(4, PLUGIN_ID_80149018, CB(fn_80147A38), CB(fn_80147A48), CB(fn_80147B84));
	if (lbl_8042C858 < 0) {
		return 0;
	}
	if (fn_80154A28(PLUGIN_ID_80149018, CB(fn_801482F8), CB(fn_80147F98), CB(fn_80148878)) < 0) {
		return 0;
	}
	lbl_8042C85C
	    = fn_801520D0(4, PLUGIN_ID_80149018, CB(fn_801489BC), CB(fn_801489CC), CB(fn_801489DC));
	if (lbl_8042C85C < 0) {
		return 0;
	}
	if (fn_80152150(PLUGIN_ID_80149018, CB(fn_80148A2C), CB(fn_801489F8), CB(fn_80148A94)) < 0) {
		return 0;
	}
	lbl_8042C860
	    = fn_80158958(4, PLUGIN_ID_80149018, CB(fn_80148AB4), CB(fn_80148AC4), CB(fn_80148AD4));
	if (lbl_8042C860 < 0) {
		return 0;
	}
	if (fn_80158998(PLUGIN_ID_80149018, CB(fn_80148B24), CB(fn_80148AF0), CB(fn_80148B8C)) < 0) {
		return 0;
	}
	return (fn_80145F2C() != 0) ? 1 : 0;
}
}
