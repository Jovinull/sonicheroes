#include "types.h"

// Retained PS2 symbols name this object TObjS11Flag and give its method family
// in the order the GameCube text keeps: three file-static RpAtomic callbacks,
// DestroyClump, CloneClump, SetUserData, SetParameter, SetPosition, Exec, the
// destructor, the TObject* constructor, EditOnChange and the
// endObj/initObj/startObj lifecycle functions. The "TObjS11Flag" class-name
// string in this unit's .data correlates the GameCube object with that family.
//
// Each flag pole carries a cloth atomic whose render callback poses the
// type's shared delta-morph atomic at the flag and draws it with the saved
// default callback; the morph clock advances once per frame per type.
//
// Like the other Stage 11 object units this one is built with deferred
// inlining: the functions are emitted in reverse definition order, and the
// compiler-generated vtable lands after the named data and ahead of the string
// literals, where retail has it.

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

struct FlagParam {
	s8 type;
	s8 variant;
	s8 direction;
	u8 pad03;
	f32 scale;
};

struct SETDATA_PARAM {
	Vec3 position;
	sAngle angle;
	u32 flags;
	u8 pad1C[0x10];
	FlagParam* params;
};

struct RwMatrix {
	u8 pad00[0x40];
};

struct RwFrame {
	u8 pad00[0x10];
	RwMatrix modelling;
};

struct RwSphere {
	Vec3 center;
	f32 radius;
};

struct RpAtomic;
typedef RpAtomic* (*RpAtomicCallBackRender)(RpAtomic*);

struct RpAtomic {
	u8 pad00[4];
	RwFrame* frame;
	u8 pad08[0x14];
	RwSphere boundingSphere;
	u8 pad2C[0x1C];
	RpAtomicCallBackRender renderCallBack;
	s32 interpolatorFlags;
};

struct RpClump {
	u8 pad00[4];
	RwFrame* frame;
};

struct RpDMorphAnimation;

struct GameState {
	u8 pad00[0x1F];
	s8 paused;
};

/* What the cloth atomic's render callback reads back through its MCC user
 * data: pointers into the owning flag. */
struct FlagUserData {
	Vec3* position;
	sAngle* angle;
	f32* time;
	f32* scale;
	s32* type;
	s32* direction;
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
	u8 pad00[0x60];
	Vec3 position;
	sAngle angle;
	u8 pad78[0x10];

	C_COLLI();
	~C_COLLI();
};

class DAnimClass
{
public:
	f32 GetTotalFrame(RpDMorphAnimation*);
};

RpAtomic* objRpClumpGetAtomic(RpClump*, RpAtomic*);

extern "C" {
extern void* lbl_8042C110;
extern void* lbl_8042C148;
extern GameState* lbl_8042C180;
extern void* lbl_8042C1D0;
extern void* lbl_8042C298;
extern DAnimClass lbl_8042C340;
extern u8 AxisX;
extern u8 AxisY;
extern u8 AxisZ;
extern u8 lbl_802FF5A0;

void __dt__7TObjectFv(void*, s16);
void __dt__7C_COLLIFv(void*, s16);
void __dt__10TObjSetObjFv(void*, s16);
void* Malloc__9THeapCtrlFUi(void*, u32);
void Free__9THeapCtrlFPv(void*, void*);
void objRpClumpForAllAtomicsToSetRenderCallbackToUseLight__FP7RpClumpUi(RpClump*, u32);
RpDMorphAnimation* LoadDeltaMorphEx__7ONEFILEFUiPc(void*, s32, void*);
RpClump* LoadClumpEx__7ONEFILEFUiPc(void*, s32, void*);
s32 CheckFileID__7ONEFILEFPc(void*, const char*);
void LoadOneFile__7ONEFILEFPc(void*, void*);
void* RpAtomicMCCGetUsrData(RpAtomic*);
void RpAtomicMCCSetUsrData(RpAtomic*, void*, s32);
f32 fn_800D7AE4(s32);
f32 fn_800D7B00(s32);
void fn_8013BD74(RpDMorphAnimation*);
void fn_8013D344(RpAtomic*, RpDMorphAnimation*);
void fn_8013D5C8(RpAtomic*, f32);
RpAtomic* fn_8014F1B0(RpAtomic*);
void fn_8014F854(RpAtomic*);
void fn_8014FFBC(RpClump*, RpAtomic* (*)(RpAtomic*, void*), void*);
RpClump* fn_80150588(RpClump*);
void fn_80150958(RpClump*);
void fn_8015BB08(void*, RpClump*);
void fn_8015BBF8(void*, RpClump*);
void* fn_8015BD78(RpClump*);
void fn_80195790(void*, void*, f32, f32, s32);
void fn_8019E880(RwFrame*);
void fn_8019EB94(RwFrame*, Vec3*, s32);
void fn_8019EC30(RwFrame*, Vec3*, s32);
void fn_801A4C84(void*);
}

/* RenderWare's RpAtomicGetBoundingSphere macro: resynchronise a dirty
 * interpolated sphere, then yield the sphere. */
#define GetBoundingSphere(atomic)                                                                  \
	((((atomic)->interpolatorFlags & 2) ? (fn_8014F854(atomic), 0) : 0), &(atomic)->boundingSphere)

class TObjS11Flag : public TObject, public TObjSetObj, public C_COLLI
{
public:
	s32 type;
	RpClump* clump;
	RpClump* cloth;
	RpAtomic* clothAtomic;
	f32* time;
	FlagUserData userData;
	s32 direction;
	f32 scale;
	s32 variant;

	void DestroyClump();
	void CloneClump();
	void SetUserData();
	void SetParameter();
	void SetPosition();
	virtual void Exec();
	inline virtual ~TObjS11Flag();
	TObjS11Flag(TObject*);
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
TObjS11Flag* __dt__11TObjS11FlagFv(TObjS11Flag*, s16);
extern void* __vt__11TObjS11Flag[];
RpAtomic* fn_8_C7550(RpAtomic*, void*);
RpAtomic* fn_8_C7580(RpAtomic*);
RpAtomic* fn_8_C787C(RpAtomic*, void*);
}

// The data names below are address names; their roles are descriptive guesses.
extern "C" {
char* lbl_8_data_18AD0[2]    = { "s11_pnw_flagl.dma", "s11_pnw_flagd.dma" };
char* lbl_8_data_18B00[2]    = { "s11_pnw_flagl.dff", "s11_pnw_flagd.dff" };
char* lbl_8_data_18B58[2][2] = {
	{ "s11_on_flagl_a.dff", "s11_on_flagl_b.dff" },
	{ "s11_on_flagd_a.dff", "s11_on_flagd_b.dff" },
};
#pragma explicit_zero_data on
RpClump* lbl_8_data_18B68[2][2]        = { { NULL, NULL }, { NULL, NULL } };
RpClump* lbl_8_data_18B78[2]           = { NULL, NULL };
RpAtomic* lbl_8_data_18B80[2]          = { NULL, NULL };
RpDMorphAnimation* lbl_8_data_18B88[2] = { NULL, NULL };
s32 lbl_8_data_18B90[2]                = { 0, 0 };
s32 lbl_8_data_18B98[2]                = { 0, 0 };
#pragma explicit_zero_data reset
char* s11FlagFieldNames[4] = { "type      : light", "pole", "direction : up", "scale(def:1.0)" };
char* lbl_8_data_18C00[2]  = { "type      : light", "type      : dark" };
char* lbl_8_data_18C1C[2]  = { "direction : up", "direction : down" };
char* lbl_8_data_18C30     = "TObjS11Flag";
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
void* lbl_8_bss_1CD8;
RpAtomicCallBackRender lbl_8_bss_1CDC;
f32 lbl_8_bss_1CE0;
f32 lbl_8_bss_1CE4;
SETOBJ_PARAM s11FlagEntry;
void s11FlagUnload();
void s11FlagLoad();
void s11FlagCreate();
}

extern "C" void s11FlagRegister()
{
	s11FlagEntry.flags       = 0;
	s11FlagEntry.field18     = 0;
	s11FlagEntry.displayName = "S11 FLAG";
	s11FlagEntry.init        = s11FlagLoad;
	s11FlagEntry.end         = s11FlagUnload;
	s11FlagEntry.create      = s11FlagCreate;
	s11FlagEntry.field10     = 0;
	s11FlagEntry.flags       = 0x21000;
	s11FlagEntry.field18     = 0;
	s11FlagEntry.field20     = 0x14;
	s11FlagEntry.id          = 0x1188;
	s11FlagEntry.count       = 2;
	s11FlagEntry.field21     = 0;
	s11FlagEntry.fieldTypes  = "cccF";
	s11FlagEntry.fields      = s11FlagFieldNames;
	if (s11FlagEntry.fieldTypes != NULL)
		s11FlagEntry.flags |= 8;
	else
		s11FlagEntry.flags &= ~8;
}

__declspec(section ".ctors") void (*const s11FlagCtorEntry)() = s11FlagRegister;

extern "C" void s11FlagCreate()
{
	new (lbl_8042C148) TObjS11Flag((TObject*)lbl_8042C110);
}

extern "C" void s11FlagLoad()
{
	void* stage = *(void**)((u8*)lbl_8042C1D0 + 0x8C18);
	if (stage != NULL) {
		lbl_8_bss_1CD8 = stage;
		fn_801A4C84(stage);
	} else {
		return;
	}
	int i;
	int j;
	void* archive = *(void**)((u8*)lbl_8042C298 + 0xA50);
	LoadOneFile__7ONEFILEFPc(archive, &lbl_802FF5A0);
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 2; j++) {
			lbl_8_data_18B68[i][j] = LoadClumpEx__7ONEFILEFUiPc(
			    archive, CheckFileID__7ONEFILEFPc(archive, lbl_8_data_18B58[i][j]), &lbl_802FF5A0);
		}
		lbl_8_data_18B78[i] = LoadClumpEx__7ONEFILEFUiPc(
		    archive, CheckFileID__7ONEFILEFPc(archive, lbl_8_data_18B00[i]), &lbl_802FF5A0);
		fn_8014FFBC(lbl_8_data_18B78[i], fn_8_C787C, &lbl_8_data_18B80[i]);
		lbl_8_data_18B88[i] = LoadDeltaMorphEx__7ONEFILEFUiPc(
		    archive, CheckFileID__7ONEFILEFPc(archive, lbl_8_data_18AD0[i]), &lbl_802FF5A0);
		if (lbl_8_data_18B88[i] != NULL) {
			lbl_8_bss_1CE0 = lbl_8042C340.GetTotalFrame(lbl_8_data_18B88[i]);
		}
	}
}

extern "C" void s11FlagUnload()
{
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			if (lbl_8_data_18B68[i][j] != NULL) {
				fn_80150958(lbl_8_data_18B68[i][j]);
				lbl_8_data_18B68[i][j] = NULL;
			}
		}
		if (lbl_8_data_18B78[i] != NULL) {
			fn_80150958(lbl_8_data_18B78[i]);
			lbl_8_data_18B78[i] = NULL;
			lbl_8_data_18B80[i] = NULL;
		}
		if (lbl_8_data_18B88[i] != NULL) {
			fn_8013BD74(lbl_8_data_18B88[i]);
			lbl_8_data_18B88[i] = NULL;
		}
	}
}

void TObjS11Flag::EditOnChange(SETDATA_PARAM* data)
{
	FlagParam* params = data->params;
	if (params->type < 0)
		params->type = 0;
	if (params->type > 1)
		params->type = 1;
	if (params->variant < 0)
		params->variant = 0;
	if (params->variant >= 2)
		params->variant = 1;
	if (params->direction < 0)
		params->direction = 0;
	if (params->direction > 1)
		params->direction = 1;
	s11FlagFieldNames[0] = lbl_8_data_18C00[params->type];
	s11FlagFieldNames[2] = lbl_8_data_18C1C[params->direction];
}

TObjS11Flag::TObjS11Flag(TObject* parent)
    : TObject(parent)
{
	className  = lbl_8_data_18C30;
	objectSize = sizeof(TObjS11Flag);
	time       = &lbl_8_bss_1CE4;
	SetParameter();
	clump = NULL;
	cloth = NULL;
	CloneClump();
	SetUserData();
	SetPosition();
}

extern "C" TObjS11Flag* __dt__11TObjS11FlagFv(TObjS11Flag* self, s16 flags)
{
	if (self != NULL) {
		*(void***)((u8*)self + 0x18) = __vt__11TObjS11Flag;
		*(void***)((u8*)self + 0x2C) = __vt__11TObjS11Flag + 11;
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

void TObjS11Flag::Exec()
{
	if (CheckRangeOut() != 0 || CheckMustKill() != 0) {
		signal |= 1;
		return;
	}
	if (lbl_8042C180->paused != 0) {
		return;
	}
	if (OnEdit() != 0) {
		s32 oldType    = type;
		s32 oldVariant = variant;
		SetParameter();
		if (type != oldType || variant != oldVariant) {
			DestroyClump();
			CloneClump();
			SetUserData();
		}
		SetPosition();
	}
	if (time != NULL && lbl_8_data_18B90[type] == 0) {
		*time += 0.02f;
		if (*time >= lbl_8_bss_1CE0) {
			*time -= lbl_8_bss_1CE0;
		}
		lbl_8_data_18B90[type] = 1;
		lbl_8_data_18B98[type] = 0;
	}
	// Retail queries the edit state once more and ignores the answer.
	if (OnEdit() != 0) {
		return;
	}
}

void TObjS11Flag::SetPosition()
{
	if (clump != NULL) {
		RwFrame* rwFrame = clump->frame;
		Vec3 size        = { scale, scale, scale };
		fn_8019EC30(rwFrame, &size, 0);
		if (direction == 1) {
			fn_80195790(
			    &rwFrame->modelling, &AxisX, 1.0f - fn_800D7AE4(0x8000), fn_800D7B00(0x8000), 2);
			fn_8019E880(rwFrame);
		}
		fn_80195790(&rwFrame->modelling, &AxisY, 1.0f - fn_800D7AE4(frame->angle.y),
		    fn_800D7B00(frame->angle.y), 2);
		fn_8019E880(rwFrame);
		fn_80195790(&rwFrame->modelling, &AxisX, 1.0f - fn_800D7AE4(frame->angle.x),
		    fn_800D7B00(frame->angle.x), 2);
		fn_8019E880(rwFrame);
		fn_80195790(&rwFrame->modelling, &AxisZ, 1.0f - fn_800D7AE4(frame->angle.z),
		    fn_800D7B00(frame->angle.z), 2);
		fn_8019E880(rwFrame);
		fn_8019EB94(rwFrame, &frame->position, 2);
		if (cloth != NULL) {
			rwFrame = cloth->frame;
			fn_8019EC30(rwFrame, &size, 0);
			if (direction == 1) {
				fn_80195790(&rwFrame->modelling, &AxisX, 1.0f - fn_800D7AE4(0x8000),
				    fn_800D7B00(0x8000), 2);
				fn_8019E880(rwFrame);
			}
			fn_80195790(&rwFrame->modelling, &AxisY, 1.0f - fn_800D7AE4(frame->angle.y),
			    fn_800D7B00(frame->angle.y), 2);
			fn_8019E880(rwFrame);
			fn_80195790(&rwFrame->modelling, &AxisX, 1.0f - fn_800D7AE4(frame->angle.x),
			    fn_800D7B00(frame->angle.x), 2);
			fn_8019E880(rwFrame);
			fn_80195790(&rwFrame->modelling, &AxisZ, 1.0f - fn_800D7AE4(frame->angle.z),
			    fn_800D7B00(frame->angle.z), 2);
			fn_8019E880(rwFrame);
			fn_8019EB94(rwFrame, &frame->position, 2);
		}
	}
}

void TObjS11Flag::SetParameter()
{
	SETDATA_PARAM* data = frame;
	FlagParam* params   = data->params;
	C_COLLI::position   = data->position;
	data                = frame;
	C_COLLI::angle      = data->angle;
	direction           = params->direction;
	type                = params->type;
	variant             = params->variant;
	scale               = 1.0f + params->scale;
}

void TObjS11Flag::SetUserData()
{
	FlagUserData* data;
	userData.position  = &frame->position;
	userData.angle     = &frame->angle;
	userData.time      = time;
	userData.scale     = &scale;
	userData.type      = &type;
	userData.direction = &direction;
	data               = &userData;
	RpAtomicMCCSetUsrData(clothAtomic, &data, sizeof(data));
}

void TObjS11Flag::CloneClump()
{
	if (clump == NULL) {
		clump = fn_80150588(lbl_8_data_18B68[type][variant]);
		if (clump != NULL) {
			fn_8015BB08(*(void**)((u8*)lbl_8042C1D0 + 0x7260), clump);
			objRpClumpForAllAtomicsToSetRenderCallbackToUseLight__FP7RpClumpUi(clump, 0x10);
		}
	}
	if (cloth == NULL) {
		cloth = fn_80150588(*(RpClump**)((u8*)lbl_8042C1D0 + 0xB08));
		if (cloth != NULL) {
			fn_8015BB08(*(void**)((u8*)lbl_8042C1D0 + 0x7278), cloth);
			RpAtomic* atomic = objRpClumpGetAtomic(cloth, NULL);
			fn_8014FFBC(cloth, fn_8_C7550, &clothAtomic);
			*GetBoundingSphere(atomic) = *GetBoundingSphere(lbl_8_data_18B80[type]);
		}
	}
}

void TObjS11Flag::DestroyClump()
{
	RpClump* model = clump;
	if (model != NULL) {
		fn_8015BBF8(fn_8015BD78(model), model);
		fn_80150958(clump);
		clump = NULL;
	}
	model = cloth;
	if (model != NULL) {
		fn_8015BBF8(fn_8015BD78(model), model);
		fn_80150958(cloth);
		cloth       = NULL;
		clothAtomic = NULL;
	}
}

extern "C" RpAtomic* fn_8_C787C(RpAtomic* atomic, void* data)
{
	*(RpAtomic**)data = atomic;
	lbl_8_bss_1CDC    = atomic->renderCallBack;
	return NULL;
}

extern "C" RpAtomic* fn_8_C7580(RpAtomic* atomic)
{
	FlagUserData* data = *(FlagUserData**)RpAtomicMCCGetUsrData(atomic);
	if (data == NULL) {
		return atomic;
	}
	if (lbl_8_data_18B80[*data->type] == NULL || lbl_8_data_18B88[*data->type] == NULL) {
		return atomic;
	}
	RwFrame* rwFrame = lbl_8_data_18B80[*data->type]->frame;
	Vec3 size        = { *data->scale, *data->scale, *data->scale };
	fn_8019EC30(rwFrame, &size, 0);
	if (*data->direction == 1) {
		fn_80195790(
		    &rwFrame->modelling, &AxisX, 1.0f - fn_800D7AE4(0x8000), fn_800D7B00(0x8000), 2);
		fn_8019E880(rwFrame);
	}
	fn_80195790(&rwFrame->modelling, &AxisY, 1.0f - fn_800D7AE4(data->angle->y),
	    fn_800D7B00(data->angle->y), 2);
	fn_8019E880(rwFrame);
	fn_80195790(&rwFrame->modelling, &AxisX, 1.0f - fn_800D7AE4(data->angle->x),
	    fn_800D7B00(data->angle->x), 2);
	fn_8019E880(rwFrame);
	fn_80195790(&rwFrame->modelling, &AxisZ, 1.0f - fn_800D7AE4(data->angle->z),
	    fn_800D7B00(data->angle->z), 2);
	fn_8019E880(rwFrame);
	fn_8019EB94(rwFrame, data->position, 2);
	if (lbl_8_data_18B98[*data->type] == 0) {
		fn_8013D344(lbl_8_data_18B80[*data->type], lbl_8_data_18B88[*data->type]);
		fn_8013D5C8(lbl_8_data_18B80[*data->type], *data->time);
		lbl_8_data_18B98[*data->type] = 1;
		lbl_8_data_18B90[*data->type] = 0;
	}
	lbl_8_bss_1CDC(lbl_8_data_18B80[*data->type]);
	return atomic;
}

extern "C" RpAtomic* fn_8_C7550(RpAtomic* atomic, void* data)
{
	*(RpAtomic**)data      = atomic;
	atomic->renderCallBack = fn_8_C7580;
	if (atomic->renderCallBack == NULL) {
		atomic->renderCallBack = fn_8014F1B0;
	}
	return NULL;
}
