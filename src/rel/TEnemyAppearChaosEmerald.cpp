#include "types.h"

struct RwV3d {
	f32 x;
	f32 y;
	f32 z;
};

struct sAngle {
	s32 x;
	s32 y;
	s32 z;
};

struct AppearChaosEmeraldParam {
	RwV3d scale;
	f32 appearPosition;
};

struct SETDATA_PARAM {
	RwV3d position;
	sAngle angle;
	u8 pad18[0x14];
	AppearChaosEmeraldParam* member;
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
	virtual void Error(char* message);
	virtual void Render();
};

struct TObjectTail {
	s16 field1C;
	s16 objectSize;
	s16 field20;
	s16 field22;
	s16 field24;
	s16 field26;
};

class TEditMotion
{
public:
	SETDATA_PARAM* volatile frame;

	virtual void EditOnChange(SETDATA_PARAM* setData);
};

extern "C" void* __nw__10TObjSampleFUl(u32 size);

class TEnemyAppearChaosEmerald : public TObject, public TObjectTail, public TEditMotion
{
public:
	u8 collision[0xA8];
	u8 controller[8];
	f32 appearPosition;

	virtual ~TEnemyAppearChaosEmerald();
	virtual void Exec();
	virtual void EditOnChange(SETDATA_PARAM* setData);

	TEnemyAppearChaosEmerald(TObject* parent);
	static void Create();

	static void* operator new(unsigned long size) { return __nw__10TObjSampleFUl(size); }
	static void operator delete(void* object);
};

struct GameState;

extern "C" {
void markSampleForDeletion(TEnemyAppearChaosEmerald* object);
void setupObjClass(void* entry, char* name, void (*initialize)(), void (*finalize)(), void* create,
    void*, void*, void*, u32, u32, u32, u32, char*, void*);
u32 fn_16_D10(void* collision);
void fn_16_1180(void* collision, SETDATA_PARAM* setData, sAngle* angle);
int fn_16_F20(GameState* state, int flag);
void fn_16_5F3C8(TEnemyAppearChaosEmerald* object);
void fn_16_5F608(TEnemyAppearChaosEmerald* object, TObject* parent);
void fn_16_6492C(int index, f32 position);
int fn_16_93ACC(void* controller, SETDATA_PARAM* setData, f32 value);
void fn_16_93BE8(void* controller, int flags);
void fn_16_93C3C(void* controller);

int fn_8005B8BC(void* motion);
int fn_8005B8D8(void* motion);
int fn_8005B9F0(void* motion);
void fn_8005BC04(void* motion);
void fn_80021824(void* collision);

extern GameState* lbl_8042C180;
extern u8 lbl_8042C1A4[];
extern TObject* lbl_16_bss_1058;
extern f32 lbl_16_rodata_1738;

TEnemyAppearChaosEmerald* __dt__24TEnemyAppearChaosEmeraldFv(TEnemyAppearChaosEmerald*, s16);
TEnemyAppearChaosEmerald* __ct__24TEnemyAppearChaosEmeraldFP7TObject(
    TEnemyAppearChaosEmerald*, TObject*);
void Exec__24TEnemyAppearChaosEmeraldFv(TEnemyAppearChaosEmerald*);
void EditOnChange__24TEnemyAppearChaosEmeraldFP13SETDATA_PARAM(
    TEnemyAppearChaosEmerald*, SETDATA_PARAM*);
}

extern "C" char TEnemyAppearChaosEmeraldClassName[]     = "TEnemyAppearChaosEmerald";
extern "C" char* TEnemyAppearChaosEmeraldClassNamePtr   = TEnemyAppearChaosEmeraldClassName;
extern "C" char TEnemyAppearChaosEmeraldScaleXName[]    = "SCALE X";
extern "C" char TEnemyAppearChaosEmeraldScaleYName[]    = "SCALE Y";
extern "C" char TEnemyAppearChaosEmeraldScaleZName[]    = "SCALE Z";
extern "C" char TEnemyAppearChaosEmeraldAppearPosName[] = "APPEAR_POS";
extern "C" char* TEnemyAppearChaosEmeraldFieldNames[4]  = {
	TEnemyAppearChaosEmeraldScaleXName,
	TEnemyAppearChaosEmeraldScaleYName,
	TEnemyAppearChaosEmeraldScaleZName,
	TEnemyAppearChaosEmeraldAppearPosName,
};
extern "C" const volatile f32 TEnemyAppearChaosEmeraldZero;
extern "C" const f32 TEnemyAppearChaosEmeraldConstant;
extern "C" void* __vt__24TEnemyAppearChaosEmerald[];

extern "C" {
u8 ObjS40EnemyAppearChaosEmerald[0x30];
}

#pragma opt_lifetimes off
void TEnemyAppearChaosEmerald::Exec()
{
	AppearChaosEmeraldParam* volatile member = frame->member;

	if (!fn_16_93ACC(controller, frame, lbl_16_rodata_1738)) {
		fn_8005BC04((void*)&frame);
		markSampleForDeletion(this);
		return;
	}

	if (fn_8005B9F0((void*)&frame) || fn_8005B8BC((void*)&frame)) {
		markSampleForDeletion(this);
		return;
	}

	if (fn_16_F20(lbl_8042C180, 0x1F))
		return;

	fn_16_5F3C8(this);
	if (fn_8005B8D8((void*)&frame))
		return;

	fn_80021824(lbl_8042C1A4);
	if (fn_16_D10(collision))
		fn_16_6492C(0, appearPosition);

	fn_16_1180(collision, frame, &frame->angle);
}

void TEnemyAppearChaosEmerald::EditOnChange(SETDATA_PARAM* setData)
{
	AppearChaosEmeraldParam* member = setData->member;

	if (member->scale.x < TEnemyAppearChaosEmeraldZero)
		member->scale.x = TEnemyAppearChaosEmeraldZero;
	if (member->scale.y < TEnemyAppearChaosEmeraldZero)
		member->scale.y = TEnemyAppearChaosEmeraldZero;
	if (member->scale.z < TEnemyAppearChaosEmeraldZero)
		member->scale.z = TEnemyAppearChaosEmeraldZero;
	appearPosition = member->appearPosition;
}

TEnemyAppearChaosEmerald::~TEnemyAppearChaosEmerald()
{
	AppearChaosEmeraldParam* volatile member = frame->member;
	fn_16_93BE8((u8*)this + 0xD8, 0);
}

extern "C" TEnemyAppearChaosEmerald* __ct__24TEnemyAppearChaosEmeraldFP7TObject(
    TEnemyAppearChaosEmerald* object, TObject* parent)
{
	fn_16_5F608(object, parent);
	fn_16_93C3C((u8*)object + 0xD8);
	*(void**)((u8*)object + 0x18) = __vt__24TEnemyAppearChaosEmerald;
	*(void**)((u8*)object + 0x2C) = __vt__24TEnemyAppearChaosEmerald + 11;
	object->className             = TEnemyAppearChaosEmeraldClassNamePtr;
	object->objectSize            = sizeof(TEnemyAppearChaosEmerald);

	register AppearChaosEmeraldParam* member = object->frame->member;
	if (TEnemyAppearChaosEmeraldZero == member->appearPosition) {
		object->appearPosition = member->appearPosition = TEnemyAppearChaosEmeraldConstant;
	}
	object->appearPosition      = member->appearPosition;
	*(u32*)((u8*)object + 0xBC) = 0x6000FFFF;
	return object;
}

void TEnemyAppearChaosEmerald::Create()
{
	register TEnemyAppearChaosEmerald* object
	    = (TEnemyAppearChaosEmerald*)__nw__10TObjSampleFUl(sizeof(TEnemyAppearChaosEmerald));
	if (object != 0)
		object = __ct__24TEnemyAppearChaosEmeraldFP7TObject(object, lbl_16_bss_1058);
}

extern "C" char ObjS40EnemyAppearChaosEmeraldName[];
extern "C" char TEnemyAppearChaosEmeraldFieldTypes;

extern "C" void __sinit_TEnemyAppearChaosEmerald_cpp()
{
	setupObjClass(ObjS40EnemyAppearChaosEmerald, ObjS40EnemyAppearChaosEmeraldName, 0, 0,
	    (void*)TEnemyAppearChaosEmerald::Create, 0, 0, 0, 0x32, 0x15E8, 2, 0,
	    &TEnemyAppearChaosEmeraldFieldTypes, TEnemyAppearChaosEmeraldFieldNames);
}

__declspec(section ".ctors") void (*const TEnemyAppearChaosEmeraldCtorEntry)()
    = __sinit_TEnemyAppearChaosEmerald_cpp;

extern "C" __declspec(section ".rodata") const volatile f32 TEnemyAppearChaosEmeraldZero = 0.0f;
extern "C" __declspec(section ".rodata") const f32 TEnemyAppearChaosEmeraldConstant      = 2000.0f;
extern "C" __declspec(section ".rodata") const f32 TEnemyAppearChaosEmeraldConstantTail  = 0.0f;
#pragma opt_lifetimes reset
