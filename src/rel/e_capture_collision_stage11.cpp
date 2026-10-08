#include "types.h"

// Retained PS2 symbols name this object TObjCaptureCollision and give its
// method family in the order the GameCube text keeps: KillMyself, TDisp, Exec,
// SetParameter, ResetVariable, the destructor, the TObject* constructor,
// CreateInstance, EditOnChange and the initObj/endObj/startObj lifecycle
// functions. The "TObjCaptureCollision" class-name string in this unit's .data
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

struct sAngle {
	s32 x;
	s32 y;
	s32 z;
};

/* An unreferenced vector this family of units carries at the head of its
 * .rodata, the way an internal-linkage const from a shared header lands in
 * each translation unit that includes it. Its name and home are unknown. */
#pragma force_active on
static const Vec3 lbl_8_rodata_17B0 = { 0.0f, 1.5f, 0.0f };
#pragma force_active reset

struct SETDATA_PARAM {
	Vec3 position;
	sAngle angle;
	u32 flags;
	u8 pad1C[0x10];
	s32* params;
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
s32 CheckRangeOut__10TObjSetObjFv(void*);
}

class TObjSetObj : public SetObjHdr
{
public:
	virtual void EditOnChange(SETDATA_PARAM*);

	s32 CheckRangeOut() { return CheckRangeOut__10TObjSetObjFv(this); }
	s32 CheckMustKill() { return CheckMustKill__10TObjSetObjFv(this); }
};

extern "C" {
extern void* lbl_8042C10C;
extern void* lbl_8042C148;

void __ct__7TObjectFP7TObject(void*, void*);
void __dt__7TObjectFv(void*, s16);
void __dt__10TObjSetObjFv(void*, s16);
void* Malloc__9THeapCtrlFUi(void*, u32);
void Free__9THeapCtrlFPv(void*, void*);
void __ct__10TObjSetObjFv(void*);
}

class TObjCaptureCollision : public TObject, public TObjSetObj
{
public:
	Vec3 position;
	sAngle angle;

	BOOL KillMyself();
	virtual void TDisp();
	virtual void Exec();
	void SetParameter();
	void ResetVariable();
	inline virtual ~TObjCaptureCollision();
	static TObjCaptureCollision* CreateInstance();
	virtual void EditOnChange(SETDATA_PARAM*);
};

// The constructor and destructor are written against the object's storage:
// retail constructs and destroys the TObjSetObj base through out-of-line
// functions that keep their address names, which a C++ base-class call would
// rename. The compiler still generates the class vtable and its adjustor
// thunk from the virtual declarations above.
extern "C" {
TObjCaptureCollision* __ct__20TObjCaptureCollisionFP7TObject(TObjCaptureCollision*, TObject*);
TObjCaptureCollision* __dt__20TObjCaptureCollisionFv(TObjCaptureCollision*, s16);
extern void* __vt__20TObjCaptureCollision[];
}

#define SETOBJ(self) ((void*)((u8*)(self) + 0x28))

// The data names below are descriptive guesses. The lower bound is zero but
// lives in .data in retail beside the upper one.
extern "C" {
char* captureCollisionFieldNames[1] = { "NUMBER" };
#pragma explicit_zero_data on
s32 captureCollisionMinimum = 0;
#pragma explicit_zero_data reset
s32 captureCollisionMaximum   = 255;
char* CL_TObjCaptureCollision = "TObjCaptureCollision";
}

/* Allocations that construct the object are placement new-expressions in
 * retail: MWCC null-checks their result through a compiler temporary, the
 * shape it gives an object with a destructor-bearing subobject (the TObject
 * base). The object's constructor is the storage-level function above, so the
 * new-expressions construct this same-sized stand-in, whose default
 * constructor forwards to it the way TObjCaptureCollision() would. */
struct ObjectStorage {
	~ObjectStorage();
};

struct CaptureCollisionStorage : ObjectStorage {
	u8 data[sizeof(TObjCaptureCollision)];

	CaptureCollisionStorage()
	{
		__ct__20TObjCaptureCollisionFP7TObject((TObjCaptureCollision*)this, (TObject*)lbl_8042C10C);
	}
	static void* operator new(unsigned long size, void* heap)
	{
		return Malloc__9THeapCtrlFUi(heap, size);
	}
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
	u8 pad2C[0xC];
};

extern "C" {
SETOBJ_PARAM captureCollisionEntry;
void endObjCaptureCollision();
void initObjCaptureCollision();
void startObjCaptureCollision();
}

extern "C" void captureCollisionRegister()
{
	captureCollisionEntry.flags       = 0;
	captureCollisionEntry.field18     = 0;
	captureCollisionEntry.displayName = "CAPTURE COLLISION";
	captureCollisionEntry.init        = initObjCaptureCollision;
	captureCollisionEntry.end         = endObjCaptureCollision;
	captureCollisionEntry.create      = startObjCaptureCollision;
	captureCollisionEntry.field10     = 0;
	captureCollisionEntry.flags       = 0x20000;
	captureCollisionEntry.field18     = 0;
	captureCollisionEntry.field20     = 0x1E;
	captureCollisionEntry.id          = 0x65;
	captureCollisionEntry.count       = 4;
	captureCollisionEntry.field21     = 0;
	captureCollisionEntry.fieldTypes  = "i";
	captureCollisionEntry.fields      = captureCollisionFieldNames;
	if (captureCollisionEntry.fieldTypes != NULL)
		captureCollisionEntry.flags |= 8;
	else
		captureCollisionEntry.flags &= ~8;
}

__declspec(section ".ctors") void (*const captureCollisionCtorEntry)() = captureCollisionRegister;

extern "C" void startObjCaptureCollision()
{
	new (lbl_8042C148) CaptureCollisionStorage();
}

extern "C" void initObjCaptureCollision() { }

extern "C" void endObjCaptureCollision() { }

void TObjCaptureCollision::EditOnChange(SETDATA_PARAM* data)
{
	s32* value = data->params;
	s32* clamped;
	if (*value < captureCollisionMinimum) {
		clamped = &captureCollisionMinimum;
	} else if (*value > captureCollisionMaximum) {
		clamped = &captureCollisionMaximum;
	} else {
		clamped = value;
	}
	*value = *clamped;
}

// Retail keeps the allocation and the constructed object in separate registers
// here, which this unit reproduces only below the unit's optimization level.
#pragma optimization_level 3
TObjCaptureCollision* TObjCaptureCollision::CreateInstance()
{
	return (TObjCaptureCollision*)new (lbl_8042C148) CaptureCollisionStorage();
}
#pragma optimization_level reset

extern "C" TObjCaptureCollision* __ct__20TObjCaptureCollisionFP7TObject(
    TObjCaptureCollision* self, TObject* parent)
{
	__ct__7TObjectFP7TObject(self, parent);
	__ct__10TObjSetObjFv(SETOBJ(self));
	*(void***)((u8*)self + 0x18) = __vt__20TObjCaptureCollision;
	*(void***)((u8*)self + 0x2C) = __vt__20TObjCaptureCollision + 11;
	self->className              = CL_TObjCaptureCollision;
	self->objectSize             = sizeof(TObjCaptureCollision);
	self->ResetVariable();
	self->SetParameter();
	return self;
}

extern "C" TObjCaptureCollision* __dt__20TObjCaptureCollisionFv(
    TObjCaptureCollision* self, s16 flags)
{
	if (self != NULL) {
		*(void***)((u8*)self + 0x18) = __vt__20TObjCaptureCollision;
		*(void***)((u8*)self + 0x2C) = __vt__20TObjCaptureCollision + 11;
		__dt__10TObjSetObjFv(SETOBJ(self), 0);
		__dt__7TObjectFv(self, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, self);
		}
	}
	return self;
}

void TObjCaptureCollision::ResetVariable()
{
	position.x = position.y = position.z = 0.0f;
	angle.x = angle.y = angle.z = 0;
}

void TObjCaptureCollision::SetParameter()
{
	SETDATA_PARAM* data = frame;
	position            = data->position;
	data                = frame;
	angle               = data->angle;
}

void TObjCaptureCollision::Exec()
{
	if (KillMyself()) {
		signal |= 1;
	}
}

void TObjCaptureCollision::TDisp() { }

BOOL TObjCaptureCollision::KillMyself()
{
	if (CheckRangeOut() != 0 || CheckMustKill() != 0) {
		return TRUE;
	}
	return FALSE;
}
