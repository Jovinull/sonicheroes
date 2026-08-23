#include "types.h"

// Retained PS2 symbols identify o_s33_chip.cpp and the complete
// TObjS33Chip method/lifecycle family.  The GameCube class string, vtable,
// registration record, constructor entry, and neighboring object data
// independently establish the retail translation-unit boundaries.

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
	volatile u32 flags;
	u8 pad1C[0x10];
	s16* params;
};

struct ChipThunkPrimary {
	u8 pad04[0x24];
	virtual void PrimarySlot();
};

struct ChipThunkSecondary {
	virtual void EditOnChange(SETDATA_PARAM*);
};

struct ChipThunk : ChipThunkPrimary, ChipThunkSecondary {
	virtual void EditOnChange(SETDATA_PARAM*);
};

extern "C" void fn_801A4C84(void*);

struct Motion {
	SETDATA_PARAM* frame;
	void** vtable;
};

class TObject;

extern "C" {
extern void* lbl_8042C110;
extern void* lbl_8042C148;
extern void* lbl_8042C1D0;
extern void* lbl_8042C298;

extern u8 lbl_80239978;
extern u8 lbl_80239984;
extern u8 lbl_80239990;
extern u8 lbl_802FF5A0;

void __ct__7TObjectFP7TObject(void*, void*);
void __dt__7TObjectFv(void*, s16);
void dtor_8005BD3C(Motion*, s16);
void fn_8005BE6C(Motion*);
s32 fn_8005B8BC(Motion*);
s32 fn_8005B8D8(Motion*);
s32 fn_8005B9F0(Motion*);
void fn_8005D5C8(void*, u32);
f32 fn_800D7AE4(s32);
f32 fn_800D7B00(s32);
void* fn_80018A34(void*, u32);
void fn_800189A4(void*, void*);
void* fn_800BB92C(void*, s32, void*);
s32 fn_800BC6CC(void*, const char*);
void fn_800BC9F4(void*, void*);
void* fn_80150588(void*);
void fn_80150958(void*);
void fn_8015BB08(void*, void*);
void fn_8015BBF8(void*, void*);
void fn_80195790(void*, void*, f32, f32, s32);
void fn_8019E880(void*);
void fn_8019EB94(void*, Vec3*, s32);
void fn_801A4C84(void*);

void Debug__7TObjectFv();
void ImmAftSetRaster__7TObjectFv();
void PDisp__7TObjectFv();
void Render__7TObjectFv();
void objDefaultTDisp();
void Error__7TObjectFPc();
}

class TObjS33Chip
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
	Vec3 position;
	s32 angleX;
	s32 angleY;
	s32 angleZ;
	s32 rotation;
	s32 rotationSpeed;
	void* model;

	void SetPosition();
	void SetParameter();
	void Disp();
	void Exec();
	void EditOnChange(SETDATA_PARAM*);
	TObjS33Chip(TObject*);
	~TObjS33Chip();

	static void operator delete(void* object) { fn_800189A4(lbl_8042C148, object); }
};

extern "C" {
TObjS33Chip* __dt__11TObjS33ChipFv(TObjS33Chip*, s16);
void Exec__11TObjS33ChipFv(TObjS33Chip*);
void Disp__11TObjS33ChipFv(TObjS33Chip*);
void EditOnChange__9ChipThunkFP13SETDATA_PARAM(ChipThunk*, SETDATA_PARAM*);
TObjS33Chip* AdjustorEditOnChange__11TObjS33ChipFP13SETDATA_PARAM(void*, SETDATA_PARAM*);
extern void* chipVtable[15];
extern char* CL_TObjS33Chip;
extern void* chipResource;
extern char* chipFieldNames;
}

extern "C" const f32 chipOne[2] = { 1.0f, 0.0f };

#pragma opt_common_subs off
#pragma opt_propagation off
void TObjS33Chip::SetPosition()
{
	void* atomic = *(void**)((u8*)model + 4);
	fn_8019EB94(atomic, &position, 0);

	f32 sine    = fn_800D7B00(angleZ);
	f32 cosine  = fn_800D7AE4(angleZ);
	f32 inverse = chipOne[0] - cosine;
	fn_80195790((u8*)atomic + 0x10, &lbl_80239990, inverse, sine, 1);
	fn_8019E880(atomic);

	sine    = fn_800D7B00(angleX);
	cosine  = fn_800D7AE4(angleX);
	inverse = chipOne[0] - cosine;
	fn_80195790((u8*)atomic + 0x10, &lbl_80239978, inverse, sine, 1);
	fn_8019E880(atomic);

	sine    = fn_800D7B00(angleY + rotation);
	cosine  = fn_800D7AE4(angleY + rotation);
	inverse = chipOne[0] - cosine;
	fn_80195790((u8*)atomic + 0x10, &lbl_80239984, inverse, sine, 1);
	fn_8019E880(atomic);
}
#pragma opt_propagation reset
#pragma opt_common_subs reset

void TObjS33Chip::SetParameter()
{
	position             = motion.frame->position;
	SETDATA_PARAM* frame = motion.frame;
	angleX               = frame->angleX;
	angleY               = frame->angleY;
	angleZ               = frame->angleZ;
	rotationSpeed        = motion.frame->params[0];
}

void TObjS33Chip::Disp() { }

#pragma opt_common_subs off
#pragma opt_propagation off
void TObjS33Chip::Exec()
{
	if (fn_8005B9F0(&motion) != 0 || fn_8005B8BC(&motion) != 0) {
		signal |= 1;
		return;
	}

	if (fn_8005B8D8(&motion) != 0)
		SetParameter();

	rotation += rotationSpeed;
	void* atomic = *(void**)((u8*)model + 4);
	fn_8019EB94(atomic, &position, 0);

	f32 sine    = fn_800D7B00(angleZ);
	f32 cosine  = fn_800D7AE4(angleZ);
	f32 inverse = chipOne[0] - cosine;
	fn_80195790((u8*)atomic + 0x10, &lbl_80239990, inverse, sine, 1);
	fn_8019E880(atomic);

	sine    = fn_800D7B00(angleX);
	cosine  = fn_800D7AE4(angleX);
	inverse = chipOne[0] - cosine;
	fn_80195790((u8*)atomic + 0x10, &lbl_80239978, inverse, sine, 1);
	fn_8019E880(atomic);

	sine    = fn_800D7B00(angleY + rotation);
	cosine  = fn_800D7AE4(angleY + rotation);
	inverse = chipOne[0] - cosine;
	fn_80195790((u8*)atomic + 0x10, &lbl_80239984, inverse, sine, 1);
	fn_8019E880(atomic);
	if (fn_8005B8D8(&motion) != 0)
		return;
}
#pragma opt_propagation reset
#pragma opt_common_subs reset

TObjS33Chip::~TObjS33Chip()
{
	vtable        = chipVtable;
	motion.vtable = chipVtable + 11;
	if (model != NULL) {
		void* manager = *(void**)((u8*)lbl_8042C1D0 + 0x725C);
		fn_8015BBF8(manager, model);
		fn_80150958(model);
	}
	dtor_8005BD3C(&motion, 0);
	__dt__7TObjectFv(this, 0);
}

static inline void constructChip(TObjS33Chip* object, TObject* parent)
{
	__ct__7TObjectFP7TObject(object, parent);
	fn_8005BE6C(&object->motion);
	object->vtable        = chipVtable;
	object->motion.vtable = chipVtable + 11;
	object->className     = CL_TObjS33Chip;
	object->objectSize    = sizeof(TObjS33Chip);
	object->SetParameter();
	object->model = fn_80150588(chipResource);
	void* manager = *(void**)((u8*)lbl_8042C1D0 + 0x725C);
	fn_8015BB08(manager, object->model);
	u32 flags = object->motion.frame->flags;
	fn_8005D5C8(object->model, ((flags & 0x1C0000) >> 18) + 4);
	object->rotation = 0;
}

TObjS33Chip::TObjS33Chip(TObject* parent)
{
	constructChip(this, parent);
}

struct ChipInitializer {
	u8 data[sizeof(TObjS33Chip)];
};

static inline void initializeChip(ChipInitializer* self)
{
	TObjS33Chip* object = (TObjS33Chip*)self;
	__ct__7TObjectFP7TObject(object, lbl_8042C110);
	fn_8005BE6C(&object->motion);
	object->vtable        = chipVtable;
	object->motion.vtable = chipVtable + 11;
	object->className     = CL_TObjS33Chip;
	object->objectSize    = sizeof(TObjS33Chip);
	object->SetParameter();
	object->model = fn_80150588(chipResource);
	void* manager = *(void**)((u8*)lbl_8042C1D0 + 0x725C);
	fn_8015BB08(manager, object->model);
	u32 flags = object->motion.frame->flags;
	fn_8005D5C8(object->model, ((flags & 0x1C0000) >> 18) + 4);
	object->rotation = 0;
}

void ChipThunk::EditOnChange(SETDATA_PARAM*) { }

extern "C" void endObjS33Chip()
{
	if (chipResource != NULL) {
		fn_80150958(chipResource);
		chipResource = NULL;
	}
}

extern "C" char chipModelName[];

extern "C" void initObjS33Chip()
{
	void* stage = *(void**)((u8*)lbl_8042C1D0 + 0x8C18);
	if (!(stage != NULL && (fn_801A4C84(stage), true)))
		return;
	void* archive = *(void**)((u8*)lbl_8042C298 + 0xA50);
	fn_800BC9F4(archive, &lbl_802FF5A0);
	s32 id       = fn_800BC6CC(archive, chipModelName);
	chipResource = fn_800BB92C(archive, id, &lbl_802FF5A0);
}

#pragma optimization_level 2
#pragma opt_common_subs off
extern "C" void startObjS33Chip()
{
#pragma opt_propagation off
	void* allocation = fn_80018A34(lbl_8042C148, sizeof(TObjS33Chip));
	if (allocation != NULL) {
		ChipInitializer* object = (ChipInitializer*)allocation;
		initializeChip(object);
	}
}
#pragma opt_common_subs reset
#pragma optimization_level reset

extern "C" char chipClassName[] = "TObjS33Chip";
extern "C" char* CL_TObjS33Chip = chipClassName;

extern "C" void* chipVtable[15] = {
	NULL,
	NULL,
	(void*)__dt__11TObjS33ChipFv,
	(void*)Exec__11TObjS33ChipFv,
	(void*)Disp__11TObjS33ChipFv,
	(void*)objDefaultTDisp,
	(void*)PDisp__7TObjectFv,
	(void*)ImmAftSetRaster__7TObjectFv,
	(void*)Debug__7TObjectFv,
	(void*)Error__7TObjectFPc,
	(void*)Render__7TObjectFv,
	NULL,
	NULL,
	(void*)AdjustorEditOnChange__11TObjS33ChipFP13SETDATA_PARAM,
	(void*)EditOnChange__9ChipThunkFP13SETDATA_PARAM,
};

extern "C" char chipModelName[]   = "S33_ON_CHIP.DFF";
extern "C" char chipDisplayName[] = "S33_CHIP OBJECT";
extern "C" char chipFieldTypes[]  = "s";

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

extern "C" SETOBJ_PARAM ObjS33ChipParam;

extern "C" void __sinit_o_s33_chip_cpp()
{
	ObjS33ChipParam.flags       = 0;
	ObjS33ChipParam.field18     = 0;
	ObjS33ChipParam.displayName = chipDisplayName;
	ObjS33ChipParam.init        = initObjS33Chip;
	ObjS33ChipParam.end         = endObjS33Chip;
	ObjS33ChipParam.create      = startObjS33Chip;
	ObjS33ChipParam.field10     = 0;
	ObjS33ChipParam.flags       = 0x20000;
	ObjS33ChipParam.field18     = 0;
	ObjS33ChipParam.field20     = 0x1E;
	ObjS33ChipParam.id          = 0x3380;
	ObjS33ChipParam.count       = 2;
	ObjS33ChipParam.field21     = 0;
	ObjS33ChipParam.fieldTypes  = chipFieldTypes;
	ObjS33ChipParam.fields      = &chipFieldNames;
	if (ObjS33ChipParam.fieldTypes != NULL)
		ObjS33ChipParam.flags |= 8;
	else
		ObjS33ChipParam.flags &= ~8;
}

extern "C" {
void* chipResource;
SETOBJ_PARAM ObjS33ChipParam;
}

__declspec(section ".ctors") void (*const ChipCtorEntry)() = __sinit_o_s33_chip_cpp;
