#include "types.h"

// Retained PS2 symbols name this object TObjGrass and give its method family
// in the order the GameCube text keeps: DestroyClump, CloneClump, SetParameter,
// Exec, SetPosition, the destructor, the TObject* constructor, the
// SetHierarchyForSkinAtomic/GetHierarchy/GetChildFrameHierarchy helpers,
// EditOnChange and the endObj/initObj/startObj lifecycle functions. The
// "TObjGrass" class-name string in this unit's .data correlates the GameCube
// object with that family.
//
// Like the other Stage 11 object units this one is built with deferred
// inlining: the functions are emitted in reverse definition order, and the
// compiler-generated vtable lands after the named data and ahead of the string
// literals, where retail has it. The hierarchy helpers are file-static in
// retail; GetHierarchy is only ever inlined, but its out-of-line copy survives.

struct Vec3 {
	f32 x;
	f32 y;
	f32 z;
};

struct sAngle {
	s32 x;
	s32 y;
	s32 z;
};

struct GrassParam {
	s8 type;
	s8 direction;
	u8 pad02[2];
	f32 scale;
};

struct SETDATA_PARAM {
	Vec3 position;
	sAngle angle;
	u32 flags;
	u8 pad1C[0x10];
	GrassParam* params;
};

struct RwMatrix {
	u8 pad00[0x40];
};

struct RwFrame {
	u8 pad00[0x10];
	RwMatrix modelling;
};

struct RpAtomic;

struct RpClump {
	u8 pad00[4];
	RwFrame* frame;
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

struct CCL_INFO {
	u32 attribute;
	u32 kind;
	f32 unk08;
	f32 radius;
	f32 unk10;
	f32 height;
	f32 depth;
	u32 pad1C[5];
};

struct TObjectHdr {
	const char* className;
	u16 signal;
	u8 pad06[0x12];
};

class TObject : public TObjectHdr
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
}

class TObjSetObj : public SetObjHdr
{
public:
	TObjSetObj();
	virtual void EditOnChange(SETDATA_PARAM*);

	s32 CheckRangeOut() { return CheckRangeOut__10TObjSetObjFv(this); }
	s32 CheckMustKill() { return CheckMustKill__10TObjSetObjFv(this); }
	s32 OnEdit() { return OnEdit__10TObjSetObjFv(this); }
};

class C_COLLI
{
public:
	u8 pad00[0x10];
	CCL_INFO* shape;
	u8 pad14[0x4C];
	Vec3 position;
	sAngle angle;
	u8 pad78[4];
	Vec3 previous;

	C_COLLI();
	~C_COLLI();
	void Init(CCL_INFO*, int, u8);
	void CalcRange();
	void Entry();
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

void __dt__7TObjectFv(void*, s16);
void __dt__7C_COLLIFv(void*, s16);
void __dt__10TObjSetObjFv(void*, s16);
void* Malloc__9THeapCtrlFUi(void*, u32);
void Free__9THeapCtrlFPv(void*, void*);
void objRpClumpForAllAtomicsToSetRenderCallbackToUseLight__FP7RpClumpUi(RpClump*, u32);
void fn_800B4A38(void*, s32, Vec3*, s32, s32, s32, s32);
void* LoadHAnimationEx__7ONEFILEFUiPc(void*, s32, void*);
RpClump* LoadClumpEx__7ONEFILEFUiPc(void*, s32, void*);
s32 CheckFileID__7ONEFILEFPc(void*, const char*);
void LoadOneFile__7ONEFILEFPc(void*, void*);
f32 fn_800D7AE4(s32);
f32 fn_800D7B00(s32);
void fn_8013F3A4(RpHAnimHierarchy*);
RpHAnimHierarchy* fn_8013F484(RwFrame*);
void fn_8013FC30(RpHAnimHierarchy*);
void fn_8014FFBC(RpClump*, RpAtomic* (*)(RpAtomic*, void*), void*);
RpClump* fn_80150588(RpClump*);
void fn_80150958(RpClump*);
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

class TObjGrass : public TObject, public TObjSetObj, public C_COLLI
{
public:
	Vec3 position;
	sAngle angle;
	f32 scale;
	s32 direction;
	s32 type;
	RpClump* clumps[5];
	RpClump* edgeClumps[3];
	RpHAnimHierarchy* hierarchies[5];
	RpHAnimHierarchy* edgeHierarchies[3];

	void DestroyClump();
	void CloneClump();
	void SetParameter();
	virtual void Exec();
	void SetPosition();
	inline virtual ~TObjGrass();
	TObjGrass(TObject*);
	virtual void EditOnChange(SETDATA_PARAM*);

	static void* operator new(unsigned long size, void* heap)
	{
		return Malloc__9THeapCtrlFUi(heap, size);
	}
};

// The destructor is written against the object's storage: retail destroys the
// TObjSetObj and C_COLLI bases through out-of-line functions that keep their
// address names, which a C++ base-class call would rename. The compiler still
// generates the class vtable and its adjustor thunk from the virtual
// declarations above.
extern "C" {
TObjGrass* __dt__9TObjGrassFv(TObjGrass*, s16);
extern void* __vt__9TObjGrass[];
}

// The data names below are address names; their roles are descriptive guesses.
extern "C" {
char* lbl_8_data_18778[2][5] = {
	{ "s11_on_grassa1l.anm", "s11_on_grassa2l.anm", "s11_on_grassa3l.anm", "s11_on_grassa4l.anm",
	    "s11_on_grassa5l.anm" },
	{ "s11_on_grassa1d.anm", "s11_on_grassa2d.anm", "s11_on_grassa3d.anm", "s11_on_grassa4d.anm",
	    "s11_on_grassa5d.anm" },
};
char* lbl_8_data_18868[2][5] = {
	{ "s11_on_grassa1l.dff", "s11_on_grassa2l.dff", "s11_on_grassa3l.dff", "s11_on_grassa4l.dff",
	    "s11_on_grassa5l.dff" },
	{ "s11_on_grassa1d.dff", "s11_on_grassa2d.dff", "s11_on_grassa3d.dff", "s11_on_grassa4d.dff",
	    "s11_on_grassa5d.dff" },
};
char* lbl_8_data_18920[2][3] = {
	{ "s11_pnw_grassa1l.dff", "s11_pnw_grassa2l.dff", "s11_pnw_grassa3l.dff" },
	{ "s11_pnw_grassa1d.dff", "s11_pnw_grassa2d.dff", "s11_pnw_grassa3d.dff" },
};
#pragma explicit_zero_data on
RpClump* lbl_8_data_18938[2][5]
    = { { NULL, NULL, NULL, NULL, NULL }, { NULL, NULL, NULL, NULL, NULL } };
RpClump* lbl_8_data_18960[2][3] = { { NULL, NULL, NULL }, { NULL, NULL, NULL } };
void* lbl_8_data_18978[2][5]
    = { { NULL, NULL, NULL, NULL, NULL }, { NULL, NULL, NULL, NULL, NULL } };
#pragma explicit_zero_data reset
char* grassObjectFieldNames[3] = { "type      : light", "direction : up", "scale(def:1.0)" };
char* lbl_8_data_189F4[2]      = { "type      : light", "type      : dark" };
char* lbl_8_data_18A10[2]      = { "direction : up", "direction : down" };
CCL_INFO lbl_8_data_18A18      = { 0xFFE0, 2, 0.0f, -10.0f, 0.0f, 20.0f, 0.0f };
char* lbl_8_data_18A54         = "TObjGrass";
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
u8 lbl_8_bss_1CA8;
SETOBJ_PARAM grassObjectEntry;
void grassObjectUnload();
void grassObjectLoad();
void grassObjectCreate();
}

extern "C" void grassObjectRegister()
{
	grassObjectEntry.flags       = 0;
	grassObjectEntry.field18     = 0;
	grassObjectEntry.displayName = "GRASS OBJECT";
	grassObjectEntry.init        = grassObjectLoad;
	grassObjectEntry.end         = grassObjectUnload;
	grassObjectEntry.create      = grassObjectCreate;
	grassObjectEntry.field10     = 0;
	grassObjectEntry.flags       = 0x20000;
	grassObjectEntry.field18     = 0;
	grassObjectEntry.field20     = 0x1E;
	grassObjectEntry.id          = 0x118B;
	grassObjectEntry.count       = 2;
	grassObjectEntry.field21     = 0;
	grassObjectEntry.fieldTypes  = "ccF";
	grassObjectEntry.fields      = grassObjectFieldNames;
	if (grassObjectEntry.fieldTypes != NULL)
		grassObjectEntry.flags |= 8;
	else
		grassObjectEntry.flags &= ~8;
}

__declspec(section ".ctors") void (*const grassObjectCtorEntry)() = grassObjectRegister;

extern "C" void grassObjectCreate()
{
	new (lbl_8042C148) TObjGrass((TObject*)lbl_8042C110);
}

extern "C" void grassObjectLoad()
{
	void* stage = *(void**)((u8*)lbl_8042C1D0 + 0x8C18);
	if (stage != NULL) {
		fn_801A4C84(stage);
	} else {
		return;
	}
	int i;
	int j;
	void* archive = *(void**)((u8*)lbl_8042C298 + 0xA50);
	LoadOneFile__7ONEFILEFPc(archive, &lbl_802FF5A0);
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 5; j++) {
			lbl_8_data_18938[i][j] = LoadClumpEx__7ONEFILEFUiPc(
			    archive, CheckFileID__7ONEFILEFPc(archive, lbl_8_data_18868[i][j]), &lbl_802FF5A0);
		}
		for (j = 0; j < 3; j++) {
			lbl_8_data_18960[i][j] = LoadClumpEx__7ONEFILEFUiPc(
			    archive, CheckFileID__7ONEFILEFPc(archive, lbl_8_data_18920[i][j]), &lbl_802FF5A0);
		}
		for (j = 0; j < 5; j++) {
			lbl_8_data_18978[i][j] = LoadHAnimationEx__7ONEFILEFUiPc(
			    archive, CheckFileID__7ONEFILEFPc(archive, lbl_8_data_18778[i][j]), &lbl_802FF5A0);
		}
	}
}

extern "C" void grassObjectUnload()
{
	int j;
	for (int i = 0; i < 2; i++) {
		for (j = 0; j < 5; j++) {
			if (lbl_8_data_18938[i][j] != NULL) {
				fn_80150958(lbl_8_data_18938[i][j]);
				lbl_8_data_18938[i][j] = NULL;
			}
		}
		for (j = 0; j < 3; j++) {
			if (lbl_8_data_18960[i][j] != NULL) {
				fn_80150958(lbl_8_data_18960[i][j]);
				lbl_8_data_18960[i][j] = NULL;
			}
		}
		for (j = 0; j < 5; j++) {
			if (lbl_8_data_18978[i][j] != NULL) {
				fn_8020C2D8(lbl_8_data_18978[i][j]);
				lbl_8_data_18978[i][j] = NULL;
			}
		}
	}
}

void TObjGrass::EditOnChange(SETDATA_PARAM* data)
{
	GrassParam* params = data->params;
	if (params->type < 0)
		params->type = 0;
	if (params->type > 1)
		params->type = 1;
	if (params->direction < 0)
		params->direction = 0;
	if (params->direction > 1)
		params->direction = 1;
	grassObjectFieldNames[0] = lbl_8_data_189F4[params->type];
	grassObjectFieldNames[1] = lbl_8_data_18A10[params->direction];
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
	hierarchy                   = fn_8013F484(clump->frame);
	if (hierarchy == NULL) {
		fn_8019EB10(clump->frame, GetChildFrameHierarchy, &hierarchy);
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

TObjGrass::TObjGrass(TObject* parent)
    : TObject(parent)
{
	className  = lbl_8_data_18A54;
	objectSize = sizeof(TObjGrass);
	SetParameter();
	clumps[0]     = NULL;
	clumps[1]     = NULL;
	clumps[2]     = NULL;
	clumps[3]     = NULL;
	clumps[4]     = NULL;
	edgeClumps[0] = NULL;
	edgeClumps[1] = NULL;
	edgeClumps[2] = NULL;
	CloneClump();
	SetPosition();
	Init(&lbl_8_data_18A18, 1, 4);
	shape->height = lbl_8_data_18A18.height * scale;
	shape->radius = lbl_8_data_18A18.radius * scale;
	shape->unk10  = lbl_8_data_18A18.unk10 * scale;
}

extern "C" TObjGrass* __dt__9TObjGrassFv(TObjGrass* self, s16 flags)
{
	if (self != NULL) {
		*(void***)((u8*)self + 0x18) = __vt__9TObjGrass;
		*(void***)((u8*)self + 0x2C) = __vt__9TObjGrass + 11;
		self->DestroyClump();
		__dt__7C_COLLIFv((u8*)self + 0x30, 0);
		__dt__10TObjSetObjFv((u8*)self + 0x28, 0);
		__dt__7TObjectFv(self, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, self);
		}
	}
	return self;
}

void TObjGrass::SetPosition()
{
	Vec3 size;
	size.x = size.y = size.z = scale;
	for (int i = 0; i < 5; i++) {
		RwFrame* frame = clumps[i]->frame;
		fn_8019EB94(frame, &position, 0);
		fn_80195790(
		    &frame->modelling, &AxisY, 1.0f - fn_800D7AE4(angle.y), fn_800D7B00(angle.y), 1);
		fn_8019E880(frame);
		if (direction == 1) {
			fn_80195790(
			    &frame->modelling, &AxisZ, 1.0f - fn_800D7AE4(0x8000), fn_800D7B00(0x8000), 1);
			fn_8019E880(frame);
		}
		fn_8019EC30(frame, &size, 1);
	}
	for (int i = 0; i < 3; i++) {
		RwFrame* frame = edgeClumps[i]->frame;
		fn_8019EB94(frame, &position, 0);
		fn_80195790(
		    &frame->modelling, &AxisY, 1.0f - fn_800D7AE4(angle.y), fn_800D7B00(angle.y), 1);
		fn_8019E880(frame);
		if (direction == 1) {
			fn_80195790(
			    &frame->modelling, &AxisZ, 1.0f - fn_800D7AE4(0x8000), fn_800D7B00(0x8000), 1);
			fn_8019E880(frame);
		}
		fn_8019EC30(frame, &size, 1);
	}
}

void TObjGrass::Exec()
{
	if (CheckRangeOut() != 0 || CheckMustKill() != 0) {
		signal |= 1;
		return;
	}
	f32 total;
	f32 time;
	for (int i = 0; i < 5; i++) {
		total = 60.0f * hierarchies[i]->interpolator->animation->duration;
		time  = (f32)lbl_8042C180->frame - total * (s32)((f32)lbl_8042C180->frame / total);
		fn_8020D02C(hierarchies[i]->interpolator, time / 60.0f);
		fn_8013FC30(hierarchies[i]);
	}
	for (int i = 0; i < 3; i++) {
		total = 60.0f * edgeHierarchies[i]->interpolator->animation->duration;
		time  = (f32)lbl_8042C180->frame - total * (s32)((f32)lbl_8042C180->frame / total);
		fn_8020D02C(edgeHierarchies[i]->interpolator, time / 60.0f);
		fn_8013FC30(edgeHierarchies[i]);
	}
	if (OnEdit() != 0) {
		s32 oldType = type;
		SetParameter();
		if (type != oldType) {
			DestroyClump();
			CloneClump();
		}
		SetPosition();
		return;
	}
	if (time < total && total <= 1.0f + time) {
		if (lbl_8042C388 != NULL) {
			fn_800B4A38(lbl_8042C388, 0x5A14, &position, 0, 1, (s8)lbl_8_bss_1CA8, 0);
		}
	}
	previous          = C_COLLI::position;
	C_COLLI::position = position;
	C_COLLI::angle    = angle;
	Entry();
}

void TObjGrass::SetParameter()
{
	SETDATA_PARAM* data = frame;
	GrassParam* params  = data->params;
	position            = data->position;
	data                = frame;
	angle               = data->angle;
	angle.z             = 0;
	angle.x             = 0;
	direction           = params->direction;
	type                = params->type;
	scale               = 1.0f + params->scale;
}

void TObjGrass::CloneClump()
{
	for (int i = 0; i < 5; i++) {
		if (clumps[i] == NULL) {
			clumps[i] = fn_80150588(lbl_8_data_18938[type][i]);
			fn_8015BB08(*(void**)((u8*)lbl_8042C1D0 + 0x725C), clumps[i]);
			objRpClumpForAllAtomicsToSetRenderCallbackToUseLight__FP7RpClumpUi(
			    clumps[i], ((frame->flags & 0x1C0000) >> 18) + 4);
			hierarchies[i] = GetHierarchy(clumps[i]);
			fn_8014FFBC(clumps[i], SetHierarchyForSkinAtomic, hierarchies[i]);
			hierarchies[i]->flags |= 0x3000;
			fn_8020C72C(hierarchies[i]->interpolator, lbl_8_data_18978[type][i]);
			fn_8013F3A4(hierarchies[i]);
			fn_8013FC30(hierarchies[i]);
			fn_8020D02C(hierarchies[i]->interpolator, 0.0f);
			fn_8020CC18(hierarchies[i]->interpolator, 0.0f);
		}
	}
	for (int i = 0; i < 3; i++) {
		if (edgeClumps[i] == NULL) {
			edgeClumps[i] = fn_80150588(lbl_8_data_18960[type][i]);
			fn_8015BB08(*(void**)((u8*)lbl_8042C1D0 + 0x7284), edgeClumps[i]);
			objRpClumpForAllAtomicsToSetRenderCallbackToUseLight__FP7RpClumpUi(
			    edgeClumps[i], ((frame->flags & 0x1C0000) >> 18) + 4);
			edgeHierarchies[i] = GetHierarchy(edgeClumps[i]);
			fn_8014FFBC(edgeClumps[i], SetHierarchyForSkinAtomic, edgeHierarchies[i]);
			edgeHierarchies[i]->flags |= 0x3000;
			fn_8020C72C(edgeHierarchies[i]->interpolator, lbl_8_data_18978[type][i]);
			fn_8013F3A4(edgeHierarchies[i]);
			fn_8013FC30(edgeHierarchies[i]);
			fn_8020D02C(edgeHierarchies[i]->interpolator, 0.0f);
			fn_8020CC18(edgeHierarchies[i]->interpolator, 0.0f);
		}
	}
}

void TObjGrass::DestroyClump()
{
	int i;
	for (i = 0; i < 5; i++) {
		if (clumps[i] != NULL) {
			fn_8015BBF8(*(void**)((u8*)lbl_8042C1D0 + 0x725C), clumps[i]);
			fn_80150958(clumps[i]);
			clumps[i] = NULL;
		}
	}
	for (i = 0; i < 3; i++) {
		if (edgeClumps[i] != NULL) {
			fn_8015BBF8(*(void**)((u8*)lbl_8042C1D0 + 0x7284), edgeClumps[i]);
			fn_80150958(edgeClumps[i]);
			edgeClumps[i] = NULL;
		}
	}
}
