#include "types.h"

struct RpAtomic {
	u8 pad00[0x48];
	void* renderCallback;
};

struct Vec3 {
	f32 x, y, z;
};

struct TransformConstants {
	Vec3 zero;
	f32 values[9];
};

struct FlagRenderFrame {
	Vec3* position;
	s32* anglesXZ;
	s32* angleY;
	f32* animationFrame;
	f32* scale;
};

struct FlagMotion {
	FlagRenderFrame* frame;
};

struct ObjectFrame {
	Vec3 position;
	s32 angleX;
	s32 angleY;
	s32 angleZ;
	u8 pad18[0x14];
	void* params;
};

struct TObject;

struct FlagObject {
	u8 pad00[0x18];
	void** vtable;
	u8 pad1C[0x0C];
	ObjectFrame* frame;
	void** motionVtable;
	u8 pad30[0x8C];
	void* modelBC;
	void* modelC0;
	void* modelC4;
	u8 padC8[4];
	void* allocatedCC;
};

struct FlagFrame {
	u8 pad00[0x2C];
	void* params;
};

struct FlagThunkPrimary {
	u8 pad04[0x24];
	virtual void PrimarySlot();
};

struct FlagThunkSecondary {
	virtual void EditOnChange(FlagFrame*);
};

struct FlagThunk : FlagThunkPrimary, FlagThunkSecondary {
	virtual void EditOnChange(FlagFrame*);
};

struct FlagParams {
	s8 type;
	u8 pad01[3];
	s32 angle;
	f32 scale;
};

struct ObjectEntry {
	const char* name;
	void (*load)();
	void (*unload)();
	void (*create)();
	void (*reset)(void*);
	u32 flags;
	u32 unk18;
	s16 id;
	s16 count;
	u8 category;
	u8 unk21;
	u8 pad22[2];
	const char* fieldTypes;
	const char** fieldNames;
	u32 pad2C;
};

extern "C" RpAtomic* flagRenderCallback(RpAtomic*);
extern "C" void flagDisp();
extern "C" void flagExec(FlagObject*);
extern "C" FlagObject* flagDtor(FlagObject*, s16);
extern "C" void EditOnChange__9FlagThunkFP9FlagFrame(FlagThunk*, FlagFrame*);
extern "C" void AdjustorEditOnChange__9FlagThunkFP9FlagFrame(FlagThunk*, FlagFrame*);
extern "C" void fn_8014F1B0();
extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_8042C340[];
extern "C" u8 lbl_8029C310[];
extern "C" u8 lbl_802FF5A0[];
extern "C" void* flagModels[8];
extern "C" void* flagResources[3];
extern "C" void* flagSecondaryModel;
extern "C" void* flagPrimaryModel;
extern "C" void* flagAnimation;
extern "C" void* flagSavedRenderCallback;
extern "C" f32 flagUnknownFloat;
extern "C" s32 flagAnimationState;
extern "C" s32 flagPositionInitialized;
extern "C" Vec3 flagZeroVector;
extern "C" TransformConstants flagTransformZeroConstants;
extern "C" f32 flagAngleFactor;
extern "C" f32 flagAnimationStep;
extern "C" f32 flagZeroScale;
extern "C" f32 flagOneScale;
extern "C" char flagDisplayName[];
extern "C" char flagFieldTypes[];
extern "C" const char* flagFieldNames[3];
extern "C" const char* flagTypeNames[12];
extern "C" const f32 flagMinScale;
extern "C" const char* flagAssetNames[8];
extern "C" char flagAssetFormat[];
extern "C" char flagModelFormat[];
extern "C" char flagAnimationFormat[];
extern "C" const char* flagClassName;
extern "C" u32 flagCollisionConfig[];
extern "C" void* flagCallbackContext;
extern "C" ObjectEntry flagEntry;
extern "C" void* flagVtable[15];
extern "C" void* fn_80018A34(void*, u32);
extern "C" FlagObject* flagCtor(FlagObject*, TObject*);
extern "C" void fn_80150958(void*);
extern "C" void* fn_80150588(void*);
extern "C" void fn_8015BB08(void*, void*);
extern "C" void* fn_8015BD78(void*);
extern "C" void fn_8015BBF8(void*, void*);
extern "C" void fn_8013BD74(void*);
extern "C" void flagInit();
extern "C" void __dl__FPv(void*);
extern "C" void dtor_8003C52C(void*, s32);
extern "C" void dtor_8005BD3C(void*, s32);
extern "C" void __dt__7TObjectFv(void*, s32);
extern "C" void fn_800189A4(void*, void*);
extern "C" const char* fn_800194C4(void*);
extern "C" void fn_801A4C84(void*);
extern "C" void fn_800BC9F4(void*, void*);
extern "C" void* fn_800BC6CC(void*, const char*);
extern "C" void* fn_800BB92C(void*, void*, void*);
extern "C" void* fn_800BB39C(void*, void*, void*);
extern "C" void fn_8014FFBC(void*, void*, void*);
extern "C" f32 GetTotalFrame__10DAnimClassFP17RpDMorphAnimation(void*, void*);
extern "C" s32 sprintf(char*, const char*, ...);
extern "C" FlagMotion* fn_8005F4E8();
extern "C" void fn_8019EC30(void*, const Vec3*, s32);
extern "C" void fn_8019ED68(void*, const Vec3*, f32, s32);
extern "C" void fn_8019EB94(void*, const Vec3*, s32);
extern "C" Vec3 lbl_80239978;
extern "C" Vec3 lbl_80239984;
extern "C" Vec3 lbl_80239990;
extern "C" void fn_8013D344(void*, void*);
extern "C" void fn_8013D5C8(void*, f32);
extern "C" void __ct__7TObjectFP7TObject(void*, TObject*);
extern "C" void fn_8005BE6C(void*);
extern "C" void fn_8003C618(void*);
extern "C" void* fn_8005E394(void*, s32);
extern "C" void fn_8014F854(void*);
extern "C" void* fn_80057644(u32);
extern "C" void fn_8005F50C(void*, void*, s32);
extern "C" void fn_8003C200(void*, void*, s32, s32);
extern "C" s32 fn_8005B9F0(void*);
extern "C" s32 fn_8005B8BC(void*);
extern "C" s32 fn_8005B8D8(void*);
extern "C" void fn_8003BC38(void*);
extern "C" void* lbl_8042C180;
extern "C" void objDefaultTDisp();
extern "C" void objDefaultPDisp();
extern "C" void objDefaultImmAftSetRaster();
extern "C" void objDefaultDebug();
extern "C" void fn_80017854();
extern "C" void objDefaultRender();

extern "C" {
__declspec(section ".rodata") TransformConstants flagTransformZeroConstants
    = { { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f } };
__declspec(section ".rodata") Vec3 flagZeroVector   = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") f32 flagAngleFactor   = 0.0054931640625f;
__declspec(section ".rodata") f32 flagAnimationStep = 0.02f;
__declspec(section ".rodata") f32 flagZeroScale     = 0.0f;
__declspec(section ".rodata") f32 flagOneScale      = 1.0f;
__declspec(section ".rodata") f32 flagCollisionConstants[10]
    = { 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f };

void* flagModels[8]           = { };
char flagAssetName0[16]       = "on_hata1_1.dff";
char flagAssetName1[16]       = "on_hata1_2.dff";
char flagAssetName2[16]       = "on_hata1_3.dff";
char flagAssetName3[16]       = "on_hata1_4.dff";
char flagAssetName4[16]       = "on_hata2_1.dff";
char flagAssetName5[16]       = "on_hata2_2.dff";
char flagAssetName6[16]       = "on_hata2_3.dff";
char flagAssetName7[16]       = "on_hata2_4.dff";
const char* flagAssetNames[8] = { flagAssetName0, flagAssetName1, flagAssetName2, flagAssetName3,
	flagAssetName4, flagAssetName5, flagAssetName6, flagAssetName7 };
char flagFieldName0[8]        = "Type   ";
char flagFieldName1[12]       = "Flag Angle";
char flagFieldName2[8]        = "SCALE";
const char* flagFieldNames[3] = { flagFieldName0, flagFieldName1, flagFieldName2 };
char flagTypeName0[8]         = "TYPE1 1";
char flagTypeName1[8]         = "TYPE1 2";
char flagTypeName2[8]         = "TYPE1 3";
char flagTypeName3[8]         = "TYPE1 4";
char flagTypeName4[8]         = "TYPE2 1";
char flagTypeName5[8]         = "TYPE2 2";
char flagTypeName6[8]         = "TYPE2 3";
char flagTypeName7[8]         = "TYPE2 4";
char flagTypeName8[16]        = "TYPE1 1NFLAG";
char flagTypeName9[16]        = "TYPE1 2NFLAG";
char flagTypeName10[16]       = "TYPE1 3NFLAG";
char flagTypeName11[16]       = "TYPE1 4NFLAG";
const char* flagTypeNames[12] = { flagTypeName0, flagTypeName1, flagTypeName2, flagTypeName3,
	flagTypeName4, flagTypeName5, flagTypeName6, flagTypeName7, flagTypeName8, flagTypeName9,
	flagTypeName10, flagTypeName11 };
u32 flagCollisionConfig[36]   = { 0x0001FF0C, 0x00000008, 0x00000000, 0x42960000, 0x00000000,
	0x41100000, 0x42960000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x0000FF0C,
	0x00000008, 0x00000000, 0x43160000, 0x00000000, 0x41100000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x0001FF0C, 0x00000008, 0x00000000, 0xC1A00000, 0x00000000,
	0x41100000, 0x41A00000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };
char flagClassText[12]        = "TObjS01Flag";
const char* flagClassName     = flagClassText;
void* flagVtable[15]          = { NULL, NULL, (void*)flagDtor, (void*)flagExec, (void*)flagDisp,
	(void*)objDefaultTDisp, (void*)objDefaultPDisp, (void*)objDefaultImmAftSetRaster,
	(void*)objDefaultDebug, (void*)fn_80017854, (void*)objDefaultRender, NULL, NULL,
	(void*)AdjustorEditOnChange__9FlagThunkFP9FlagFrame,
	(void*)EditOnChange__9FlagThunkFP9FlagFrame };
char flagAssetFormat[8]       = "%s_%s";
char flagModelFormat[]        = "%s_pn_hata0.dff";
char flagAnimationFormat[]    = "%s_pn_hata0.dma";
char flagDisplayName[12]      = "S01 FLAG";
char flagFieldTypes[8]        = "cxF";
}

extern "C" RpAtomic* flagChangeRenderCallback(RpAtomic* atomic, RpAtomic** result)
{
	*result                = atomic;
	atomic->renderCallback = (void*)flagRenderCallback;
	if (atomic->renderCallback == NULL)
		atomic->renderCallback = (void*)fn_8014F1B0;
	return NULL;
}

extern "C" RpAtomic* flagCaptureRenderCallback(RpAtomic* atomic, RpAtomic** result)
{
	*result                 = atomic;
	flagSavedRenderCallback = atomic->renderCallback;
	return NULL;
}

extern "C" RpAtomic* flagRenderCallback(RpAtomic* atomic)
{
	FlagMotion* motion = fn_8005F4E8();
	void* model        = *(void**)((u8*)flagPrimaryModel + 4);
	Vec3 scale         = flagZeroVector;
	scale.x            = *motion->frame->scale;
	scale.y            = scale.x;
	scale.z            = scale.x;
	fn_8019EC30(model, &scale, 0);
	fn_8019ED68(model, &lbl_80239984, flagAngleFactor * (f32)*motion->frame->angleY, 2);
	fn_8019ED68(model, &lbl_80239984, flagAngleFactor * (f32)motion->frame->anglesXZ[1], 2);
	fn_8019ED68(model, &lbl_80239978, flagAngleFactor * (f32)motion->frame->anglesXZ[0], 2);
	fn_8019ED68(model, &lbl_80239990, flagAngleFactor * (f32)motion->frame->anglesXZ[2], 2);
	fn_8019EB94(model, motion->frame->position, 2);
	if (flagPositionInitialized == 0) {
		fn_8013D344(flagPrimaryModel, flagAnimation);
		fn_8013D5C8(flagPrimaryModel, *motion->frame->animationFrame);
		flagPositionInitialized = 1;
		flagAnimationState      = 0;
	}
	((void (*)(void*))flagSavedRenderCallback)(flagPrimaryModel);
	return atomic;
}

extern "C" void flagDisp() { }

static inline void setFlagPosition(FlagObject* object)
{
	FlagParams* params = (FlagParams*)object->frame->params;
	if (object->modelBC != NULL) {
		void* model      = *(void**)((u8*)object->modelBC + 4);
		const Vec3& zero = flagTransformZeroConstants.zero;
		Vec3 scale       = zero;
		scale.x          = params->scale;
		scale.y          = scale.x;
		scale.z          = scale.x;
		fn_8019EC30(model, &scale, 0);
		fn_8019ED68(model, &lbl_80239984, flagAngleFactor * (f32)object->frame->angleY, 2);
		fn_8019ED68(model, &lbl_80239978, flagAngleFactor * (f32)object->frame->angleX, 2);
		fn_8019ED68(model, &lbl_80239990, flagAngleFactor * (f32)object->frame->angleZ, 2);
		fn_8019EB94(model, &object->frame->position, 2);
		if (object->modelC0 != NULL) {
			model = *(void**)((u8*)object->modelC0 + 4);
			fn_8019EC30(model, &scale, 0);
			fn_8019EC30(model, &scale, 0);
			fn_8019ED68(model, &lbl_80239984, flagAngleFactor * (f32)params->angle, 2);
			fn_8019ED68(model, &lbl_80239984, flagAngleFactor * (f32)object->frame->angleY, 2);
			fn_8019ED68(model, &lbl_80239978, flagAngleFactor * (f32)object->frame->angleX, 2);
			fn_8019ED68(model, &lbl_80239990, flagAngleFactor * (f32)object->frame->angleZ, 2);
			fn_8019EB94(model, &object->frame->position, 2);
		}
	}
}

#pragma force_active on
extern "C" void flagSetPosition(FlagObject* object)
{
	setFlagPosition(object);
}
#pragma force_active reset

static inline void copyFlagFrame(FlagObject* object)
{
	ObjectFrame* frame           = object->frame;
	*(Vec3*)((u8*)object + 0xAC) = *(Vec3*)((u8*)object + 0x90);
	*(Vec3*)((u8*)object + 0x90) = frame->position;
	*(s32*)((u8*)object + 0x9C)  = frame->angleX;
	*(s32*)((u8*)object + 0xA0)  = frame->angleY;
	*(s32*)((u8*)object + 0xA4)  = frame->angleZ;
	fn_8003BC38((u8*)object + 0x30);
}

extern "C" void flagExec(FlagObject* object)
{
	if (fn_8005B9F0(&object->frame) || fn_8005B8BC(&object->frame)) {
		*(u16*)((u8*)object + 4) |= 1;
		return;
	}
	if (*(s8*)((u8*)lbl_8042C180 + 0x1F) != 0) {
		copyFlagFrame(object);
		return;
	}
	if (fn_8005B8D8(&object->frame))
		setFlagPosition(object);
	if (*(f32**)((u8*)object + 0xC8) != NULL && flagAnimationState == NULL) {
		**(f32**)((u8*)object + 0xC8) += flagAnimationStep;
		f32* frame = *(f32**)((u8*)object + 0xC8);
		if (*frame >= flagUnknownFloat)
			*frame -= flagUnknownFloat;
		flagAnimationState      = 1;
		flagPositionInitialized = 0;
	}
	if (fn_8005B8D8(&object->frame))
		setFlagPosition(object);
	else
		copyFlagFrame(object);
}

#pragma dont_inline on
void FlagThunk::EditOnChange(FlagFrame* frame)
{
	FlagObject* object = (FlagObject*)this;
	FlagParams* params = (FlagParams*)frame->params;
	if (params->type < 0)
		params->type = 0;
	if (params->type >= 12)
		params->type = 11;
	f32 scale        = params->scale;
	f32 minimumScale = flagZeroScale;
	if (scale < minimumScale)
		params->scale = minimumScale;
	s8 objectType = *(s8*)((u8*)object + 0xB8);
	if (objectType != params->type) {
		s8 modelIndex;
		if (params->type < 8)
			modelIndex = params->type;
		else
			modelIndex = params->type - 8;
		if (object->modelBC != NULL) {
			void* model = object->modelBC;
			fn_8015BBF8(fn_8015BD78(model), model);
			fn_80150958(object->modelBC);
			object->modelBC = NULL;
		}
		if (flagModels[modelIndex] != NULL) {
			object->modelBC = fn_80150588(flagModels[modelIndex]);
			fn_8015BB08(*(void**)(lbl_8042C1D0 + 0x7260), object->modelBC);
		}
		*(s8*)((u8*)object + 0xB8) = params->type;
	}
	flagFieldNames[0] = flagTypeNames[*(s8*)((u8*)object + 0xB8)];
}
#pragma dont_inline reset

extern "C" FlagObject* flagDtor(FlagObject* object, s16 flags)
{
	if (object != NULL) {
		object->vtable       = flagVtable;
		object->motionVtable = flagVtable + 11;
		if (object->allocatedCC != NULL)
			__dl__FPv(object->allocatedCC);
		if (object->modelC0 != NULL) {
			void* model = object->modelC0;
			fn_8015BBF8(fn_8015BD78(model), model);
			fn_80150958(object->modelC0);
			object->modelC0 = NULL;
			object->modelC4 = NULL;
		}
		if (object->modelBC != NULL) {
			void* model = object->modelBC;
			fn_8015BBF8(fn_8015BD78(model), model);
			fn_80150958(object->modelBC);
			object->modelBC = NULL;
		}
		dtor_8003C52C((u8*)object + 0x30, 0);
		dtor_8005BD3C(&object->frame, 0);
		__dt__7TObjectFv(object, 0);
		if (flags > 0)
			fn_800189A4(lbl_8042C148, object);
	}
	return object;
}

extern "C" FlagObject* flagCtor(FlagObject* object, TObject* parent)
{
	void* collision;
	__ct__7TObjectFP7TObject(object, parent);
	fn_8005BE6C(&object->frame);
	fn_8003C618(object->pad30);
	object->vtable              = flagVtable;
	object->motionVtable        = flagVtable + 11;
	FlagParams* params          = (FlagParams*)object->frame->params;
	*(const char**)object       = flagClassName;
	*(u16*)((u8*)object + 0x1E) = 0xD0;
	if (params->type >= 12 || params->type < 0)
		params->type = 0;
	*(s8*)((u8*)object + 0xB8) = params->type;
	s8 modelIndex;
	if (params->type < 8)
		modelIndex = params->type;
	else
		modelIndex = params->type - 8;
	if (flagModels[modelIndex] != NULL) {
		object->modelBC = fn_80150588(flagModels[modelIndex]);
		fn_8015BB08(*(void**)(lbl_8042C1D0 + 0x7260), object->modelBC);
	} else {
		object->modelBC = NULL;
	}
	if (*(s8*)((u8*)object + 0xB8) < 8) {
		object->modelC0 = fn_80150588(*(void**)(lbl_8042C1D0 + 0xB08));
		fn_8015BB08(*(void**)(lbl_8042C1D0 + 0x7278), object->modelC0);
		void* atomic = fn_8005E394(object->modelC0, 0);
		fn_8014FFBC(object->modelC0, (void*)flagChangeRenderCallback, &object->modelC4);
		if ((*(s32*)((u8*)flagPrimaryModel + 0x4C) & 2))
			fn_8014F854(flagPrimaryModel);
		void* primary = flagPrimaryModel;
		if ((*(s32*)((u8*)atomic + 0x4C) & 2))
			fn_8014F854(atomic);
		struct Sphere {
			Vec3 center;
			f32 radius;
		};
		*(Sphere*)((u8*)atomic + 0x1C) = *(Sphere*)((u8*)primary + 0x1C);
		*(void**)((u8*)object + 0xC8)  = &flagCallbackContext;
		object->allocatedCC            = fn_80057644(20);
		if (object->allocatedCC != NULL) {
			((void**)object->allocatedCC)[0] = object->frame;
			((void**)object->allocatedCC)[1] = (u8*)object->frame + 0xC;
			((void**)object->allocatedCC)[2] = (u8*)params + 4;
			((void**)object->allocatedCC)[3] = *(void**)((u8*)object + 0xC8);
			((void**)object->allocatedCC)[4] = (u8*)params + 8;
			fn_8005F50C(object->modelC4, &object->allocatedCC, 4);
		}
	} else {
		object->modelC0               = NULL;
		object->modelC4               = NULL;
		object->allocatedCC           = NULL;
		*(void**)((u8*)object + 0xC8) = NULL;
	}
	if (flagZeroScale == params->scale)
		params->scale = flagOneScale;
	setFlagPosition(object);
	collision = object;
	if (object != NULL)
		collision = object->pad30;
	s8 type = *(s8*)((u8*)object + 0xB8);
	if (type < 4 || type > 7)
		fn_8003C200(object->pad30, flagCollisionConfig, 3, 4);
	else
		fn_8003C200(object->pad30, flagCollisionConfig, 2, 4);
	*(u16*)((u8*)collision + 8) &= ~0x40;
	return object;
}

extern "C" void flagEnd()
{
	for (s8 i = 0; i < 8; ++i) {
		if (flagModels[i] != NULL) {
			fn_80150958(flagModels[i]);
			flagModels[i] = NULL;
		}
	}
	if (flagSecondaryModel != NULL) {
		fn_80150958(flagSecondaryModel);
		flagSecondaryModel = NULL;
		flagPrimaryModel   = NULL;
	}
	if (flagAnimation != NULL) {
		fn_8013BD74(flagAnimation);
		flagAnimation = NULL;
	}
}

extern "C" void flagInit()
{
	char modelPath[64];
	char path[64];
	s32 stageType         = *(s32*)(*(u8**)(lbl_8029C310 + 0x34) + 4);
	s32 modelCount        = 8;
	const char* stageName = fn_800194C4(lbl_8029C310);
	if (stageType == 0x10)
		modelCount = 4;
	void* resource = *(void**)(lbl_8042C1D0 + 0x8C18);
	if (resource != NULL) {
		flagResources[0] = resource;
		fn_801A4C84(resource);
	} else {
		return;
	}
	fn_800BC9F4(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	for (s32 i = 0; i < modelCount; ++i) {
		sprintf(modelPath, flagAssetFormat, stageName, flagAssetNames[i]);
		flagModels[i] = fn_800BB92C(*(void**)(lbl_8042C298 + 0xA50),
		    fn_800BC6CC(*(void**)(lbl_8042C298 + 0xA50), modelPath), lbl_802FF5A0);
	}
	sprintf(path, flagModelFormat, stageName);
	flagSecondaryModel = fn_800BB92C(*(void**)(lbl_8042C298 + 0xA50),
	    fn_800BC6CC(*(void**)(lbl_8042C298 + 0xA50), path), lbl_802FF5A0);
	fn_8014FFBC(flagSecondaryModel, (void*)flagCaptureRenderCallback, &flagPrimaryModel);
	sprintf(path, flagAnimationFormat, stageName);
	flagAnimation = fn_800BB39C(*(void**)(lbl_8042C298 + 0xA50),
	    fn_800BC6CC(*(void**)(lbl_8042C298 + 0xA50), path), lbl_802FF5A0);
	if (flagAnimation != NULL)
		flagUnknownFloat
		    = GetTotalFrame__10DAnimClassFP17RpDMorphAnimation(lbl_8042C340, flagAnimation);
}

extern "C" void flagCreate()
{
	void* object = fn_80018A34(lbl_8042C148, 0xD0);
	if (object != NULL)
		flagCtor((FlagObject*)object, (TObject*)lbl_8042C110);
}

extern "C" {
void* flagResources[3];
void* flagSecondaryModel;
void* flagPrimaryModel;
void* flagAnimation;
void* flagSavedRenderCallback;
f32 flagUnknownFloat;
void* flagCallbackContext;
s32 flagAnimationState;
s32 flagPositionInitialized;
ObjectEntry flagEntry;
}

extern "C" void __sinit_o_s01_hata_cpp()
{
	flagEntry.flags      = 0;
	flagEntry.unk18      = 0;
	flagEntry.name       = flagDisplayName;
	flagEntry.load       = flagInit;
	flagEntry.unload     = flagEnd;
	flagEntry.create     = flagCreate;
	flagEntry.reset      = NULL;
	flagEntry.flags      = 0x21000;
	flagEntry.unk18      = 0;
	flagEntry.category   = 0x14;
	flagEntry.id         = 0x181;
	flagEntry.count      = 2;
	flagEntry.unk21      = 0;
	flagEntry.fieldTypes = flagFieldTypes;
	flagEntry.fieldNames = flagFieldNames;
	if (flagEntry.fieldTypes != NULL)
		flagEntry.flags |= 8;
	else
		flagEntry.flags &= ~8;
}

__declspec(section ".ctors") void (*const flagCtorEntry)() = __sinit_o_s01_hata_cpp;
