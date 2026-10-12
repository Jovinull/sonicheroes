#include "types.h"

// Retained PS2 symbols name this object TObjTree and give its method family in
// the order the GameCube text keeps: SetCollisionParameter, SetParameter,
// Exec, SetPosition, the destructor, the TObject* constructor, the
// SetHierarchyForSkinAtomic/GetHierarchy/GetChildFrameHierarchy helpers,
// EditOnChange and the endObj/initObj/startObj lifecycle functions. The
// "TObjTree" class-name string in this unit's .data correlates the GameCube
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

struct TreeParam {
	f32 scale;
	s8 direction;
};

struct SETDATA_PARAM {
	Vec3 position;
	sAngle angle;
	u32 flags;
	u8 pad1C[0x10];
	TreeParam* params;
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

/* The collision shape a tree registers; the dimensions are scaled by the
 * tree's own scale. */
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

class TObjTree : public TObject, public TObjSetObj, public C_COLLI
{
public:
	Vec3 position;
	sAngle angle;
	f32 scale;
	s32 direction;
	RpClump* clumps[2];
	RpHAnimHierarchy* hierarchy;

	void SetCollisionParameter();
	void SetParameter();
	virtual void Exec();
	void SetPosition();
	inline virtual ~TObjTree();
	TObjTree(TObject*);
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
TObjTree* __dt__8TObjTreeFv(TObjTree*, s16);
extern void* __vt__8TObjTree[];
}

// The data names below are address names; their roles are descriptive guesses.
extern "C" {
#pragma explicit_zero_data on
RpClump* lbl_8_data_18298[2] = { NULL, NULL };
#pragma explicit_zero_data reset
char* treeObjectFieldNames[2] = { "scale(def:1.0)", "direction : up" };
char* lbl_8_data_182DC[2]     = { "direction : up", "direction : down" };
CCL_INFO lbl_8_data_182E4     = { 0x0008FFE0, 2, 0.0f, 17.5f, 0.0f, 15.0f, 17.5f };
char* lbl_8_data_18320        = "TObjTree";
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
	u8 pad2C[4];
};

extern "C" {
u8 lbl_8_bss_1C40;
void* lbl_8_bss_1C44;
SETOBJ_PARAM treeObjectEntry;
void treeObjectUnload();
void treeObjectLoad();
void treeObjectCreate();
}

extern "C" void treeObjectRegister()
{
	treeObjectEntry.flags       = 0;
	treeObjectEntry.field18     = 0;
	treeObjectEntry.displayName = "TREE OBJECT";
	treeObjectEntry.init        = treeObjectLoad;
	treeObjectEntry.end         = treeObjectUnload;
	treeObjectEntry.create      = treeObjectCreate;
	treeObjectEntry.field10     = 0;
	treeObjectEntry.flags       = 0x20000;
	treeObjectEntry.field18     = 0;
	treeObjectEntry.field20     = 0x1E;
	treeObjectEntry.id          = 0x118A;
	treeObjectEntry.count       = 2;
	treeObjectEntry.field21     = 0;
	treeObjectEntry.fieldTypes  = "Fc";
	treeObjectEntry.fields      = treeObjectFieldNames;
	if (treeObjectEntry.fieldTypes != NULL)
		treeObjectEntry.flags |= 8;
	else
		treeObjectEntry.flags &= ~8;
}

__declspec(section ".ctors") void (*const treeObjectCtorEntry)() = treeObjectRegister;

extern "C" void treeObjectCreate()
{
	new (lbl_8042C148) TObjTree((TObject*)lbl_8042C110);
}

extern "C" void treeObjectLoad()
{
	void* stage = *(void**)((u8*)lbl_8042C1D0 + 0x8C18);
	if (stage != NULL) {
		fn_801A4C84(stage);
	} else {
		return;
	}
	void* archive = *(void**)((u8*)lbl_8042C298 + 0xA50);
	LoadOneFile__7ONEFILEFPc(archive, &lbl_802FF5A0);
	lbl_8_data_18298[0] = LoadClumpEx__7ONEFILEFUiPc(
	    archive, CheckFileID__7ONEFILEFPc(archive, "s11_on_tree.dff"), &lbl_802FF5A0);
	lbl_8_data_18298[1] = LoadClumpEx__7ONEFILEFUiPc(
	    archive, CheckFileID__7ONEFILEFPc(archive, "s11_pnw_tree.dff"), &lbl_802FF5A0);
	lbl_8_bss_1C44 = LoadHAnimationEx__7ONEFILEFUiPc(
	    archive, CheckFileID__7ONEFILEFPc(archive, "s11_pnw_tree.anm"), &lbl_802FF5A0);
}

extern "C" void treeObjectUnload()
{
	for (int i = 0; i < 2; i++) {
		if (lbl_8_data_18298[i] != NULL) {
			fn_80150958(lbl_8_data_18298[i]);
			lbl_8_data_18298[i] = NULL;
		}
	}
	if (lbl_8_bss_1C44 != NULL) {
		fn_8020C2D8(lbl_8_bss_1C44);
		lbl_8_bss_1C44 = NULL;
	}
}

void TObjTree::EditOnChange(SETDATA_PARAM* data)
{
	TreeParam* params = data->params;
	if (params->direction < 0)
		params->direction = 0;
	if (params->direction > 1)
		params->direction = 1;
	treeObjectFieldNames[1] = lbl_8_data_182DC[params->direction];
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

TObjTree::TObjTree(TObject* parent)
    : TObject(parent)
{
	className  = lbl_8_data_18320;
	objectSize = sizeof(TObjTree);
	SetParameter();
	for (int i = 0; i < 2; i++) {
		clumps[i] = fn_80150588(lbl_8_data_18298[i]);
		if (i == 0) {
			fn_8015BB08(*(void**)((u8*)lbl_8042C1D0 + 0x725C), clumps[0]);
		} else {
			fn_8015BB08(*(void**)((u8*)lbl_8042C1D0 + 0x7284), clumps[1]);
		}
		// Read through a volatile view, as the shared Stage 11 ironball
		// constructor does, so the load keeps its place ahead of the clump.
		u32 flags = *(volatile u32*)&frame->flags;
		objRpClumpForAllAtomicsToSetRenderCallbackToUseLight__FP7RpClumpUi(
		    clumps[i], ((flags & 0x1C0000) >> 18) + 4);
	}
	hierarchy = GetHierarchy(clumps[1]);
	fn_8014FFBC(clumps[1], SetHierarchyForSkinAtomic, hierarchy);
	hierarchy->flags |= 0x3000;
	fn_8020C72C(hierarchy->interpolator, lbl_8_bss_1C44);
	fn_8013F3A4(hierarchy);
	fn_8013FC30(hierarchy);
	fn_8020D02C(hierarchy->interpolator, 0.0f);
	fn_8020CC18(hierarchy->interpolator, 0.0f);
	SetPosition();
	if (OnEdit() == 0) {
		Init(&lbl_8_data_182E4, 1, 4);
		SetCollisionParameter();
	}
}

extern "C" TObjTree* __dt__8TObjTreeFv(TObjTree* self, s16 flags)
{
	if (self != NULL) {
		*(void***)((u8*)self + 0x18) = __vt__8TObjTree;
		*(void***)((u8*)self + 0x2C) = __vt__8TObjTree + 11;
		for (int i = 0; i < 2; i++) {
			if (self->clumps[i] != NULL) {
				if (i == 0) {
					fn_8015BBF8(*(void**)((u8*)lbl_8042C1D0 + 0x725C), self->clumps[i]);
				} else {
					fn_8015BBF8(*(void**)((u8*)lbl_8042C1D0 + 0x7284), self->clumps[i]);
				}
				fn_80150958(self->clumps[i]);
				self->clumps[i] = NULL;
			}
		}
		__dt__7C_COLLIFv((u8*)self + 0x30, 0);
		__dt__10TObjSetObjFv((u8*)self + 0x28, 0);
		__dt__7TObjectFv(self, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, self);
		}
	}
	return self;
}

void TObjTree::SetPosition()
{
	Vec3 size;
	size.x = size.y = size.z = scale;
	for (int i = 0; i < 2; i++) {
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
}

void TObjTree::Exec()
{
	if (CheckRangeOut() != 0 || CheckMustKill() != 0) {
		signal |= 1;
		return;
	}
	f32 total = 60.0f * hierarchy->interpolator->animation->duration;
	f32 time  = (f32)lbl_8042C180->frame - total * (s32)((f32)lbl_8042C180->frame / total);
	fn_8020D02C(hierarchy->interpolator, time / 60.0f);
	fn_8013FC30(hierarchy);
	if (OnEdit() != 0) {
		SetParameter();
		SetPosition();
		return;
	}
	if (time < total && total <= 1.0f + time) {
		Vec3 pos = position;
		pos.y += 15.0f * scale;
		if (lbl_8042C388 != NULL) {
			fn_800B4A38(lbl_8042C388, 0x5A17, &pos, 0, 1, (s8)lbl_8_bss_1C40, 0);
		}
	}
	previous          = C_COLLI::position;
	C_COLLI::position = position;
	C_COLLI::angle    = angle;
	Entry();
}

void TObjTree::SetParameter()
{
	SETDATA_PARAM* data = frame;
	TreeParam* params   = data->params;
	position            = data->position;
	data                = frame;
	angle               = data->angle;
	angle.z             = 0;
	angle.x             = 0;
	direction           = params->direction;
	scale               = 1.0f + params->scale;
}

void TObjTree::SetCollisionParameter()
{
	if (direction == 1) {
		shape->radius = -lbl_8_data_182E4.radius * scale;
	} else {
		shape->radius = lbl_8_data_182E4.radius * scale;
	}
	shape->height = lbl_8_data_182E4.height * scale;
	shape->depth  = lbl_8_data_182E4.depth * scale;
	CalcRange();
}
