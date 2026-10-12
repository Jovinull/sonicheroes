#include "types.h"

// Retained PS2 symbols name this object TObjS11Door and give its method family
// in the order the GameCube text keeps: DestroyClump, CloneClump, SetPosition,
// SetParameter, Disp, IsnotThereAnySameCommunicateId, Exec, the destructor,
// the TObject* constructor, EditOnChange and the endObj/initObj/startObj
// lifecycle functions. The "TObjS11Door" class-name string in this unit's
// .data correlates the GameCube object with that family.
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
static const Vec3 lbl_8_rodata_1628 = { 0.0f, 1.5f, 0.0f };
#pragma force_active reset

struct DoorParam {
	s8 direction;
};

struct SETDATA_PARAM {
	Vec3 position;
	sAngle angle;
	u32 flags;
	u8 pad1C[0xE];
	u8 group;
	u8 pad2B[1];
	DoorParam* params;
};

/* One entry of the stage's per-group set-object lists. */
struct SetObjNode {
	u8 pad00[0x38];
	SetObjNode* next;
};

struct ObjectManager {
	u8 pad000[0x30];
	SetObjNode* lists[1];
};

struct RwMatrix {
	u8 pad00[0x40];
};

struct RwFrame {
	u8 pad00[0x10];
	RwMatrix modelling;
};

struct RpClump {
	u8 pad00[4];
	RwFrame* frame;
};

struct CCL_INFO {
	u32 attribute;
	u32 flags;
	f32 params[6];
	u32 pad20[4];
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
extern void* lbl_8042C1D0;
extern ObjectManager* lbl_8042C298;
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
s32 IsAnnihilated__19nEnemyCommunicationFUc(u8);
s32 objGroupAllActive();
void fn_800B52E8(void*, s32, s32, s32);
RpClump* LoadClumpEx__7ONEFILEFUiPc(void*, s32, void*);
s32 CheckFileID__7ONEFILEFPc(void*, const char*);
void LoadOneFile__7ONEFILEFPc(void*, void*);
f32 fn_800D7AE4(s32);
f32 fn_800D7B00(s32);
RpClump* fn_80150588(RpClump*);
void fn_80150958(RpClump*);
void fn_8015BB08(void*, RpClump*);
void fn_8015BBF8(void*, RpClump*);
void fn_80195790(void*, void*, f32, f32, s32);
void fn_8019E880(RwFrame*);
void fn_8019EB94(RwFrame*, Vec3*, s32);
void fn_801A4C84(void*);
}

class TObjS11Door : public TObject, public TObjSetObj, public C_COLLI
{
public:
	Vec3 position;
	sAngle angle;
	s32 state;
	s32 timer;
	s32 direction;
	s32 rightStopped;
	s32 leftStopped;
	s32 rightSpeed;
	s32 leftSpeed;
	s32 rightAngle;
	s32 leftAngle;
	RpClump* clumps[2];

	void DestroyClump();
	void CloneClump();
	inline void CloneClumpOnCreate();
	void SetPosition();
	void SetParameter();
	virtual void Disp();
	u8 IsnotThereAnySameCommunicateId();
	virtual void Exec();
	inline virtual ~TObjS11Door();
	TObjS11Door(TObject*);
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
TObjS11Door* __dt__11TObjS11DoorFv(TObjS11Door*, s16);
extern void* __vt__11TObjS11Door[];
}

// The data names below are address names; their roles are descriptive guesses.
extern "C" {
u8 lbl_8_data_15130 = 0x40;
u8 lbl_8_data_15131 = 0x40;
#pragma explicit_zero_data on
RpClump* lbl_8_data_15134[2] = { NULL, NULL };
#pragma explicit_zero_data reset
char* lbl_8_data_15164[2]        = { "s11_on_doorr.dff", "s11_on_doorl.dff" };
s32 lbl_8_data_1516C[2]          = { -0x4000, 0x4000 };
s32 lbl_8_data_15174             = 24;
f32 lbl_8_data_15178             = 0.99f;
f32 lbl_8_data_1517C             = 0.3333f;
f32 lbl_8_data_15180             = -0.75f;
f32 lbl_8_data_15184             = 0.75f;
s32 lbl_8_data_15188             = 15;
char* s11doorObjectFieldNames[1] = { "direction : up" };
char* lbl_8_data_151B4[2]        = { "direction : up", "direction : down" };
CCL_INFO lbl_8_data_151BC[3]     = {
	{ 0x4FFE0, 0, { 0.0f, 40.0f, 3.5f, 35.0f, 45.0f, 3.5f } },
	{ 0x4FFE0, 0x10, { 30.0f, 40.0f, -15.0f, 5.0f, 40.0f, 15.0f } },
	{ 0x4FFE0, 0x10, { -30.0f, 40.0f, -15.0f, 5.0f, 40.0f, 15.0f } },
};
CCL_INFO lbl_8_data_1524C[3] = {
	{ 0x4FFE0, 0, { 0.0f, -40.0f, 3.5f, 35.0f, 45.0f, 3.5f } },
	{ 0x4FFE0, 0x10, { 30.0f, -40.0f, -15.0f, 5.0f, 40.0f, 15.0f } },
	{ 0x4FFE0, 0x10, { -30.0f, -40.0f, -15.0f, 5.0f, 40.0f, 15.0f } },
};
char* lbl_8_data_152E8 = "TObjS11Door";
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
SETOBJ_PARAM s11doorObjectEntry;
void s11doorObjectUnload();
void s11doorObjectLoad();
void s11doorObjectCreate();
}

extern "C" void s11doorObjectRegister()
{
	s11doorObjectEntry.flags       = 0;
	s11doorObjectEntry.field18     = 0;
	s11doorObjectEntry.displayName = "S11DOOR OBJECT";
	s11doorObjectEntry.init        = s11doorObjectLoad;
	s11doorObjectEntry.end         = s11doorObjectUnload;
	s11doorObjectEntry.create      = s11doorObjectCreate;
	s11doorObjectEntry.field10     = 0;
	s11doorObjectEntry.flags       = 0x20000;
	s11doorObjectEntry.field18     = 0;
	s11doorObjectEntry.field20     = 0x1E;
	s11doorObjectEntry.id          = 0x1101;
	s11doorObjectEntry.count       = 2;
	s11doorObjectEntry.field21     = 0;
	s11doorObjectEntry.fieldTypes  = "c";
	s11doorObjectEntry.fields      = s11doorObjectFieldNames;
	if (s11doorObjectEntry.fieldTypes != NULL)
		s11doorObjectEntry.flags |= 8;
	else
		s11doorObjectEntry.flags &= ~8;
}

__declspec(section ".ctors") void (*const s11doorObjectCtorEntry)() = s11doorObjectRegister;

extern "C" void s11doorObjectCreate()
{
	new (lbl_8042C148) TObjS11Door((TObject*)lbl_8042C110);
}

extern "C" void s11doorObjectLoad()
{
	void* stage = *(void**)((u8*)lbl_8042C1D0 + 0x8C18);
	if (stage != NULL) {
		fn_801A4C84(stage);
	} else {
		return;
	}
	LoadOneFile__7ONEFILEFPc(*(void**)((u8*)lbl_8042C298 + 0xA50), &lbl_802FF5A0);
	for (int i = 0; i < 2; i++) {
		lbl_8_data_15134[i] = LoadClumpEx__7ONEFILEFUiPc(*(void**)((u8*)lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)((u8*)lbl_8042C298 + 0xA50), lbl_8_data_15164[i]),
		    &lbl_802FF5A0);
	}
}

extern "C" void s11doorObjectUnload()
{
	for (int i = 0; i < 2; i++) {
		if (lbl_8_data_15134[i] != NULL) {
			fn_80150958(lbl_8_data_15134[i]);
			lbl_8_data_15134[i] = NULL;
		}
	}
}

void TObjS11Door::EditOnChange(SETDATA_PARAM* data)
{
	DoorParam* params = data->params;
	if (params->direction < 0)
		params->direction = 0;
	if (params->direction > 1)
		params->direction = 1;
	s11doorObjectFieldNames[0] = lbl_8_data_151B4[params->direction];
}

// CloneClump() as the constructor runs it. Retail's constructor reads the frame
// flags ahead of reloading the clump, unlike the method; the shared Stage 11
// constructors force that read order through a volatile view.
inline void TObjS11Door::CloneClumpOnCreate()
{
	for (int i = 0; i < 2; i++) {
		if (clumps[i] == NULL) {
			clumps[i] = fn_80150588(lbl_8_data_15134[i]);
			fn_8015BB08(*(void**)((u8*)lbl_8042C1D0 + 0x725C), clumps[i]);
			u32 flags = *(volatile u32*)&frame->flags;
			objRpClumpForAllAtomicsToSetRenderCallbackToUseLight__FP7RpClumpUi(
			    clumps[i], ((flags & 0x1C0000) >> 18) + 4);
		}
	}
}

TObjS11Door::TObjS11Door(TObject* parent)
    : TObject(parent)
{
	className  = lbl_8_data_152E8;
	objectSize = sizeof(TObjS11Door);
	SetParameter();
	clumps[0] = clumps[1] = NULL;
	rightSpeed = leftSpeed = 0;
	rightStopped = leftStopped = 0;
	if (frame->flags & 0x10000) {
		rightAngle = lbl_8_data_1516C[0];
		leftAngle  = lbl_8_data_1516C[1];
	} else {
		rightAngle = leftAngle = 0;
	}
	CloneClumpOnCreate();
	SetPosition();
	if (OnEdit() == 0) {
		if (direction == 1) {
			Init(lbl_8_data_1524C, 3, 4);
		} else {
			Init(lbl_8_data_151BC, 3, 4);
		}
		if (frame->flags & 0x10000) {
			shape[0].flags |= 0x10;
			shape[1].flags &= ~0x10;
			shape[2].flags &= ~0x10;
			CalcRange();
		}
	}
}

extern "C" TObjS11Door* __dt__11TObjS11DoorFv(TObjS11Door* self, s16 flags)
{
	if (self != NULL) {
		*(void***)((u8*)self + 0x18) = __vt__11TObjS11Door;
		*(void***)((u8*)self + 0x2C) = __vt__11TObjS11Door + 11;
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

void TObjS11Door::Exec()
{
	if (CheckRangeOut() != 0 || CheckMustKill() != 0) {
		signal |= 1;
		return;
	}
	switch (state) {
		case 0:
			if ((IsnotThereAnySameCommunicateId() != 0 || objGroupAllActive() != 0)
			    && IsAnnihilated__19nEnemyCommunicationFUc(frame->group)) {
				state = 1;
				if (lbl_8042C388 != NULL) {
					fn_800B52E8(lbl_8042C388, 0x5A02, (s8)lbl_8_data_15130, 0);
				}
				frame->flags |= 0x10000;
				timer = 0;
			}
			break;
		case 1:
			if (rightStopped == 0) {
				timer++;
				if (timer == lbl_8_data_15188) {
					shape[0].flags |= 0x10;
					shape[1].flags &= ~0x10;
					CalcRange();
				}
				rightSpeed -= lbl_8_data_15174;
				rightSpeed = rightSpeed * lbl_8_data_15178;
				rightAngle += rightSpeed;
				if (rightAngle < lbl_8_data_1516C[0]) {
					rightStopped = 1;
					if (lbl_8042C388 != NULL) {
						fn_800B52E8(lbl_8042C388, 0x5A03, (s8)lbl_8_data_15131, 0);
					}
					rightSpeed = rightSpeed * lbl_8_data_1517C;
					timer      = 0;
				}
			} else {
				rightSpeed = rightSpeed + lbl_8_data_15180 * (rightAngle - lbl_8_data_1516C[0]);
				rightSpeed = rightSpeed * lbl_8_data_15184;
				rightAngle += rightSpeed;
				timer++;
			}
			if (leftStopped == 0) {
				if (timer == lbl_8_data_15188) {
					shape[0].flags |= 0x10;
					shape[2].flags &= ~0x10;
					CalcRange();
				}
				leftSpeed += lbl_8_data_15174;
				leftSpeed = leftSpeed * lbl_8_data_15178;
				leftAngle += leftSpeed;
				if (leftAngle > lbl_8_data_1516C[1]) {
					leftStopped = 1;
					if (lbl_8042C388 != NULL) {
						fn_800B52E8(lbl_8042C388, 0x5A03, (s8)lbl_8_data_15131, 0);
					}
					leftSpeed = leftSpeed * lbl_8_data_1517C;
				}
			} else {
				leftSpeed = leftSpeed + lbl_8_data_15180 * (leftAngle - lbl_8_data_1516C[1]);
				leftSpeed = leftSpeed * lbl_8_data_15184;
				leftAngle += leftSpeed;
			}
			if (timer > 60.0f) {
				state = 2;
			}
			SetPosition();
			break;
		case 2:
			break;
	}
	previous          = C_COLLI::position;
	C_COLLI::position = position;
	C_COLLI::angle    = angle;
	Entry();
}

u8 TObjS11Door::IsnotThereAnySameCommunicateId()
{
	SetObjNode* node = lbl_8042C298->lists[frame->group];
	return node == (SetObjNode*)frame && node->next == NULL;
}

void TObjS11Door::Disp() { }

void TObjS11Door::SetParameter()
{
	SETDATA_PARAM* data = frame;
	DoorParam* params   = data->params;
	position            = data->position;
	data                = frame;
	angle               = data->angle;
	angle.z             = 0;
	angle.x             = 0;
	if (frame->flags & 0x10000) {
		state = 2;
	} else {
		state = 0;
	}
	direction = params->direction;
	timer     = 0;
}

void TObjS11Door::SetPosition()
{
	Vec3 offsets[2]  = { { 30.0f, 0.0f, 0.0f }, { -30.0f, 0.0f, 0.0f } };
	RwFrame* rwFrame = clumps[0]->frame;
	fn_8019EB94(rwFrame, &position, 0);
	fn_80195790(&rwFrame->modelling, &AxisY, 1.0f - fn_800D7AE4(angle.y), fn_800D7B00(angle.y), 1);
	fn_8019E880(rwFrame);
	if (direction == 1) {
		fn_80195790(
		    &rwFrame->modelling, &AxisZ, 1.0f - fn_800D7AE4(0x8000), fn_800D7B00(0x8000), 1);
		fn_8019E880(rwFrame);
	}
	fn_8019EB94(rwFrame, &offsets[0], 1);
	fn_80195790(
	    &rwFrame->modelling, &AxisY, 1.0f - fn_800D7AE4(rightAngle), fn_800D7B00(rightAngle), 1);
	fn_8019E880(rwFrame);
	rwFrame = clumps[1]->frame;
	fn_8019EB94(rwFrame, &position, 0);
	fn_80195790(&rwFrame->modelling, &AxisY, 1.0f - fn_800D7AE4(angle.y), fn_800D7B00(angle.y), 1);
	fn_8019E880(rwFrame);
	if (direction == 1) {
		fn_80195790(
		    &rwFrame->modelling, &AxisZ, 1.0f - fn_800D7AE4(0x8000), fn_800D7B00(0x8000), 1);
		fn_8019E880(rwFrame);
	}
	fn_8019EB94(rwFrame, &offsets[1], 1);
	fn_80195790(
	    &rwFrame->modelling, &AxisY, 1.0f - fn_800D7AE4(leftAngle), fn_800D7B00(leftAngle), 1);
	fn_8019E880(rwFrame);
}

void TObjS11Door::CloneClump()
{
	for (int i = 0; i < 2; i++) {
		if (clumps[i] == NULL) {
			clumps[i] = fn_80150588(lbl_8_data_15134[i]);
			fn_8015BB08(*(void**)((u8*)lbl_8042C1D0 + 0x725C), clumps[i]);
			objRpClumpForAllAtomicsToSetRenderCallbackToUseLight__FP7RpClumpUi(
			    clumps[i], ((frame->flags & 0x1C0000) >> 18) + 4);
		}
	}
}

void TObjS11Door::DestroyClump()
{
	for (int i = 0; i < 2; i++) {
		if (clumps[i] != NULL) {
			fn_8015BBF8(*(void**)((u8*)lbl_8042C1D0 + 0x725C), clumps[i]);
			fn_80150958(clumps[i]);
			clumps[i] = NULL;
		}
	}
}
