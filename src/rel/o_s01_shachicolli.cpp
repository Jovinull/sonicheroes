#include "types.h"

// The PS2 beta symbol table identifies o_s01_shachicolli.cpp, the
// TObjS01ShachiColli class, its vtable, both lifecycle methods, Exec, the
// communication callback, and the static initializer.  The GameCube vtable,
// constructor entry, registration record, and contiguous data independently
// establish this retail TU.  The adjustor at 0x8A854 forwards to
// TObjS01Shachi::EditOnChange and therefore closes the preceding Shachi TU;
// this object's owned text begins with SetCommuicateFlag at 0x8A85C.

struct Vec3 {
	f32 x;
	f32 y;
	f32 z;
};

struct SETDATA_PARAM {
	Vec3 position;
	s32 angleX;
	s32 angleY;
	s32 angleZ;
	u32 flags;
	u8 pad1C[0x10];
	void* params;
};

struct Motion {
	SETDATA_PARAM* frame;
	void** vtable;
	u8 pad08[8];
};

class TObject;

extern "C" void fn_800189A4(void*, void*);
extern "C" void* lbl_8042C148;

class TObjS01ShachiColli
{
public:
	const char* className;
	u16 signal;
	u8 pad06[0x12];
	void** vtable;
	s16 pad1C;
	s16 objectSize;
	u8 pad20[8];
	Motion motion;
	u8 pad38[0x58];
	Vec3 position;
	u32 angleX;
	u32 angleY;
	u32 angleZ;
	u32 padA8;
	Vec3 oldPosition;
	void* resource;
	u32 color;
	u8 padC0[0xC];

	void SetCommuicateFlag(u8, s32);
	void Exec();
	TObjS01ShachiColli(TObject*);
	~TObjS01ShachiColli();
	static void operator delete(void* object) { fn_800189A4(lbl_8042C148, object); }
};

struct ShachiColliDispatchPrefix {
	u8 pad00[0x18];
};

struct ShachiColliDispatch : ShachiColliDispatchPrefix {
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
	virtual void Slot12();
	virtual void SetCommunication(u8, s32);
};

extern "C" {
extern void* lbl_8042C298;
extern void* lbl_8042C180;
extern void* lbl_8042C1A4;
extern void* lbl_8042C148;
extern void* lbl_8042C110;

extern void* lbl_3_data_A1BC;

s32 fn_8005B9F0(Motion*);
s32 fn_8005B8BC(Motion*);
s32 fn_8005B8D8(Motion*);
void fn_8005BC04(Motion*);
void fn_80021824(void*);
void* fn_800211A8(void*);
void fn_8003BC38(void*);
void fn_800189A4(void*, void*);
void* fn_80018A34(void*, u32);
void s01ObjectBaseUpdate(TObjS01ShachiColli*);
void s01ObjectBaseDtor(TObjS01ShachiColli*, s16);
void s01ObjectBaseCtor(TObjS01ShachiColli*, void*);

void fn_3_1A9B0();
extern "C" void TDisp__13TObjS01CisekiFv();
void PDisp__7TObjectFv();
void ImmAftSetRaster__7TObjectFv();
void Debug__7TObjectFv();
void Error__7TObjectFPc();
void Render__7TObjectFv();
void fn_3_7CCD0();
extern "C" void MotionNoop__13TObjS01CisekiFv();
void s01ObjectBaseNoop();
void s01ObjectBaseEditOnChange();
TObjS01ShachiColli* __dt__18TObjS01ShachiColliFv(TObjS01ShachiColli*, s16);
void Exec__18TObjS01ShachiColliFv(TObjS01ShachiColli*);
void SetCommuicateFlag__18TObjS01ShachiColliFUci(TObjS01ShachiColli*, u8, s32);
extern void* shachiColliVtable[18];
extern char* CL_TObjS01ShachiColli;
}

void TObjS01ShachiColli::SetCommuicateFlag(u8 group, s32 value)
{
	u8* objects = (u8*)lbl_8042C298;
	u32 offset  = group;
	offset <<= 2;
	objects += offset;
	void* found  = *(void**)(objects + 0x30);
	void* object = found;
	if (found != NULL)
		goto loop_test;
	goto done;
loop_body: {
	if (*(u16*)((u8*)object + 0x28) == 0x182) {
		void* storage = *(void**)((u8*)object + 0x30);
		if (storage != NULL)
			*(s32*)storage = value;
	}
	object = *(void**)((u8*)object + 0x38);
}
loop_test:
	if (object != NULL)
		goto loop_body;
done:
	return;
}

void TObjS01ShachiColli::Exec()
{
	if (fn_8005B9F0(&motion) != 0 || fn_8005B8BC(&motion) != 0) {
		signal |= 1;
		return;
	}
	if (*(s8*)((u8*)lbl_8042C180 + 0x1F) != 0)
		return;

	s01ObjectBaseUpdate(this);
	if (fn_8005B8D8(&motion) != 0)
		return;

	fn_80021824(&lbl_8042C1A4);
	void* entry = fn_800211A8(motion.pad08);
	void* active;
	if (entry != NULL)
		active = *(void**)((u8*)entry + 4);
	else
		active = NULL;
	if (active != NULL) {
		((ShachiColliDispatch*)this)->SetCommunication(motion.frame->pad1C[0xE], 1);
		return;
	}

	SETDATA_PARAM* frame = motion.frame;
	oldPosition          = position;
	position             = frame->position;
	angleX               = frame->angleX;
	angleY               = frame->angleY;
	angleZ               = frame->angleZ;
	fn_8003BC38((u8*)this + 0x30);
}

TObjS01ShachiColli::~TObjS01ShachiColli()
{
	vtable        = shachiColliVtable;
	motion.vtable = shachiColliVtable + 11;
	if (fn_8005B8D8(&motion) != 0)
		((ShachiColliDispatch*)this)->SetCommunication(motion.frame->pad1C[0xE], 0);
	fn_8005BC04(&motion);
	s01ObjectBaseDtor(this, 0);
}

TObjS01ShachiColli::TObjS01ShachiColli(TObject* parent)
{
	s01ObjectBaseCtor(this, parent);
	vtable        = shachiColliVtable;
	motion.vtable = shachiColliVtable + 11;
	className     = CL_TObjS01ShachiColli;
	objectSize    = 0xCC;
	color         = 0x2000FF00;
}

extern "C" void startObj_S01_ShachiColli()
{
	TObjS01ShachiColli* object
	    = (TObjS01ShachiColli*)fn_80018A34(lbl_8042C148, sizeof(TObjS01ShachiColli));
	if (object != NULL) {
		s01ObjectBaseCtor(object, lbl_8042C110);
		object->vtable        = shachiColliVtable;
		object->motion.vtable = shachiColliVtable + 11;
		object->className     = CL_TObjS01ShachiColli;
		object->objectSize    = 0xCC;
		object->color         = 0x2000FF00;
	}
}

extern "C" char shachiColliClassName[] = "TObjS01ShachiColli";
extern "C" char* CL_TObjS01ShachiColli = shachiColliClassName;

extern "C" void* shachiColliVtable[18] = {
	NULL,
	NULL,
	(void*)__dt__18TObjS01ShachiColliFv,
	(void*)Exec__18TObjS01ShachiColliFv,
	(void*)fn_3_1A9B0,
	(void*)TDisp__13TObjS01CisekiFv,
	(void*)PDisp__7TObjectFv,
	(void*)ImmAftSetRaster__7TObjectFv,
	(void*)Debug__7TObjectFv,
	(void*)Error__7TObjectFPc,
	(void*)Render__7TObjectFv,
	NULL,
	NULL,
	(void*)fn_3_7CCD0,
	(void*)MotionNoop__13TObjS01CisekiFv,
	(void*)SetCommuicateFlag__18TObjS01ShachiColliFUci,
	(void*)s01ObjectBaseNoop,
	(void*)s01ObjectBaseEditOnChange,
};

extern "C" char shachiColliDisplayName[] = "S01 COLLI FOR SHACHI";
extern "C" char shachiColliFieldTypes[]  = "FFF";

struct SETOBJ_PARAM {
	char* displayName;
	u32 field04;
	u32 field08;
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
	u32 pad2C;
};

extern "C" SETOBJ_PARAM ObjS01ShachiColliParam;

extern "C" void __sinit_o_s01_shachicolli_cpp()
{
	ObjS01ShachiColliParam.flags       = 0;
	ObjS01ShachiColliParam.field18     = 0;
	ObjS01ShachiColliParam.displayName = shachiColliDisplayName;
	ObjS01ShachiColliParam.field04     = 0;
	ObjS01ShachiColliParam.field08     = 0;
	ObjS01ShachiColliParam.create      = startObj_S01_ShachiColli;
	ObjS01ShachiColliParam.field10     = 0;
	ObjS01ShachiColliParam.flags       = 0;
	ObjS01ShachiColliParam.field18     = 0;
	ObjS01ShachiColliParam.field20     = 0x14;
	ObjS01ShachiColliParam.id          = 0x185;
	ObjS01ShachiColliParam.count       = 2;
	ObjS01ShachiColliParam.field21     = 0;
	ObjS01ShachiColliParam.fieldTypes  = shachiColliFieldTypes;
	ObjS01ShachiColliParam.fields      = &lbl_3_data_A1BC;
	if (ObjS01ShachiColliParam.fieldTypes != NULL)
		ObjS01ShachiColliParam.flags |= 8;
	else
		ObjS01ShachiColliParam.flags &= ~8;
}

extern "C" {
SETOBJ_PARAM ObjS01ShachiColliParam;
}

__declspec(section ".ctors") void (*const ShachiColliCtorEntry)() = __sinit_o_s01_shachicolli_cpp;
