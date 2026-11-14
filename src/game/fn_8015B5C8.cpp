// Attaches the world-sector plugin family (HYPOTHESIS: a RenderWare world plugin attach for IDs
// 0x509, 0x50E, 0x510 and 0x1F): registers engine globals and camera, atomic, clump and light
// extensions for 0x509 (offsets kept in lbl_8042C918-lbl_8042C924), geometry/sector extensions and
// stream callbacks for 0x50E and 0x510, and atomic/sector/material stream callbacks for 0x1F, then
// runs fn_8015BFFC. Any negative registration result fails the attach. Returns 1 on success.
#include "types.h"

#define CB(f) ((void*)(f))

extern "C" {
// Declared volatile as a reconstruction aid: the retail code reloads each offset after storing it
// before folding it into the status.
extern volatile s32 lbl_8042C918;
extern volatile s32 lbl_8042C91C;
extern volatile s32 lbl_8042C920;
extern volatile s32 lbl_8042C924;
s32 RwEngineRegisterPlugin(s32 size, u32 pluginID, void* open, void* close);
// HYPOTHESIS: Rw/Rp ...RegisterPlugin (size, ID, constructor, destructor, copy) and
// ...RegisterPluginStream (ID, read, write, getSize) for cameras, atomics, clumps, lights,
// geometries, world sectors and materials.
s32 fn_8019D138(s32 size, u32 pluginID, void* ctor, void* dtor, void* copy);
s32 fn_801520D0(s32 size, u32 pluginID, void* ctor, void* dtor, void* copy);
s32 fn_80152110(s32 size, u32 pluginID, void* ctor, void* dtor, void* copy);
s32 fn_801541BC(s32 size, u32 pluginID, void* ctor, void* dtor, void* copy);
s32 fn_80152FDC(s32 size, u32 pluginID, void* ctor, void* dtor, void* copy);
s32 fn_80158958(s32 size, u32 pluginID, void* ctor, void* dtor, void* copy);
s32 fn_80159F3C(s32 size, u32 pluginID, void* ctor, void* dtor, void* copy);
s32 fn_801549E8(s32 size, u32 pluginID, void* ctor, void* dtor, void* copy);
s32 fn_8015301C(u32 pluginID, void* read, void* write, void* getSize);
s32 fn_80158998(u32 pluginID, void* read, void* write, void* getSize);
s32 fn_80152150(u32 pluginID, void* read, void* write, void* getSize);
s32 fn_80159F7C(u32 pluginID, void* read, void* write, void* getSize);
s32 fn_80154A28(u32 pluginID, void* read, void* write, void* getSize);
s32 fn_8015BFFC(void);
void fn_8015A120(void);
void fn_8015A224(void);
void fn_8015A3E4(void);
void fn_8015A49C(void);
void fn_8015A440(void);
void fn_8015A8EC(void);
void fn_8015A928(void);
void fn_8015A924(void);
void fn_8015A9F8(void);
void fn_8015AA64(void);
void fn_8015AA20(void);
void fn_8015AD00(void);
void fn_8015AD6C(void);
void fn_8015AD28(void);
void fn_8015B33C(void);
void fn_8015B308(void);
void fn_8015B398(void);
void fn_8015B524(void);
void fn_8015B4D0(void);
void fn_8015B590(void);
void fn_8015B3E4(void);
void fn_8015B3C0(void);
void fn_8015B428(void);
void fn_8015B46C(void);
void fn_8015B448(void);
void fn_8015B4B0(void);
void fn_8014F028(void);
void fn_8014F0A4(void);
void fn_8014F120(void);
void fn_8014DB78(void);
void fn_8014DBF4(void);
void fn_8014DC70(void);
void fn_8014DC98(void);
void fn_8014DD14(void);
void fn_8014DD90(void);
void fn_8015460C(void);
void fn_80154688(void);
void fn_80154704(void);

s32 fn_8015B5C8(void)
{
	s32 status;
	status       = RwEngineRegisterPlugin(0xC, 0x509, CB(fn_8015A120), CB(fn_8015A224));
	lbl_8042C918 = fn_8019D138(0x1C, 0x509, CB(fn_8015A3E4), CB(fn_8015A49C), CB(fn_8015A440));
	status |= lbl_8042C918;
	lbl_8042C91C = fn_801520D0(8, 0x509, CB(fn_8015A8EC), CB(fn_8015A928), CB(fn_8015A924));
	status |= lbl_8042C91C;
	lbl_8042C920 = fn_80152110(8, 0x509, CB(fn_8015A9F8), CB(fn_8015AA64), CB(fn_8015AA20));
	status |= lbl_8042C920;
	lbl_8042C924 = fn_801541BC(8, 0x509, CB(fn_8015AD00), CB(fn_8015AD6C), CB(fn_8015AD28));
	status |= lbl_8042C924;
	status |= fn_80152FDC(0, 0x50E, 0, 0, 0);
	status |= fn_80158958(0, 0x50E, 0, 0, 0);
	status |= fn_8015301C(0x50E, CB(fn_8015B33C), CB(fn_8015B308), CB(fn_8015B398));
	status |= fn_80158998(0x50E, CB(fn_8015B524), CB(fn_8015B4D0), CB(fn_8015B590));
	status |= fn_80152FDC(0, 0x510, 0, 0, 0);
	status |= fn_80158958(0, 0x510, 0, 0, 0);
	status |= fn_8015301C(0x510, CB(fn_8015B3E4), CB(fn_8015B3C0), CB(fn_8015B428));
	status |= fn_80158998(0x510, CB(fn_8015B46C), CB(fn_8015B448), CB(fn_8015B4B0));
	status |= fn_801520D0(0, 0x1F, 0, 0, 0);
	status |= fn_80152150(0x1F, CB(fn_8014F028), CB(fn_8014F0A4), CB(fn_8014F120));
	status |= fn_80159F3C(0, 0x1F, 0, 0, 0);
	status |= fn_80159F7C(0x1F, CB(fn_8014DB78), CB(fn_8014DBF4), CB(fn_8014DC70));
	status |= fn_80158958(0, 0x1F, 0, 0, 0);
	status |= fn_80158998(0x1F, CB(fn_8014DC98), CB(fn_8014DD14), CB(fn_8014DD90));
	status |= fn_801549E8(0, 0x1F, 0, 0, 0);
	status |= fn_80154A28(0x1F, CB(fn_8015460C), CB(fn_80154688), CB(fn_80154704));
	if (status < 0) {
		return 0;
	}
	return (fn_8015BFFC() != 0) ? 1 : 0;
}
}
