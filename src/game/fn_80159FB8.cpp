// Attaches the world plugin family (HYPOTHESIS: RpWorldPluginAttach): registers the engine globals
// of the modules with IDs 0x501-0x505, 0x50A, 0x507 and 0x50B with their open/close callbacks
// (a negative result from any of them fails the attach), then runs the further attach steps
// fn_8015B5C8, fn_8014FE38 and fn_8015C988. Returns 1 when everything succeeds.
#include "types.h"

typedef void* (*RwModuleCallback80159FB8)(void* instance, s32 offset, s32 size);

extern "C" {
s32 RwEngineRegisterPlugin(
    s32 size, u32 pluginID, RwModuleCallback80159FB8 open, RwModuleCallback80159FB8 close);
void* fn_80154770(void* instance, s32 offset, s32 size);
void* fn_801547FC(void* instance, s32 offset, s32 size);
void* fn_801556E0(void* instance, s32 offset, s32 size);
void* fn_80155688(void* instance, s32 offset, s32 size);
void* fn_8015225C(void* instance, s32 offset, s32 size);
void* fn_80152274(void* instance, s32 offset, s32 size);
void* fn_8014FD48(void* instance, s32 offset, s32 size);
void* fn_8014FC8C(void* instance, s32 offset, s32 size);
void* fn_80154580(void* instance, s32 offset, s32 size);
void* fn_80154508(void* instance, s32 offset, s32 size);
void* fn_801588F0(void* instance, s32 offset, s32 size);
void* fn_80158904(void* instance, s32 offset, s32 size);
void* fn_80159120(void* instance, s32 offset, s32 size);
void* fn_801590B8(void* instance, s32 offset, s32 size);
void* fn_8014EFD4(void* instance, s32 offset, s32 size);
void* fn_8014EFC0(void* instance, s32 offset, s32 size);
s32 fn_8015B5C8(void);
s32 fn_8014FE38(void);
s32 fn_8015C988(void);

s32 fn_80159FB8(void)
{
	s32 status;
	status = RwEngineRegisterPlugin(4, 0x501, fn_80154770, fn_801547FC);
	status |= RwEngineRegisterPlugin(0x30, 0x502, fn_801556E0, fn_80155688);
	status |= RwEngineRegisterPlugin(4, 0x503, fn_8015225C, fn_80152274);
	status |= RwEngineRegisterPlugin(8, 0x504, fn_8014FD48, fn_8014FC8C);
	status |= RwEngineRegisterPlugin(4, 0x505, fn_80154580, fn_80154508);
	status |= RwEngineRegisterPlugin(0, 0x50A, fn_801588F0, fn_80158904);
	status |= RwEngineRegisterPlugin(0xC, 0x507, fn_80159120, fn_801590B8);
	status |= RwEngineRegisterPlugin(0, 0x50B, fn_8014EFD4, fn_8014EFC0);
	if (status < 0) {
		return 0;
	}
	if (fn_8015B5C8() == 0) {
		return 0;
	}
	if (fn_8014FE38() == 0) {
		return 0;
	}
	return (fn_8015C988() != 0) ? 1 : 0;
}
}
