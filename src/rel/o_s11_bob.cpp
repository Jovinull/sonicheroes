#include "types.h"

// Retained PS2 symbols identify o_s11_bob.cpp and its complete constructor,
// destructor, lifecycle, and static-initializer family.  The GameCube class
// string, vtable, model names, registration record, and neighboring object
// data independently establish the retail translation-unit boundaries.

struct SETDATA_PARAM;

struct Motion {
	SETDATA_PARAM* frame;
	void** vtable;
};

class TObject;

extern "C" {
extern void* lbl_8042C110;
extern void* lbl_8042C148;
extern void* lbl_8042C1D0;
extern void* lbl_8042C298;
extern u8 lbl_802FF5A0;

void __ct__7TObjectFP7TObject(void*, void*);
void __dt__7TObjectFv(void*, s16);
void __dt__10TObjSetObjFv(Motion*, s16);
void __ct__10TObjSetObjFv(Motion*);
void* Malloc__9THeapCtrlFUi(void*, u32);
void Free__9THeapCtrlFPv(void*, void*);
void* LoadClumpEx__7ONEFILEFUiPc(void*, s32, void*);
s32 CheckFileID__7ONEFILEFPc(void*, const char*);
void LoadOneFile__7ONEFILEFPc(void*, void*);
void fn_80150958(void*);
void fn_801A4C84(void*);

void Disp__7TObjectFv();
void Exec__10TObjS31BobFv();
void EditOnChange__10TObjSetObjFP13SETDATA_PARAM();
void Debug__7TObjectFv();
void ImmAftSetRaster__7TObjectFv();
void PDisp__7TObjectFv();
void Render__7TObjectFv();
void TDisp__7TObjectFv();
void Error__7TObjectFPc();
}

class TObjS11Bob
{
public:
	const char* className;
	u16 signal;
	u8 pad06[0x12];
	void** vtable;
	s16 pad1C;
	s16 objectSize;
	u8 pad20[8];
	Motion motion;

	TObjS11Bob(TObject*);
	~TObjS11Bob();

	static void operator delete(void* object) { Free__9THeapCtrlFPv(lbl_8042C148, object); }
};

extern "C" {
TObjS11Bob* __dt__10TObjS11BobFv(TObjS11Bob*, s16);
extern void* bobVtable[14];
extern char* CL_TObjS11Bob;
}

TObjS11Bob::~TObjS11Bob()
{
	vtable        = bobVtable;
	motion.vtable = bobVtable + 11;
	__dt__10TObjSetObjFv(&motion, 0);
	__dt__7TObjectFv(this, 0);
}

static inline void constructBob(TObjS11Bob* object, TObject* parent)
{
	__ct__7TObjectFP7TObject(object, parent);
	__ct__10TObjSetObjFv(&object->motion);
	object->vtable        = bobVtable;
	object->motion.vtable = bobVtable + 11;
	object->className     = CL_TObjS11Bob;
	object->objectSize    = sizeof(TObjS11Bob);
}

TObjS11Bob::TObjS11Bob(TObject* parent)
{
	constructBob(this, parent);
}

extern "C" {
extern void* bobResource;
extern void* bobLightResource;
}

extern "C" void endObjS11Bob()
{
	if (bobResource != NULL) {
		fn_80150958(bobResource);
		bobResource = NULL;
	}
	if (bobLightResource != NULL) {
		fn_80150958(bobLightResource);
		bobLightResource = NULL;
	}
}

extern "C" char bobModelName[];
extern "C" char bobLightModelName[];

static inline void* stageArchive()
{
	return *(void**)((u8*)lbl_8042C298 + 0xA50);
}

extern "C" void initObjS11Bob()
{
	void* stage = *(void**)((u8*)lbl_8042C1D0 + 0x8C18);
	if (!(stage != NULL && (fn_801A4C84(stage), true)))
		return;

	LoadOneFile__7ONEFILEFPc(stageArchive(), &lbl_802FF5A0);
	s32 id           = CheckFileID__7ONEFILEFPc(stageArchive(), bobModelName);
	bobResource      = LoadClumpEx__7ONEFILEFUiPc(stageArchive(), id, &lbl_802FF5A0);
	id               = CheckFileID__7ONEFILEFPc(stageArchive(), bobLightModelName);
	bobLightResource = LoadClumpEx__7ONEFILEFUiPc(stageArchive(), id, &lbl_802FF5A0);
}

struct BobInitializer {
	u8 data[sizeof(TObjS11Bob)];
};

static inline void initializeBob(BobInitializer* self)
{
	TObjS11Bob* object = (TObjS11Bob*)self;
	__ct__7TObjectFP7TObject(object, lbl_8042C110);
	__ct__10TObjSetObjFv(&object->motion);
	object->vtable        = bobVtable;
	object->motion.vtable = bobVtable + 11;
	object->className     = CL_TObjS11Bob;
	object->objectSize    = sizeof(TObjS11Bob);
}

#pragma optimization_level 2
#pragma opt_common_subs off
extern "C" void startObjS11Bob()
{
#pragma opt_propagation off
	void* allocation = Malloc__9THeapCtrlFUi(lbl_8042C148, sizeof(TObjS11Bob));
	if (allocation != NULL) {
		BobInitializer* object = (BobInitializer*)allocation;
		initializeBob(object);
	}
}
#pragma opt_common_subs reset
#pragma optimization_level reset

extern "C" char bobClassName[] = "TObjS11Bob";
extern "C" char* CL_TObjS11Bob = bobClassName;

extern "C" void* bobVtable[14] = {
	NULL,
	NULL,
	(void*)__dt__10TObjS11BobFv,
	(void*)Exec__10TObjS31BobFv,
	(void*)Disp__7TObjectFv,
	(void*)TDisp__7TObjectFv,
	(void*)PDisp__7TObjectFv,
	(void*)ImmAftSetRaster__7TObjectFv,
	(void*)Debug__7TObjectFv,
	(void*)Error__7TObjectFPc,
	(void*)Render__7TObjectFv,
	NULL,
	NULL,
	(void*)EditOnChange__10TObjSetObjFP13SETDATA_PARAM,
};

extern "C" char bobModelName[]      = "s12_o_bobsleigh.dff";
extern "C" char bobLightModelName[] = "s12_kw_light2.dff";
extern "C" char bobDisplayName[]    = "S11BOB OBJECT(DUMMY)";

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

extern "C" SETOBJ_PARAM ObjS11BobParam;

extern "C" void __sinit_o_s11_bob_cpp()
{
	ObjS11BobParam.flags       = 0;
	ObjS11BobParam.field18     = 0;
	ObjS11BobParam.displayName = bobDisplayName;
	ObjS11BobParam.init        = initObjS11Bob;
	ObjS11BobParam.end         = endObjS11Bob;
	ObjS11BobParam.create      = startObjS11Bob;
	ObjS11BobParam.field10     = 0;
	ObjS11BobParam.flags       = 0x02000000;
	ObjS11BobParam.field18     = 0;
	ObjS11BobParam.field20     = 0x1E;
	ObjS11BobParam.id          = 0x110A;
	ObjS11BobParam.count       = 2;
	ObjS11BobParam.field21     = 0;
	ObjS11BobParam.fieldTypes  = NULL;
	ObjS11BobParam.fields      = NULL;
	if (ObjS11BobParam.fieldTypes != NULL)
		ObjS11BobParam.flags |= 8;
	else
		ObjS11BobParam.flags &= ~8;
}

extern "C" {
void* bobResource;
void* bobLightResource;
SETOBJ_PARAM ObjS11BobParam;
}

__declspec(section ".ctors") void (*const BobCtorEntry)() = __sinit_o_s11_bob_cpp;
