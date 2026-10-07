#include "types.h"

// Retained PS2 symbols name this object TObjS12Fan (o_s12_fan.cpp there) and
// give its method family: DestroyClump, CloneClump, SetPosition, SetParameter,
// Exec, the destructor, the TObject* constructor and the initObj/endObj/startObj
// lifecycle functions. The "TObjS12Fan" class-name string in this unit's .data
// independently correlates the GameCube object with that family.

struct Vec3 {
	f32 x;
	f32 y;
	f32 z;
};

struct SETDATA_PARAM {
	Vec3 position;
	s32 angleX;
	s32 angleY;
	s32 angleZ;
	u32 flags;
};

// Retail emits this unreferenced vector at the head of the unit's .rodata, the
// way an internal-linkage const from a shared header lands in every translation
// unit that includes it. Its name and home header are unknown. The retail link
// keeps it although nothing reads it; a local symbol cannot be listed in the
// module's force_active set, so the object carries the flag itself.
#pragma force_active on
static const Vec3 lbl_8_rodata_1F18 = { 0.0f, 1.5f, 0.0f };
#pragma force_active reset

class TObject
{
public:
	const char* className;
	u16 signal;
	u8 pad06[0x12];
	void** vtable;
	s16 pad1C;
	s16 objectSize;
	u8 pad20[8];

	TObject(TObject*);
	~TObject();
};

extern "C" {
void dtor_8005BD3C(void*, s16);
void fn_8005BE6C(void*);
}

struct Motion {
	SETDATA_PARAM* frame;
	void** vtable;

	Motion() { fn_8005BE6C(this); }
};

extern "C" {
extern void* lbl_8042C110;
extern void* lbl_8042C148;
extern void* lbl_8042C180;
extern void* lbl_8042C1D0;
extern void* lbl_8042C298;
extern u8 lbl_80239984;
extern u8 lbl_802FF5A0;

s32 fn_8005B8BC(Motion*);
s32 fn_8005B9F0(Motion*);
void fn_8005D5C8(void*, u32);
f32 fn_800D7AE4(s32);
f32 fn_800D7B00(s32);
void* Malloc__9THeapCtrlFUi(void*, u32);
void Free__9THeapCtrlFPv(void*, void*);
void* fn_80150588(void*);
void fn_80150958(void*);
void fn_8015BB08(void*, void*);
void fn_8015BBF8(void*, void*);
void fn_80195790(void*, void*, f32, f32, s32);
void fn_8019E880(void*);
void fn_8019EB94(void*, Vec3*, s32);
void fn_801A4C84(void*);
void* LoadClumpEx__7ONEFILEFUiPc(void*, s32, void*);
s32 CheckFileID__7ONEFILEFPc(void*, const char*);
void LoadOneFile__7ONEFILEFPc(void*, void*);

void Disp__7TObjectFv();
void fn_8005B8B8();
void TDisp__7TObjectFv();
void PDisp__7TObjectFv();
void ImmAftSetRaster__7TObjectFv();
void Debug__7TObjectFv();
void Error__7TObjectFPc();
void Render__7TObjectFv();
}

class TObjS12Fan : public TObject, public Motion
{
public:
	Vec3 position;
	void* model;

	void DestroyClump();
	void CloneClump();
	void SetPosition();
	void SetParameter();
	void Exec();
	TObjS12Fan();
	TObjS12Fan(TObject*);
	~TObjS12Fan();

	static void* operator new(unsigned long size, void* heap)
	{
		return Malloc__9THeapCtrlFUi(heap, size);
	}
	static void operator delete(void* object) { Free__9THeapCtrlFPv(lbl_8042C148, object); }
};

// The s12fan* data names and CL_TObjS12Fan (after o_s11_cloud's CL_TObjS11Cloud)
// are descriptive guesses; the retail object carries no names for them.
extern "C" {
TObjS12Fan* __dt__10TObjS12FanFv(TObjS12Fan*, s16);
void Exec__10TObjS12FanFv(TObjS12Fan*);
extern void* s12fanVtable[14];
extern char* CL_TObjS12Fan;
extern s32 s12fanRotationSpeed;
extern char s12fanModelName[];
extern char s12fanObjectDisplayName[];
}

extern "C" void* s12fanModel;

void TObjS12Fan::DestroyClump()
{
	if (model != NULL) {
		void* manager = *(void**)((u8*)lbl_8042C1D0 + 0x725C);
		fn_8015BBF8(manager, model);
		fn_80150958(model);
		model = NULL;
	}
}

void TObjS12Fan::CloneClump()
{
	if (model == NULL) {
		model         = fn_80150588(s12fanModel);
		void* manager = *(void**)((u8*)lbl_8042C1D0 + 0x725C);
		fn_8015BB08(manager, model);
		fn_8005D5C8(model, ((frame->flags & 0x1C0000) >> 18) + 4);
	}
}

void TObjS12Fan::SetPosition()
{
	s32 time;
	void* atomic = *(void**)((u8*)model + 4);
	fn_8019EB94(atomic, &position, 0);
	time     = *(s32*)((u8*)lbl_8042C180 + 0x30);
	f32 sine = fn_800D7B00(s12fanRotationSpeed * time);
	fn_80195790(
	    (u8*)atomic + 0x10, &lbl_80239984, 1.0f - fn_800D7AE4(s12fanRotationSpeed * time), sine, 1);
	fn_8019E880(atomic);
}

void TObjS12Fan::SetParameter()
{
	position = frame->position;
}

#pragma opt_common_subs off
void TObjS12Fan::Exec()
{
	if (fn_8005B9F0((Motion*)((u8*)this + 0x28)) != 0
	    || fn_8005B8BC((Motion*)((u8*)this + 0x28)) != 0) {
		signal |= 1;
		return;
	}
	SetPosition();
}
#pragma opt_common_subs reset

TObjS12Fan::~TObjS12Fan()
{
	TObject::vtable = s12fanVtable;
	Motion::vtable  = s12fanVtable + 11;
	DestroyClump();
	dtor_8005BD3C((u8*)this + 0x28, 0);
}

static inline void constructFan(TObjS12Fan* object)
{
	object->TObject::vtable = s12fanVtable;
	object->Motion::vtable  = s12fanVtable + 11;
	object->className       = CL_TObjS12Fan;
	object->objectSize      = sizeof(TObjS12Fan);
	object->SetParameter();
	object->model = NULL;
	// Written out rather than calling CloneClump(): retail's constructor reads the
	// frame flags before reloading the model, the reverse of the method's order.
	if (object->model == NULL) {
		object->model = fn_80150588(s12fanModel);
		fn_8015BB08(*(void**)((u8*)lbl_8042C1D0 + 0x725C), object->model);
		u32 flags = object->frame->flags;
		fn_8005D5C8(object->model, ((flags & 0x1C0000) >> 18) + 4);
	}
	object->SetPosition();
}

TObjS12Fan::TObjS12Fan(TObject* parent)
    : TObject(parent)
    , Motion()
{
	constructFan(this);
}

inline TObjS12Fan::TObjS12Fan()
    : TObject((TObject*)lbl_8042C110)
    , Motion()
{
	constructFan(this);
}

extern "C" void endObjS12Fan()
{
	if (s12fanModel != NULL) {
		fn_80150958(s12fanModel);
		s12fanModel = NULL;
	}
}

extern "C" void initObjS12Fan()
{
	void* stage = *(void**)((u8*)lbl_8042C1D0 + 0x8C18);
	if (!(stage != NULL && (fn_801A4C84(stage), 1)))
		return;

	LoadOneFile__7ONEFILEFPc(*(void**)((u8*)lbl_8042C298 + 0xA50), &lbl_802FF5A0);
	s32 id = CheckFileID__7ONEFILEFPc(*(void**)((u8*)lbl_8042C298 + 0xA50), s12fanModelName);
	s12fanModel
	    = LoadClumpEx__7ONEFILEFUiPc(*(void**)((u8*)lbl_8042C298 + 0xA50), id, &lbl_802FF5A0);
}

extern "C" void startObjS12Fan()
{
	new (lbl_8042C148) TObjS12Fan();
}

struct SETOBJ_PARAM {
	char* displayName;
	void (*init)();
	void (*end)();
	void (*create)();
	u32 field10;
	u32 flags;
	u32 field18;
	u16 id;
	u16 count;
	u8 field20;
	u8 field21;
	u8 pad22[2];
	char* fieldTypes;
	void* fields;
};

extern "C" {
void* s12fanModel;
SETOBJ_PARAM s12fanObjectEntry;
}

extern "C" void s12fanObjectRegister()
{
	s12fanObjectEntry.flags       = 0;
	s12fanObjectEntry.field18     = 0;
	s12fanObjectEntry.displayName = s12fanObjectDisplayName;
	s12fanObjectEntry.init        = initObjS12Fan;
	s12fanObjectEntry.end         = endObjS12Fan;
	s12fanObjectEntry.create      = startObjS12Fan;
	s12fanObjectEntry.field10     = 0;
	s12fanObjectEntry.flags       = 0x20000;
	s12fanObjectEntry.field18     = 0;
	s12fanObjectEntry.field20     = 0x1E;
	s12fanObjectEntry.id          = 0x1187;
	s12fanObjectEntry.count       = 2;
	s12fanObjectEntry.field21     = 0;
	s12fanObjectEntry.fieldTypes  = NULL;
	s12fanObjectEntry.fields      = NULL;
	if (s12fanObjectEntry.fieldTypes != NULL)
		s12fanObjectEntry.flags |= 8;
	else
		s12fanObjectEntry.flags &= ~8;
}

__declspec(section ".ctors") void (*const s12fanObjectCtorEntry)() = s12fanObjectRegister;

extern "C" s32 s12fanRotationSpeed    = 0x444;
extern "C" char TObjS12FanClassName[] = "TObjS12Fan";
extern "C" char* CL_TObjS12Fan        = TObjS12FanClassName;
extern "C" void* s12fanVtable[14]     = {
	0,
	0,
	(void*)__dt__10TObjS12FanFv,
	(void*)Exec__10TObjS12FanFv,
	(void*)Disp__7TObjectFv,
	(void*)TDisp__7TObjectFv,
	(void*)PDisp__7TObjectFv,
	(void*)ImmAftSetRaster__7TObjectFv,
	(void*)Debug__7TObjectFv,
	(void*)Error__7TObjectFPc,
	(void*)Render__7TObjectFv,
	0,
	0,
	(void*)fn_8005B8B8,
};
extern "C" char s12fanModelName[]         = "s12_on_fan.dff";
extern "C" char s12fanObjectDisplayName[] = "S12FAN OBJECT";
