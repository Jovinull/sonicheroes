#include "types.h"

// Retained PS2 symbols name this object TObjS12Celestial and give its method
// family in the order the GameCube text keeps: DestroyClump, CloneClump(int),
// SetPosition, SetParameter, Disp, Exec, the destructor and the TObject*
// constructor. The "TObjS12Celestial" class-name string in this unit's .data
// correlates the GameCube object with that family.
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

/* An unreferenced vector every unit of this family carries at the head of its
 * .rodata, the way an internal-linkage const from a shared header lands in
 * each translation unit that includes it. Its name and home are unknown. */
#pragma force_active on
static const Vec3 lbl_8_rodata_1660 = { 0.0f, 1.5f, 0.0f };
#pragma force_active reset

struct CelestialParam {
	s32 modelNo;
	f32 rotateX;
	f32 rotateY;
	f32 rotateZ;
	f32 scale;
};

struct SETDATA_PARAM {
	Vec3 position;
	s32 angleX;
	s32 angleY;
	s32 angleZ;
	u32 flags;
	u8 pad1C[0x10];
	CelestialParam* params;
};

struct RwMatrix {
	u8 data[0x40];
};
struct RwFrame {
	u8 pad00[0x10];
	RwMatrix modelling;
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
s32 fn_8005B8BC(void*);
s32 fn_8005B9F0(void*);
}

class TObjSetObj : public SetObjHdr
{
public:
	virtual void EditOnChange(SETDATA_PARAM*);

	s32 CheckMustKill() { return fn_8005B9F0(this); }
	s32 CheckRangeOut() { return fn_8005B8BC(this); }
};

extern "C" {
extern void* lbl_8042C110;
extern void* lbl_8042C148;
extern void* lbl_8042C1D0;
extern void* lbl_8042C298;
extern u8 AxisX;
extern u8 AxisY;
extern u8 AxisZ;
extern u8 lbl_802FF5A0;

void __ct__7TObjectFP7TObject(void*, void*);
void __dt__7TObjectFv(void*, s16);
void dtor_8005BD3C(void*, s16);
void* Malloc__9THeapCtrlFUi(void*, u32);
void Free__9THeapCtrlFPv(void*, void*);
void fn_8005BE6C(void*);
void fn_8005D5C8(void*, u32);
void* LoadClumpEx__7ONEFILEFUiPc(void*, s32, void*);
s32 CheckFileID__7ONEFILEFPc(void*, const char*);
void LoadOneFile__7ONEFILEFPc(void*, void*);
void fn_800BDF30(void*);
void fn_800BE1F4(void*);
void fn_800BE274(void*);
f32 fn_800D7AE4(s32);
f32 fn_800D7B00(s32);
void* fn_80150588(void*);
void fn_80150958(void*);
void fn_8015BB08(void*, void*);
void fn_8015BBF8(void*, void*);
void fn_80195790(RwMatrix*, void*, f32, f32, s32);
void fn_8019E880(RwFrame*);
void fn_8019EB94(RwFrame*, Vec3*, s32);
void fn_8019EC30(RwFrame*, Vec3*, s32);
void fn_801A4C84(void*);
}

class TObjS12Celestial : public TObject, public TObjSetObj
{
public:
	Vec3 position;
	s32 angleX;
	s32 angleY;
	s32 angleZ;
	s32 speedX;
	s32 speedY;
	s32 speedZ;
	f32 scale;
	s32 modelNo;
	void* model;

	void DestroyClump();
	void CloneClump(s32);
	void SetPosition();
	void SetParameter();
	virtual void Disp();
	virtual void Exec();
	inline virtual ~TObjS12Celestial();
	virtual void EditOnChange(SETDATA_PARAM*);
};

// The constructor and destructor are written against the object's storage:
// retail constructs and destroys the TObjSetObj base through out-of-line
// functions that keep their address names, which a C++ base-class call would
// rename. The compiler still generates the class vtable and its adjustor
// thunk from the virtual declarations above.
extern "C" {
TObjS12Celestial* __ct__16TObjS12CelestialFP7TObject(TObjS12Celestial*, TObject*);
TObjS12Celestial* __dt__16TObjS12CelestialFv(TObjS12Celestial*, s16);
extern void* __vt__16TObjS12Celestial[];
}

#define SETOBJ(self) ((void*)((u8*)(self) + 0x28))

// The data names below are descriptive guesses.
extern "C" {
char* s12celestialModelNames[2] = { "s12_k_tikankyuu_1.dff", "s12_k_tikankyuu_2.dff" };
char* s12celestialObjectFieldNames[5]
    = { "model no.", "x rotate speed", "y rotate speed", "z rotate speed", "scale(def:1.0)" };
char* CL_TObjS12Celestial = "TObjS12Celestial";
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
void* s12celestialModels[2];
SETOBJ_PARAM s12celestialObjectEntry;
void endObjS12Celestial();
void initObjS12Celestial();
void startObjS12Celestial();
}

extern "C" void s12celestialObjectRegister()
{
	s12celestialObjectEntry.flags       = 0;
	s12celestialObjectEntry.field18     = 0;
	s12celestialObjectEntry.displayName = "S12CELESTIAL OBJECT";
	s12celestialObjectEntry.init        = initObjS12Celestial;
	s12celestialObjectEntry.end         = endObjS12Celestial;
	s12celestialObjectEntry.create      = startObjS12Celestial;
	s12celestialObjectEntry.field10     = 0;
	s12celestialObjectEntry.flags       = 0x20000;
	s12celestialObjectEntry.field18     = 0;
	s12celestialObjectEntry.field20     = 0x1E;
	s12celestialObjectEntry.id          = 0x1181;
	s12celestialObjectEntry.count       = 2;
	s12celestialObjectEntry.field21     = 0;
	s12celestialObjectEntry.fieldTypes  = "iffff";
	s12celestialObjectEntry.fields      = s12celestialObjectFieldNames;
	if (s12celestialObjectEntry.fieldTypes != NULL)
		s12celestialObjectEntry.flags |= 8;
	else
		s12celestialObjectEntry.flags &= ~8;
}

__declspec(section ".ctors") void (*const s12celestialObjectCtorEntry)()
    = s12celestialObjectRegister;

/* startObjS12Celestial is a placement new-expression in retail: the result of
 * the allocation is null-checked through a compiler temporary, the shape MWCC
 * gives a new-expression whose object has a subobject with a destructor (the
 * TObject base). The object's real constructor is the storage-level function
 * above, so the new-expression constructs this same-sized stand-in, whose
 * default constructor forwards to it the way TObjS12Celestial() would. */
struct ObjectStorage {
	~ObjectStorage();
};

struct S12CelestialStorage : ObjectStorage {
	u8 data[sizeof(TObjS12Celestial)];

	S12CelestialStorage()
	{
		__ct__16TObjS12CelestialFP7TObject((TObjS12Celestial*)this, (TObject*)lbl_8042C110);
	}
	static void* operator new(unsigned long size, void* heap)
	{
		return Malloc__9THeapCtrlFUi(heap, size);
	}
};

extern "C" void startObjS12Celestial()
{
	new (lbl_8042C148) S12CelestialStorage();
}

#pragma opt_propagation on
extern "C" void initObjS12Celestial()
{
	void* stage = *(void**)((u8*)lbl_8042C1D0 + 0x8C18);
	if (!(stage != NULL && (fn_801A4C84(stage), 1)))
		return;

	fn_800BE274(*(void**)((u8*)lbl_8042C1D0 + 0x8C18));
	LoadOneFile__7ONEFILEFPc(*(void**)((u8*)lbl_8042C298 + 0xA50), &lbl_802FF5A0);
	s32 i;
	for (i = 0; i < 2; i++) {
		s12celestialModels[i] = LoadClumpEx__7ONEFILEFUiPc(*(void**)((u8*)lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(
		        *(void**)((u8*)lbl_8042C298 + 0xA50), s12celestialModelNames[i]),
		    &lbl_802FF5A0);
		if (s12celestialModels[i] != NULL) {
			fn_800BDF30(s12celestialModels[i]);
		}
	}
	fn_800BE1F4(*(void**)((u8*)lbl_8042C1D0 + 0x8C18));
}

extern "C" void endObjS12Celestial()
{
	s32 i;
	for (i = 0; i < 2; i++) {
		fn_80150958(s12celestialModels[i]);
		s12celestialModels[i] = NULL;
	}
}
#pragma opt_propagation reset

void TObjS12Celestial::EditOnChange(SETDATA_PARAM* data)
{
	s32* modelNo = &data->params->modelNo;
	if (*modelNo < 0) {
		*modelNo = 0;
	} else if (*modelNo >= 2) {
		*modelNo = 1;
	}
}

extern "C" TObjS12Celestial* __ct__16TObjS12CelestialFP7TObject(
    TObjS12Celestial* self, TObject* parent)
{
	__ct__7TObjectFP7TObject(self, parent);
	fn_8005BE6C(SETOBJ(self));
	*(void***)((u8*)self + 0x18) = __vt__16TObjS12Celestial;
	*(void***)((u8*)self + 0x2C) = __vt__16TObjS12Celestial + 11;
	self->className              = CL_TObjS12Celestial;
	self->objectSize             = sizeof(TObjS12Celestial);
	self->speedX = self->speedY = self->speedZ = 0;
	self->SetParameter();
	self->model = NULL;
	self->CloneClump(self->modelNo);
	self->SetPosition();
	return self;
}

extern "C" TObjS12Celestial* __dt__16TObjS12CelestialFv(TObjS12Celestial* self, s16 flags)
{
	if (self != NULL) {
		*(void***)((u8*)self + 0x18) = __vt__16TObjS12Celestial;
		*(void***)((u8*)self + 0x2C) = __vt__16TObjS12Celestial + 11;
		self->DestroyClump();
		dtor_8005BD3C(SETOBJ(self), 0);
		__dt__7TObjectFv(self, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, self);
		}
	}
	return self;
}

void TObjS12Celestial::Exec()
{
	if (CheckMustKill() != 0 || CheckRangeOut() != 0) {
		signal |= 1;
		return;
	}
	angleX += speedX;
	angleY += speedY;
	angleZ += speedZ;
	SetPosition();
}

void TObjS12Celestial::Disp() { }

void TObjS12Celestial::SetParameter()
{
	SETDATA_PARAM* data    = frame;
	CelestialParam* params = data->params;
	position               = data->position;
	modelNo                = params->modelNo;
	speedX                 = 182.04445f * params->rotateX;
	speedY                 = 182.04445f * params->rotateY;
	speedZ                 = 182.04445f * params->rotateZ;
	scale                  = 1.0f + params->scale;
}

void TObjS12Celestial::SetPosition()
{
	Vec3 size;
	size.x = size.y = size.z = scale;
	RwFrame* frame           = *(RwFrame**)((u8*)model + 4);
	fn_8019EB94(frame, &position, 0);
	f32 sine = fn_800D7B00(angleZ);
	fn_80195790(&frame->modelling, &AxisZ, 1.0f - fn_800D7AE4(angleZ), sine, 1);
	fn_8019E880(frame);
	sine = fn_800D7B00(angleY);
	fn_80195790(&frame->modelling, &AxisY, 1.0f - fn_800D7AE4(angleY), sine, 1);
	fn_8019E880(frame);
	sine = fn_800D7B00(angleX);
	fn_80195790(&frame->modelling, &AxisX, 1.0f - fn_800D7AE4(angleX), sine, 1);
	fn_8019E880(frame);
	fn_8019EC30(frame, &size, 1);
}

void TObjS12Celestial::CloneClump(s32 index)
{
	if (model == NULL) {
		model = fn_80150588(s12celestialModels[index]);
		fn_8015BB08(*(void**)((u8*)lbl_8042C1D0 + 0x72A0), model);
		fn_8005D5C8(model, 0x10);
	}
}

void TObjS12Celestial::DestroyClump()
{
	if (model != NULL) {
		fn_8015BBF8(*(void**)((u8*)lbl_8042C1D0 + 0x72A0), model);
		fn_80150958(model);
		model = NULL;
	}
}
