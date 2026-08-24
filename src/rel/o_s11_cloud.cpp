#include "types.h"

// Retained PS2 symbols identify o_s11_cloud.cpp and its complete
// TObjS11Cloud method/lifecycle family. The GameCube model and UV resource
// strings, class/vtable metadata, editor tables, registration record, ctor
// entry, and adjacent object metadata independently establish this TU's
// boundaries.

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
	volatile u32 flags;
	u8 pad1C[0x10];
	u8* params;
};

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

struct CloudThunkPrimary {
	u8 pad04[0x24];
	virtual void PrimarySlot();
};

struct CloudThunkSecondary {
	virtual void EditOnChange(SETDATA_PARAM*);
};

struct CloudThunk : CloudThunkPrimary, CloudThunkSecondary {
	virtual void EditOnChange(SETDATA_PARAM*);
};

struct Motion {
	SETDATA_PARAM* frame;
	void** vtable;

	Motion() { fn_8005BE6C(this); }
	~Motion() { }
};

inline void* operator new(unsigned long, void* placement)
{
	return placement;
}

extern "C" {
extern void* lbl_8042C110;
extern void* lbl_8042C148;
extern void* lbl_8042C180;
extern void* lbl_8042C1D0;
extern void* lbl_8042C298;
extern u8 lbl_80239984;
extern u8 lbl_80239990;
extern u8 lbl_8029C310;
extern u8 lbl_802FF5A0;

void __ct__7TObjectFP7TObject(void*, void*);
void __dt__7TObjectFv(void*, s16);
s32 fn_8005B8BC(Motion*);
s32 fn_8005B9F0(Motion*);
void fn_8005C014(void*, void*);
void fn_8005D5C8(void*, u32);
void* fn_8005E394(void*, s32);
void fn_8005BF88();
f32 fn_800D7AE4(s32);
f32 fn_800D7B00(s32);
void* fn_80018A34(void*, u32);
void fn_800189A4(void*, void*);
void fn_8011B7CC(void*);
void fn_8011B844(void*, f32);
void fn_801491A8();
void fn_8014FFBC(void*, void*, void*);
void* fn_80150588(void*);
void fn_80150958(void*);
void fn_8015BB08(void*, void*);
void fn_8015BBF8(void*, void*);
void fn_80195790(void*, void*, f32, f32, s32);
void fn_8019E880(void*);
void fn_8019EB94(void*, Vec3*, s32);
void fn_801A4C84(void*);
void* fn_800BAE0C(void*, s32, void*);
void* fn_800BB92C(void*, s32, void*);
s32 fn_800BC6CC(void*, const char*);
void fn_800BC9F4(void*, void*);

void Debug__7TObjectFv();
void ImmAftSetRaster__7TObjectFv();
void PDisp__7TObjectFv();
void Render__7TObjectFv();
void objDefaultTDisp();
void Error__7TObjectFPc();
}

class TObjS11Cloud : public TObject, public Motion
{
public:
	Vec3 position;
	s32 angleX;
	s32 angleY;
	s32 angleZ;
	s32 modelNo;
	s32 direction;
	f32 speed;
	void* model;

	void DestroyClump();
	void CloneClump(s32);
	void SetPosition();
	void SetParameter();
	void Disp();
	void Exec();
	TObjS11Cloud();
	TObjS11Cloud(TObject*);
	~TObjS11Cloud();

	static void* operator new(unsigned long size, void* heap) { return fn_80018A34(heap, size); }
	static void operator delete(void* object) { fn_800189A4(lbl_8042C148, object); }
};

extern "C" {
TObjS11Cloud* __dt__12TObjS11CloudFv(TObjS11Cloud*, s16);
void Exec__12TObjS11CloudFv(TObjS11Cloud*);
void Disp__12TObjS11CloudFv(TObjS11Cloud*);
void EditOnChange__12TObjS11CloudFP13SETDATA_PARAM(TObjS11Cloud*, SETDATA_PARAM*);
void AdjustorEditOnChange__12TObjS11CloudFP13SETDATA_PARAM(void*, SETDATA_PARAM*);
extern void* cloudVtable[15];
extern char* CL_TObjS11Cloud;
extern void* cloudModels[6];
extern void* cloudUvResource;
extern u8 cloudUvState[0x44];
extern s32 cloudLastFrame;
extern f32 cloudOne;
extern f32 cloudHalf;
extern char cloudDisplayName[];
extern char cloudFieldTypes[];
extern char* cloudFieldNames[3];
}

extern "C" __declspec(section ".rodata") f32 cloudOne         = 1.0f;
extern "C" __declspec(section ".rodata") f32 cloudHalf        = 0.5f;
extern "C" __declspec(section ".rodata") u32 cloudConstantPad = 0;

void TObjS11Cloud::DestroyClump()
{
	if (model != NULL) {
		void* manager = *(void**)((u8*)lbl_8042C1D0 + 0x72A0);
		fn_8015BBF8(manager, model);
		fn_80150958(model);
		model = NULL;
	}
}

void TObjS11Cloud::CloneClump(s32 index)
{
	if (model == NULL) {
		model         = fn_80150588(cloudModels[index]);
		void* manager = *(void**)((u8*)lbl_8042C1D0 + 0x72A0);
		fn_8015BB08(manager, model);
		fn_8005D5C8(model, 0x10);
	}
}

#pragma opt_common_subs off
void TObjS11Cloud::SetPosition()
{
	void* atomic = *(void**)((u8*)model + 4);
	fn_8019EB94(atomic, &position, 0);
	f32 sine = fn_800D7B00(angleY);
	fn_80195790((u8*)atomic + 0x10, &lbl_80239984, cloudOne - fn_800D7AE4(angleY), sine, 1);
	fn_8019E880(atomic);
	if (direction == 1) {
		sine = fn_800D7B00(0x8000);
		fn_80195790((u8*)atomic + 0x10, &lbl_80239990, cloudOne - fn_800D7AE4(0x8000), sine, 1);
		fn_8019E880(atomic);
	}
}
#pragma opt_common_subs reset

void TObjS11Cloud::SetParameter()
{
	SETDATA_PARAM* frame = Motion::frame;
	u8* params           = frame->params;
	position             = frame->position;
	frame                = Motion::frame;
	angleX               = frame->angleX;
	angleY               = frame->angleY;
	angleZ               = frame->angleZ;
	angleZ               = 0;
	angleX               = 0;
	modelNo              = *(s32*)params;
	speed                = cloudOne + *(f32*)(params + 4);
	direction            = *(s8*)(params + 8);
}

#pragma push
#pragma section const_type ".cloudbias"                                                            \
                           ".cloudbias"
void TObjS11Cloud::Disp()
{
	u8* display = (u8*)lbl_8042C180;
	if (*(s8*)(display + 0x20) == 0) {
		s32 frame = *(s32*)(display + 0x30);
		if (cloudLastFrame != frame) {
			f32 time = speed * (cloudHalf * (f32)(frame - cloudLastFrame));
			fn_8011B844(cloudUvResource, time);
			fn_8014FFBC(model, (void*)fn_8005BF88, cloudUvState);
			cloudLastFrame = frame;
		}
	}
}
#pragma pop

#pragma opt_common_subs off
void TObjS11Cloud::Exec()
{
	if (fn_8005B9F0((Motion*)((u8*)this + 0x28)) != 0
	    || fn_8005B8BC((Motion*)((u8*)this + 0x28)) != 0) {
		signal |= 1;
		return;
	}
	SetPosition();
}
#pragma opt_common_subs reset

TObjS11Cloud::~TObjS11Cloud()
{
	TObject::vtable = cloudVtable;
	Motion::vtable  = cloudVtable + 11;
	DestroyClump();
	dtor_8005BD3C((u8*)this + 0x28, 0);
}

static inline void constructCloud(TObjS11Cloud* object)
{
	object->TObject::vtable = cloudVtable;
	object->Motion::vtable  = cloudVtable + 11;
	object->className       = CL_TObjS11Cloud;
	object->objectSize      = sizeof(TObjS11Cloud);
	object->SetParameter();
	object->model = NULL;
	object->CloneClump(object->modelNo);
	fn_8005E394(object->model, 0);
	fn_801491A8();
	object->SetPosition();
}

#pragma opt_common_subs off
TObjS11Cloud::TObjS11Cloud(TObject* parent)
    : TObject(parent)
    , Motion()
{
	constructCloud(this);
}

inline TObjS11Cloud::TObjS11Cloud()
    : TObject((TObject*)lbl_8042C110)
    , Motion()
{
	constructCloud(this);
}
#pragma opt_common_subs reset

struct CloudInitializer {
	u8 data[sizeof(TObjS11Cloud)];
};

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

#pragma optimization_level 2
static inline void releaseCloudModels(s32 count, s32 index)
{
	void** model;
	void* clear;
	model = cloudModels;
	clear = NULL;
	while (index < count) {
		fn_80150958(*model);
		*model = clear;
		model++;
		index++;
	}
}
#pragma optimization_level reset

void CloudThunk::EditOnChange(SETDATA_PARAM* frame)
{
	u8* params = frame->params;
	s32 count  = *(s32*)((u8*)&lbl_8029C310 + 0x2C) == 0x15 ? 3 : 6;
	s32* model = (s32*)params;
	if (*model < 0)
		*model = 0;
	else if (*model >= count)
		*model = count - 1;
	s8* direction = (s8*)(params + 8);
	if (*direction < 0)
		*direction = 0;
	if (*direction > 1)
		*direction = 1;
	extern char* cloudDirectionDescriptions[2];
	extern char* cloudFieldNames[3];
	cloudFieldNames[2] = cloudDirectionDescriptions[*direction];
}

#pragma opt_common_subs off
#pragma opt_propagation off
extern "C" void endObjS11Cloud()
{
	s32 count = *(s32*)((u8*)&lbl_8029C310 + 0x2C) == 0x15 ? 3 : 6;
	releaseCloudModels(count, 0);
	fn_8011B7CC(cloudUvResource);
	cloudUvResource = NULL;
}
#pragma opt_propagation reset
#pragma opt_common_subs reset

extern "C" char* cloudModelNames[6];
extern "C" char cloudUvName[];

static inline void loadCloudModels(
    s32 count, s32 index, void** archiveRoot, void* context, void* uvState)
{
	void** model;
	char** name;
	name  = cloudModelNames;
	model = cloudModels;
	while (index < count) {
		void* archive = *(void**)((u8*)*archiveRoot + 0xA50);
		s32 id        = fn_800BC6CC(archive, *name);
		archive       = *(void**)((u8*)*archiveRoot + 0xA50);
		*model        = fn_800BB92C(archive, id, context);
		void* result  = fn_8005E394(*model, 0);
		fn_8005C014(result, uvState);
		name++;
		model++;
		index++;
	}
}

#pragma opt_common_subs off
extern "C" void initObjS11Cloud()
{
	void* stage = *(void**)((u8*)lbl_8042C1D0 + 0x8C18);
	if (!(stage != NULL && (fn_801A4C84(stage), true)))
		return;

	void* archive = *(void**)((u8*)lbl_8042C298 + 0xA50);
	fn_800BC9F4(archive, &lbl_802FF5A0);
	archive               = *(void**)((u8*)lbl_8042C298 + 0xA50);
	s32 id                = fn_800BC6CC(archive, cloudUvName);
	archive               = *(void**)((u8*)lbl_8042C298 + 0xA50);
	cloudUvResource       = fn_800BAE0C(archive, id, &lbl_802FF5A0);
	*(void**)cloudUvState = cloudUvResource;

	s32 count = *(s32*)((u8*)&lbl_8029C310 + 0x2C) == 0x15 ? 3 : 6;
	loadCloudModels(count, 0, (void**)&lbl_8042C298, &lbl_802FF5A0, cloudUvState);
}
#pragma opt_common_subs reset

#pragma optimization_level 2
#pragma opt_common_subs off
#pragma opt_propagation off
extern "C" void startObjS11Cloud()
{
	new (lbl_8042C148) TObjS11Cloud();
}
#pragma opt_propagation reset
#pragma opt_common_subs reset
#pragma optimization_level reset

extern "C" {
void* cloudUvResource;
u8 cloudUvState[0x44];
SETOBJ_PARAM ObjS11CloudParam;
s32 cloudLastFrame;
}

extern "C" void __sinit_o_s11_cloud_cpp()
{
	ObjS11CloudParam.flags       = 0;
	ObjS11CloudParam.field18     = 0;
	ObjS11CloudParam.displayName = cloudDisplayName;
	ObjS11CloudParam.init        = initObjS11Cloud;
	ObjS11CloudParam.end         = endObjS11Cloud;
	ObjS11CloudParam.create      = startObjS11Cloud;
	ObjS11CloudParam.field10     = 0;
	ObjS11CloudParam.flags       = 0x20000;
	ObjS11CloudParam.field18     = 0;
	ObjS11CloudParam.field20     = 0x1E;
	ObjS11CloudParam.id          = 0x1184;
	ObjS11CloudParam.count       = 2;
	ObjS11CloudParam.field21     = 0;
	ObjS11CloudParam.fieldTypes  = cloudFieldTypes;
	ObjS11CloudParam.fields      = cloudFieldNames;
	if (ObjS11CloudParam.fieldTypes != NULL)
		ObjS11CloudParam.flags |= 8;
	else
		ObjS11CloudParam.flags &= ~8;
}

#pragma push
#pragma section const_type ".cloudtail"                                                            \
                           ".cloudtail"
extern "C" const u32 cloudConstantTail[3] = {
	0,
	0x3FC00000,
	0,
};
#pragma pop
extern "C" void* cloudModels[6]     = { NULL, NULL, NULL, NULL, NULL, NULL };
extern "C" char cloudModelName1[20] = "s11_k_cloud1.dff";
extern "C" char cloudModelName2[20] = "s11_k_cloud2.dff";
extern "C" char cloudModelName3[20] = "s11_k_cloud3.dff";
extern "C" char cloudModelName4[20] = "s11_k_cloud4.dff";
extern "C" char cloudModelName5[20] = "s11_k_cloud5.dff";
extern "C" char cloudModelName6[20] = "s11_k_cloud6.dff";
extern "C" char* cloudModelNames[6] = {
	cloudModelName1,
	cloudModelName2,
	cloudModelName3,
	cloudModelName4,
	cloudModelName5,
	cloudModelName6,
};
extern "C" char cloudModelFieldName[12]    = "model no.";
extern "C" char cloudSpeedFieldName[16]    = "speed(def:1.0)";
extern "C" char cloudDirectionUp[16]       = "direction : up";
extern "C" char* cloudFieldNamesStorage[3] = {
	cloudModelFieldName,
	cloudSpeedFieldName,
	cloudDirectionUp,
};
extern "C" char cloudDirectionDown[20]         = "direction : down";
extern "C" char* cloudDirectionDescriptions[2] = {
	cloudDirectionUp,
	cloudDirectionDown,
};
extern "C" char cloudClassName[16] = "TObjS11Cloud";
extern "C" char* CL_TObjS11Cloud   = cloudClassName;
extern "C" void* cloudVtable[15]   = {
	NULL,
	NULL,
	(void*)__dt__12TObjS11CloudFv,
	(void*)Exec__12TObjS11CloudFv,
	(void*)Disp__12TObjS11CloudFv,
	(void*)objDefaultTDisp,
	(void*)PDisp__7TObjectFv,
	(void*)ImmAftSetRaster__7TObjectFv,
	(void*)Debug__7TObjectFv,
	(void*)Error__7TObjectFPc,
	(void*)Render__7TObjectFv,
	NULL,
	NULL,
	(void*)AdjustorEditOnChange__12TObjS11CloudFP13SETDATA_PARAM,
	(void*)EditOnChange__12TObjS11CloudFP13SETDATA_PARAM,
};
extern "C" char cloudUvName[]             = "s11_k_cloud.uvb";
extern "C" char cloudDisplayNameStorage[] = "S11CLOUD OBJECT";
extern "C" char cloudFieldTypesStorage[]  = "ifc";

__declspec(section ".ctors") void (*const CloudCtorEntry)() = __sinit_o_s11_cloud_cpp;
