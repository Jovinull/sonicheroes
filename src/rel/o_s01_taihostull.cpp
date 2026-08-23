#include "types.h"

// PS2 beta symbols identify o_s01_taihostull.cpp and the TObjS01Stull
// methods. GameCube code order, the class vtable, constructor entry, object
// registration record, and contiguous constants independently establish the
// retail C++ translation unit.

struct SETDATA_PARAM {
	u8 pad00[0x2C];
	f32* params;
};

struct StullThunkPrimary {
	u8 pad04[0x24];
	virtual void PrimarySlot();
};

struct StullThunkSecondary {
	virtual void EditOnChange(SETDATA_PARAM*);
};

struct StullThunk : StullThunkPrimary, StullThunkSecondary {
	virtual void EditOnChange(SETDATA_PARAM*);
};

struct RenderDescriptor {
	s32 index;
	void* (*callback)(void*);
};

struct RenderObject {
	u8 pad00[0x48];
	void* (*render)(void*);
};

struct Vec3 {
	f32 x;
	f32 y;
	f32 z;
};

struct TObject {
	u8 pad00[0x18];
	void** vtable;
	u8 pad1C[0x0C];

	TObject(TObject*);
	~TObject();
};

extern "C" void* fn_80018A34(void*, u32);
extern "C" void* lbl_8042C148;

struct TObjS01Stull : TObject {
	u8 motion[8];
	u8 collision[0x60];
	u8 pad90[0x28];
	void* resource;

	TObjS01Stull(TObject*);
	~TObjS01Stull();
	static void* operator new(unsigned long size) { return fn_80018A34(lbl_8042C148, size); }
};

extern "C" {
void* S01RenderCallback(void*);
void* fn_8014F1B0(void*);
RenderDescriptor* fn_8005F490(void*);
s32 fn_8005D3DC(void*, f32);
void fn_800B864C(void*);
void fn_8019EC30(void*, Vec3*, s32);
void fn_8019ED68(void*, void*, f32, s32);
void fn_8019EB94(void*, void*, s32);
extern void* lbl_80239978;
extern void* lbl_80239984;
extern void* lbl_80239990;

void fn_80150958(void*);
void* __ct__7TObjectFP7TObject(void*, void*);
void fn_8005BE6C(void*);
void fn_8003C618(void*);
void* fn_80150588(void*);
extern void* lbl_8042C1D0;
void fn_8015BB08(void*, void*);
void fn_8005CC94(void*, f32);
void fn_8014FFBC(void*, void (*)(RenderObject*), s32);
void fn_801A4C84(void*);
extern void* lbl_8042C298;
extern u8 lbl_8029C310[];
extern char lbl_802FF5A0[];
void fn_800BC9F4(void*, char*);
s32 fn_801C3C04(char*, char*);
char* strcpy(char*, const char*);
s32 fn_800BC6CC(void*, s32);
void* fn_800BB92C(void*, s32, char*);
void fn_800B8BEC(void*, s32);
extern void* lbl_8042C110;
int fn_8005B9F0(void*);
int fn_8005B8BC(void*);
int fn_8005B8D8(void*);
void fn_8003C200(void*, void*, s32, s32);
void fn_80021384(void*);
void fn_8003BC38(void*);
extern void* lbl_8042C180;
extern void* lbl_802D5E80;
extern void* lbl_8042C148;
void fn_8005303C(void*);
void fn_80053114(void*);
void fn_800B85D8(void*);
void fn_8005CE4C(void*);
void* fn_8015BD78(void*);
void fn_8015BBF8(void*, void*);
void dtor_8003C52C(void*, s32);
void dtor_8005BD3C(void*, s32);
void __dt__7TObjectFv(void*, s32);
void fn_800189A4(void*, void*);
void fn_3_1A9B0();
void PDisp__7TObjectFv();
void ImmAftSetRaster__7TObjectFv();
void Debug__7TObjectFv();
void Error__7TObjectFPc();
void Render__7TObjectFv();
extern void* stullResource;
extern void* stullClump;
extern char stullEmpty[4];
extern char stullDisplayName[];
extern char stullFieldTypes[];
extern char* stullFieldNames[];
extern void* stullVtable[15];
extern char* CL_TObjS01Stull;
}

static const f32 stullVector0[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
static const f32 stullVector1[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
static const f32 stullVector2[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

extern "C" void S01SetRenderCallback(RenderObject* object)
{
	object->render = S01RenderCallback;
	if (object->render == NULL)
		object->render = fn_8014F1B0;
}

extern "C" void* S01RenderCallback(void* object)
{
	RenderDescriptor* descriptor = fn_8005F490(object);
	if (fn_8005D3DC(object, descriptor->index) == 1)
		return object;
	fn_800B864C(object);
	descriptor->callback(object);
	return object;
}

static inline void SetStullPosition(TObjS01Stull* object)
{
	f32* params  = *(f32**)(*(u8**)object->motion + 0x2C);
	void* atomic = *(void**)((u8*)object->resource + 4);
	Vec3 scale   = *(Vec3*)stullVector0;
	scale.x      = params[0];
	scale.y      = params[0];
	scale.z      = params[0];
	fn_8019EC30(atomic, &scale, 0);
	fn_8019ED68(atomic, &lbl_80239984, 0.0054931640625f * *(s32*)(*(u8**)object->motion + 0x10), 2);
	fn_8019ED68(atomic, &lbl_80239978, 0.0054931640625f * *(s32*)(*(u8**)object->motion + 0x0C), 2);
	fn_8019ED68(atomic, &lbl_80239990, 0.0054931640625f * *(s32*)(*(u8**)object->motion + 0x14), 2);
	fn_8019EB94(atomic, *(u8**)object->motion, 2);
}

extern "C" void SetPosition__12TObjS01StullFv(TObjS01Stull* object)
{
	SetStullPosition(object);
}
extern "C" void TDisp__12TObjS01StullFv(TObjS01Stull* object)
{
	if (*(s8*)((u8*)lbl_8042C180 + 0x20) == 0) {
		fn_8005303C(&lbl_802D5E80);
		fn_800B85D8(object->resource);
		fn_8005CE4C(object->resource);
		fn_80053114(&lbl_802D5E80);
	}
}
extern "C" void Exec__12TObjS01StullFv(TObjS01Stull* object)
{
	f32* params = *(f32**)(*(u8**)object->motion + 0x2C);
	if (fn_8005B9F0(object->motion) != 0 || fn_8005B8BC(object->motion) != 0) {
		*(u16*)((u8*)object + 4) |= 1;
		return;
	}

	if (fn_8005B8D8(object->motion) != 0) {
		SetStullPosition(object);
	} else {
		if (*(void**)((u8*)object + 0x40) == NULL && stullClump != NULL
		    && *(void**)((u8*)stullClump + 0x28) != NULL) {
			fn_8003C200(object->collision, *(void**)((u8*)stullClump + 0x28),
			    *(s8*)((u8*)stullClump + 0x2C), 4);
			*(u16*)((u8*)object + 0x38) &= ~0x40;
			for (s8 i = 0; i < *(s8*)((u8*)stullClump + 0x2C); i++) {
				f32* vertex = (f32*)((u8*)*(void**)((u8*)object + 0x40) + i * 0x30);
				vertex[5] *= params[0];
				vertex[6] *= params[0];
				vertex[7] *= params[0];
			}
			fn_80021384(object->collision);
		}

		u8* frame                   = *(u8**)object->motion;
		*(f32*)((u8*)object + 0xAC) = *(f32*)((u8*)object + 0x90);
		*(f32*)((u8*)object + 0xB0) = *(f32*)((u8*)object + 0x94);
		*(f32*)((u8*)object + 0xB4) = *(f32*)((u8*)object + 0x98);
		*(f32*)((u8*)object + 0x90) = *(f32*)(frame + 0);
		*(f32*)((u8*)object + 0x94) = *(f32*)(frame + 4);
		*(f32*)((u8*)object + 0x98) = *(f32*)(frame + 8);
		*(u32*)((u8*)object + 0x9C) = *(u32*)(frame + 0x0C);
		*(u32*)((u8*)object + 0xA0) = *(u32*)(frame + 0x10);
		*(u32*)((u8*)object + 0xA4) = *(u32*)(frame + 0x14);
		fn_8003BC38(object->collision);
	}
}
extern "C" TObjS01Stull* __dt__12TObjS01StullFv(TObjS01Stull* object, s16 flags)
{
	if (object != NULL) {
		object->vtable                 = stullVtable;
		*(void***)(object->motion + 4) = stullVtable + 11;
		void* resource                 = object->resource;
		if (resource != NULL) {
			void* atomic = fn_8015BD78(resource);
			fn_8015BBF8(atomic, resource);
			fn_80150958(object->resource);
			object->resource = NULL;
		}
		dtor_8003C52C(object->collision, 0);
		dtor_8005BD3C(object->motion, 0);
		__dt__7TObjectFv(object, 0);
		if (flags > 0)
			fn_800189A4(lbl_8042C148, object);
	}
	return object;
}
TObjS01Stull::TObjS01Stull(TObject* parent)
    : TObject(parent)
{
	fn_8005BE6C(motion);
	fn_8003C618(collision);
	vtable                    = stullVtable;
	*(void***)(motion + 4)    = stullVtable + 11;
	f32* params               = *(f32**)(*(u8**)motion + 0x2C);
	*(char**)this             = CL_TObjS01Stull;
	*(u16*)((u8*)this + 0x1E) = sizeof(TObjS01Stull);
	resource                  = fn_80150588(stullResource);
	fn_8015BB08(*(void**)((u8*)lbl_8042C1D0 + 0x7260), resource);
	if (params[0] == 0.0f)
		params[0] = 1.0f;
	SetStullPosition(this);
	fn_8005CC94(resource, 0.0f);
	fn_8014FFBC(resource, S01SetRenderCallback, 0);
}

void StullThunk::EditOnChange(SETDATA_PARAM* param)
{
	if (*param->params < 0.0f)
		*param->params = 0.0f;
}

extern "C" void endObjS01Stull()
{
	if (stullResource != NULL) {
		fn_80150958(stullResource);
		stullResource = NULL;
	}
	stullClump = NULL;
}

struct StageResource {
	s32 stage;
	s32 asset;
	char name[0x28];
};

extern "C" StageResource lbl_3_data_B4AC[];

#pragma opt_dead_code off
extern "C" void initObjS01Stull()
{
	void* loading = *(void**)((u8*)lbl_8042C1D0 + 0x8C18);
	if (loading != NULL) {
		fn_801A4C84(loading);
	} else {
		return;
	}

	fn_800BC9F4(*(void**)((u8*)lbl_8042C298 + 0xA50), lbl_802FF5A0);
	StageResource* entry = lbl_3_data_B4AC;
	void* stage          = *(void**)(lbl_8029C310 + 0x34);
	while (entry->stage >= 0) {
		if (entry->stage == *(s32*)((u8*)stage + 4))
			break;
		entry++;
	}
	if (entry->stage < 0)
		entry = lbl_3_data_B4AC;
	if (fn_801C3C04(entry->name, stullEmpty) == 0)
		strcpy(entry->name, lbl_802FF5A0);
	s32 asset     = fn_800BC6CC(*(void**)((u8*)lbl_8042C298 + 0xA50), entry->asset);
	stullResource = fn_800BB92C(*(void**)((u8*)lbl_8042C298 + 0xA50), asset, entry->name);
	if (stullResource != NULL)
		fn_800B8BEC(stullResource, 0);
	stullClump = entry;
}
#pragma opt_dead_code reset
extern "C" void startObj_S01_Stull()
{
	new TObjS01Stull((TObject*)lbl_8042C110);
}

struct SETOBJ_PARAM {
	char* displayName;
	void (*load)();
	void (*unload)();
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
	char** fields;
	u32 pad2C;
	u32 pad30;
};

extern "C" SETOBJ_PARAM ObjS01StullParam;
extern "C" void EditOnChange__10StullThunkFP13SETDATA_PARAM(StullThunk*, SETDATA_PARAM*);
extern "C" void AdjustorEditOnChange__10StullThunkFP13SETDATA_PARAM(StullThunk*, SETDATA_PARAM*);

extern "C" void __sinit_o_s01_taihostull_cpp()
{
	ObjS01StullParam.flags       = 0;
	ObjS01StullParam.field18     = 0;
	ObjS01StullParam.displayName = stullDisplayName;
	ObjS01StullParam.load        = initObjS01Stull;
	ObjS01StullParam.unload      = endObjS01Stull;
	ObjS01StullParam.create      = startObj_S01_Stull;
	ObjS01StullParam.field10     = 0;
	ObjS01StullParam.flags       = 0x20000;
	ObjS01StullParam.field18     = 0;
	ObjS01StullParam.field20     = 0x14;
	ObjS01StullParam.id          = 0x188;
	ObjS01StullParam.count       = 2;
	ObjS01StullParam.field21     = 0;
	ObjS01StullParam.fieldTypes  = stullFieldTypes;
	ObjS01StullParam.fields      = stullFieldNames;
	if (ObjS01StullParam.fieldTypes != NULL)
		ObjS01StullParam.flags |= 8;
	else
		ObjS01StullParam.flags &= ~8;
}

extern "C" {
void* stullClump;
void* stullResource;
SETOBJ_PARAM ObjS01StullParam;

char stullFieldName[]   = "SCALE:";
char* stullFieldNames[] = { stullFieldName };
char stullClassName[]   = "TObjS01Stull";
char* CL_TObjS01Stull   = stullClassName;
void* stullVtable[15]   = {
	NULL,
	NULL,
	(void*)__dt__12TObjS01StullFv,
	(void*)Exec__12TObjS01StullFv,
	(void*)fn_3_1A9B0,
	(void*)TDisp__12TObjS01StullFv,
	(void*)PDisp__7TObjectFv,
	(void*)ImmAftSetRaster__7TObjectFv,
	(void*)Debug__7TObjectFv,
	(void*)Error__7TObjectFPc,
	(void*)Render__7TObjectFv,
	NULL,
	NULL,
	(void*)AdjustorEditOnChange__10StullThunkFP13SETDATA_PARAM,
	(void*)EditOnChange__10StullThunkFP13SETDATA_PARAM,
};
char stullEmpty[4]      = "";
char stullDisplayName[] = "S01 TAIHO DAIZA";
char stullFieldTypes[]  = "F";
}

__declspec(section ".ctors") void (*const StullCtorEntry)() = __sinit_o_s01_taihostull_cpp;

#pragma force_active on
static const f32 stullTrailingZero[1] = { 0.0f };
#pragma force_active reset
