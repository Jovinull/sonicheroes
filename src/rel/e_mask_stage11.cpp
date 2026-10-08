#include "types.h"

// Retained PS2 symbols name this object TObjMask and give its method family:
// DestroyClump, CloneClump, SetParameter, Exec, SetPosition, the destructor,
// the TObject* constructor, EditOnChange and the initObj/endObj/startObj
// lifecycle functions. The same PS2 range holds the RenderWare helpers
// SetHierarchyForSkinAtomic, GetHierarchy and GetChildFrameHierarchy, which
// the GameCube unit emits between the constructor and EditOnChange. Other
// Stage 11 units carry their own copies, so they are file-static; the module's
// link script keeps this object whole (FORCEFILES) so the inlined, otherwise
// unreferenced GetHierarchy copy survives as it does in retail. The
// "TObjMask" class-name string in this unit's .data correlates the GameCube
// object with that family.
//
// Exec inlines SetPosition and CloneClump inlines GetHierarchy although
// retail emits both after their callers; like the Stage 11 key unit this one
// is built with deferred inlining, which emits in reverse definition order, so
// the source runs from the registration function back to DestroyClump. The
// same mode places the compiler's vtable after the named data and ahead of
// the string literals, where retail has it.

struct Vec3 {
	f32 x;
	f32 y;
	f32 z;
};

struct MaskParam {
	s32 type;
	f32 scale;
	f32 speed;
	s8 direction;
};

struct SETDATA_PARAM {
	Vec3 position;
	s32 angleX;
	s32 angleY;
	s32 angleZ;
	u32 flags;
	u8 pad1C[0x10];
	MaskParam* params;
};

/* The collision shape description handed to the collision setup call. */
struct CollisionDesc {
	u32 flags;
	u32 kind;
	f32 f08;
	f32 f0C;
	f32 f10;
	f32 f14;
	f32 f18;
	f32 f1C;
	f32 f20;
	s32 f24;
	s32 f28;
	s32 f2C;
};

struct CollisionShape {
	u8 pad00[8];
	f32 f08;
	u8 pad0C[8];
	f32 f14;
	f32 f18;
};

struct MaskCollision {
	u8 pad00[0x10];
	CollisionShape* shape;
	u8 pad14[0x74];
};

struct RpClump;
struct RpAtomic;
struct RwMatrix {
	u8 data[0x40];
};
struct RwFrame {
	u8 pad00[0x10];
	RwMatrix modelling;
};
struct RtAnimAnimation {
	u8 pad00[0xC];
	f32 duration;
};
struct RtAnimInterpolator {
	RtAnimAnimation* animation;
};
struct RpHAnimHierarchy {
	u32 flags;
	u8 pad04[0x1C];
	RtAnimInterpolator* interpolator;
};

struct GameState {
	u8 pad00[0x30];
	s32 frame;
};

struct TObjectHdr {
	const char* className;
	u16 signal;
	u8 pad06[0x12];
};

class TObject : public TObjectHdr
{
public:
	virtual ~TObject();
	virtual void Exec();
	virtual void Disp();
	virtual void TDisp();
	virtual void PDisp();
	virtual void ImmAftSetRaster();
	virtual void Debug();
	virtual void Error(char*);
	virtual void Render();

	s16 pad1C;
	s16 objectSize;
	u8 pad20[8];
};

struct SetObjHdr {
	SETDATA_PARAM* frame;
};

extern "C" {
s32 CheckMustKill__10TObjSetObjFv(void*);
s32 OnEdit__10TObjSetObjFv(void*);
s32 CheckRangeOut__10TObjSetObjFv(void*);
void __ct__10TObjSetObjFv(void*);
}

class TObjSetObj : public SetObjHdr
{
public:
	virtual void EditOnChange(SETDATA_PARAM*);

	s32 CheckRangeOut() { return CheckRangeOut__10TObjSetObjFv(this); }
	s32 CheckMustKill() { return CheckMustKill__10TObjSetObjFv(this); }
	s32 OnEdit() { return OnEdit__10TObjSetObjFv(this); }
};

extern "C" {
extern void* lbl_8042C110;
extern void* lbl_8042C148;
extern GameState* lbl_8042C180;
extern void* lbl_8042C1D0;
extern void* lbl_8042C298;
extern void* lbl_8042C388;
extern u8 AxisY;
extern u8 AxisZ;
extern u8 lbl_802FF5A0;

void __ct__7TObjectFP7TObject(void*, void*);
void __dt__7TObjectFv(void*, s16);
void __dt__7C_COLLIFv(void*, s16);
void __dt__10TObjSetObjFv(void*, s16);
void* Malloc__9THeapCtrlFUi(void*, u32);
void Free__9THeapCtrlFPv(void*, void*);
void CalcRange__7C_COLLIFv(MaskCollision*, CollisionShape*, CollisionDesc*, f32);
void __ct__7C_COLLIFv(void*);
void objRpClumpForAllAtomicsToSetRenderCallbackToUseLight__FP7RpClumpUi(RpClump*, u32);
void fn_800B4A38(void*, s32, Vec3*, s32, s32, s32, s32);
void* LoadHAnimationEx__7ONEFILEFUiPc(void*, s32, void*);
void* LoadClumpEx__7ONEFILEFUiPc(void*, s32, void*);
s32 CheckFileID__7ONEFILEFPc(void*, const char*);
void LoadOneFile__7ONEFILEFPc(void*, void*);
f32 fn_800D7AE4(s32);
f32 fn_800D7B00(s32);
void fn_8013F3A4(RpHAnimHierarchy*);
RpHAnimHierarchy* fn_8013F484(RwFrame*);
void fn_8013FC30(RpHAnimHierarchy*);
void fn_8014FFBC(RpClump*, RpAtomic* (*)(RpAtomic*, void*), void*);
RpClump* fn_80150588(void*);
void fn_80150958(void*);
void fn_8015BB08(void*, RpClump*);
void fn_8015BBF8(void*, RpClump*);
void fn_80195790(void*, void*, f32, f32, s32);
void fn_8019E880(RwFrame*);
void fn_8019EB10(RwFrame*, RwFrame* (*)(RwFrame*, void*), void*);
void fn_8019EB94(RwFrame*, Vec3*, s32);
void fn_8019EC30(RwFrame*, Vec3*, s32);
void fn_801A4C84(void*);
void fn_8020C2D8(void*);
void fn_8020C72C(RtAnimInterpolator*, void*);
void fn_8020CC18(RtAnimInterpolator*, f32);
void fn_8020D02C(RtAnimInterpolator*, f32);
void fn_80226440(RpAtomic*, void*);
u32 fn_80226468(void*);
}

static RpAtomic* SetHierarchyForSkinAtomic(RpAtomic*, void*);
static RpHAnimHierarchy* GetHierarchy(RpClump*);
static RwFrame* GetChildFrameHierarchy(RwFrame*, void*);

class TObjMask : public TObject, public TObjSetObj
{
public:
	MaskCollision collision;
	Vec3 position;
	s32 angleX;
	s32 angleY;
	s32 angleZ;
	f32 speed;
	f32 scale;
	s32 direction;
	s32 type;
	RpClump* model;
	RpHAnimHierarchy* hierarchy;

	void DestroyClump();
	void CloneClump();
	void SetCollision();
	void SetParameter();
	virtual void Exec();
	void SetPosition();
	inline virtual ~TObjMask();
	virtual void EditOnChange(SETDATA_PARAM*);
};

// The constructor and destructor are written against the object's storage:
// retail constructs and destroys the TObjSetObj base through out-of-line
// functions that keep their address names, which a C++ base-class call would
// rename. The compiler still generates the class vtable and its adjustor
// thunk from the virtual declarations above.
extern "C" {
TObjMask* __ct__8TObjMaskFP7TObject(TObjMask*, TObject*);
TObjMask* __dt__8TObjMaskFv(TObjMask*, s16);
extern void* __vt__8TObjMask[];
}

#define MOTION(self) ((void*)((u8*)(self) + 0x28))

// The model, animation and data names below are descriptive guesses.
extern "C" {
u8 maskSoundVolume      = 0x20;
void* maskModels[2]     = { NULL, NULL };
void* maskAnimations[2] = { NULL, NULL };
char* maskObjectFieldNames[4]
    = { "type", "scale(def:1.0)", "animation speed(def:1.0)", "direction : up" };
char* maskDirectionNames[2] = { "direction : up", "direction : down" };
CollisionDesc maskCollisionDesc
    = { 0x3FFE3, 0x402, 95.0f, 0.0f, 0.0f, 70.0f, 10.0f, 0.0f, 0.0f, 0x4000, 0, 0 };
char* CL_TObjMask = "TObjMask";
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
SETOBJ_PARAM maskObjectEntry;
void endObjMask();
void initObjMask();
void startObjMask();
}

extern "C" void maskObjectRegister()
{
	maskObjectEntry.flags       = 0;
	maskObjectEntry.field18     = 0;
	maskObjectEntry.displayName = "MASK OBJECT";
	maskObjectEntry.init        = initObjMask;
	maskObjectEntry.end         = endObjMask;
	maskObjectEntry.create      = startObjMask;
	maskObjectEntry.field10     = 0;
	maskObjectEntry.flags       = 0x20000;
	maskObjectEntry.field18     = 0;
	maskObjectEntry.field20     = 0x1E;
	maskObjectEntry.id          = 0x118D;
	maskObjectEntry.count       = 2;
	maskObjectEntry.field21     = 0;
	maskObjectEntry.fieldTypes  = "iFFc";
	maskObjectEntry.fields      = maskObjectFieldNames;
	if (maskObjectEntry.fieldTypes != NULL)
		maskObjectEntry.flags |= 8;
	else
		maskObjectEntry.flags &= ~8;
}

__declspec(section ".ctors") void (*const maskObjectCtorEntry)() = maskObjectRegister;

extern "C" void startObjMask()
{
	TObjMask* object = (TObjMask*)Malloc__9THeapCtrlFUi(lbl_8042C148, sizeof(TObjMask));
	if (object != NULL) {
		__ct__8TObjMaskFP7TObject(object, (TObject*)lbl_8042C110);
	}
}

extern "C" void initObjMask()
{
	void* stage = *(void**)((u8*)lbl_8042C1D0 + 0x8C18);
	if (!(stage != NULL && (fn_801A4C84(stage), 1)))
		return;

	void* archive = *(void**)((u8*)lbl_8042C298 + 0xA50);
	LoadOneFile__7ONEFILEFPc(archive, &lbl_802FF5A0);
	maskModels[0] = LoadClumpEx__7ONEFILEFUiPc(
	    archive, CheckFileID__7ONEFILEFPc(archive, "s11_on_maska.dff"), &lbl_802FF5A0);
	maskModels[1] = LoadClumpEx__7ONEFILEFUiPc(
	    archive, CheckFileID__7ONEFILEFPc(archive, "s11_on_maskb.dff"), &lbl_802FF5A0);
	maskAnimations[0] = LoadHAnimationEx__7ONEFILEFUiPc(
	    archive, CheckFileID__7ONEFILEFPc(archive, "s11_on_maska.anm"), &lbl_802FF5A0);
	maskAnimations[1] = LoadHAnimationEx__7ONEFILEFUiPc(
	    archive, CheckFileID__7ONEFILEFPc(archive, "s11_on_maskb.anm"), &lbl_802FF5A0);
}

// Retail builds both induction pointers straight into their registers here,
// which this unit only reproduces with propagation enabled for the function.
#pragma opt_propagation on
extern "C" void endObjMask()
{
	s32 i;
	for (i = 0; i < 2; i++) {
		if (maskModels[i] != NULL) {
			fn_80150958(maskModels[i]);
			maskModels[i] = NULL;
		}
		if (maskAnimations[i] != NULL) {
			fn_8020C2D8(maskAnimations[i]);
			maskAnimations[i] = NULL;
		}
	}
}
#pragma opt_propagation reset

void TObjMask::EditOnChange(SETDATA_PARAM* data)
{
	MaskParam* params = data->params;
	if (params->type < 0)
		params->type = 0;
	if (params->type > 1)
		params->type = 1;
	if (params->direction < 0)
		params->direction = 0;
	if (params->direction > 1)
		params->direction = 1;
	maskObjectFieldNames[3] = maskDirectionNames[params->direction];
}

static RwFrame* GetChildFrameHierarchy(RwFrame* frame, void* data)
{
	RpHAnimHierarchy* hierarchy = fn_8013F484(frame);
	if (hierarchy == NULL) {
		fn_8019EB10(frame, GetChildFrameHierarchy, data);
		return frame;
	}
	*(RpHAnimHierarchy**)data = hierarchy;
	return NULL;
}

static RpHAnimHierarchy* GetHierarchy(RpClump* clump)
{
	RpHAnimHierarchy* hierarchy = NULL;
	hierarchy                   = fn_8013F484(*(RwFrame**)((u8*)clump + 4));
	if (hierarchy == NULL) {
		fn_8019EB10(*(RwFrame**)((u8*)clump + 4), GetChildFrameHierarchy, &hierarchy);
	}
	return hierarchy;
}

static RpAtomic* SetHierarchyForSkinAtomic(RpAtomic* atomic, void* data)
{
	if (fn_80226468(*(void**)((u8*)atomic + 0x18)) != 0) {
		fn_80226440(atomic, data);
	}
	return atomic;
}

extern "C" TObjMask* __ct__8TObjMaskFP7TObject(TObjMask* self, TObject* parent)
{
	__ct__7TObjectFP7TObject(self, parent);
	__ct__10TObjSetObjFv(MOTION(self));
	__ct__7C_COLLIFv(&self->collision);
	*(void***)((u8*)self + 0x18) = __vt__8TObjMask;
	*(void***)((u8*)self + 0x2C) = __vt__8TObjMask + 11;
	self->className              = CL_TObjMask;
	self->objectSize             = sizeof(TObjMask);
	self->SetParameter();
	self->model = NULL;
	// Written out rather than calling CloneClump(): retail's constructor reads the
	// frame flags before reloading the model, the reverse of the method's order.
	if (self->model == NULL) {
		self->model = fn_80150588(maskModels[self->type]);
		if (self->model != NULL) {
			fn_8015BB08(*(void**)((u8*)lbl_8042C1D0 + 0x725C), self->model);
			u32 flags = self->frame->flags;
			objRpClumpForAllAtomicsToSetRenderCallbackToUseLight__FP7RpClumpUi(
			    self->model, ((flags & 0x1C0000) >> 18) + 4);
			self->hierarchy = GetHierarchy(self->model);
			fn_8014FFBC(self->model, SetHierarchyForSkinAtomic, self->hierarchy);
			self->hierarchy->flags |= 0x3000;
			fn_8020C72C(self->hierarchy->interpolator, maskAnimations[self->type]);
			fn_8013F3A4(self->hierarchy);
			fn_8013FC30(self->hierarchy);
			fn_8020D02C(self->hierarchy->interpolator, 0.0f);
			fn_8020CC18(self->hierarchy->interpolator, 0.0f);
		}
	}
	self->SetPosition();
	self->OnEdit();
	return self;
}

extern "C" TObjMask* __dt__8TObjMaskFv(TObjMask* self, s16 flags)
{
	if (self != NULL) {
		*(void***)((u8*)self + 0x18) = __vt__8TObjMask;
		*(void***)((u8*)self + 0x2C) = __vt__8TObjMask + 11;
		self->DestroyClump();
		__dt__7C_COLLIFv(&self->collision, 0);
		__dt__10TObjSetObjFv(MOTION(self), 0);
		__dt__7TObjectFv(self, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, self);
		}
	}
	return self;
}

void TObjMask::SetPosition()
{
	if (model != NULL) {
		Vec3 size;
		size.x = size.y = size.z = scale;
		RwFrame* frame           = *(RwFrame**)((u8*)model + 4);
		fn_8019EB94(frame, &position, 0);
		f32 sine = fn_800D7B00(angleY);
		fn_80195790(&frame->modelling, &AxisY, 1.0f - fn_800D7AE4(angleY), sine, 1);
		fn_8019E880(frame);
		if (direction == 1) {
			sine = fn_800D7B00(0x4000);
			fn_80195790(&frame->modelling, &AxisZ, 1.0f - fn_800D7AE4(0x4000), sine, 1);
			fn_8019E880(frame);
		} else {
			sine = fn_800D7B00(-0x4000);
			fn_80195790(&frame->modelling, &AxisZ, 1.0f - fn_800D7AE4(-0x4000), sine, 1);
			fn_8019E880(frame);
		}
		fn_8019EC30(frame, &size, 1);
	}
}

void TObjMask::Exec()
{
	if (CheckRangeOut() != 0 || CheckMustKill() != 0) {
		signal |= 1;
		return;
	}
	f32 duration = 60.0f * hierarchy->interpolator->animation->duration;
	f32 frames   = speed * (f32)lbl_8042C180->frame;
	f32 time     = frames - duration * (f32)(s32)(frames / duration);
	fn_8020D02C(hierarchy->interpolator, time / 60.0f);
	fn_8013FC30(hierarchy);
	if (OnEdit() != 0) {
		s32 oldType = type;
		SetParameter();
		if (type != oldType) {
			DestroyClump();
			CloneClump();
		}
		SetPosition();
	} else {
		if (time < duration && duration <= 1.0f + time && lbl_8042C388 != NULL) {
			fn_800B4A38(lbl_8042C388, 0x5A18, &position, 0, 1, (s8)maskSoundVolume, 0);
		}
		duration *= 0.5;
		if (time < duration && duration <= 1.0f + time && lbl_8042C388 != NULL) {
			fn_800B4A38(lbl_8042C388, 0x5A19, &position, 0, 1, (s8)maskSoundVolume, 0);
		}
	}
}

void TObjMask::SetParameter()
{
	SETDATA_PARAM* data = frame;
	MaskParam* params   = data->params;
	position            = data->position;
	data                = frame;
	angleX              = data->angleX;
	angleY              = data->angleY;
	angleZ              = data->angleZ;
	angleZ              = 0;
	angleX              = 0;
	direction           = params->direction;
	scale               = 1.0f + params->scale;
	speed               = 1.0f + params->speed;
	type                = params->type;
}

// Guessed name: nothing in the unit calls it, and the PS2 family has no
// counterpart. It scales the collision shape by the object's scale.
void TObjMask::SetCollision()
{
	if (direction == 1) {
		collision.shape->f08 = -maskCollisionDesc.f0C * scale;
	} else {
		collision.shape->f08 = maskCollisionDesc.f0C * scale;
	}
	collision.shape->f14  = maskCollisionDesc.f14 * scale;
	f32 depth             = maskCollisionDesc.f18;
	f32 scaled            = depth * scale;
	CollisionShape* shape = collision.shape;
	shape->f18            = scaled;
	CalcRange__7C_COLLIFv(&collision, shape, &maskCollisionDesc, depth);
}

void TObjMask::CloneClump()
{
	if (model == NULL) {
		model = fn_80150588(maskModels[type]);
		if (model != NULL) {
			fn_8015BB08(*(void**)((u8*)lbl_8042C1D0 + 0x725C), model);
			objRpClumpForAllAtomicsToSetRenderCallbackToUseLight__FP7RpClumpUi(
			    model, ((frame->flags & 0x1C0000) >> 18) + 4);
			hierarchy = GetHierarchy(model);
			fn_8014FFBC(model, SetHierarchyForSkinAtomic, hierarchy);
			hierarchy->flags |= 0x3000;
			fn_8020C72C(hierarchy->interpolator, maskAnimations[type]);
			fn_8013F3A4(hierarchy);
			fn_8013FC30(hierarchy);
			fn_8020D02C(hierarchy->interpolator, 0.0f);
			fn_8020CC18(hierarchy->interpolator, 0.0f);
		}
	}
}

void TObjMask::DestroyClump()
{
	if (model != NULL) {
		fn_8015BBF8(*(void**)((u8*)lbl_8042C1D0 + 0x725C), model);
		fn_80150958(model);
		model = NULL;
	}
}
