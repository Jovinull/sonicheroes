#include "types.h"

struct RwV3d {
	f32 x, y, z;
};

struct sAngle {
	s32 x, y, z;
};

extern "C" void* __nw__10TObjSampleFUl(u32);

struct SETDATA_PARAM {
	RwV3d position;
	sAngle angle;
	u8 unk18[0x14];
	RwV3d* member;
};

struct CollisionInfo {
	u8 unk0[0x14];
	RwV3d scale;
};

struct RawTEndSkyBob {
	u8 base[0xE8];
};

class TObject
{
public:
	const char* className;
	u16 signal;
	u16 tag;
	TObject* prev;
	TObject* next;
	TObject* parent;
	TObject* child;

	virtual ~TObject();
	virtual void Exec();
	virtual void PDisp();
	virtual void Disp();
	virtual void TDisp();
	virtual void ImmAftSetRaster();
	virtual void Debug();
	virtual void Error(char*);
	virtual void Render();
};

struct TObjectTail {
	s16 unk1C;
	s16 objectSize;
	s16 unk20;
	s16 unk22;
	s16 unk24;
	s16 unk26;
};

class TEditMotion
{
public:
	SETDATA_PARAM* frame;

	virtual void EditOnChange(SETDATA_PARAM*);
};

class TEndSkyBob : public TObject, public TObjectTail, public TEditMotion
{
public:
	u8 collisionArea[0x90];
	RwV3d scale;
	RwV3d position;
	u8 updater[8];
	f32 distance;
	s32 finished;

	virtual ~TEndSkyBob();
	virtual void EditOnChange(SETDATA_PARAM*);
	virtual void Exec();
	TEndSkyBob(TObject*);

	static TEndSkyBob* Create();
	static void Finalize();
	static void Initialize();
	static void* operator new(unsigned long size) { return __nw__10TObjSampleFUl(size); }
	static void operator delete(void* object);
};

extern "C" {
void __dl__10TObjSampleFPv(void*);
void copyVec3(RwV3d*, SETDATA_PARAM*);
void markSampleForDeletion(TEndSkyBob*);
void setupObjClass(void*, char*, void (*)(), void (*)(), void*, void*, void*, void*, u32, u32, u32,
    u32, char*, void*);
void fn_16_900(sAngle*, sAngle*);
u32 fn_16_D10(void*);
void fn_16_DB4(void*);
int fn_16_F20(void*, int);
void fn_16_1180(void*, SETDATA_PARAM*, sAngle*);
void fn_16_5F55C(TEndSkyBob*, int);
void fn_16_5F608(TEndSkyBob*, TObject*);
void* fn_16_62FBC(int);
void fn_16_753C4();
CollisionInfo* fn_16_7738(void*, int);
f32 fn_16_5932C(void*, RwV3d*, f32);
f32 fn_16_59490(void*, RwV3d*);
void fn_16_59580(void*, void*);
void fn_16_596B0(void*, f32);
void fn_16_59E88(void*);
void fn_16_5A0F0(void*);
f32 fn_16_4D18C(RwV3d*, RwV3d*);
void fn_16_93BE8(void*, int);
void fn_16_93C3C(void*);
int fn_16_93ACC(void*, SETDATA_PARAM*, f32);

int fn_8005B8BC(void*);
int fn_8005B8D8(void*);
int fn_8005B9F0(void*);
void fn_8005BC04(void*);
void fn_8003C200(void*, void*, int, int);
void fn_80021384(void*);
void fn_80021824(void*);

extern void* lbl_8042C180;
extern u8 lbl_8042C1A4[];
extern void* lbl_8042C1F8;
extern SETDATA_PARAM* lbl_8042C208;
extern TObject* lbl_16_bss_1058;

TEndSkyBob* __ct__10TEndSkyBobFP7TObject(TEndSkyBob*, TObject*);
void Exec__10TEndSkyBobFv();
void EditOnChange__10TEndSkyBobFP13SETDATA_PARAM(TEndSkyBob*, SETDATA_PARAM*);
void PDisp__7TObjectFv();
void Disp__7TObjectFv();
void TDisp__7TObjectFv();
void ImmAftSetRaster__7TObjectFv();
void Debug__7TObjectFv();
void Error__7TObjectFPc();
void Render__7TObjectFv();
}

extern "C" char TEndSkyBobClassName[]   = "TEndSkyBob\0";
extern "C" char* TEndSkyBobClassNamePtr = TEndSkyBobClassName;
extern "C" char ScaleX[]                = "SCALE X";
extern "C" char ScaleY[]                = "SCALE Y";
extern "C" char ScaleZ[]                = "SCALE Z";
extern "C" char DoNotEdit[]             = "DONOT EDIT\0";
extern "C" char* TEndSkyBobFields[]     = { ScaleX, ScaleY, ScaleZ, DoNotEdit };
extern "C" u32 TEndSkyBobCollision[12]  = { 0x1E04F00C };

#pragma force_active on
// clang-format off
#pragma section data_type ".endsky_strings" ".endsky_strings_bss"
#pragma options align=packed
// clang-format on
extern "C" char ObjS40EndSkyBobName[];
extern "C" char TEndSkyBobFieldTypes[];
extern "C" char TEndSkyBobFieldTypesTail[];
#pragma section data_type ".data"
#pragma options align = reset
#pragma force_active reset
extern "C" {
u8 ObjS40EndSkyBob[0x2C];
u8 TEndSkyBobPath[0x6C];
}

extern "C" const f32 TEndSkyBobZero;
extern "C" const f32 TEndSkyBobHundred;
extern "C" const f32 TEndSkyBobConstants[2];
extern "C" void* __vt__10TEndSkyBob[];

#pragma optimization_level 0
void TEndSkyBob::EditOnChange(SETDATA_PARAM* setData)
{
	register RwV3d* member;
	member = setData->member;
	if (member->x < TEndSkyBobZero)
		member->x = TEndSkyBobZero;
	if (member->y < TEndSkyBobZero)
		member->y = TEndSkyBobZero;
	if (member->z < TEndSkyBobZero)
		member->z = TEndSkyBobZero;
}
void TEndSkyBob::Exec()
{
	register RwV3d* member = (*(SETDATA_PARAM**)(((RawTEndSkyBob*)this)->base + 0x28))->member;
	register CollisionInfo* info;
	register SETDATA_PARAM* stageObject;

	if (!fn_16_93ACC(
	        updater, *(SETDATA_PARAM**)(((RawTEndSkyBob*)this)->base + 0x28), TEndSkyBobHundred)) {
		fn_8005BC04(((RawTEndSkyBob*)this)->base + 0x28);
		markSampleForDeletion(this);
		return;
	}
	if (fn_8005B9F0(((RawTEndSkyBob*)this)->base + 0x28) && finished) {
		markSampleForDeletion(this);
		return;
	}
	if (fn_8005B8BC(((RawTEndSkyBob*)this)->base + 0x28)) {
		markSampleForDeletion(this);
		return;
	}

	RwV3d oldPosition = position;
	copyVec3(&position, *(SETDATA_PARAM**)(((RawTEndSkyBob*)this)->base + 0x28));
	if (fn_16_F20(lbl_8042C180, 0x1F))
		return;

	if (fn_8005B8D8(((RawTEndSkyBob*)this)->base + 0x28)) {
		scale = *member;
		if (distance <= TEndSkyBobZero) {
			member[1].x = distance = fn_16_59490(TEndSkyBobPath, &position);
		} else {
			f32 moved = fn_16_4D18C(&oldPosition, &position);
			fn_16_596B0(TEndSkyBobPath, distance);
			member[1].x = distance = fn_16_5932C(TEndSkyBobPath, &position, moved);
		}
		if (lbl_8042C1F8 != 0) {
			stageObject = lbl_8042C208;
			if (stageObject != 0)
				fn_16_900(&(*(SETDATA_PARAM**)(((RawTEndSkyBob*)this)->base + 0x28))->angle,
				    &stageObject->angle);
		}
		return;
	}

	if (fn_16_7738(((RawTEndSkyBob*)this)->base + 0x30, 0) == 0) {
		fn_8003C200(((RawTEndSkyBob*)this)->base + 0x30, TEndSkyBobCollision, 1, 4);
		info          = fn_16_7738(((RawTEndSkyBob*)this)->base + 0x30, 0);
		info->scale.x = TEndSkyBobConstants[0] * scale.x;
		info->scale.y = TEndSkyBobConstants[0] * scale.y;
		info->scale.z = TEndSkyBobConstants[0] * scale.z;
		fn_80021384(((RawTEndSkyBob*)this)->base + 0x30);
		fn_16_DB4(((RawTEndSkyBob*)this)->base + 0x30);
	}
	if (!fn_8005B8D8(((RawTEndSkyBob*)this)->base + 0x28)) {
		fn_80021824(lbl_8042C1A4);
		if (fn_16_D10(((RawTEndSkyBob*)this)->base + 0x30))
			fn_16_753C4();
		fn_16_1180(((RawTEndSkyBob*)this)->base + 0x30,
		    *(SETDATA_PARAM**)(((RawTEndSkyBob*)this)->base + 0x28),
		    &(*(SETDATA_PARAM**)(((RawTEndSkyBob*)this)->base + 0x28))->angle);
	}
}

TEndSkyBob::~TEndSkyBob()
{
	fn_16_93BE8(updater, 0);
}

extern "C" TEndSkyBob* __ct__10TEndSkyBobFP7TObject(register TEndSkyBob* object, TObject* parent)
{
	fn_16_5F608(object, parent);
	fn_16_93C3C(object->updater);
	*(void**)((u8*)object + 0x18) = __vt__10TEndSkyBob;
	*(void**)((u8*)object + 0x2C) = __vt__10TEndSkyBob + 11;
	*(char**)object               = TEndSkyBobClassNamePtr;
	*(u16*)((u8*)object + 0x1E)   = 0xE8;
	register RwV3d* member        = object->frame->member;
	*(u32*)((u8*)object + 0xBC)   = 0x61000000 - 0x100;
	object->distance              = member[1].x;
	object->finished              = 0;
	return object;
}

TEndSkyBob* TEndSkyBob::Create()
{
	TEndSkyBob* object = (TEndSkyBob*)__nw__10TObjSampleFUl(sizeof(TEndSkyBob));
	if (object != 0)
		object = __ct__10TEndSkyBobFP7TObject(object, lbl_16_bss_1058);
}

void TEndSkyBob::Finalize()
{
	fn_16_59E88(TEndSkyBobPath);
}

void TEndSkyBob::Initialize()
{
	register void* path = fn_16_62FBC(0);
	fn_16_59580(TEndSkyBobPath, path);
}

extern "C" void __sinit_TEndSkyBob_cpp()
{
	setupObjClass(ObjS40EndSkyBob, ObjS40EndSkyBobName, 0, 0, (void*)TEndSkyBob::Create, 0, 0, 0,
	    0x64, 0x15EA, 2, 0, TEndSkyBobFieldTypes, TEndSkyBobFields);
	fn_16_5A0F0(TEndSkyBobPath);
}

__declspec(section ".ctors") void (*const TEndSkyBobCtorEntry)() = __sinit_TEndSkyBob_cpp;

// clang-format off
#pragma section data_type ".endsky_strings" ".endsky_strings_bss"
// clang-format on
extern "C" char ObjS40EndSkyBobName[] = "SKYBOB END\0FFFF";
#pragma section data_type ".data"

__declspec(section ".rodata") const f32 TEndSkyBobZero         = 0.0f;
__declspec(section ".rodata") const f32 TEndSkyBobHundred      = 100.0f;
__declspec(section ".rodata") const f32 TEndSkyBobConstants[2] = { 0.5f, 0.0f };
