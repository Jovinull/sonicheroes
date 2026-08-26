#include "types.h"

// Complete stage40 editor object used to preview every special-stage particle.
struct Params {
	s8 family, effect;
	u8 texture, blend;
	f32 value[4];
	u16 count;
	s16 life;
	f32 scale;
	u8 flags[3];
};
struct Object {
	u8 base[0x28];
	void* motion;
	void* particle;
	u8 effect, family, pad[2];
	s32 timer;
};
extern "C" {
char* strchr(const char*, s32);
void markSampleForDeletion(void*);
void* __nw__10TObjSampleFUl(u32);
void __dl__10TObjSampleFPv(void*);
void __ct__7TObjectFP7TObject(void*, void*);
void __dt__7TObjectFv(void*, s16);
void fn_8005BE6C(void*);
void dtor_8005BD3C(void*, s16);
void* setupObjClass(
    void*, char*, void*, void*, void*, void*, u32, u32, u8, u16, u16, u8, char*, char**);
void* fn_16_528A4(s32, s32, void*, void*, s32, s32, s32);
void fn_16_52D08(void*);
s32 fn_8005B8D8(void*);
u32 fn_16_52464(u32);
void fn_16_5247C(u32, u8);
void fn_16_523BC(u32);
void fn_16_522CC(u32);
void fn_16_521DC(u32);
void fn_16_520EC(u32);
u32 fn_16_52064(u32);
void fn_16_52084(u32, u8);
u32 fn_16_51FCC(u32);
void fn_16_5200C(u32, u8);
u32 fn_16_51F34(u32);
void fn_16_51F74(u32, u8);
u32 fn_16_51E9C(u32);
void fn_16_51EDC(u32, u8);
u32 fn_16_51E64(u32);
void fn_16_51E80(u32, s32);
void fn_16_51E48(u32);
u32 fn_16_51DF4(u32);
void fn_16_51E10(u32, u16);
extern void* lbl_8042C110;
}
f32 particleZero = 0.0f, particleOne = 1.0f, particleScaleMin = 0.0f, particleScaleMax = 100.0f;
char particleOwnedData[0x150];
char particleDisplay[] = "PARTICLE TEST";
char particleTypes[]   = "";
char* particleFields[16];
u8 particleRegistration[0x30];
static Params* get(Object* o)
{
	return *(Params**)((u8*)o->motion + 0x2c);
}
static u32 id(Params* p)
{
	return (u8)p->effect + (p->family ? 35 : 0);
}
extern "C" void fn_16_8150C(Object* o)
{
	Params* p = get(o);
	if (p->family < 0)
		p->family = 0;
	if (p->family > 1)
		p->family = 1;
	s8 m = p->family ? 4 : 34;
	if (p->effect < 0)
		p->effect = 0;
	if (p->effect > m)
		p->effect = m;
	if (p->texture > 4)
		p->texture = 4;
	if (p->blend > 1)
		p->blend = 1;
	if (p->life < 0)
		p->life = 0;
	if (p->life > 10000)
		p->life = 10000;
	if (!p->count)
		p->count = 1;
	if (p->count > 10000)
		p->count = 10000;
}
extern "C" void fn_16_817B0(Object* o)
{
	o->particle = 0;
	o->timer    = 0;
}
extern "C" void fn_16_817C4() { }
extern "C" u32 fn_16_82080(void*);
extern "C" void fn_16_81A74(Object*);
extern "C" void fn_16_81A30(Object*);
extern "C" void fn_16_817C8(Object* o)
{
	Params* p = get(o);
	if (!o->particle) {
		if (o->timer > 60)
			fn_16_81A74(o);
	} else {
		u32 t = fn_16_82080(o->particle);
		if (t == p->count)
			fn_16_52D08(o->particle);
		if (t >= p->count && t >= p->life) {
			fn_16_81A30(o);
			o->timer = 0;
		}
	}
	if (!fn_8005B8D8(&o->motion))
		markSampleForDeletion(o);
	o->timer++;
}
extern "C" void fn_16_81DEC(Object*);
extern "C" void fn_16_81AFC(Object*);
extern "C" void fn_16_818E8(Object* o)
{
	fn_16_81A30(o);
	Params* p = get(o);
	fn_16_8150C(o);
	if (o->effect != p->effect || o->family != p->family) {
		o->effect = p->effect;
		o->family = p->family;
		fn_16_81DEC(o);
	} else
		fn_16_81AFC(o);
	fn_16_81A74(o);
}
extern "C" Object* fn_16_819A8(Object* o, s16 f)
{
	if (o) {
		fn_16_81A30(o);
		dtor_8005BD3C(&o->motion, 0);
		__dt__7TObjectFv(o, 0);
		if (f > 0)
			__dl__10TObjSampleFPv(o);
	}
	return o;
}
extern "C" void fn_16_81A30(Object* o)
{
	if (o->particle) {
		markSampleForDeletion(o->particle);
		o->particle = 0;
	}
}
extern "C" void fn_16_81A74(Object* o)
{
	Params* p = get(o);
	fn_16_81A30(o);
	o->particle = fn_16_528A4(0, id(p), o->motion, (u8*)o->motion + 0xc, 0, 0, 0);
}
extern "C" void fn_16_81BEC(Object*) { }
extern "C" void fn_16_81AFC(Object* o)
{
	Params* p = get(o);
	u32 e     = id(p);
	fn_16_5247C(e, p->texture);
	fn_16_523BC(e);
	fn_16_522CC(e);
	fn_16_521DC(e);
	fn_16_520EC(e);
	fn_16_52084(e, p->blend);
	fn_16_5200C(e, p->flags[0]);
	fn_16_51F74(e, p->flags[1]);
	fn_16_51EDC(e, p->flags[2]);
	fn_16_51E80(e, p->life);
	fn_16_51E48(e);
	fn_16_51E10(e, p->count);
	fn_16_81BEC(o);
}
extern "C" void fn_16_81DBC(char* s, s32 c)
{
	strchr(s, c);
}
extern "C" void fn_16_81DEC(Object* o)
{
	Params* p   = get(o);
	u32 e       = id(p);
	p->texture  = fn_16_52464(e);
	p->blend    = fn_16_52064(e);
	p->flags[0] = fn_16_51FCC(e);
	p->flags[1] = fn_16_51F34(e);
	p->flags[2] = fn_16_51E9C(e);
	p->life     = fn_16_51E64(e);
	p->count    = fn_16_51DF4(e);
	fn_16_81BEC(o);
}
extern "C" Object* fn_16_81EE4(Object* o, void* owner)
{
	__ct__7TObjectFP7TObject(o, owner);
	fn_8005BE6C(&o->motion);
	fn_16_817B0(o);
	Params* p = get(o);
	if (!p->count) {
		p->effect = 0;
		o->effect = 0;
		o->family = p->family;
		fn_16_81DEC(o);
		fn_16_81A74(o);
	}
	return o;
}
extern "C" void fn_16_81FA4()
{
	Object* o = (Object*)__nw__10TObjSampleFUl(0x3c);
	if (o)
		fn_16_81EE4(o, lbl_8042C110);
}
extern "C" void fn_16_81FF4()
{
	setupObjClass(particleRegistration, particleDisplay, 0, 0, (void*)fn_16_81FA4, 0, 0, 0, 0x32,
	    0x15ec, 2, 0, particleTypes, particleFields);
}
extern "C" void fn_16_82078(Object* o)
{
	fn_16_818E8((Object*)((u8*)o - 0x28));
}
extern "C" u32 fn_16_82080(void* p)
{
	return *(u32*)((u8*)p + 0x68);
}
__declspec(section ".ctors") void (*const particleCtor)(void) = fn_16_81FF4;
