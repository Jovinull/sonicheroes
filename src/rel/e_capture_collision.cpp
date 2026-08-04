#include "types.h"

struct RwV3d {
	f32 x, y, z;
};

struct sAngle {
	s32 x, y, z;
};

struct TObject;
struct ObjectRegistration;
struct SETDATA_PARAM {
	RwV3d position;
	sAngle angle;
	u8 unk18[0x14];
	s32* member;
};

class TObjCaptureCollisionPrimary
{
public:
	virtual ~TObjCaptureCollisionPrimary();
	virtual void Exec();
	virtual void Virtual2();
	virtual void TDisp();
	virtual void Virtual4();
	virtual void Virtual5();
	virtual void Virtual6();
	virtual void Virtual7();
	virtual void Virtual8();
	u8 data[0x24];
};

class TObjCaptureCollisionEditor
{
public:
	virtual void EditOnChange(SETDATA_PARAM*);
};

class TObjCaptureCollision : public TObjCaptureCollisionPrimary, public TObjCaptureCollisionEditor
{
public:
	u8 tail[0x1C];

	void EditOnChange(SETDATA_PARAM*);
	virtual ~TObjCaptureCollision();
	void TDisp();
	void Exec();
	bool KillMyself();
	void SetParameter();
	void ResetVariable();

	static TObjCaptureCollision* CreateInstance();
};

#define BYTES    ((u8*)this)
#define SET_DATA (*(SETDATA_PARAM**)(BYTES + 0x28))

static inline s32* ClampCaptureCollisionValue(s32* value, s32* minimum, s32* maximum)
{
	if (*value < *minimum)
		return minimum;
	if (*value > *maximum)
		return maximum;
	return value;
}

extern "C" {
int fn_8005B8BC(void*);
int fn_8005B9F0(void*);
void __ct__7TObjectFP7TObject();
void CaptureCollisionBaseCtor(void*, TObject*);
void fn_8005BE6C(void*);
void dtor_8005BD3C(void*, int);
void __dt__7TObjectFv(void*, int);
void* fn_80018A34(void*, u32);
void fn_800189A4(void*, void*);

extern void* lbl_8042C10C;
extern void* lbl_8042C148;

TObjCaptureCollision* __dt__20TObjCaptureCollisionFv(TObjCaptureCollision*, s16);
void Exec__20TObjCaptureCollisionFv();
void TDisp__20TObjCaptureCollisionFv();
void EditOnChange__20TObjCaptureCollisionFP13SETDATA_PARAM(TObjCaptureCollision*, SETDATA_PARAM*);
void TObjCaptureCollisionEditThunk();
void fn_3_1A9B0();
void objDefaultPDisp();
void objDefaultImmAftSetRaster();
void objDefaultDebug();
void fn_80017854();
void objDefaultRender();
}

extern "C" char TObjCaptureCollisionNumber[];
extern "C" char* TObjCaptureCollisionNumberPtr;
extern "C" s32 TObjCaptureCollisionMinimum;
extern "C" s32 TObjCaptureCollisionMaximum;
extern "C" char TObjCaptureCollisionClassName[];
extern "C" char* TObjCaptureCollisionClassNamePtr;
extern "C" void* TObjCaptureCollisionVtable[];
extern "C" char ObjCaptureCollisionName[];
extern "C" char ObjCaptureCollisionFieldTypes[];
extern "C" ObjectRegistration ObjCaptureCollision;
extern "C" const f32 TObjCaptureCollisionZero;

static inline char* GetCaptureCollisionVtable()
{
	return (char*)TObjCaptureCollisionVtable;
}

#pragma optimization_level 0
bool TObjCaptureCollision::KillMyself()
{
	if (fn_8005B9F0(BYTES + 0x28) || fn_8005B8BC(BYTES + 0x28))
		return true;
	return false;
}

void TObjCaptureCollision::TDisp() { }

#pragma optimization_level 1
void TObjCaptureCollision::Exec()
{
	int kill;
	if (fn_8005B9F0(BYTES + 0x28) || fn_8005B8BC(BYTES + 0x28))
		kill = 1;
	else
		kill = 0;
	if (kill)
		*(u16*)(BYTES + 4) |= 1;
}

void TObjCaptureCollision::SetParameter()
{
	SETDATA_PARAM* setData = SET_DATA;
	*(f32*)(BYTES + 0x30)  = setData->position.x;
	*(f32*)(BYTES + 0x34)  = setData->position.y;
	*(f32*)(BYTES + 0x38)  = setData->position.z;
	setData                = SET_DATA;
	*(s32*)(BYTES + 0x3C)  = setData->angle.x;
	*(s32*)(BYTES + 0x40)  = setData->angle.y;
	*(s32*)(BYTES + 0x44)  = setData->angle.z;
}
#pragma optimization_level 0

void TObjCaptureCollision::ResetVariable()
{
	*(f32*)(BYTES + 0x30) = *(f32*)(BYTES + 0x34) = *(f32*)(BYTES + 0x38)
	    = TObjCaptureCollisionZero;
	*(s32*)(BYTES + 0x3C) = *(s32*)(BYTES + 0x40) = *(s32*)(BYTES + 0x44) = 0;
}

#pragma optimization_level 2
extern "C" TObjCaptureCollision* __dt__20TObjCaptureCollisionFv(
    TObjCaptureCollision* object, s16 flags)
{
	if (object != 0) {
		u32 vtable                  = (u32)TObjCaptureCollisionVtable;
		*(u32*)((u8*)object + 0x18) = vtable;
		*(u32*)((u8*)object + 0x2C) = vtable + 0x2C;
		dtor_8005BD3C((u8*)object + 0x28, 0);
		__dt__7TObjectFv(object, 0);
		if (flags > 0)
			fn_800189A4(lbl_8042C148, object);
	}
	return object;
}

#pragma optimization_level 2
#pragma opt_common_subs off
#pragma opt_lifetimes off
#pragma no_register_coloring on
extern "C" TObjCaptureCollision* __ct__20TObjCaptureCollisionFP7TObject(
    TObjCaptureCollision* object, TObject* parent)
{
	__ct__7TObjectFP7TObject();
	fn_8005BE6C((u8*)object + 0x28);
	register char* vtable         = GetCaptureCollisionVtable();
	*(char**)((u8*)object + 0x18) = vtable;
	*(char**)((u8*)object + 0x2C) = vtable + 0x2C;
	*(char**)object               = TObjCaptureCollisionClassNamePtr;
	*(u16*)((u8*)object + 0x1E)   = 0x48;
	object->ResetVariable();
	object->SetParameter();
	return object;
}
#pragma opt_common_subs reset

#pragma optimization_level 2
#pragma opt_common_subs off
inline void* operator new(unsigned long, void* address) throw()
{
	return address;
}

class CaptureCollisionInitializer
{
public:
	u8 data[0x48];

	inline CaptureCollisionInitializer(TObject* parent) { InitializeObject(this, parent); }

	static inline void InitializeObject(CaptureCollisionInitializer* self, TObject* parent)
	{
		TObjCaptureCollision* object = (TObjCaptureCollision*)self;
		CaptureCollisionBaseCtor(object, parent);
		fn_8005BE6C((u8*)object + 0x28);
		u32 vtable                  = (u32)TObjCaptureCollisionVtable;
		*(u32*)((u8*)object + 0x18) = vtable;
		*(u32*)((u8*)object + 0x2C) = vtable + 0x2C;
		*(char**)object             = TObjCaptureCollisionClassNamePtr;
		*(u16*)((u8*)object + 0x1E) = 0x48;
		object->ResetVariable();
		object->SetParameter();
	}
};

TObjCaptureCollision* TObjCaptureCollision::CreateInstance()
{
	TObjCaptureCollision* allocation = (TObjCaptureCollision*)fn_80018A34(lbl_8042C148, 0x48);
	if (allocation != 0)
		new (allocation) CaptureCollisionInitializer((TObject*)lbl_8042C10C);
	return allocation;
}
#pragma opt_common_subs reset
#pragma opt_lifetimes reset
#pragma no_register_coloring off

#pragma optimization_level 2
#pragma opt_propagation off
void TObjCaptureCollision::EditOnChange(SETDATA_PARAM* setData)
{
	s32* value = setData->member;
	*value     = *ClampCaptureCollisionValue(
	    value, &TObjCaptureCollisionMinimum, &TObjCaptureCollisionMaximum);
}
#pragma opt_propagation reset
#pragma optimization_level 0

extern "C" void endObjCaptureCollision() { }

extern "C" void initObjCaptureCollision() { }

#pragma optimization_level 2
#pragma opt_common_subs off
#pragma opt_lifetimes off
#pragma no_register_coloring on
extern "C" void startObjCaptureCollision()
{
#pragma opt_propagation off
	void* allocation = fn_80018A34(lbl_8042C148, 0x48);
	if (allocation != 0) {
		register CaptureCollisionInitializer* object = (CaptureCollisionInitializer*)allocation;
		CaptureCollisionInitializer::InitializeObject(object, (TObject*)lbl_8042C10C);
	}
}
#pragma opt_common_subs reset
#pragma opt_lifetimes reset
#pragma no_register_coloring off
#pragma optimization_level 0

struct ObjectRegistration {
	char* name;
	void (*init)();
	void (*end)();
	void (*start)();
	void* reserved;
	u32 flags;
	void* reserved2;
	u16 id;
	u16 count;
	u8 category;
	u8 subtype;
	char* fieldTypes;
	char** fieldName;
	u8 padding[4];
};

#pragma optimization_level 4
extern "C" ObjectRegistration ObjCaptureCollision;

extern "C" void __sinit_e_capture_collision_cpp()
{
	ObjCaptureCollision.flags      = 0;
	ObjCaptureCollision.reserved2  = 0;
	ObjCaptureCollision.name       = ObjCaptureCollisionName;
	ObjCaptureCollision.init       = initObjCaptureCollision;
	ObjCaptureCollision.end        = endObjCaptureCollision;
	ObjCaptureCollision.start      = startObjCaptureCollision;
	ObjCaptureCollision.reserved   = 0;
	ObjCaptureCollision.flags      = 0x20000;
	ObjCaptureCollision.reserved2  = 0;
	ObjCaptureCollision.category   = 30;
	ObjCaptureCollision.id         = 101;
	ObjCaptureCollision.count      = 4;
	ObjCaptureCollision.subtype    = 0;
	ObjCaptureCollision.fieldTypes = ObjCaptureCollisionFieldTypes;
	ObjCaptureCollision.fieldName  = &TObjCaptureCollisionNumberPtr;
	if (ObjCaptureCollisionFieldTypes != 0)
		ObjCaptureCollision.flags |= 8;
	else
		ObjCaptureCollision.flags &= ~8;
}

__declspec(section ".ctors") void (*const TObjCaptureCollisionCtorEntry)()
    = __sinit_e_capture_collision_cpp;

extern "C" {
ObjectRegistration ObjCaptureCollision;
}

extern "C" char TObjCaptureCollisionNumber[]   = "NUMBER";
extern "C" char* TObjCaptureCollisionNumberPtr = TObjCaptureCollisionNumber;
// Corrected to zero by the object-layout normalizer; a nonzero initializer
// keeps this mutable bound in .data, as in the retail object.
extern "C" s32 TObjCaptureCollisionMinimum        = 1;
extern "C" s32 TObjCaptureCollisionMaximum        = 255;
extern "C" char TObjCaptureCollisionClassName[]   = "TObjCaptureCollision";
extern "C" char* TObjCaptureCollisionClassNamePtr = TObjCaptureCollisionClassName;
extern "C" void* TObjCaptureCollisionVtable[]     = {
	0,
	0,
	(void*)__dt__20TObjCaptureCollisionFv,
	(void*)Exec__20TObjCaptureCollisionFv,
	(void*)fn_3_1A9B0,
	(void*)TDisp__20TObjCaptureCollisionFv,
	(void*)objDefaultPDisp,
	(void*)objDefaultImmAftSetRaster,
	(void*)objDefaultDebug,
	(void*)fn_80017854,
	(void*)objDefaultRender,
	0,
	0,
	(void*)TObjCaptureCollisionEditThunk,
	(void*)EditOnChange__20TObjCaptureCollisionFP13SETDATA_PARAM,
};
extern "C" char ObjCaptureCollisionName[]       = "CAPTURE COLLISION";
extern "C" char ObjCaptureCollisionFieldTypes[] = "i";

__declspec(section ".rodata") const f32 TObjCaptureCollisionZero = 0.0f;
