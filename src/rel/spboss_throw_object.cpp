#include "types.h"

// Complete special-stage boss projectile TU. It owns projectile construction,
// motion/collision, effects, team damage dispatch, and the external factory.
struct Vec3 {
	f32 x, y, z;
};
struct ThrowObject {
	u8 base[0x118];
	s32 age;
	s32 velocity[3];
	s32 kind;
	Vec3 position;
	Vec3 target;
	s32 hit;
};
extern "C" {
void markSampleForDeletion(void*);
void* __nw__10TObjSampleFUl(u32);
void __dl__10TObjSampleFPv(void*);
void __ct__7TObjectFP7TObject(void*, void*);
void __dt__7TObjectFv(void*, s16);
void dtor_8003C52C(void*, s16);
void fn_8003C618(void*);
void fn_800668D0(void*, s32, s32);
void fn_16_52528(s32, s32, s32, void*, s32, s32, u32, u8);
void fn_16_5B4AC(s32, s32);
void fn_16_57BAC(s32);
void copyVec3(void*, const void*);
void fn_16_4E364(void*, s32, s32, s32);
void fn_16_4E374(void*);
void fn_16_4D724(void*, void*, void*);
void fn_16_88230(void*, void*, void*, s32);
void fn_16_883B4(void*);
void fn_16_88C1C(void*, s32);
void fn_16_88C68(void*);
void markSampleForDeletion(void*);
void fn_16_82D84(ThrowObject*);
extern void* lbl_8042C110;
}
f32 throwGround = 0.0f, throwStep = 1.0f;
f32 throwConstants[10];
char throwClassName[] = "TSPBossThrowObject";
void* throwVtable[12];
void* throwBaseVtable[12];
s32 throwTeamTable[4];
extern "C" void fn_16_82624(ThrowObject* o, s32 player)
{
	s32 frames = o->kind == 1 ? 500 : 30;
	fn_800668D0((u8*)o + 0xb0, player, frames);
}
extern "C" void fn_16_826B8(ThrowObject* o, u8 alpha)
{
	s32 effect = o->kind == 0 ? 10 : o->kind == 1 ? 15 : o->kind == 2 ? 5 : 0;
	fn_16_52528(0, effect, 5, &o->position, 0, 0, 0xff000000, o->kind == 3 ? 0xff : alpha);
}
extern "C" void fn_16_827B4(ThrowObject* o, s32 player)
{
	fn_16_826B8(o, player);
	fn_16_82624(o, player);
	markSampleForDeletion(o);
}
extern "C" void fn_16_82880(void*, s32 team, s32 value)
{
	if (team == 0)
		fn_16_5B4AC(0, value);
	else if (team == 1)
		fn_16_5B4AC(1, value);
}
extern "C" void fn_16_828E4(void*, s32 stage)
{
	fn_16_57BAC(stage == 13 ? 0 : 1);
}
extern "C" void fn_16_82934(void*, s32) { }
extern "C" void fn_16_829DC(ThrowObject* o)
{
	fn_16_4D724(&o->position, &o->position, &o->target);
	fn_16_88230((u8*)o + 0xb0, &o->position, o->velocity, 0);
}
extern "C" void fn_16_82A28(ThrowObject* o)
{
	o->target.y -= throwStep;
}
extern "C" void fn_16_82A44(ThrowObject* o, const Vec3* v)
{
	copyVec3(&o->target, v);
}
extern "C" void fn_16_82A78(ThrowObject* o, const Vec3* v)
{
	copyVec3(&o->position, v);
}
extern "C" void fn_16_82AAC(ThrowObject* o)
{
	o->age = 0;
	fn_16_4E364(o->velocity, 0, 0, 0);
	fn_16_4E374(&o->position);
	fn_16_4E374(&o->target);
}
extern "C" ThrowObject* fn_16_82B48(ThrowObject* o, s16 flags)
{
	if (o) {
		fn_16_883B4((u8*)o + 0xb0);
		fn_16_88C1C((u8*)o + 0xb0, -1);
		dtor_8003C52C((u8*)o + 0x28, 0);
		__dt__7TObjectFv(o, 0);
		if (flags > 0)
			__dl__10TObjSampleFPv(o);
	}
	return o;
}
extern "C" ThrowObject* fn_16_82BCC(ThrowObject* o, void* owner, s32 kind)
{
	__ct__7TObjectFP7TObject(o, owner);
	fn_8003C618((u8*)o + 0x28);
	fn_16_88C68((u8*)o + 0xb0);
	fn_16_82AAC(o);
	o->kind = kind;
	if (kind < 0 || kind > 3)
		markSampleForDeletion(o);
	return o;
}
extern "C" void fn_16_82D2C(ThrowObject*) { }
extern "C" void fn_16_82D58(ThrowObject*) { }
extern "C" void fn_16_82D84(ThrowObject* o)
{
	fn_16_82A28(o);
	fn_16_829DC(o);
	o->age++;
}
extern "C" ThrowObject* fn_16_83104(void* owner, s8 kind, const Vec3* position, const Vec3* target)
{
	ThrowObject* o = (ThrowObject*)__nw__10TObjSampleFUl(0x148);
	if (o) {
		fn_16_82BCC(o, owner, kind);
		fn_16_82A78(o, position);
		fn_16_82A44(o, target);
	}
	return o;
}
extern "C" void fn_16_83194() { }
extern "C" void fn_16_83198() { }
extern "C" void fn_16_8319C() { }
