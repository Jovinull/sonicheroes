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

// Explicit ABI views retained for the external C helpers and transform accesses.
// Construction, destruction and virtual dispatch use the native classes below.
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

// Observed leading RwObject fields only; no RpClump objects are allocated here.
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

// Layout view used inside SetPosition/Exec; never constructed separately.
typedef struct Antenna {
	TObjectStorage base;
	Motion motion;
	Transform transform;
	f32 phase;
	RpClump* model;
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
extern "C" void fn_8019EB94(void*, Frame*, s32);
extern "C" void fn_801A4C84(void*);

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

struct SETDATA_PARAM;
class TObject
{
public:
	const char* ClassName;
	u16 Signal, Tag;
	TObject *Prev, *Next, *Parent, *Child;
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
	u16 ExecTime, DispTime, TDispTime, PDispTime, ImmAftSetRasterTime;
	static void* operator new(unsigned long size)
	{
		return Malloc__9THeapCtrlFUi(lbl_8042C148, size);
	}
	static void operator delete(void* memory)
	{
		Free__9THeapCtrlFPv(lbl_8042C148, (TObjectStorage*)memory);
	}
};
class TObjSetObj
{
public:
	Frame* ObjParam;
	TObjSetObj();
	~TObjSetObj();
	virtual void EditOnChange(SETDATA_PARAM*);
};
class C_COLLI
{
	u32 fields[34];

public:
	C_COLLI();
	~C_COLLI();
};
class TObjS13Antenna : public TObject, public TObjSetObj, public C_COLLI
{
public:
	f32 animTime;
	RpClump* pClump;
	TObjS13Antenna(TObject*);
	virtual ~TObjS13Antenna();
	virtual void Exec();
	virtual void EditOnChange(SETDATA_PARAM*);
	void DestroyClump(RpClump**);
	void CloneClump(RpClump**);
	void SetPosition();
};
typedef char AntennaNativeSize[(sizeof(TObjS13Antenna) == 0xC0) ? 1 : -1];

void TObjS13Antenna::DestroyClump(RpClump** model)
{
	fn_9_75888(model);
}

void TObjS13Antenna::CloneClump(RpClump** model)
{
	fn_9_75D2C(&antennaAsset, 0, model, 0);
	fn_9_757C4(*model, &antennaAsset.words[5], 0);
}

void TObjS13Antenna::SetPosition()
{
	Antenna* object = (Antenna*)this;
	u8* model       = object->model->model;
	f32 c;
	f32 s;

	c = fn_800D7B00(object->motion.frame->angle.z);
	s = antennaOne - fn_800D7AE4(object->motion.frame->angle.z);
	fn_80195790(model + 0x10, &AxisY, s, c, 0);
	fn_8019E880(model);

	c = fn_800D7B00(object->motion.frame->angle.y);
	s = antennaOne - fn_800D7AE4(object->motion.frame->angle.y);
	fn_80195790(model + 0x10, &AxisX, s, c, 2);
	fn_8019E880(model);

	c = fn_800D7B00(object->motion.frame->angle.x);
	s = antennaOne - fn_800D7AE4(object->motion.frame->angle.x);
	fn_80195790(model + 0x10, &AxisZ, s, c, 2);
	fn_8019E880(model);
	fn_8019EB94(model, object->motion.frame, 2);
}

void TObjS13Antenna::Exec()
{
	Antenna* object = (Antenna*)this;
	f32 duration    = ((f32*)&antennaAsset)[7];

	if (CheckRangeOut__10TObjSetObjFv(&object->motion) != 0
	    || CheckMustKill__10TObjSetObjFv(&object->motion) != 0) {
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
		Entry__7C_COLLIFv(&object->transform);
		return;
	}

	if (OnEdit__10TObjSetObjFv(&object->motion) != 0) {
		SetPosition();
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
		Entry__7C_COLLIFv(&object->transform);
	}
}

void TObjS13Antenna::EditOnChange(SETDATA_PARAM*) { }

TObjS13Antenna::~TObjS13Antenna()
{
	fn_9_75888(&pClump);
}

TObjS13Antenna::TObjS13Antenna(TObject* owner)
    : TObject(owner)
    , TObjSetObj()
    , C_COLLI()
{
	ClassName = antennaClassNamePtr;
	DispTime  = sizeof(TObjS13Antenna);
	animTime  = antennaZeroPool[0];
	CloneClump(&pClump);
	SetPosition();
	fn_8003BF04(&static_cast<C_COLLI&>(*this), antennaCollision, 2, 4);
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
	LoadOneFile__7ONEFILEFPc(*(void**)((u8*)lbl_8042C298 + 0xA50), lbl_802FF5A0);
	ModelAsset* asset = &antennaAsset;
	for (u8 i = 0; i < 1; i++) {
		fn_9_765CC(asset, 0);
		asset++;
	}
}

extern "C" void antennaCreate(void)
{
	new TObjS13Antenna((TObject*)lbl_8042C110);
}

extern "C" ObjectEntry antennaEntry;
extern "C" char antennaDisplayName[];

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
extern "C" const __declspec(section ".rodata") f32 antennaOne       = 1.0f;
extern "C" const __declspec(section ".rodata") f32 antennaFrameStep = 0.0166667f;
extern "C" const __declspec(section ".rodata") f32 antennaFullTurn  = 65536.0f;
// Preserve the configured constant range. The unreferenced zero bytes have
// uncertain historical ownership; these names do not recover original arrays.
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
extern "C" char antennaDisplayName[]       = "S13D ANTENNA";

extern "C" {
ObjectEntry antennaEntry;
// Opaque zero storage retained from the configured unit extent. Its original
// declarations and historical ownership have not been established.
u32 antennaBssTail[4];
}

__declspec(section ".ctors") void (*const antennaCtorEntry)(void) = antennaRegister;

#pragma force_active reset
