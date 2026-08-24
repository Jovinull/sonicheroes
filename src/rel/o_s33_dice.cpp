#include "types.h"

// Retained PS2 symbols identify o_s33_dice.cpp and the complete TObjS33Dice
// method/lifecycle family.  The GameCube model strings, class metadata,
// vtable, registration record, constructor entry, and neighboring object data
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

struct DiceThunkPrimary {
	u8 pad04[0x24];
	virtual void PrimarySlot();
};

struct DiceThunkSecondary {
	virtual void EditOnChange(SETDATA_PARAM*);
};

struct DiceThunk : DiceThunkPrimary, DiceThunkSecondary {
	virtual void EditOnChange(SETDATA_PARAM*);
};

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

class TObjS33Dice
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
	s32 color;
	void* onModel;
	void* pnModel;

	void SetPosition();
	void SetParameter();
	void Disp();
	void Exec();
	TObjS33Dice(TObject*);
	~TObjS33Dice();

	static void operator delete(void* object) { fn_800189A4(lbl_8042C148, object); }
};

extern "C" {
TObjS33Dice* __dt__11TObjS33DiceFv(TObjS33Dice*, s16);
void Exec__11TObjS33DiceFv(TObjS33Dice*);
void Disp__11TObjS33DiceFv(TObjS33Dice*);
void EditOnChange__11TObjS33DiceFP13SETDATA_PARAM(TObjS33Dice*, SETDATA_PARAM*);
TObjS33Dice* AdjustorEditOnChange__11TObjS33DiceFP13SETDATA_PARAM(void*, SETDATA_PARAM*);
extern void* diceVtable[15];
extern char* CL_TObjS33Dice;
extern void* diceOnResources[2];
extern void* dicePnResources[2];
}

extern "C" const f32 diceOne[2] = { 1.0f, 0.0f };

static inline void setDiceModelPosition(TObjS33Dice* object, void* model)
{
	void* atomic = *(void**)((u8*)model + 4);
	fn_8019EB94(atomic, &object->position, 0);

	f32 sine    = fn_800D7B00(object->angleZ);
	f32 cosine  = fn_800D7AE4(object->angleZ);
	f32 inverse = diceOne[0] - cosine;
	fn_80195790((u8*)atomic + 0x10, &lbl_80239990, inverse, sine, 1);
	fn_8019E880(atomic);

	sine    = fn_800D7B00(object->angleX);
	cosine  = fn_800D7AE4(object->angleX);
	inverse = diceOne[0] - cosine;
	fn_80195790((u8*)atomic + 0x10, &lbl_80239978, inverse, sine, 1);
	fn_8019E880(atomic);

	sine    = fn_800D7B00(object->angleY + object->rotation);
	cosine  = fn_800D7AE4(object->angleY + object->rotation);
	inverse = diceOne[0] - cosine;
	fn_80195790((u8*)atomic + 0x10, &lbl_80239984, inverse, sine, 1);
	fn_8019E880(atomic);
}

#pragma opt_common_subs off
#pragma opt_propagation off
void TObjS33Dice::SetPosition()
{
	setDiceModelPosition(this, onModel);
	setDiceModelPosition(this, pnModel);
}
#pragma opt_propagation reset
#pragma opt_common_subs reset

void TObjS33Dice::SetParameter()
{
	position             = motion.frame->position;
	SETDATA_PARAM* frame = motion.frame;
	angleX               = frame->angleX;
	angleY               = frame->angleY;
	angleZ               = frame->angleZ;
	frame                = motion.frame;
	s16* params          = frame->params;
	color                = params[0];
	rotationSpeed        = params[1];
}

void TObjS33Dice::Disp() { }

#pragma opt_common_subs off
#pragma opt_propagation off
void TObjS33Dice::Exec()
{
	if (fn_8005B9F0(&motion) != 0 || fn_8005B8BC(&motion) != 0) {
		signal |= 1;
		return;
	}

	if (fn_8005B8D8(&motion) != 0) {
		s32 oldColor = color;
		SetParameter();
		if (oldColor != color) {
			void* manager = *(void**)((u8*)lbl_8042C1D0 + 0x725C);
			fn_8015BBF8(manager, onModel);
			fn_80150958(onModel);

			manager = *(void**)((u8*)lbl_8042C1D0 + 0x7274);
			fn_8015BBF8(manager, pnModel);
			fn_80150958(pnModel);

			onModel = fn_80150588(diceOnResources[color]);
			manager = *(void**)((u8*)lbl_8042C1D0 + 0x725C);
			fn_8015BB08(manager, onModel);

			pnModel = fn_80150588(dicePnResources[color]);
			manager = *(void**)((u8*)lbl_8042C1D0 + 0x7274);
			fn_8015BB08(manager, pnModel);

			fn_8005D5C8(onModel, ((motion.frame->flags & 0x1C0000) >> 18) + 4);
			fn_8005D5C8(pnModel, ((motion.frame->flags & 0x1C0000) >> 18) + 4);
		}
	}

	rotation += rotationSpeed;
	setDiceModelPosition(this, onModel);
	setDiceModelPosition(this, pnModel);
	if (fn_8005B8D8(&motion) != 0)
		return;
}
#pragma opt_propagation reset
#pragma opt_common_subs reset

TObjS33Dice::~TObjS33Dice()
{
	vtable        = diceVtable;
	motion.vtable = diceVtable + 11;
	if (onModel != NULL) {
		void* manager = *(void**)((u8*)lbl_8042C1D0 + 0x725C);
		fn_8015BBF8(manager, onModel);
		fn_80150958(onModel);
	}
	if (pnModel != NULL) {
		void* manager = *(void**)((u8*)lbl_8042C1D0 + 0x7274);
		fn_8015BBF8(manager, pnModel);
		fn_80150958(pnModel);
	}
	dtor_8005BD3C(&motion, 0);
	__dt__7TObjectFv(this, 0);
}

static inline void constructDice(TObjS33Dice* object, TObject* parent)
{
	__ct__7TObjectFP7TObject(object, parent);
	fn_8005BE6C(&object->motion);
	object->vtable        = diceVtable;
	object->motion.vtable = diceVtable + 11;
	object->className     = CL_TObjS33Dice;
	object->objectSize    = sizeof(TObjS33Dice);
	object->SetParameter();

	object->onModel = fn_80150588(diceOnResources[object->color]);
	void* manager   = *(void**)((u8*)lbl_8042C1D0 + 0x725C);
	fn_8015BB08(manager, object->onModel);

	object->pnModel = fn_80150588(dicePnResources[object->color]);
	manager         = *(void**)((u8*)lbl_8042C1D0 + 0x7274);
	fn_8015BB08(manager, object->pnModel);

	u32 flags = object->motion.frame->flags;
	fn_8005D5C8(object->onModel, ((flags & 0x1C0000) >> 18) + 4);
	flags = object->motion.frame->flags;
	fn_8005D5C8(object->pnModel, ((flags & 0x1C0000) >> 18) + 4);
	object->rotation = 0;
}

TObjS33Dice::TObjS33Dice(TObject* parent)
{
	constructDice(this, parent);
}

struct DiceInitializer {
	u8 data[sizeof(TObjS33Dice)];
};

static inline void initializeDice(DiceInitializer* self)
{
	TObjS33Dice* object = (TObjS33Dice*)self;
	__ct__7TObjectFP7TObject(object, lbl_8042C110);
	fn_8005BE6C(&object->motion);
	object->vtable        = diceVtable;
	object->motion.vtable = diceVtable + 11;
	object->className     = CL_TObjS33Dice;
	object->objectSize    = sizeof(TObjS33Dice);
	object->SetParameter();

	object->onModel = fn_80150588(diceOnResources[object->color]);
	void* manager   = *(void**)((u8*)lbl_8042C1D0 + 0x725C);
	fn_8015BB08(manager, object->onModel);

	object->pnModel = fn_80150588(dicePnResources[object->color]);
	manager         = *(void**)((u8*)lbl_8042C1D0 + 0x7274);
	fn_8015BB08(manager, object->pnModel);

	u32 flags = object->motion.frame->flags;
	fn_8005D5C8(object->onModel, ((flags & 0x1C0000) >> 18) + 4);
	flags = object->motion.frame->flags;
	fn_8005D5C8(object->pnModel, ((flags & 0x1C0000) >> 18) + 4);
	object->rotation = 0;
}

extern "C" char* diceFieldNames[2];
extern "C" char* diceColorDescriptions[2];

void DiceThunk::EditOnChange(SETDATA_PARAM* frame)
{
	s16* params = frame->params;
	if (params[0] < 0)
		params[0] = 0;
	if (params[0] >= 2)
		params[0] = 1;
	diceFieldNames[0] = diceColorDescriptions[params[0]];
}

extern "C" void endObjS33Dice()
{
	for (s32 i = 0; i < 2; i++) {
		if (diceOnResources[i] != NULL) {
			fn_80150958(diceOnResources[i]);
			diceOnResources[i] = NULL;
		}
		if (dicePnResources[i] != NULL) {
			fn_80150958(dicePnResources[i]);
			dicePnResources[i] = NULL;
		}
	}
}

extern "C" char* diceOnModelNames[2];
extern "C" char* dicePnModelNames[2];

extern "C" void initObjS33Dice()
{
	void* stage = *(void**)((u8*)lbl_8042C1D0 + 0x8C18);
	if (!(stage != NULL && (fn_801A4C84(stage), true)))
		return;

	s32 i;
	void* archive = *(void**)((u8*)lbl_8042C298 + 0xA50);
	fn_800BC9F4(archive, &lbl_802FF5A0);
	i = 0;
	for (; i < 2; i++) {
		s32 id             = fn_800BC6CC(archive, diceOnModelNames[i]);
		diceOnResources[i] = fn_800BB92C(archive, id, &lbl_802FF5A0);
		id                 = fn_800BC6CC(archive, dicePnModelNames[i]);
		dicePnResources[i] = fn_800BB92C(archive, id, &lbl_802FF5A0);
	}
}

#pragma optimization_level 2
#pragma opt_common_subs off
extern "C" void startObjS33Dice()
{
#pragma opt_propagation off
	void* allocation = fn_80018A34(lbl_8042C148, sizeof(TObjS33Dice));
	if (allocation != NULL) {
		DiceInitializer* object = (DiceInitializer*)allocation;
		initializeDice(object);
	}
}
#pragma opt_common_subs reset
#pragma optimization_level reset

extern "C" char diceOnRedModelName[]   = "S33_ON_DICERED.DFF";
extern "C" char diceOnWhiteModelName[] = "S33_ON_DICEWHITE.DFF";
extern "C" char* diceOnModelNames[2]   = {
	diceOnRedModelName,
	diceOnWhiteModelName,
};
extern "C" char dicePnRedModelName[]   = "S33_PN_DICERED.DFF";
extern "C" char dicePnWhiteModelName[] = "S33_PN_DICEWHITE.DFF";
extern "C" char* dicePnModelNames[2]   = {
	dicePnRedModelName,
	dicePnWhiteModelName,
};
extern "C" char diceColorFieldName[]         = "color";
extern "C" char diceRotationSpeedFieldName[] = "rot speed";
extern "C" char* diceFieldNames[2]           = {
	diceColorFieldName,
	diceRotationSpeedFieldName,
};
extern "C" char diceColorRedDescription[]   = "color : red";
extern "C" char diceColorWhiteDescription[] = "color : white";
extern "C" char* diceColorDescriptions[2]   = {
	diceColorRedDescription,
	diceColorWhiteDescription,
};
extern "C" char diceClassName[] = "TObjS33Dice";
extern "C" char* CL_TObjS33Dice = diceClassName;
extern "C" void* diceVtable[15] = {
	NULL,
	NULL,
	(void*)__dt__11TObjS33DiceFv,
	(void*)Exec__11TObjS33DiceFv,
	(void*)Disp__11TObjS33DiceFv,
	(void*)objDefaultTDisp,
	(void*)PDisp__7TObjectFv,
	(void*)ImmAftSetRaster__7TObjectFv,
	(void*)Debug__7TObjectFv,
	(void*)Error__7TObjectFPc,
	(void*)Render__7TObjectFv,
	NULL,
	NULL,
	(void*)AdjustorEditOnChange__11TObjS33DiceFP13SETDATA_PARAM,
	(void*)EditOnChange__11TObjS33DiceFP13SETDATA_PARAM,
};
extern "C" char diceDisplayName[]    = "S33_DICE OBJECT";
extern "C" char diceFieldTypes[]     = "ss";
extern "C" char diceSpeedFieldName[] = "rot speed";
extern "C" char* chipFieldNames      = diceSpeedFieldName;

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

extern "C" SETOBJ_PARAM ObjS33DiceParam;
extern "C" char diceDisplayNameRef[];
extern "C" char diceFieldTypesRef[];
extern "C" char* diceFieldNamesRef[2];

extern "C" void __sinit_o_s33_dice_cpp()
{
	ObjS33DiceParam.flags       = 0;
	ObjS33DiceParam.field18     = 0;
	ObjS33DiceParam.displayName = diceDisplayNameRef;
	ObjS33DiceParam.init        = initObjS33Dice;
	ObjS33DiceParam.end         = endObjS33Dice;
	ObjS33DiceParam.create      = startObjS33Dice;
	ObjS33DiceParam.field10     = 0;
	ObjS33DiceParam.flags       = 0x20000;
	ObjS33DiceParam.field18     = 0;
	ObjS33DiceParam.field20     = 0x1E;
	ObjS33DiceParam.id          = 0x3381;
	ObjS33DiceParam.count       = 2;
	ObjS33DiceParam.field21     = 0;
	ObjS33DiceParam.fieldTypes  = diceFieldTypesRef;
	ObjS33DiceParam.fields      = diceFieldNamesRef;
	if (ObjS33DiceParam.fieldTypes != NULL)
		ObjS33DiceParam.flags |= 8;
	else
		ObjS33DiceParam.flags &= ~8;
}

extern "C" {
void* diceOnResources[2];
void* dicePnResources[2];
SETOBJ_PARAM ObjS33DiceParam;
}

__declspec(section ".ctors") void (*const DiceCtorEntry)() = __sinit_o_s33_dice_cpp;
