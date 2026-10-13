#include "types.h"
#include "game/calc.h"

// Preserve the configured unit, including standalone methods and residual
// storage whose original declarations have not been established.
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

typedef struct TObjectStorage {
	const char* className;
	u16 signal;
	u16 tag;
	struct TObjectStorage* prev;
	struct TObjectStorage* next;
	struct TObjectStorage* parent;
	struct TObjectStorage* child;
	void** vtable;
	s16 unk1C;
	s16 objectSize;
	s16 unk20;
	s16 unk22;
	s16 unk24;
	s16 unk26;
} TObjectStorage;

typedef struct Motion {
	Frame* frame;
	void** vtable;
} Motion;

typedef struct RpClump {
	void* resource;
	u8* model;
} RpClump;

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
	TObjectStorage base;
	Motion motion;
	Transform transform;
	s16 particleTimer;
	s16 padBA;
	f32 phase;
	RpClump* model;
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

struct SETDATA_PARAM;
struct TObjectData {
	const char* className;
	u16 signal, tag;
	void* prev;
	void* next;
	void* parent;
	void* child;
};
class TObject : public TObjectData
{
public:
	TObject(TObject*);
	virtual ~TObject();
	virtual void Exec();
	virtual void Disp();
	virtual void TDisp();
	virtual void PDisp();
	virtual void ImmAftSetRaster();
	virtual void Debug();
	virtual void Error(char*);
	virtual void Render();
	s16 unk1C, objectSize, unk20, unk22, unk24, unk26;
	static void* operator new(unsigned long);
	static void operator delete(void*);
};
struct SetObjData {
	Frame* frame;
};
class TObjSetObj : public SetObjData
{
public:
	TObjSetObj();
	~TObjSetObj();
	virtual void EditOnChange(SETDATA_PARAM*);
};
class C_COLLI
{
public:
	Transform storage;
	C_COLLI();
	~C_COLLI();
};
class TObjS13BlinkLight : public TObject, public TObjSetObj, public C_COLLI
{
public:
	TObjS13BlinkLight(TObject*);
	virtual ~TObjS13BlinkLight();
	virtual void Exec();
	virtual void EditOnChange(SETDATA_PARAM*);
	void CreateParticle();
	void DestroyClump(RpClump**);
	void CloneClump(RpClump**);
	void SetPosition();
	s16 timer;
	f32 animTime;
	RpClump* pClump;
	void* ptclFrame;
};
extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;
extern "C" void* lbl_8042C180;
extern "C" void* lbl_8042C1D0;
extern "C" void* lbl_8042C298;
extern "C" Vec3 AxisX;
extern "C" Vec3 AxisY;
extern "C" Vec3 AxisZ;
extern "C" char lbl_802FF5A0[];

extern "C" void __ct__7TObjectFP7TObject(TObjectStorage*, void*);
extern "C" void __dt__7TObjectFv(TObjectStorage*, s32);
extern "C" void Error__7TObjectFPc(void);
extern "C" void Free__9THeapCtrlFPv(void*, TObjectStorage*);
extern "C" void* Malloc__9THeapCtrlFUi(void*, u32);
extern "C" void Entry__7C_COLLIFv(void*);
extern "C" void fn_8003BF04(void*, const u32*, s32, s32);
extern "C" void __ct__7C_COLLIFv(void*);
extern "C" void __dt__7C_COLLIFv(void*, s32);
extern "C" void* fn_800628D0(s32, const Vec3*, const void*);
extern "C" s32 CheckMustKill__10TObjSetObjFv(Motion*);
extern "C" s32 OnEdit__10TObjSetObjFv(Motion*);
extern "C" s32 CheckRangeOut__10TObjSetObjFv(Motion*);
extern "C" void __dt__10TObjSetObjFv(Motion*, s32);
extern "C" void __ct__10TObjSetObjFv(Motion*);
extern "C" void LoadOneFile__7ONEFILEFPc(void*, void*);
extern "C" f32 fn_800D7AE4(s32);
extern "C" f32 fn_800D7B00(s32);
extern "C" void fn_80195790(void*, const Vec3*, f32, f32, s32);
extern "C" void fn_8019E880(void*);
extern "C" void* fn_8019E8EC(void*);
extern "C" void fn_8019EB94(void*, Frame*, s32);
extern "C" void fn_801A4C84(void*);

extern "C" void* fn_9_752F4(RpClump*, s32);
extern "C" void fn_9_75764(RpClump*, f32);
extern "C" void fn_9_757C4(RpClump*, void*, s32);
extern "C" void fn_9_75888(void*);
extern "C" void fn_9_75D2C(ModelAsset*, s32, RpClump**, s32);
extern "C" void fn_9_76448(ModelAsset*);
extern "C" void fn_9_765CC(ModelAsset*, s32);

extern "C" void Disp__7TObjectFv(void);
extern "C" void TDisp__7TObjectFv(void);
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
extern "C" void* __vt__17TObjS13BlinkLight[];
#define blinkLightVtable __vt__17TObjS13BlinkLight

inline void TObject::operator delete(void* object)
{
	Free__9THeapCtrlFPv(lbl_8042C148, (TObjectStorage*)object);
}

void TObjS13BlinkLight::CreateParticle()
{
	BlinkLight* object = (BlinkLight*)this;
	if (object->particle != NULL) {
		void* transform = fn_8019E8EC(object->particle);
		Vec3 position;
		struct {
			s32 x, y, z;
		} angle;

		position.x = ((f32*)transform)[12];
		position.y = ((f32*)transform)[13];
		position.z = ((f32*)transform)[14];
		GetRotYXZ((RwMatrixTag*)transform, &angle.x, &angle.y, &angle.z);
		fn_800628D0(5, &position, &angle);
	}
}

void TObjS13BlinkLight::DestroyClump(RpClump** model)
{
	fn_9_75888(model);
}

void TObjS13BlinkLight::CloneClump(RpClump** model)
{
	fn_9_75D2C(&blinkLightAsset, 0, model, 0);
	fn_9_757C4(*model, &blinkLightAsset.words[5], 0);
}

void TObjS13BlinkLight::SetPosition()
{
	BlinkLight* object = (BlinkLight*)this;
	u8* model          = object->model->model;
	f32 c;
	f32 s;

	c = fn_800D7B00(object->motion.frame->angleZ);
	s = 1.0f - fn_800D7AE4(object->motion.frame->angleZ);
	fn_80195790(model + 0x10, &AxisY, s, c, 0);
	fn_8019E880(model);

	c = fn_800D7B00(object->motion.frame->angleY);
	s = 1.0f - fn_800D7AE4(object->motion.frame->angleY);
	fn_80195790(model + 0x10, &AxisX, s, c, 2);
	fn_8019E880(model);

	c = fn_800D7B00(object->motion.frame->angleX);
	s = 1.0f - fn_800D7AE4(object->motion.frame->angleX);
	fn_80195790(model + 0x10, &AxisZ, s, c, 2);
	fn_8019E880(model);
	fn_8019EB94(model, object->motion.frame, 2);
}

void TObjS13BlinkLight::Exec()
{
	BlinkLight* object = (BlinkLight*)this;
	f32 duration       = ((f32*)&blinkLightAsset)[7];

	if (CheckRangeOut__10TObjSetObjFv(&object->motion) != 0
	    || CheckMustKill__10TObjSetObjFv(&object->motion) != 0) {
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
		Entry__7C_COLLIFv(&object->transform);
		return;
	}

	if (OnEdit__10TObjSetObjFv(&object->motion) != 0) {
		((TObjS13BlinkLight*)object)->SetPosition();
	} else {
		object->phase += 0.0166667f;
		if (object->phase >= duration) {
			object->phase -= duration;
		}
		fn_9_75764(object->model, object->phase);

		if (--object->particleTimer <= 0) {
			CreateParticle();
			object->particleTimer = 60;
		}
		Frame* frame                       = object->motion.frame;
		object->transform.previousPosition = object->transform.position;
		object->transform.position         = frame->position;
		object->transform.angleY           = frame->angleY;
		object->transform.angleZ           = frame->angleZ;
		object->transform.angleX           = frame->angleX;
		Entry__7C_COLLIFv(&object->transform);
	}
}

void TObjS13BlinkLight::EditOnChange(SETDATA_PARAM*) { }

TObjS13BlinkLight::~TObjS13BlinkLight()
{
	fn_9_75888(&pClump);
}

TObjS13BlinkLight::TObjS13BlinkLight(TObject* owner)
    : TObject(owner)
    , TObjSetObj()
    , C_COLLI()
{

	className  = blinkLightClassNamePtr;
	objectSize = sizeof(TObjS13BlinkLight);
	animTime   = blinkLightZeroPool[0];

	CloneClump(&pClump);
	SetPosition();
	ptclFrame = fn_9_752F4(pClump, 1);
	timer     = 0;
	fn_8003BF04(&static_cast<C_COLLI&>(*this), blinkLightCollision, 2, 4);
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
	LoadOneFile__7ONEFILEFPc(*(void**)((u8*)lbl_8042C298 + 0xA50), lbl_802FF5A0);
	ModelAsset* asset = &blinkLightAsset;
	for (u8 i = 0; i < 1; i++) {
		fn_9_765CC(asset, 0);
		asset++;
	}
}

inline void* TObject::operator new(unsigned long size)
{
	return Malloc__9THeapCtrlFUi(lbl_8042C148, size);
}
extern "C" void blinkLightCreate(void)
{
	new TObjS13BlinkLight((TObject*)lbl_8042C110);
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
// Only the first scalar is referenced. The remaining forty zero bytes retain
// the configured extent; their original declarations and ownership are unknown.
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
// Opaque residual zero storage under the inferred unit boundary, not recovered
// class fields or a proven compiler-generated registration node.
u32 blinkLightBssTail[3];
}

__declspec(section ".ctors") void (*const blinkLightCtorEntry)(void) = blinkLightRegister;

#pragma force_active reset
