#include "types.h"

#pragma force_active on

typedef struct Vec3 {
	f32 x;
	f32 y;
	f32 z;
} Vec3;

typedef struct EulerAngles {
	s32 y;
	s32 z;
	s32 x;
} EulerAngles;

typedef struct Frame {
	Vec3 position;
	EulerAngles angle;
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

typedef struct Antenna {
	TObject base;
	Motion motion;
	Transform transform;
	f32 phase;
	ModelHolder* model;
} Antenna;

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

class AntennaPrimaryBase
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

class AntennaEditBase
{
public:
	virtual void editOnChange(void*);
};

class AntennaVirtual : public AntennaPrimaryBase, public AntennaEditBase
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
extern "C" void Error__7TObjectFPc(void);
extern "C" void fn_800189A4(void*, TObject*);
extern "C" void* fn_80018A34(void*, u32);
extern "C" void fn_8003BC38(void*);
extern "C" void fn_8003BF04(void*, const u32*, s32, s32);
extern "C" void fn_8003C618(void*);
extern "C" void dtor_8003C52C(void*, s32);
extern "C" s32 fn_8005B8BC(Motion*);
extern "C" s32 fn_8005B8D8(Motion*);
extern "C" s32 fn_8005B9F0(Motion*);
extern "C" void dtor_8005BD3C(Motion*, s32);
extern "C" void fn_8005BE6C(Motion*);
extern "C" void fn_800BC9F4(void*, void*);
extern "C" f32 fn_800D7AE4(s32);
extern "C" f32 fn_800D7B00(s32);
extern "C" void fn_80195790(void*, const Vec3*, f32, f32, s32);
extern "C" void fn_8019E880(void*);
extern "C" void fn_8019EB94(void*, Frame*, s32);
extern "C" void fn_801A4C84(void*);

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

extern "C" void* antennaResource[];
extern "C" char antennaFilename[];
extern "C" ModelAsset antennaAsset;
extern "C" const u32 antennaCollision[24];
extern "C" const f32 antennaOne;
extern "C" const f32 antennaFrameStep;
extern "C" const f32 antennaFullTurn;
extern "C" const f32 antennaZeroPool[5];
extern "C" char antennaClassName[];
extern "C" const char* antennaClassNamePtr;
extern "C" void* __vt__14AntennaVirtual[];
#define antennaVtable __vt__14AntennaVirtual

extern "C" void antennaDestroyClump(Antenna*, ModelHolder** model)
{
	fn_9_75888(model);
}

extern "C" void antennaCloneClump(Antenna*, ModelHolder** model)
{
	fn_9_75D2C(&antennaAsset, 0, model, 0);
	fn_9_757C4(*model, &antennaAsset.words[5], 0);
}

extern "C" void antennaSetPosition(Antenna* object)
{
	u8* model = object->model->model;
	f32 c;
	f32 s;

	c = fn_800D7B00(object->motion.frame->angle.z);
	s = antennaOne - fn_800D7AE4(object->motion.frame->angle.z);
	fn_80195790(model + 0x10, &lbl_80239984, s, c, 0);
	fn_8019E880(model);

	c = fn_800D7B00(object->motion.frame->angle.y);
	s = antennaOne - fn_800D7AE4(object->motion.frame->angle.y);
	fn_80195790(model + 0x10, &lbl_80239978, s, c, 2);
	fn_8019E880(model);

	c = fn_800D7B00(object->motion.frame->angle.x);
	s = antennaOne - fn_800D7AE4(object->motion.frame->angle.x);
	fn_80195790(model + 0x10, &lbl_80239990, s, c, 2);
	fn_8019E880(model);
	fn_8019EB94(model, object->motion.frame, 2);
}

extern "C" void antennaExec(Antenna* object)
{
	f32 duration = ((f32*)&antennaAsset)[7];

	if (fn_8005B9F0(&object->motion) != 0 || fn_8005B8BC(&object->motion) != 0) {
		object->base.signal |= 1;
		return;
	}

	if (((s8*)lbl_8042C180)[0x1F] != 0) {
		Frame* frame                       = object->motion.frame;
		object->transform.previousPosition = object->transform.position;
		object->transform.position         = frame->position;
		object->transform.angleY           = frame->angle.y;
		object->transform.angleZ           = frame->angle.z;
		object->transform.angleX           = frame->angle.x;
		fn_8003BC38(&object->transform);
		return;
	}

	if (fn_8005B8D8(&object->motion) != 0) {
		antennaSetPosition(object);
	} else {
		object->phase += antennaFrameStep;
		if (object->phase >= duration) {
			object->phase -= duration;
		}
		fn_9_75764(object->model, object->phase);

		Frame* frame       = object->motion.frame;
		EulerAngles angles = frame->angle;
		angles.z           = (s32)(angles.z + antennaFullTurn * (object->phase / duration));
		object->transform.previousPosition = object->transform.position;
		object->transform.position         = frame->position;
		object->transform.angleY           = angles.y;
		object->transform.angleZ           = angles.z;
		object->transform.angleX           = angles.x;
		fn_8003BC38(&object->transform);
	}
}

void AntennaVirtual::editOnChange(void*) { }

extern "C" Antenna* antennaDtor(Antenna* object, s16 flags)
{
	if (object != NULL) {
		object->base.vtable   = antennaVtable;
		object->motion.vtable = antennaVtable + 11;
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

extern "C" Antenna* antennaCtor(Antenna* object, void* owner)
{
	__ct__7TObjectFP7TObject(&object->base, owner);
	fn_8005BE6C(&object->motion);
	fn_8003C618(&object->transform);

	object->base.vtable     = antennaVtable;
	object->motion.vtable   = antennaVtable + 11;
	object->base.className  = antennaClassNamePtr;
	object->base.objectSize = sizeof(Antenna);
	object->phase           = antennaZeroPool[0];

	antennaCloneClump(object, &object->model);
	antennaSetPosition(object);
	fn_8003BF04(&object->transform, antennaCollision, 2, 4);
	return object;
}

extern "C" void antennaEnd(void)
{
	ModelAsset* asset = &antennaAsset;
	for (u8 i = 0; i < 1; i++) {
		fn_9_76448(asset);
		asset++;
	}
}

extern "C" void antennaInit(void)
{
	void* stage = *(void**)((u8*)lbl_8042C1D0 + 0x8C18);
	if (stage != NULL) {
		fn_801A4C84(stage);
	} else {
		return;
	}
	fn_800BC9F4(*(void**)((u8*)lbl_8042C298 + 0xA50), lbl_802FF5A0);
	ModelAsset* asset = &antennaAsset;
	for (u8 i = 0; i < 1; i++) {
		fn_9_765CC(asset, 0);
		asset++;
	}
}

class AntennaAllocation
{
public:
	Antenna object;
	AntennaAllocation(void* owner) { antennaCtor(&object, owner); }
	static void* operator new(unsigned long, void* memory) { return memory; }
};

extern "C" void antennaCreate(void)
{
	void* memory = fn_80018A34(lbl_8042C148, sizeof(AntennaAllocation));
	if (memory != NULL) {
		new (memory) AntennaAllocation(lbl_8042C110);
	}
}

extern "C" ObjectEntry antennaEntry;
extern "C" char antennaDisplayName[17];

extern "C" void antennaRegister(void)
{
	antennaEntry.flags      = 0;
	antennaEntry.unk18      = 0;
	antennaEntry.name       = antennaDisplayName;
	antennaEntry.load       = antennaInit;
	antennaEntry.unload     = antennaEnd;
	antennaEntry.create     = antennaCreate;
	antennaEntry.reset      = NULL;
	antennaEntry.flags      = 0x1000;
	antennaEntry.unk18      = 0;
	antennaEntry.unk20      = 10;
	antennaEntry.unk1C      = 0x1386;
	antennaEntry.unk1E      = 2;
	antennaEntry.unk21      = 0;
	antennaEntry.fieldTypes = NULL;
	antennaEntry.fieldNames = NULL;
	if (antennaEntry.fieldTypes != NULL) {
		antennaEntry.flags |= 8;
	} else {
		antennaEntry.flags &= ~8;
	}
}

extern "C" void* antennaResource[1] = { NULL };
extern "C" char antennaFilename[]   = "dobj13_antena_on";
extern "C" ModelAsset antennaAsset  = {
	{ 0x04000000, 4, 0, 0, 0, 0x02000000, 0, 0, 0 },
	antennaResource,
	antennaFilename,
};
extern "C" const u32 antennaCollision[24] = {
	0x0002FF0C,
	0,
	0,
	0x41700000,
	0,
	0x41700000,
	0x41700000,
	0,
	0,
	0,
	0,
	0,
	0x0008FF0C,
	0,
	0,
	0x42200000,
	0,
	0x41700000,
	0x41F00000,
	0,
	0,
	0,
	0,
	0x00004000,
};
extern "C" const __declspec(section ".rodata") f32 antennaOne         = 1.0f;
extern "C" const __declspec(section ".rodata") f32 antennaFrameStep   = 0.0166667f;
extern "C" const __declspec(section ".rodata") f32 antennaFullTurn    = 65536.0f;
extern "C" const __declspec(section ".rodata") u32 antennaRodataPad   = 0;
extern "C" const __declspec(section ".rodata") f32 antennaZeroPool[5] = {
	0.0f,
	0.0f,
	0.0f,
	0.0f,
	0.0f,
};
extern "C" char antennaClassName[]         = "TObjS13Antenna";
extern "C" const char* antennaClassNamePtr = antennaClassName;
extern "C" char antennaDisplayName[17]     = "S13D ANTENNA";

extern "C" {
ObjectEntry antennaEntry;
u32 antennaBssTail[4];
}

__declspec(section ".ctors") void (*const antennaCtorEntry)(void) = antennaRegister;

#pragma force_active reset
