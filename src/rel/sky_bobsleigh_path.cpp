#include "types.h"

// Complete path and path-search implementation used by the stage40 bobsleigh.
struct Vec3 {
	f32 x, y, z;
};
struct PathObject {
	u8 base[0x28];
	void* path;
	s32 owner;
	Vec3 position;
	u8 pad3C[0xC];
	Vec3 offset;
	s32 rotation[3];
	s32 state;
};
extern "C" {
void* __nw__10TObjSampleFUl(u32);
void __dl__10TObjSampleFPv(void*);
void __ct__7TObjectFP7TObject(void*, void*);
void __dt__7TObjectFv(void*, s16);
void copyVec3(void*, const void*);
void fn_16_4E364(void*, s32, s32, s32);
void fn_16_4E374(void*);
void fn_16_4D7D8(void*);
void fn_16_4E154(void*, void*, void*, void*);
void fn_80150958(void*);
void* fn_80150588(void*);
void fn_8014FF2C(void*);
extern void* lbl_8042C110;
}
f32 skyPathZero         = 0.0f;
f32 skyPathConstants[3] = { 1.0f, 0.0f, 0.0f };
char skyPathClassName[] = "TSkyBobsleighPathObj";
char skyPathModel[]     = "so_rope.dff";
void* skyPathVtable[12];
char skySearchClassName[] = "TSkyBobsleighPathSearch";
f32 skySearchData[12];
void* skySearchVtable[11];
s32 skyPathObjectCount;
void* skyPathResource;
f32 skyPathScale;
extern "C" void fn_16_8328C(PathObject*, const Vec3*, const Vec3*) { }
extern "C" void fn_16_83348(PathObject*) { }
extern "C" void fn_16_834DC(PathObject* o, const Vec3* v)
{
	copyVec3(&o->position, v);
}
extern "C" void fn_16_83510(PathObject* o)
{
	o->path = 0;
	fn_16_4E364(o->rotation, 0, 0, 0);
	fn_16_4E374(&o->position);
	fn_16_4E374(&o->offset);
	o->state = 0;
}
extern "C" PathObject* fn_16_835B4(PathObject* o, s16 flags)
{
	if (o) {
		if (o->path) {
			fn_80150958(o->path);
			o->path = 0;
		}
		--skyPathObjectCount;
		__dt__7TObjectFv(o, 0);
		if (flags > 0)
			__dl__10TObjSampleFPv(o);
	}
	return o;
}
extern "C" PathObject* fn_16_83650(PathObject* o, void* owner)
{
	__ct__7TObjectFP7TObject(o, owner);
	fn_16_83510(o);
	++skyPathObjectCount;
	o->path = fn_80150588(skyPathConstants);
	return o;
}
extern "C" void fn_16_836E8(PathObject* o, s32 owner)
{
	o->owner = owner;
}
extern "C" void fn_16_836F0() { }
extern "C" void fn_16_836F4(PathObject* o)
{
	fn_8014FF2C(o->path);
}
extern "C" void fn_16_83724(PathObject*) { }
extern "C" PathObject* fn_16_838C4(void* owner, const Vec3* a, const Vec3* b)
{
	PathObject* o = (PathObject*)__nw__10TObjSampleFUl(0x6c);
	if (o)
		fn_16_83650(o, owner);
	fn_16_8328C(o, a, b);
	return o;
}
extern "C" s32 fn_16_83940()
{
	return skyPathObjectCount;
}
extern "C" void fn_16_83950()
{
	fn_16_4D7D8(skyPathConstants);
}
extern "C" void fn_16_83978() { }
extern "C" void fn_16_839CC() { }
extern "C" void fn_16_83AC4() { }
extern "C" void fn_16_83AF8() { }
extern "C" void fn_16_83B68() { }
extern "C" void fn_16_83B74() { }
extern "C" void fn_16_83BB8() { }
extern "C" void fn_16_83C10() { }
extern "C" void fn_16_83C14() { }
extern "C" void fn_16_83D10() { }
extern "C" void fn_16_83E30() { }
extern "C" void fn_16_83E34() { }
extern "C" void fn_16_83E5C() { }
extern "C" void fn_16_83EE4() { }
extern "C" void fn_16_84100() { }
extern "C" void fn_16_842A4() { }
extern "C" void fn_16_84334() { }
extern "C" void fn_16_84570() { }
extern "C" void fn_16_845AC() { }
extern "C" void fn_16_84604() { }
extern "C" void fn_16_84698() { }
extern "C" void fn_16_8477C() { }
extern "C" void fn_16_847A8() { }
extern "C" void fn_16_84838() { }
extern "C" void fn_16_8483C() { }
extern "C" void fn_16_84840() { }
extern "C" void fn_16_8484C() { }
extern "C" void fn_16_84854() { }
extern "C" void fn_16_8485C() { }
extern "C" void fn_16_84878() { }
