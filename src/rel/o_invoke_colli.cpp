#include "types.h"

// The PS2 beta symbols identify o_invoke_colli.cpp and the complete
// TObjSetInvokeColli method family.  The GameCube vtable, constructor entry,
// registration record, and identical object sequence in nine stage overlays
// independently establish the retail translation-unit boundary.

struct Vec3 {
	f32 x, y, z;
};

struct SetData {
	Vec3 position;
	s8 mode;
	u8 leaderOnly;
	u8 pad0E[0x1E];
	void* values;
};

struct Motion {
	SetData* frame;
	void** vtable;
	u8 pad08[8];
};

struct ObjectEntry {
	char* name;
	void (*init)();
	void (*end)();
	void (*start)();
	void* reset;
	u32 flags;
	void* reserved;
	u16 id;
	u16 count;
	u8 category;
	u8 subtype;
	u8 pad22[2];
	char* fieldTypes;
	char** fieldNames;
};

#define BYTE(object, offset)  (*(u8*)((u8*)(object) + (offset)))
#define HALF(object, offset)  (*(u16*)((u8*)(object) + (offset)))
#define WORD(object, offset)  (*(u32*)((u8*)(object) + (offset)))
#define PTR(object, offset)   (*(void**)((u8*)(object) + (offset)))
#define FLOAT(object, offset) (*(f32*)((u8*)(object) + (offset)))

extern "C" {
void* fn_3_4EE40(void*);
void fn_80021824(void*);
void* fn_800211A8(void*);
int fn_80041B64(void*);
void* fn_800924E4();
void fn_80063E7C(void*, int);
int fn_8005B9F0(void*);
int fn_8005B8BC(void*);
int fn_8005B8D8(void*);
void fn_8003BC38(void*);
void dtor_8003C52C(void*, int);
void dtor_8005BD3C(void*, int);
void __dt__7TObjectFv(void*, int);
void __ct__7TObjectFP7TObject(void*, void*);
void fn_8005BE6C(void*);
void fn_8003C618(void*);
void fn_8003C200(void*, void*, int, int);
void fn_80021384(void*);
void* fn_80018A34(void*, u32);
void fn_800189A4(void*, void*);

extern void* lbl_8042C298;
extern void* lbl_8042C1A4;
extern void* lbl_8042C148;
extern void* lbl_8042C110;

extern u8 lbl_3_data_5640[];
extern u32 lbl_3_data_5820[];
extern void* lbl_3_data_5854[];

void fn_3_1A9B0();
void objDefaultPDisp();
void objDefaultImmAftSetRaster();
void objDefaultDebug();
void fn_80017854();
void objDefaultRender();
void fn_3_4FC90();
}

extern "C" const f32 InvokeZero;
extern "C" const f32 InvokeDefaultScale;
extern "C" const f32 InvokeDefaultDepth;
extern "C" const f32 InvokeHalf;
extern "C" void* InvokeVtable[];
extern "C" char* InvokeModeNames[];
extern "C" char* invokeCollisionFieldNames[];

class TObject
{
	u8 pad00[0x28];

public:
	TObject(TObject*);
	~TObject();
	static void* operator new(unsigned long size, void* heap) { return fn_80018A34(heap, size); }
};

struct TObjSetInvokeColli : TObject {
	Motion motion;
	u8 pad38[0x9C];
	void SetCommuicateFlag(u8, int);
	int CheckHitPlayer();
	TObjSetInvokeColli();
	TObjSetInvokeColli(TObject*);
};

struct InvokeObjectTable {
	u8 pad00[0x30];
	void* objects[1];
};
extern "C" void SetCommuicateFlag__18TObjSetInvokeColliFUci(void*, u8, int);

struct InvokeDispatchPrefix {
	u8 pad00[0x18];
};

struct InvokeDispatch : InvokeDispatchPrefix {
	virtual void Slot00();
	virtual void Slot01();
	virtual void Slot02();
	virtual void Slot03();
	virtual void Slot04();
	virtual void Slot05();
	virtual void Slot06();
	virtual void Slot07();
	virtual void Slot08();
	virtual void Slot09();
	virtual void Slot10();
	virtual void Slot11();
	virtual void SetCommunication(u8, int);
};

struct InvokeThunkPrimary {
	u8 pad04[0x24];
	virtual void PrimarySlot();
};

struct InvokeThunkSecondary {
	virtual void BaseSlot();
};

struct InvokeThunk : InvokeThunkPrimary, InvokeThunkSecondary {
	virtual void BaseSlot();
};

void InvokeThunk::BaseSlot()
{
	fn_3_4EE40(this);
}

void TObjSetInvokeColli::SetCommuicateFlag(u8 group, int value)
{
	void* self                 = this;
	InvokeObjectTable* objects = (InvokeObjectTable*)lbl_8042C298;
	u32 offset                 = group;
	void* found                = objects->objects[offset];
	void* object               = found;
	if (found != 0)
		goto loop_test;
	return;
loop_body: {
	if (HALF(object, 0x28) == WORD(self, 0xC0)) {
		void* storage = PTR(object, 0x30);
		if (storage != 0)
			*(int*)storage = value;
	}
	object = PTR(object, 0x38);
}
loop_test:
	if (object != 0)
		goto loop_body;
	return;
}

#pragma opt_common_subs off
#pragma opt_strength_reduction off
#pragma opt_loop_invariants off
#pragma opt_propagation off
static inline int CheckInvokeHit(TObjSetInvokeColli* self)
{
	SetData* data = *(SetData**)((u8*)self->motion.frame + 0x2C);
	if (data->leaderOnly == 1) {
		fn_80021824(&lbl_8042C1A4);
		void* node;
		void* player;
		while ((player = ((node = fn_800211A8(self->motion.pad08)) != 0 ? PTR(node, 4) : 0)) != 0) {
			int playerKind = fn_80041B64(PTR(player, 0x78));
			void* manager  = fn_800924E4();
			if (manager != 0
			    && playerKind == (s8)BYTE((u8*)manager + (s8)BYTE(manager, 0x3A), 0x110))
				return 1;
		}
	} else {
		return fn_800211A8(self->motion.pad08) != 0;
	}
	return 0;
}

#pragma force_active on
int TObjSetInvokeColli::CheckHitPlayer()
{
	return CheckInvokeHit(this);
}
#pragma force_active reset
#pragma opt_propagation reset
#pragma opt_loop_invariants reset
#pragma opt_strength_reduction reset
#pragma opt_common_subs reset

extern "C" void TDisp__18TObjSetInvokeColliFv(void* self)
{
	void* resource = PTR(self, 0xB8);
	if (resource != 0) {
		fn_80063E7C(resource, 1);
		PTR(self, 0xB8) = 0;
	}
}

#pragma opt_common_subs off
#pragma opt_strength_reduction off
#pragma opt_loop_invariants off
extern "C" void Exec__18TObjSetInvokeColliFv(void* self)
{
	SetData* data = *(SetData**)((u8*)PTR(self, 0x28) + 0x2C);
	if (fn_8005B9F0((u8*)self + 0x28) != 0 || fn_8005B8BC((u8*)self + 0x28) != 0) {
		HALF(self, 4) |= 1;
		return;
	}
	if (fn_8005B8D8((u8*)self + 0x28) != 0) {
		FLOAT(self, 0xC8) = data->position.x;
		FLOAT(self, 0xCC) = data->position.y;
		FLOAT(self, 0xD0) = data->position.z;
		return;
	}
	fn_80021824(&lbl_8042C1A4);
	if (((TObjSetInvokeColli*)self)->CheckHitPlayer()) {
		if ((int)WORD(self, 0xC4) == 0)
			((InvokeDispatch*)self)->SetCommunication(BYTE(PTR(self, 0x28), 0x2A), 0);
		else
			((InvokeDispatch*)self)->SetCommunication(BYTE(PTR(self, 0x28), 0x2A), 1);
	}
	SetData* frame    = (SetData*)PTR(self, 0x28);
	FLOAT(self, 0xAC) = FLOAT(self, 0x90);
	FLOAT(self, 0xB0) = FLOAT(self, 0x94);
	FLOAT(self, 0xB4) = FLOAT(self, 0x98);
	FLOAT(self, 0x90) = FLOAT(frame, 0);
	FLOAT(self, 0x94) = FLOAT(frame, 4);
	FLOAT(self, 0x98) = FLOAT(frame, 8);
	WORD(self, 0x9C)  = WORD(frame, 0xC);
	WORD(self, 0xA0)  = WORD(frame, 0x10);
	WORD(self, 0xA4)  = WORD(frame, 0x14);
	fn_8003BC38((u8*)self + 0x30);
}
#pragma opt_loop_invariants reset
#pragma opt_strength_reduction reset
#pragma opt_common_subs reset

#pragma opt_common_subs off
extern "C" void* __dt__18TObjSetInvokeColliFv(void* self, s16 flags)
{
	if (self != 0) {
		WORD(self, 0x18) = (u32)InvokeVtable;
		WORD(self, 0x2C) = (u32)InvokeVtable + 0x2C;
		void* resource   = PTR(self, 0xB8);
		if (resource != 0) {
			fn_80063E7C(resource, 1);
			PTR(self, 0xB8) = 0;
		}
		if (fn_8005B8D8((u8*)self + 0x28))
			((InvokeDispatch*)self)->SetCommunication(BYTE(PTR(self, 0x28), 0x2A), 0);
		dtor_8003C52C((u8*)self + 0x30, 0);
		dtor_8005BD3C((u8*)self + 0x28, 0);
		__dt__7TObjectFv(self, 0);
		if (flags > 0)
			fn_800189A4(lbl_8042C148, self);
	}
	return self;
}
#pragma opt_common_subs reset

#pragma opt_common_subs off
static inline void InitializeInvoke(void* self, void* parent)
{
	fn_8005BE6C((u8*)self + 0x28);
	fn_8003C618((u8*)self + 0x30);
	WORD(self, 0x18) = (u32)InvokeVtable;
	WORD(self, 0x2C) = (u32)InvokeVtable + 0x2C;
	void* frame      = PTR(self, 0x28);
	void* data       = PTR(frame, 0x2C);
	if (InvokeZero == FLOAT(data, 0) && InvokeZero == FLOAT(data, 4)
	    && InvokeZero == FLOAT(data, 8)) {
		FLOAT(data, 0) = InvokeDefaultScale;
		FLOAT(data, 4) = InvokeDefaultScale;
		FLOAT(data, 8) = InvokeDefaultDepth;
	}
	FLOAT(self, 0xC8) = FLOAT(data, 0);
	FLOAT(self, 0xCC) = FLOAT(data, 4);
	FLOAT(self, 0xD0) = FLOAT(data, 8);
	WORD(self, 0xC0)  = (u32)lbl_3_data_5854[(s8)BYTE(data, 0xC) * 2];
	WORD(self, 0xC4)  = (u32)lbl_3_data_5854[(s8)BYTE(data, 0xC) * 2 + 1];
	WORD(self, 0xBC)  = lbl_3_data_5820[0];
	WORD(self, 0xB8)  = 0;
	if (WORD(self, 0x40) == 0) {
		fn_8003C200((u8*)self + 0x30, lbl_3_data_5640, 1, 4);
		void* collision        = PTR(self, 0x40);
		FLOAT(collision, 0x14) = InvokeHalf * FLOAT(self, 0xC8);
		FLOAT(collision, 0x18) = InvokeHalf * FLOAT(self, 0xCC);
		FLOAT(collision, 0x1C) = InvokeHalf * FLOAT(self, 0xD0);
		fn_80021384((u8*)self + 0x30);
		HALF(self, 0x38) &= ~0x40;
	}
}
#pragma opt_common_subs reset

#pragma opt_common_subs off
#pragma force_active on
TObjSetInvokeColli::TObjSetInvokeColli(TObject* parent)
    : TObject(parent)
{
	InitializeInvoke(this, parent);
}
#pragma force_active reset
#pragma opt_common_subs reset

inline TObjSetInvokeColli::TObjSetInvokeColli()
    : TObject((TObject*)lbl_8042C110)
{
	InitializeInvoke(this, lbl_8042C110);
}

#pragma opt_propagation off
extern "C" void EditOnChange__18TObjSetInvokeColliFP13SETDATA_PARAM(void* self, SetData* set)
{
	f32* values = (f32*)set->values;
	{
		f32 zero;
		f32 value = values[0];
		zero      = InvokeZero;
		if (value < zero)
			values[0] = zero;
	}
	{
		f32 zero;
		f32 value = values[1];
		zero      = InvokeZero;
		if (value < zero)
			values[1] = zero;
	}
	{
		f32 zero;
		f32 value = values[2];
		zero      = InvokeZero;
		if (value < zero)
			values[2] = zero;
	}
	s8& mode = *(s8*)((u8*)values + 0xC);
	if (mode < 0)
		mode = 0;
	if (mode >= 10)
		mode = 9;
	u8& leader = *(u8*)((u8*)values + 0xD);
	if (leader > 1)
		leader = 1;
	WORD(self, 0xC0)             = (u32)lbl_3_data_5854[mode * 2];
	WORD(self, 0xC4)             = (u32)lbl_3_data_5854[mode * 2 + 1];
	invokeCollisionFieldNames[3] = InvokeModeNames[mode];
}
#pragma opt_propagation reset

#pragma optimization_level 2
#pragma opt_common_subs off
extern "C" void invokeCollisionCreate()
{
	new (lbl_8042C148) TObjSetInvokeColli();
}
#pragma opt_common_subs reset
#pragma optimization_level reset

extern "C" void invokeCollisionRegister();
extern "C" ObjectEntry invokeCollisionEntry;
extern "C" char invokeCollisionDisplayName[];
extern "C" char invokeCollisionFieldTypes[];

extern "C" void invokeCollisionRegister()
{
	invokeCollisionEntry.flags    = 0;
	invokeCollisionEntry.reserved = 0;

	invokeCollisionEntry.name  = invokeCollisionDisplayName;
	invokeCollisionEntry.init  = 0;
	invokeCollisionEntry.end   = 0;
	invokeCollisionEntry.start = invokeCollisionCreate;
	invokeCollisionEntry.reset = 0;

	invokeCollisionEntry.flags    = 0;
	invokeCollisionEntry.reserved = 0;
	invokeCollisionEntry.category = 0x32;
	invokeCollisionEntry.id       = 0x20B;
	invokeCollisionEntry.count    = 2;
	invokeCollisionEntry.subtype  = 0;

	invokeCollisionEntry.fieldTypes = invokeCollisionFieldTypes;
	invokeCollisionEntry.fieldNames = invokeCollisionFieldNames;

	if (invokeCollisionFieldTypes != 0)
		invokeCollisionEntry.flags |= 8;
	else
		invokeCollisionEntry.flags &= ~8;
}

__declspec(section ".ctors") void (*const invokeCollisionCtorEntry)() = invokeCollisionRegister;

extern "C" char InvokeScaleX[]               = "SCALE X";
extern "C" char InvokeScaleY[]               = "SCALE Y";
extern "C" char InvokeScaleZ[]               = "SCALE Z";
extern "C" char InvokeUniqueId[]             = "UNIQUE ID LIST";
extern "C" char InvokeOnlyLeader[]           = "OnlyLeader";
extern "C" char* invokeCollisionFieldNames[] = {
	InvokeScaleX,
	InvokeScaleY,
	InvokeScaleZ,
	InvokeUniqueId,
	InvokeOnlyLeader,
};
extern "C" char InvokeUnused[]      = "NOT IN USE";
extern "C" char InvokeBigElevator[] = "BIG ELEVATOR(0402)";
extern "C" char InvokeEnergyUp[]    = "ENERGY UP(0412)";
extern "C" char InvokeShutter[]     = "SHUTTER (0410)";
extern "C" char InvokeBallOn[]      = "BALLGLS ON (0480)";
extern "C" char InvokeBallOff[]     = "BALLGLS OFF (0480)";
extern "C" char InvokeSenkan[]      = "SENKAN MOV";
extern "C" char InvokeHakai[]       = "HAKAI(1320)";
extern "C" char InvokeFallAshiba[]  = "FALL ASHIBA(1400)";
extern "C" char* InvokeModeNames[]  = {
	InvokeUnused,
	InvokeUnused,
	InvokeBigElevator,
	InvokeEnergyUp,
	InvokeShutter,
	InvokeBallOn,
	InvokeBallOff,
	InvokeSenkan,
	InvokeHakai,
	InvokeFallAshiba,
};
extern "C" void* InvokeVtable[] = {
	0,
	0,
	(void*)__dt__18TObjSetInvokeColliFv,
	(void*)Exec__18TObjSetInvokeColliFv,
	(void*)fn_3_1A9B0,
	(void*)TDisp__18TObjSetInvokeColliFv,
	(void*)objDefaultPDisp,
	(void*)objDefaultImmAftSetRaster,
	(void*)objDefaultDebug,
	(void*)fn_80017854,
	(void*)objDefaultRender,
	0,
	0,
	(void*)fn_3_4FC90,
	(void*)SetCommuicateFlag__18TObjSetInvokeColliFUci,
	(void*)EditOnChange__18TObjSetInvokeColliFP13SETDATA_PARAM,
};
extern "C" char invokeCollisionDisplayName[] = "INVOKE COLLI";
extern "C" char invokeCollisionFieldTypes[]  = "FFFcC";

extern "C" {
ObjectEntry invokeCollisionEntry;
}

extern "C" __declspec(section ".rodata") const f32 InvokeZero         = 0.0f;
extern "C" __declspec(section ".rodata") const f32 InvokeDefaultScale = 100.0f;
extern "C" __declspec(section ".rodata") const f32 InvokeDefaultDepth = 10.0f;
extern "C" __declspec(section ".rodata") const f32 InvokeHalf         = 0.5f;
