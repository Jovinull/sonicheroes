#include "types.h"

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

struct CisekiParams {
	f32 x;
	f32 y;
	f32 z;
	s8 type;
	u8 pad0D[3];
};

struct CisekiThunkPrimary {
	u8 pad04[0x24];
	virtual void PrimarySlot();
};

struct CisekiThunkSecondary {
	virtual void EditOnChange(SETDATA_PARAM*);
};

struct CisekiThunk : CisekiThunkPrimary, CisekiThunkSecondary {
	virtual void EditOnChange(SETDATA_PARAM*);
};

struct Motion {
	SETDATA_PARAM* frame;
	void** vtable;
	u8 pad08[8];
};

extern "C" void fn_800189A4(void*, void*);
extern "C" void* lbl_8042C148;

class TObject;

class TObjS01Ciseki
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

	void SetCommuicateFlag(u8, s32, u16*, u16);
	void SetCommuicateFlag(u8, s32);
	void Exec();
	void TDisp();
	void MotionNoop();
	TObjS01Ciseki(TObject*);
	~TObjS01Ciseki();
	static void operator delete(void* object) { fn_800189A4(lbl_8042C148, object); }
};

extern "C" {
extern void* lbl_8042C298;
extern void* lbl_8042C148;
extern void* lbl_8042C110;
extern void* lbl_8042C1A4;

extern void* lbl_3_data_9ED4[];
extern void* lbl_3_data_9F04[];
extern void* lbl_3_data_9F0C;
extern void* lbl_3_data_9F14;

void* fn_80057644(u32);
s32 fn_8005B9F0(Motion*);
s32 fn_8005B8BC(Motion*);
s32 fn_8005B8D8(Motion*);
void fn_80021824(void*);
void* fn_800211A8(void*);
void fn_8003BC38(void*);
void fn_800189A4(void*, void*);
void* fn_80018A34(void*, u32);
void fn_80063E7C(void*, s32);
void s01ObjectBaseUpdate(TObjS01Ciseki*);
void s01ObjectBaseDtor(TObjS01Ciseki*, s16);
void fn_3_7CB30(TObjS01Ciseki*, void*);

void fn_3_1A9B0();
void objDefaultPDisp();
void objDefaultImmAftSetRaster();
void objDefaultDebug();
void fn_80017854();
void objDefaultRender();

TObjS01Ciseki* __dt__13TObjS01CisekiFv(TObjS01Ciseki*, s16);
TObjS01Ciseki* __ct__13TObjS01CisekiFP7TObject(TObjS01Ciseki*, void*);
void Exec__13TObjS01CisekiFv(TObjS01Ciseki*);
void TDisp__13TObjS01CisekiFv(TObjS01Ciseki*);
void MotionNoop__13TObjS01CisekiFv(TObjS01Ciseki*);
void SetCommuicateFlag__13TObjS01CisekiFUci(TObjS01Ciseki*, u8, s32);
void SetCommuicateFlag__13TObjS01CisekiFUciPUsUs(TObjS01Ciseki*, u8, s32, u16*, u16);
void EditOnChange__11CisekiThunkFP13SETDATA_PARAM(CisekiThunk*, SETDATA_PARAM*);
void AdjustorEditOnChange__11CisekiThunkFP13SETDATA_PARAM(CisekiThunk*, SETDATA_PARAM*);
extern void* cisekiVtable[18];
extern char* CL_TObjS01Ciseki;
}

extern "C" const f32 cisekiPadding = 0.0f;

static inline void setCommunicationValue(void* object, s32 value)
{
	void** storage = *(void***)((u8*)object + 0x30);
	if (storage != NULL) {
		*storage = (void*)value;
	} else {
		storage = (void**)fn_80057644(4);
		if (storage != NULL) {
			*storage                       = (void*)value;
			*(void***)((u8*)object + 0x30) = storage;
		}
	}
}

extern "C" void continueObjS01Ciseki() { }

#pragma opt_propagation off
void TObjS01Ciseki::SetCommuicateFlag(u8 group, s32 value, u16*, u16 count)
{
	u8* objects = (u8*)lbl_8042C298;
	u32 offset  = group;
	offset <<= 2;
	objects += offset;
	void* found  = *(void**)(objects + 0x30);
	void* object = found;
	if (found != NULL)
		goto outer_test;
	goto done;
outer_body:
	u16 i = 0;
	goto inner_test;
inner_body:
	setCommunicationValue(object, value);
	++i;
inner_test:
	if (i < count)
		goto inner_body;
	object = *(void**)((u8*)object + 0x38);
outer_test:
	if (object != NULL)
		goto outer_body;
done:
	return;
}

void TObjS01Ciseki::SetCommuicateFlag(u8 group, s32 value)
{
	u8* objects = (u8*)lbl_8042C298;
	u32 offset  = group;
	offset <<= 2;
	objects += offset;
	void* found  = *(void**)(objects + 0x30);
	void* object = found;
	if (found != NULL)
		goto outer_test;
	goto done;
loop_entry:
	goto outer_test;
outer_body:
	u16 id = *(u16*)((u8*)object + 0x28);
	if ((u16)(id - 0x105) <= 1 || id == 0x107)
		setCommunicationValue(object, value);
	object = *(void**)((u8*)object + 0x38);
outer_test:
	if (object != NULL)
		goto outer_body;
done:
	return;
}
#pragma opt_propagation reset

typedef void (*CommunicationMethod)(TObjS01Ciseki*, u8, s32, void*, s32);

struct CisekiDispatchPrefix {
	u8 pad00[0x18];
};

struct CisekiDispatch : CisekiDispatchPrefix {
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
	virtual void Slot13();
	virtual void SetCommunication(u8, s32, void*, s32);
};

static inline void callCommunication(TObjS01Ciseki* object, s32 enabled, CisekiParams* params)
{
	switch (params->type) {
		case 0:
			((CisekiDispatch*)object)
			    ->SetCommunication(object->motion.frame->pad1C[0xE], enabled, &lbl_3_data_9F0C, 3);
			break;
		case 1:
			((CisekiDispatch*)object)
			    ->SetCommunication(object->motion.frame->pad1C[0xE], enabled, &lbl_3_data_9F14, 2);
			break;
	}
}

void TObjS01Ciseki::Exec()
{
	CisekiParams* params = (CisekiParams*)motion.frame->params;
	if (fn_8005B9F0(&motion) != 0 || fn_8005B8BC(&motion) != 0) {
		signal |= 1;
		return;
	}

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
	if (active != NULL)
		callCommunication(this, 1, params);

	SETDATA_PARAM* frame = motion.frame;
	oldPosition          = position;
	position             = frame->position;
	angleX               = frame->angleX;
	angleY               = frame->angleY;
	angleZ               = frame->angleZ;
	fn_8003BC38((u8*)this + 0x30);
}

void CisekiThunk::EditOnChange(SETDATA_PARAM* frame)
{
	CisekiParams* params = (CisekiParams*)frame->params;
	if (params->x < 0.0f)
		params->x = 0.0f;
	if (params->y < 0.0f)
		params->y = 0.0f;
	if (params->z < 0.0f)
		params->z = 0.0f;
	if (params->type < 0)
		params->type = 0;
	if (params->type >= 2)
		params->type = 1;
	lbl_3_data_9ED4[3] = lbl_3_data_9F04[params->type];
}

TObjS01Ciseki::~TObjS01Ciseki()
{
	vtable               = cisekiVtable;
	motion.vtable        = cisekiVtable + 11;
	CisekiParams* params = (CisekiParams*)motion.frame->params;
	if (fn_8005B8D8(&motion) != 0)
		callCommunication(this, 0, params);
	s01ObjectBaseDtor(this, 0);
}

TObjS01Ciseki::TObjS01Ciseki(TObject* parent)
{
	fn_3_7CB30(this, parent);
	vtable               = cisekiVtable;
	motion.vtable        = cisekiVtable + 11;
	CisekiParams* params = (CisekiParams*)motion.frame->params;
	className            = CL_TObjS01Ciseki;
	objectSize           = 0xCC;
	color                = 0x2000FF00;
	if (params->type < 0)
		params->type = 0;
	if (params->type > 2)
		params->type = 1;
}

extern "C" void startObj_S01_Ciseki()
{
	TObjS01Ciseki* object = (TObjS01Ciseki*)fn_80018A34(lbl_8042C148, sizeof(TObjS01Ciseki));
	if (object != NULL) {
		fn_3_7CB30(object, lbl_8042C110);
		object->vtable        = cisekiVtable;
		object->motion.vtable = cisekiVtable + 11;
		CisekiParams* params  = (CisekiParams*)object->motion.frame->params;
		object->className     = CL_TObjS01Ciseki;
		object->objectSize    = 0xCC;
		object->color         = 0x2000FF00;
		if (params->type < 0)
			params->type = 0;
		if (params->type > 2)
			params->type = 1;
	}
}

extern "C" void endObjS01Ciseki() { }

void TObjS01Ciseki::MotionNoop() { }

void TObjS01Ciseki::TDisp()
{
	if (resource != NULL) {
		fn_80063E7C(resource, 1);
		resource = NULL;
	}
}

extern "C" char cisekiClassName[] = "TObjS01Ciseki";
extern "C" char* CL_TObjS01Ciseki = cisekiClassName;

extern "C" void* cisekiVtable[18] = {
	NULL,
	NULL,
	(void*)__dt__13TObjS01CisekiFv,
	(void*)Exec__13TObjS01CisekiFv,
	(void*)fn_3_1A9B0,
	(void*)TDisp__13TObjS01CisekiFv,
	(void*)objDefaultPDisp,
	(void*)objDefaultImmAftSetRaster,
	(void*)objDefaultDebug,
	(void*)fn_80017854,
	(void*)objDefaultRender,
	NULL,
	NULL,
	(void*)AdjustorEditOnChange__11CisekiThunkFP13SETDATA_PARAM,
	(void*)MotionNoop__13TObjS01CisekiFv,
	(void*)SetCommuicateFlag__13TObjS01CisekiFUci,
	(void*)SetCommuicateFlag__13TObjS01CisekiFUciPUsUs,
	(void*)EditOnChange__11CisekiThunkFP13SETDATA_PARAM,
};

extern "C" char cisekiDisplayName[] = "S01 COLLI FOR ISEKI";
extern "C" char cisekiFieldTypes[]  = "FFFc";
extern "C" u32 cisekiEntry[12]      = {
	0x0004F00C,
	4,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
};

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

extern "C" SETOBJ_PARAM ObjS01CisekiParam;

extern "C" void __sinit_o_s01_ciseki_cpp()
{
	ObjS01CisekiParam.flags       = 0;
	ObjS01CisekiParam.field18     = 0;
	ObjS01CisekiParam.displayName = cisekiDisplayName;
	ObjS01CisekiParam.field04     = 0;
	ObjS01CisekiParam.field08     = 0;
	ObjS01CisekiParam.create      = startObj_S01_Ciseki;
	ObjS01CisekiParam.field10     = 0;
	ObjS01CisekiParam.flags       = 0;
	ObjS01CisekiParam.field18     = 0;
	ObjS01CisekiParam.field20     = 0x32;
	ObjS01CisekiParam.id          = 0x108;
	ObjS01CisekiParam.count       = 2;
	ObjS01CisekiParam.field21     = 0;
	ObjS01CisekiParam.fieldTypes  = cisekiFieldTypes;
	ObjS01CisekiParam.fields      = lbl_3_data_9ED4;
	if (ObjS01CisekiParam.fieldTypes != NULL)
		ObjS01CisekiParam.flags |= 8;
	else
		ObjS01CisekiParam.flags &= ~8;
}

extern "C" {
SETOBJ_PARAM ObjS01CisekiParam;
}

__declspec(section ".ctors") void (*const CisekiCtorEntry)() = __sinit_o_s01_ciseki_cpp;
