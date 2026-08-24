#include "types.h"

// Retained PS2 symbols identify o_s33_slot.cpp and the complete
// TObjS33Slot method/lifecycle family.  The GameCube class string, vtable,
// registration record, constructor entry, and neighboring object data
// independently establish the retail translation-unit boundaries.

#pragma force_active on

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
	void* params;
};

struct SlotThunkPrimary {
	u8 pad04[0x24];
	virtual void PrimarySlot();
};

struct SlotThunkSecondary {
	virtual void EditOnChange(SETDATA_PARAM*);
};

struct SlotThunk : SlotThunkPrimary, SlotThunkSecondary {
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
extern void* lbl_8042C180;
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
void fn_8019EB10(void*, void*, void*);
void fn_801A4C84(void*);
void* fn_8013F484(void*);
void fn_8013F3A4(void*);
void fn_8013FC30(void*);
void fn_8014FFBC(void*, void*, void*);
void fn_8020C72C(void*, void*);
void fn_8020D02C(void*, f32);
void fn_8020CC18(void*, f32);
void fn_8020C2D8(void*);
void* fn_80226468(void*);
void fn_80226440(void*, void*);
void* fn_800BB0D4(void*, s32, void*);

void Debug__7TObjectFv();
void ImmAftSetRaster__7TObjectFv();
void PDisp__7TObjectFv();
void Render__7TObjectFv();
void objDefaultTDisp();
void Error__7TObjectFPc();
}

class TObjS33Slot
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
	f32 rotationSpeed;
	s32 modelIndex;
	void* model;
	void* atomic;

	void InitAnim();
	void SetPosition();
	void SetParameter();
	void Disp();
	void Exec();
	void EditOnChange(SETDATA_PARAM*);
	TObjS33Slot(TObject*);
	~TObjS33Slot();

	static void operator delete(void* object) { fn_800189A4(lbl_8042C148, object); }
};

extern "C" {
TObjS33Slot* __dt__11TObjS33SlotFv(TObjS33Slot*, s16);
void Exec__11TObjS33SlotFv(TObjS33Slot*);
void Disp__11TObjS33SlotFv(TObjS33Slot*);
void EditOnChange__9SlotThunkFP13SETDATA_PARAM(SlotThunk*, SETDATA_PARAM*);
TObjS33Slot* AdjustorEditOnChange__11TObjS33SlotFP13SETDATA_PARAM(void*, SETDATA_PARAM*);
extern void* slotVtable[15];
extern char* CL_TObjS33Slot;
extern char* slotFieldNames[2];
extern void* slotResources[3];
extern void* slotAnimation;
void* slotFindAtomic(void*);
void* slotAtomicCallback(void*, void*);
void* slotAtomicSearch(void*, void*);
}

void TObjS33Slot::InitAnim()
{
	void* currentModel = model;
	void* found        = NULL;
	found              = fn_8013F484(*(void**)((u8*)currentModel + 4));
	if (found == NULL)
		fn_8019EB10(*(void**)((u8*)currentModel + 4), (void*)slotAtomicSearch, &found);
	atomic = found;
	fn_8014FFBC(model, (void*)slotAtomicCallback, atomic);
	*(u32*)atomic |= 0x3000;
	fn_8020C72C(*(void**)((u8*)atomic + 0x20), slotAnimation);
	fn_8013F3A4(atomic);
	fn_8013FC30(atomic);
	fn_8020D02C(*(void**)((u8*)atomic + 0x20), 0.0f);
	fn_8020CC18(*(void**)((u8*)atomic + 0x20), 0.0f);
}

#pragma opt_common_subs off
#pragma opt_propagation off
void TObjS33Slot::SetPosition()
{
	void* atomic = *(void**)((u8*)model + 4);
	fn_8019EB94(atomic, &position, 0);

	f32 sine    = fn_800D7B00(angleZ);
	f32 cosine  = fn_800D7AE4(angleZ);
	f32 inverse = 1.0f - cosine;
	fn_80195790((u8*)atomic + 0x10, &lbl_80239990, inverse, sine, 1);
	fn_8019E880(atomic);

	sine    = fn_800D7B00(angleX);
	cosine  = fn_800D7AE4(angleX);
	inverse = 1.0f - cosine;
	fn_80195790((u8*)atomic + 0x10, &lbl_80239978, inverse, sine, 1);
	fn_8019E880(atomic);

	sine    = fn_800D7B00(angleY);
	cosine  = fn_800D7AE4(angleY);
	inverse = 1.0f - cosine;
	fn_80195790((u8*)atomic + 0x10, &lbl_80239984, inverse, sine, 1);
	fn_8019E880(atomic);
}
#pragma opt_propagation reset
#pragma opt_common_subs reset

void TObjS33Slot::SetParameter()
{
	position             = motion.frame->position;
	SETDATA_PARAM* frame = motion.frame;
	angleX               = frame->angleX;
	angleY               = frame->angleY;
	angleZ               = frame->angleZ;
	s32* params          = (s32*)motion.frame->params;
	modelIndex           = params[0];
	rotationSpeed        = *(f32*)(params + 1);
}

void TObjS33Slot::Disp() { }

#pragma opt_common_subs off
#pragma opt_propagation off
void TObjS33Slot::Exec()
{
	s32 i;
	f32 speed;

	if (fn_8005B9F0(&motion) != 0 || fn_8005B8BC(&motion) != 0) {
		signal |= 1;
		return;
	}

	if (fn_8005B8D8(&motion) != 0) {
		s32 previous = modelIndex;
		SetParameter();
		if (previous != modelIndex) {
			fn_8015BBF8(*(void**)((u8*)lbl_8042C1D0 + 0x725C), model);
			fn_80150958(model);
			model = fn_80150588(slotResources[modelIndex]);
			fn_8015BB08(*(void**)((u8*)lbl_8042C1D0 + 0x725C), model);
			fn_8005D5C8(model, ((motion.frame->flags & 0x1C0000) >> 18) + 4);
			InitAnim();
		}
	}

	i              = 0;
	void** carrier = &lbl_8042C180;
	do {
		void* animation = *(void**)((u8*)atomic + 0x20);
		speed           = rotationSpeed;
		s32 frames      = *(s32*)((u8*)*carrier + 0x30);
		fn_8020D02C(animation, speed * (f32)frames / 60.0f);
		fn_8013FC30(atomic);
		++i;
	} while (i < 3);

	carrier = (void**)*(void**)((u8*)model + 4);
	fn_8019EB94(carrier, &position, 0);

	fn_80195790(
	    (u8*)carrier + 0x10, &lbl_80239990, 1.0f - fn_800D7AE4(angleZ), fn_800D7B00(angleZ), 1);
	fn_8019E880(carrier);

	fn_80195790(
	    (u8*)carrier + 0x10, &lbl_80239978, 1.0f - fn_800D7AE4(angleX), fn_800D7B00(angleX), 1);
	fn_8019E880(carrier);

	fn_80195790(
	    (u8*)carrier + 0x10, &lbl_80239984, 1.0f - fn_800D7AE4(angleY), fn_800D7B00(angleY), 1);
	fn_8019E880(carrier);

	if (fn_8005B8D8(&motion) != 0)
		return;
}
#pragma opt_propagation reset
#pragma opt_common_subs reset

TObjS33Slot::~TObjS33Slot()
{
	vtable        = slotVtable;
	motion.vtable = slotVtable + 11;
	if (model != NULL) {
		void* manager = *(void**)((u8*)lbl_8042C1D0 + 0x725C);
		fn_8015BBF8(manager, model);
		fn_80150958(model);
	}
	dtor_8005BD3C(&motion, 0);
	__dt__7TObjectFv(this, 0);
}

static inline void constructSlot(TObjS33Slot* object, TObject* parent)
{
	__ct__7TObjectFP7TObject(object, parent);
	fn_8005BE6C(&object->motion);
	object->vtable        = slotVtable;
	object->motion.vtable = slotVtable + 11;
	object->className     = CL_TObjS33Slot;
	object->objectSize    = sizeof(TObjS33Slot);
	object->SetParameter();
	object->model = fn_80150588(slotResources[object->modelIndex]);
	void* manager = *(void**)((u8*)lbl_8042C1D0 + 0x725C);
	fn_8015BB08(manager, object->model);
	u32 flags = object->motion.frame->flags;
	fn_8005D5C8(object->model, ((flags & 0x1C0000) >> 18) + 4);
	object->InitAnim();
}

TObjS33Slot::TObjS33Slot(TObject* parent)
{
	constructSlot(this, parent);
}

struct SlotInitializer {
	u8 data[sizeof(TObjS33Slot)];
};

static inline void initializeSlot(SlotInitializer* self)
{
	TObjS33Slot* object = (TObjS33Slot*)self;
	__ct__7TObjectFP7TObject(object, lbl_8042C110);
	fn_8005BE6C(&object->motion);
	object->vtable        = slotVtable;
	object->motion.vtable = slotVtable + 11;
	object->className     = CL_TObjS33Slot;
	object->objectSize    = sizeof(TObjS33Slot);
	object->SetParameter();
	object->model = fn_80150588(slotResources[object->modelIndex]);
	void* manager = *(void**)((u8*)lbl_8042C1D0 + 0x725C);
	fn_8015BB08(manager, object->model);
	u32 flags = object->motion.frame->flags;
	fn_8005D5C8(object->model, ((flags & 0x1C0000) >> 18) + 4);
	object->InitAnim();
}

extern "C" void* slotAtomicCallback(void* atomicObject, void* data)
{
	if (fn_80226468(*(void**)((u8*)atomicObject + 0x18)) != NULL)
		fn_80226440(atomicObject, data);
	return atomicObject;
}

extern "C" void* slotFindAtomic(void* model)
{
	void* found = NULL;
	found       = fn_8013F484(*(void**)((u8*)model + 4));
	if (found == NULL)
		fn_8019EB10(*(void**)((u8*)model + 4), (void*)slotAtomicSearch, &found);
	return found;
}

extern "C" void* slotAtomicSearch(void* object, void* data)
{
	void** result = (void**)data;
	void* found   = fn_8013F484(object);
	if (found == NULL) {
		fn_8019EB10(object, (void*)slotAtomicSearch, result);
		return object;
	}
	*result = found;
	return NULL;
}

void SlotThunk::EditOnChange(SETDATA_PARAM* frame)
{
	s32* model = (s32*)frame->params;
	if (*model < 0)
		*model = 0;
	if (*model >= 3)
		*model = 2;
}

extern "C" void endObjS33Slot()
{
	for (s32 i = 0; i < 3; ++i) {
		if (slotResources[i] != NULL) {
			fn_80150958(slotResources[i]);
			slotResources[i] = NULL;
		}
	}
	if (slotAnimation != NULL) {
		fn_8020C2D8(slotAnimation);
		slotAnimation = NULL;
	}
}

extern "C" char* slotModelNames[3];
extern "C" char slotAnimationName[];

extern "C" void initObjS33Slot()
{
	void* stage = *(void**)((u8*)lbl_8042C1D0 + 0x8C18);
	if (!(stage != NULL && (fn_801A4C84(stage), true)))
		return;
	s32 i;
	void* archive = *(void**)((u8*)lbl_8042C298 + 0xA50);
	fn_800BC9F4(archive, &lbl_802FF5A0);
	for (i = 0; i < 3; ++i) {
		s32 id           = fn_800BC6CC(archive, slotModelNames[i]);
		slotResources[i] = fn_800BB92C(archive, id, &lbl_802FF5A0);
	}
	s32 id        = fn_800BC6CC(archive, slotAnimationName);
	slotAnimation = fn_800BB0D4(archive, id, &lbl_802FF5A0);
}

#pragma optimization_level 2
#pragma opt_common_subs off
extern "C" void startObjS33Slot()
{
#pragma opt_propagation off
	void* allocation = fn_80018A34(lbl_8042C148, sizeof(TObjS33Slot));
	if (allocation != NULL) {
		SlotInitializer* object = (SlotInitializer*)allocation;
		initializeSlot(object);
	}
}
#pragma opt_common_subs reset
#pragma optimization_level reset

extern "C" char slotModelName1[]   = "S33_ON_SLOT1.DFF";
extern "C" char slotModelName2[]   = "S33_ON_SLOT2.DFF";
extern "C" char slotModelName3[]   = "S33_ON_SLOT3.DFF";
extern "C" char* slotModelNames[3] = {
	slotModelName1,
	slotModelName2,
	slotModelName3,
};
extern "C" char slotFieldName1[]   = "drum no.";
extern "C" char slotFieldName2[]   = "rot speed";
extern "C" char* slotFieldNames[2] = {
	slotFieldName1,
	slotFieldName2,
};

extern "C" char slotClassName[] = "TObjS33Slot";
extern "C" char* CL_TObjS33Slot = slotClassName;

extern "C" void* slotVtable[15] = {
	NULL,
	NULL,
	(void*)__dt__11TObjS33SlotFv,
	(void*)Exec__11TObjS33SlotFv,
	(void*)Disp__11TObjS33SlotFv,
	(void*)objDefaultTDisp,
	(void*)PDisp__7TObjectFv,
	(void*)ImmAftSetRaster__7TObjectFv,
	(void*)Debug__7TObjectFv,
	(void*)Error__7TObjectFPc,
	(void*)Render__7TObjectFv,
	NULL,
	NULL,
	(void*)AdjustorEditOnChange__11TObjS33SlotFP13SETDATA_PARAM,
	(void*)EditOnChange__9SlotThunkFP13SETDATA_PARAM,
};

extern "C" char slotAnimationName[] = "S33_ON_SLOT1.ANM";
extern "C" char slotDisplayName[]   = "S33_SLOT OBJECT";
extern "C" char slotFieldTypes[]    = "if";

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
	u32 pad2C;
};

extern "C" SETOBJ_PARAM ObjS33SlotParam;

extern "C" void __sinit_o_s33_slot_cpp()
{
	ObjS33SlotParam.flags       = 0;
	ObjS33SlotParam.field18     = 0;
	ObjS33SlotParam.displayName = slotDisplayName;
	ObjS33SlotParam.init        = initObjS33Slot;
	ObjS33SlotParam.end         = endObjS33Slot;
	ObjS33SlotParam.create      = startObjS33Slot;
	ObjS33SlotParam.field10     = 0;
	ObjS33SlotParam.flags       = 0x20000;
	ObjS33SlotParam.field18     = 0;
	ObjS33SlotParam.field20     = 0x1E;
	ObjS33SlotParam.id          = 0x3383;
	ObjS33SlotParam.count       = 2;
	ObjS33SlotParam.field21     = 0;
	ObjS33SlotParam.fieldTypes  = slotFieldTypes;
	ObjS33SlotParam.fields      = slotFieldNames;
	if (ObjS33SlotParam.fieldTypes != NULL)
		ObjS33SlotParam.flags |= 8;
	else
		ObjS33SlotParam.flags &= ~8;
}

extern "C" {
void* slotResources[3];
void* slotAnimation;
SETOBJ_PARAM ObjS33SlotParam;
}

__declspec(section ".ctors") void (*const SlotCtorEntry)() = __sinit_o_s33_slot_cpp;

#pragma force_active reset
