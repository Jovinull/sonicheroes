#include "types.h"

// The original object retains its standalone helpers and editor storage even
// when no external relocation names them.
#pragma force_active on

typedef struct Vec3 {
	f32 x;
	f32 y;
	f32 z;
} Vec3;

typedef struct Frame {
	Vec3 position;
	s32 angleY;
	s32 angleZ;
	s32 angleX;
} Frame;

typedef struct TObject {
	const char* className;
	u16 signal;
	u16 tag;
	struct TObject* prev;
	struct TObject* next;
	struct TObject* parent;
	struct TObject* child;
	void** vtable;
	s16 unk1C;
	s16 objectSize;
	s16 unk20;
	s16 unk22;
	s16 unk24;
	s16 unk26;
} TObject;

typedef struct Motion {
	Frame* frame;
	void** vtable;
} Motion;

typedef struct ModelHolder {
	void* resource;
	u8* model;
} ModelHolder;

typedef struct Transform {
	u8 pad00[0x60];
	Vec3 position;
	s32 angleY;
	s32 angleZ;
	s32 angleX;
	u32 pad78;
	Vec3 previousPosition;
} Transform;

typedef struct BlinkLight {
	TObject base;
	Motion motion;
	Transform transform;
	s16 particleTimer;
	s16 padBA;
	f32 phase;
	ModelHolder* model;
	void* particle;
} BlinkLight;

typedef struct ModelAsset {
	u32 words[9];
	void** resource;
	char* filename;
} ModelAsset;

typedef struct ObjectEntry {
	const char* name;
	void (*load)(void);
	void (*unload)(void);
	void (*create)(void);
	void (*reset)(void);
	u32 flags;
	u32 unk18;
	u16 unk1C;
	s16 unk1E;
	u8 unk20;
	u8 unk21;
	u8 pad22[2];
	const char* fieldTypes;
	const char** fieldNames;
} ObjectEntry;

class BlinkLightPrimaryBase
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	u8 layoutPad[0x24];
};

class BlinkLightEditBase
{
public:
	virtual void editOnChange(void*);
};

class BlinkLightVirtual : public BlinkLightPrimaryBase, public BlinkLightEditBase
{
public:
	virtual void editOnChange(void*);
};

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;
extern "C" void* lbl_8042C180;
extern "C" void* lbl_8042C1D0;
extern "C" void* lbl_8042C298;
extern "C" Vec3 lbl_80239978;
extern "C" Vec3 lbl_80239984;
extern "C" Vec3 lbl_80239990;
extern "C" char lbl_802FF5A0[];

extern "C" void __ct__7TObjectFP7TObject(TObject*, void*);
extern "C" void __dt__7TObjectFv(TObject*, s32);
extern "C" void fn_80017854(void);
extern "C" void fn_800189A4(void*, TObject*);
extern "C" void* fn_80018A34(void*, u32);
extern "C" void fn_8003BC38(void*);
extern "C" void fn_8003BF04(void*, const u32*, s32, s32);
extern "C" void fn_8003C618(void*);
extern "C" void dtor_8003C52C(void*, s32);
extern "C" void* fn_800628D0(s32, const Vec3*, const Vec3*);
extern "C" s32 fn_8005B8BC(Motion*);
extern "C" s32 fn_8005B8D8(Motion*);
extern "C" s32 fn_8005B9F0(Motion*);
extern "C" void dtor_8005BD3C(Motion*, s32);
extern "C" void fn_8005BE6C(Motion*);
extern "C" void fn_800BC9F4(void*, void*);
extern "C" void fn_800D1108(void*, f32*, f32*, f32*);
extern "C" f32 fn_800D7AE4(s32);
extern "C" f32 fn_800D7B00(s32);
extern "C" void fn_80195790(void*, const Vec3*, f32, f32, s32);
extern "C" void fn_8019E880(void*);
extern "C" void* fn_8019E8EC(void*);
extern "C" void fn_8019EB94(void*, Frame*, s32);
extern "C" void fn_801A4C84(void*);

extern "C" void* fn_9_752F4(ModelHolder*, s32);
extern "C" void fn_9_75764(ModelHolder*, f32);
extern "C" void fn_9_757C4(ModelHolder*, void*, s32);
extern "C" void fn_9_75888(void*);
extern "C" void fn_9_75D2C(ModelAsset*, s32, ModelHolder**, s32);
extern "C" void fn_9_76448(ModelAsset*);
extern "C" void fn_9_765CC(ModelAsset*, s32);

extern "C" void fn_9_1A9B4(void);
extern "C" void objDefaultTDisp(void);
extern "C" void objDefaultPDisp(void);
extern "C" void objDefaultImmAftSetRaster(void);
extern "C" void objDefaultDebug(void);
extern "C" void objDefaultRender(void);

extern "C" void* blinkLightResource[];
extern "C" char blinkLightFilename[];
extern "C" ModelAsset blinkLightAsset;
extern "C" const u32 blinkLightCollision[24];
extern "C" const f32 blinkLightZeroPool[11];
extern "C" char blinkLightClassName[];
extern "C" const char* blinkLightClassNamePtr;
extern "C" void* __vt__17BlinkLightVirtual[];
#define blinkLightVtable __vt__17BlinkLightVirtual

extern "C" void blinkLightCreateParticle(BlinkLight* object)
{
	if (object->particle != NULL) {
		void* transform = fn_8019E8EC(object->particle);
		Vec3 position;
		Vec3 angle;

		position.x = ((f32*)transform)[12];
		position.y = ((f32*)transform)[13];
		position.z = ((f32*)transform)[14];
		fn_800D1108(transform, &angle.x, &angle.y, &angle.z);
		fn_800628D0(5, &position, &angle);
	}
}

extern "C" void blinkLightDestroyClump(BlinkLight*, ModelHolder** model)
{
	fn_9_75888(model);
}

extern "C" void blinkLightCloneClump(BlinkLight*, ModelHolder** model)
{
	fn_9_75D2C(&blinkLightAsset, 0, model, 0);
	fn_9_757C4(*model, &blinkLightAsset.words[5], 0);
}

extern "C" void blinkLightSetPosition(BlinkLight* object)
{
	u8* model = object->model->model;
	f32 c;
	f32 s;

	c = fn_800D7B00(object->motion.frame->angleZ);
	s = 1.0f - fn_800D7AE4(object->motion.frame->angleZ);
	fn_80195790(model + 0x10, &lbl_80239984, s, c, 0);
	fn_8019E880(model);

	c = fn_800D7B00(object->motion.frame->angleY);
	s = 1.0f - fn_800D7AE4(object->motion.frame->angleY);
	fn_80195790(model + 0x10, &lbl_80239978, s, c, 2);
	fn_8019E880(model);

	c = fn_800D7B00(object->motion.frame->angleX);
	s = 1.0f - fn_800D7AE4(object->motion.frame->angleX);
	fn_80195790(model + 0x10, &lbl_80239990, s, c, 2);
	fn_8019E880(model);
	fn_8019EB94(model, object->motion.frame, 2);
}

extern "C" void blinkLightExec(BlinkLight* object)
{
	f32 duration = ((f32*)&blinkLightAsset)[7];

	if (fn_8005B9F0(&object->motion) != 0 || fn_8005B8BC(&object->motion) != 0) {
		object->base.signal |= 1;
		return;
	}

	if (((s8*)lbl_8042C180)[0x1F] != 0) {
		Frame* frame                       = object->motion.frame;
		object->transform.previousPosition = object->transform.position;
		object->transform.position         = frame->position;
		object->transform.angleY           = frame->angleY;
		object->transform.angleZ           = frame->angleZ;
		object->transform.angleX           = frame->angleX;
		fn_8003BC38(&object->transform);
		return;
	}

	if (fn_8005B8D8(&object->motion) != 0) {
		blinkLightSetPosition(object);
	} else {
		object->phase += 0.0166667f;
		if (object->phase >= duration) {
			object->phase -= duration;
		}
		fn_9_75764(object->model, object->phase);

		if (--object->particleTimer <= 0) {
			blinkLightCreateParticle(object);
			object->particleTimer = 60;
		}
		Frame* frame                       = object->motion.frame;
		object->transform.previousPosition = object->transform.position;
		object->transform.position         = frame->position;
		object->transform.angleY           = frame->angleY;
		object->transform.angleZ           = frame->angleZ;
		object->transform.angleX           = frame->angleX;
		fn_8003BC38(&object->transform);
	}
}

void BlinkLightVirtual::editOnChange(void*) { }

extern "C" BlinkLight* blinkLightDtor(BlinkLight* object, s16 flags)
{
	if (object != NULL) {
		object->base.vtable   = blinkLightVtable;
		object->motion.vtable = blinkLightVtable + 11;
		fn_9_75888(&object->model);
		dtor_8003C52C(&object->transform, 0);
		dtor_8005BD3C(&object->motion, 0);
		__dt__7TObjectFv(&object->base, 0);
		if (flags > 0) {
			fn_800189A4(lbl_8042C148, &object->base);
		}
	}
	return object;
}

extern "C" BlinkLight* blinkLightCtor(BlinkLight* object, void* owner)
{
	__ct__7TObjectFP7TObject(&object->base, owner);
	fn_8005BE6C(&object->motion);
	fn_8003C618(&object->transform);

	object->base.vtable     = blinkLightVtable;
	object->motion.vtable   = blinkLightVtable + 11;
	object->base.className  = blinkLightClassNamePtr;
	object->base.objectSize = sizeof(BlinkLight);
	object->phase           = blinkLightZeroPool[0];

	blinkLightCloneClump(object, &object->model);
	blinkLightSetPosition(object);
	object->particle      = fn_9_752F4(object->model, 1);
	object->particleTimer = 0;
	fn_8003BF04(&object->transform, blinkLightCollision, 2, 4);
	return object;
}

extern "C" void blinkLightEnd(void)
{
	ModelAsset* asset = &blinkLightAsset;
	for (u8 i = 0; i < 1; i++) {
		fn_9_76448(asset);
		asset++;
	}
}

extern "C" void blinkLightInit(void)
{
	void* stage = *(void**)((u8*)lbl_8042C1D0 + 0x8C18);
	if (stage != NULL) {
		fn_801A4C84(stage);
	} else {
		return;
	}
	fn_800BC9F4(*(void**)((u8*)lbl_8042C298 + 0xA50), lbl_802FF5A0);
	ModelAsset* asset = &blinkLightAsset;
	for (u8 i = 0; i < 1; i++) {
		fn_9_765CC(asset, 0);
		asset++;
	}
}

// Placement construction preserves the original factory's inlined constructor.
class BlinkLightAllocation
{
public:
	BlinkLight object;
	BlinkLightAllocation(void* owner) { blinkLightCtor(&object, owner); }
	static void* operator new(unsigned long, void* memory) { return memory; }
};

extern "C" void blinkLightCreate(void)
{
	void* memory = fn_80018A34(lbl_8042C148, sizeof(BlinkLightAllocation));
	if (memory != NULL) {
		new (memory) BlinkLightAllocation(lbl_8042C110);
	}
}

extern "C" ObjectEntry blinkLightEntry;
extern "C" char blinkLightDisplayName[];

extern "C" void blinkLightRegister(void)
{
	blinkLightEntry.flags      = 0;
	blinkLightEntry.unk18      = 0;
	blinkLightEntry.name       = blinkLightDisplayName;
	blinkLightEntry.load       = blinkLightInit;
	blinkLightEntry.unload     = blinkLightEnd;
	blinkLightEntry.create     = blinkLightCreate;
	blinkLightEntry.reset      = NULL;
	blinkLightEntry.flags      = 0x1000;
	blinkLightEntry.unk18      = 0;
	blinkLightEntry.unk20      = 10;
	blinkLightEntry.unk1C      = 0x1385;
	blinkLightEntry.unk1E      = 2;
	blinkLightEntry.unk21      = 0;
	blinkLightEntry.fieldTypes = NULL;
	blinkLightEntry.fieldNames = NULL;
	if (blinkLightEntry.fieldTypes != NULL) {
		blinkLightEntry.flags |= 8;
	} else {
		blinkLightEntry.flags &= ~8;
	}
}

extern "C" void* blinkLightResource[1] = { NULL };
extern "C" char blinkLightFilename[]   = "dobj13_light_blink_on";
extern "C" ModelAsset blinkLightAsset  = {
	{ 0x04000000, 4, 0, 0, 0, 0x02000000, 0, 0, 0 },
	blinkLightResource,
	blinkLightFilename,
};
extern "C" const u32 blinkLightCollision[24] = {
	0x0002FF0C,
	0,
	0,
	0x41A00000,
	0,
	0x41200000,
	0x41A00000,
	0,
	0,
	0,
	0,
	0,
	0x0000FF0C,
	0,
	0,
	0x42080000,
	0,
	0x41400000,
	0,
	0,
	0,
	0,
	0,
	0,
};
extern "C" const __declspec(section ".rodata") f32 blinkLightZeroPool[11] = {
	0.0f,
	0.0f,
	0.0f,
	0.0f,
	0.0f,
	0.0f,
	0.0f,
	0.0f,
	0.0f,
	0.0f,
	0.0f,
};
extern "C" char blinkLightClassName[]         = "TObjS13BlinkLight";
extern "C" const char* blinkLightClassNamePtr = blinkLightClassName;
extern "C" char blinkLightDisplayName[]       = "S13D BlinkLight";

extern "C" {
ObjectEntry blinkLightEntry;
u32 blinkLightBssTail[3];
}

__declspec(section ".ctors") void (*const blinkLightCtorEntry)(void) = blinkLightRegister;

#pragma force_active reset
