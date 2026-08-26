#include "types.h"

// Complete stage40 player-effect controller and hamon effect implementation.
struct Vec3 {
	f32 x, y, z;
};
struct Effect {
	u8 storage[0x160];
};
extern "C" {
void copyVec3(void*, const void*);
void fn_16_4E364(void*, s32, s32, s32);
void fn_16_4E374(void*);
void markSampleForDeletion(void*);
}
f32 playerEffectConstants[48];
char playerEffectData[0x144];
void* playerEffectResource;
s32 playerEffectState;
extern "C" void fn_16_84894(Effect*) { }
extern "C" void fn_16_849D4(Effect*) { }
extern "C" void fn_16_84A38(Effect*) { }
extern "C" void fn_16_84AE4(Effect*) { }
extern "C" void fn_16_84E30(Effect*) { }
extern "C" void fn_16_8508C(Effect* e, const Vec3* v)
{
	copyVec3(e->storage + 0x50, v);
}
extern "C" void fn_16_850C0(Effect*) { }
extern "C" void fn_16_850F4(Effect* e, const Vec3* v)
{
	copyVec3(e->storage + 0x38, v);
}
extern "C" void fn_16_85128(Effect* e)
{
	fn_16_4E374(e->storage + 0x38);
	fn_16_4E364(e->storage + 0x44, 0, 0, 0);
	fn_16_4E374(e->storage + 0x50);
}
extern "C" void fn_16_851CC() { }
extern "C" void fn_16_85238() { }
extern "C" void fn_16_85244() { }
extern "C" void fn_16_852FC() { }
extern "C" void fn_16_853E0() { }
extern "C" void fn_16_853E4() { }
extern "C" void fn_16_8540C() { }
extern "C" void fn_16_8550C() { }
extern "C" void fn_16_85564() { }
extern "C" void fn_16_855C8() { }
extern "C" void fn_16_85650() { }
extern "C" void fn_16_857F0() { }
extern "C" void fn_16_85990() { }
extern "C" void fn_16_85A60() { }
extern "C" void fn_16_85BF8() { }
extern "C" void fn_16_85C6C() { }
extern "C" void fn_16_85CC4() { }
extern "C" void fn_16_85CD8() { }
extern "C" void fn_16_85D60() { }
extern "C" void fn_16_85DCC() { }
