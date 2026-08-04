#include "types.h"

struct Vec3 {
	f32 x, y, z;
};

struct Vec3Bits {
	u32 x, y, z;
};

struct SetData;

struct IwamizuThunkPrimary {
	u8 pad04[0x24];
	virtual void PrimarySlot();
};

struct IwamizuThunkSecondary {
	virtual void BaseSlot(SetData*);
};

struct IwamizuThunk : IwamizuThunkPrimary, IwamizuThunkSecondary {
	virtual void BaseSlot(SetData*);
};

struct ObjectEntry {
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
	u8 pad[2];
	char* fieldTypes;
	char** fieldNames;
};

extern "C" {
void* fn_3_81128(void*);
void* fn_3_82320(void*);
void objDefaultTDisp();
void objDefaultPDisp();
void objDefaultImmAftSetRaster();
void objDefaultDebug();
void fn_80017854();
void objDefaultRender();
void fn_8005F4B4(void*, void*);
void* fn_8005F490();
int fn_8004A5B8(void*, int, int);
void fn_8014F1B0();
void fn_8019EC30(void*, Vec3*, int);
void fn_8019ED68(void*, const void*, f32, int);
void fn_8019EB94(void*, void*, int);
void fn_8011B844(void*, f32);
void fn_8005BF88();
void fn_8014FFBC(void*, void*, int);
int fn_8005B9F0(void*);
int fn_8005B8BC(void*);
int fn_8005B8D8(void*);
void fn_800B4A38(void*, int, void*, void*, int, int, int);
void fn_8015BBF8(void*, void*);
void fn_80150958(void*);
void dtor_8005BD3C(void*, int);
void __dt__7TObjectFv(void*, int);
void fn_800189A4(void*, void*);
void __ct__7TObjectFP7TObject(void*, void*);
void fn_8005BE6C(void*);
void* fn_80150588(void*);
void fn_8015BB08(void*, void*);
void fn_8011B7CC(void*);
void __dl__FPv(void*);
void fn_801A4C84(void*);
void fn_800BC9F4(void*, void*);
void* fn_800BC6CC(void*, const char*);
void* fn_800BB92C(void*, void*, void*);
void* fn_8005E394(void*, int);
void* fn_800BAE0C(void*, void*, void*);
void fn_8005C014(void*, void*);
void* fn_80018A34(void*, u32);

extern void* lbl_8042C1D0;
extern void* lbl_8042C298;
extern void* lbl_8042C180;
extern void* lbl_8042C388;
extern void* lbl_8042C148;
extern void* lbl_8042C110;
extern void* lbl_802FF5A0;
extern const f64 lbl_80239984;

void* fn_3_816D8(void*);
void* fn_3_81858(void*);
void* fn_3_81128(void*);
}

extern "C" char IwamizuClassName[];
extern "C" char* IwamizuClassNamePtr;
extern "C" void* IwamizuVtable[];
extern "C" char IwamizuModelName[];
extern "C" char IwamizuAnimationName[];
extern "C" char IwamizuObjectName[];
extern "C" char IwamizuFieldTypes[];
extern "C" char* IwamizuFieldNames[];
extern "C" void* IwamizuModeTable[];
extern "C" f32 IwamizuSoundVolume;
extern "C" s8 IwamizuSoundPan;

extern "C" void* IwamizuArchive;
extern "C" void* IwamizuAnimation;
extern "C" void* IwamizuAnimationCallback;
extern "C" void* IwamizuScratch[2];
extern "C" void* IwamizuClump;
extern "C" s32 IwamizuDispInitialized;
extern "C" u8 IwamizuRenderState[0x44];
extern "C" ObjectEntry IwamizuEntry;

extern "C" const Vec3 IwamizuZeroVector;
extern "C" const f32 IwamizuMinimum;
extern "C" const f64 IwamizuIntBias;
extern "C" const f32 IwamizuZero;
extern "C" const f32 IwamizuOne;
extern "C" void EditOnChange__14TObjS01IwamizuFP13SETDATA_PARAM(void*, SetData*);

#define BYTE(object, offset)  (*(u8*)((u8*)(object) + (offset)))
#define SBYTE(object, offset) (*(s8*)((u8*)(object) + (offset)))
#define HALF(object, offset)  (*(u16*)((u8*)(object) + (offset)))
#define WORD(object, offset)  (*(u32*)((u8*)(object) + (offset)))
#define PTR(object, offset)   (*(void**)((u8*)(object) + (offset)))
#define FLOAT(object, offset) (*(f32*)((u8*)(object) + (offset)))

void IwamizuThunk::BaseSlot(SetData* setData)
{
	EditOnChange__14TObjS01IwamizuFP13SETDATA_PARAM(this, setData);
}

struct IwamizuCallback {
	u8 pad[0x48];
	void (*function)();
};

extern "C" void* SetIwamizuCallback(IwamizuCallback* callback, void* argument)
{
	void (*oldFunction)()            = callback->function;
	void (*volatile savedFunction)() = oldFunction;
	void* volatile savedArgument;
	if (oldFunction == (void (*)())fn_3_816D8) {
		savedArgument = argument;
		return callback;
	} else {
		savedArgument = argument;
		fn_8005F4B4(callback, (void*)&savedArgument);
		callback->function = (void (*)())fn_3_816D8;
		if (callback->function == 0)
			callback->function = fn_8014F1B0;
		return 0;
	}
}

struct CallbackState {
	int mode;
	void (*invoke)(void*);
};

#pragma optimization_level 2
#pragma opt_common_subs off
extern "C" void* fn_3_816D8(void* argument)
{
	CallbackState* state = (CallbackState*)fn_8005F490();
	int invoke           = 0;
	switch (state->mode) {
		case 1:
			if (fn_8004A5B8(lbl_8042C1D0, 3, 0) == 1)
				invoke = 1;
			break;
		case 2: {
			int i          = 4;
			void** manager = &lbl_8042C1D0;
			do {
				if (fn_8004A5B8(*manager, i, 0) == 1) {
					invoke = 1;
					break;
				}
				++i;
			} while (i <= 5);
			break;
		}
		case 3: {
			int i          = 5;
			void** manager = &lbl_8042C1D0;
			do {
				if (fn_8004A5B8(*manager, i, 0) == 1) {
					invoke = 1;
					break;
				}
				++i;
			} while (i <= 7);
			if (!invoke && fn_8004A5B8(lbl_8042C1D0, 15, 0) == 1)
				invoke = 1;
			break;
		}
		default:
			invoke = 1;
			break;
	}
	if (invoke == 1)
		state->invoke(argument);
	return argument;
}

extern "C" int CaptureIwamizuCallback(IwamizuCallback* callback, void** output)
{
	*output            = callback;
	callback->function = (void (*)())fn_3_81858;
	if (callback->function == 0)
		callback->function = fn_8014F1B0;
	return 0;
}

extern "C" void* fn_3_81858(void* argument)
{
	((void (*)(void*))((IwamizuCallback*)IwamizuAnimationCallback)->function)(argument);
	return argument;
}

struct SetData {
	Vec3 position;
	u32 flags;
	u8 pad10[0x1C];
	void* values;
};

struct IwamizuMotion {
	SetData* frame;
	void** vtable;
	void* animation;
	u8 pad0C[4];
};

class TObject;

class TObject
{
public:
	void* className;
	u16 signal;
	u8 pad06[0x12];
	void** vtable;
	s16 pad1C;
	s16 objectSize;
	u8 pad20[8];

	TObject(TObject*);
	~TObject();
	static void* operator new(unsigned long size, void* heap) { return fn_80018A34(heap, size); }
};

struct TObjS01Iwamizu : TObject {
	IwamizuMotion motion;

	TObjS01Iwamizu();
	TObjS01Iwamizu(TObject*);
	~TObjS01Iwamizu();
};

static inline void SetIwamizuPosition(void* self)
{
	void* clump     = PTR(self, 0x30);
	void* frame     = *(void**)((u8*)clump + 4);
	f32* values     = *(f32**)((u8*)PTR(self, 0x28) + 0x2C);
	f32 value       = values[0];
	Vec3Bits scale  = *(const Vec3Bits*)&IwamizuZeroVector;
	*(f32*)&scale.x = value;
	*(f32*)&scale.y = value;
	*(f32*)&scale.z = value;
	fn_8019EC30(frame, (Vec3*)&scale, 0);
	fn_8019ED68(frame, &lbl_80239984, IwamizuMinimum * (f32)(s32)WORD(PTR(self, 0x28), 0x10), 2);
	fn_8019EB94(frame, PTR(self, 0x28), 2);
}

extern "C" void SetPosition__14TObjS01IwamizuFv(void* self)
{
	SetIwamizuPosition(self);
}

extern "C" void Disp__14TObjS01IwamizuFv(void* self)
{
	if (IwamizuDispInitialized == 0) {
		fn_8011B844(IwamizuClump, IwamizuSoundVolume);
		fn_8014FFBC(PTR(self, 0x30), (void*)fn_8005BF88, (int)IwamizuRenderState);
		IwamizuDispInitialized = 1;
	}
}

#pragma opt_propagation off
#pragma opt_lifetimes off
extern "C" void Exec__14TObjS01IwamizuFv(void* self)
{
	s8 pan;
	if (fn_8005B9F0((u8*)self + 0x28) || fn_8005B8BC((u8*)self + 0x28)) {
		HALF(self, 4) |= 1;
	} else {
		if (fn_8005B8D8((u8*)self + 0x28)) {
			SetIwamizuPosition(self);
		} else {
			if (SBYTE(lbl_8042C180, 0x1F) == 0) {
				IwamizuDispInitialized = 0;
				if (lbl_8042C388 != 0)
					fn_800B4A38(
					    lbl_8042C388, 0x5012, PTR(self, 0x28), self, 3, (pan = IwamizuSoundPan), 5);
			}
		}
	}
}
#pragma opt_lifetimes reset
#pragma opt_propagation reset

extern "C" void* __dt__14TObjS01IwamizuFv(void* self, s16 flags)
{
	if (self != 0) {
		WORD(self, 0x18)         = (u32)IwamizuVtable;
		WORD(self, 0x2C)         = (u32)IwamizuVtable + 0x2C;
		register void* animation = PTR(self, 0x30);
		if (animation != 0) {
			fn_8015BBF8(*(void**)((u8*)lbl_8042C1D0 + 0x72AC), animation);
			fn_80150958(PTR(self, 0x30));
			PTR(self, 0x30) = 0;
		}
		dtor_8005BD3C((u8*)self + 0x28, 0);
		__dt__7TObjectFv(self, 0);
		if (flags > 0)
			fn_800189A4(lbl_8042C148, self);
	}
	return self;
}

inline TObject::TObject(TObject* parent)
{
	__ct__7TObjectFP7TObject(this, parent);
}

static inline void InitializeIwamizuBody(void* self)
{
	fn_8005BE6C((u8*)self + 0x28);
	WORD(self, 0x18) = (u32)IwamizuVtable;
	WORD(self, 0x2C) = (u32)IwamizuVtable + 0x2C;
	f32* values      = *(f32**)((u8*)PTR(self, 0x28) + 0x2C);
	PTR(self, 0)     = IwamizuClassNamePtr;
	HALF(self, 0x1E) = 0x38;
	if (fn_8005B8D8((u8*)self + 0x28)) {
		if (IwamizuZero == *values)
			*values = IwamizuOne;
		if (*(s8*)((u8*)values + 8) < 0 || *(s8*)((u8*)values + 8) >= 4)
			*(s8*)((u8*)values + 8) = 0;
	}
	PTR(self, 0x30) = fn_80150588(IwamizuAnimation);
	fn_8015BB08(*(void**)((u8*)lbl_8042C1D0 + 0x72AC), PTR(self, 0x30));
	fn_8014FFBC(PTR(self, 0x30), (void*)SetIwamizuCallback, *(s8*)((u8*)values + 8));
	SetIwamizuPosition(self);
}

TObjS01Iwamizu::TObjS01Iwamizu(TObject* parent)
    : TObject(parent)
{
	InitializeIwamizuBody(this);
}

inline TObjS01Iwamizu::TObjS01Iwamizu()
    : TObject((TObject*)lbl_8042C110)
{
	InitializeIwamizuBody(this);
}

extern "C" void EditOnChange__14TObjS01IwamizuFP13SETDATA_PARAM(void*, SetData* setData)
{
	f32* values = (f32*)setData->values;
	if (values[0] < IwamizuZero)
		values[0] = IwamizuZero;
	if (values[1] < IwamizuZero)
		values[1] = IwamizuZero;
	s8& mode = *(s8*)((u8*)values + 8);
	if (mode < 0)
		mode = 0;
	if (mode >= 4)
		mode = 3;
	IwamizuFieldNames[2] = (char*)IwamizuModeTable[mode];
}

extern "C" void endObjS01Iwamizu()
{
	if (IwamizuClump != 0) {
		fn_8011B7CC(IwamizuClump);
		IwamizuClump = 0;
	}
	if (IwamizuScratch[0] != 0) {
		__dl__FPv(IwamizuScratch[0]);
		IwamizuScratch[0] = 0;
	}
	if (IwamizuAnimation != 0) {
		fn_80150958(IwamizuAnimation);
		IwamizuAnimation         = 0;
		IwamizuAnimationCallback = 0;
	}
}

#pragma optimization_level reset
#pragma opt_common_subs reset
extern "C" void initObjS01Iwamizu()
{
	void* archive = *(void**)((u8*)lbl_8042C1D0 + 0x8C18);
	if (archive != 0) {
		IwamizuArchive = archive;
		fn_801A4C84(archive);
	} else {
		return;
	}
	fn_800BC9F4(*(void**)((u8*)lbl_8042C298 + 0xA50), &lbl_802FF5A0);
	void* model      = fn_800BC6CC(*(void**)((u8*)lbl_8042C298 + 0xA50), IwamizuModelName);
	IwamizuAnimation = fn_800BB92C(*(void**)((u8*)lbl_8042C298 + 0xA50), model, &lbl_802FF5A0);
	IwamizuAnimationCallback = fn_8005E394(IwamizuAnimation, 0);
	void* animation = fn_800BC6CC(*(void**)((u8*)lbl_8042C298 + 0xA50), IwamizuAnimationName);
	IwamizuClump    = fn_800BAE0C(*(void**)((u8*)lbl_8042C298 + 0xA50), animation, &lbl_802FF5A0);
	if (IwamizuAnimation != 0 && IwamizuClump != 0) {
		*(void**)IwamizuRenderState = IwamizuClump;
		fn_8005C014(fn_8005E394(IwamizuAnimation, 0), IwamizuRenderState);
	}
}
#pragma optimization_level 2
#pragma opt_common_subs off

extern "C" void startObj_S01_Iwamizu()
{
	new (lbl_8042C148) TObjS01Iwamizu();
}

#pragma optimization_level reset
#pragma opt_common_subs reset
extern "C" void __sinit_o_s01_iwamizu_cpp()
{
	IwamizuEntry.flags      = 0;
	IwamizuEntry.reserved2  = 0;
	IwamizuEntry.name       = IwamizuObjectName;
	IwamizuEntry.init       = initObjS01Iwamizu;
	IwamizuEntry.end        = endObjS01Iwamizu;
	IwamizuEntry.start      = startObj_S01_Iwamizu;
	IwamizuEntry.reserved   = 0;
	IwamizuEntry.flags      = 0x21000;
	IwamizuEntry.reserved2  = 0;
	IwamizuEntry.category   = 0x32;
	IwamizuEntry.id         = 0x186;
	IwamizuEntry.count      = 2;
	IwamizuEntry.subtype    = 0;
	IwamizuEntry.fieldTypes = IwamizuFieldTypes;
	IwamizuEntry.fieldNames = IwamizuFieldNames;
	if (IwamizuEntry.fieldTypes != 0) {
		IwamizuEntry.flags |= 8;
	} else {
		IwamizuEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const IwamizuCtorEntry)() = __sinit_o_s01_iwamizu_cpp;

extern "C" f32 IwamizuSoundVolume    = 1.6f;
extern "C" s8 IwamizuSoundPan        = 10;
extern "C" char IwamizuScale[]       = "SCALE";
extern "C" char IwamizuSpeed[]       = "SPEED";
extern "C" char IwamizuBlock[]       = "BLOCK";
extern "C" char IwamizuUnused[]      = "NOT IN USE";
extern "C" char* IwamizuFieldNames[] = {
	IwamizuScale,
	IwamizuSpeed,
	IwamizuBlock,
	IwamizuUnused,
	IwamizuUnused,
};
extern "C" char IwamizuBlockAll[]   = "BLOCK ALL";
extern "C" char IwamizuBlock3[]     = "BLOCK 3";
extern "C" char IwamizuBlock45[]    = "BLOCK 4 5";
extern "C" char IwamizuBlockRest[]  = "BLOCK 567 15";
extern "C" void* IwamizuModeTable[] = {
	IwamizuBlockAll,
	IwamizuBlock3,
	IwamizuBlock45,
	IwamizuBlockRest,
};
extern "C" char IwamizuClassName[]   = "TObjS01Iwamizu";
extern "C" char* IwamizuClassNamePtr = IwamizuClassName;
extern "C" void* IwamizuVtable[]     = {
	0,
	0,
	(void*)__dt__14TObjS01IwamizuFv,
	(void*)Exec__14TObjS01IwamizuFv,
	(void*)Disp__14TObjS01IwamizuFv,
	(void*)objDefaultTDisp,
	(void*)objDefaultPDisp,
	(void*)objDefaultImmAftSetRaster,
	(void*)objDefaultDebug,
	(void*)fn_80017854,
	(void*)objDefaultRender,
	0,
	0,
	(void*)fn_3_82320,
	(void*)EditOnChange__14TObjS01IwamizuFP13SETDATA_PARAM,
};
extern "C" char IwamizuModelName[]     = "s01_an_iwamizu.dff";
extern "C" char IwamizuAnimationName[] = "s01_iwamizu_anm.uvb";
extern "C" char IwamizuObjectName[]    = "S01D IWAMIZU ";
extern "C" char IwamizuFieldTypes[]    = "FFccs";
extern "C" u16 IwamizuId               = 45;

extern "C" {
void* IwamizuArchive;
void* IwamizuAnimation;
void* IwamizuAnimationCallback;
void* IwamizuScratch[2];
void* IwamizuClump;
s32 IwamizuDispInitialized;
u8 IwamizuRenderState[0x44];
ObjectEntry IwamizuEntry;
}

extern "C" __declspec(section ".rodata") const Vec3 IwamizuZeroVector = { 0.0f, 0.0f, 0.0f };
extern "C" __declspec(section ".rodata") const f32 IwamizuMinimum     = 0.0054931640625f;
extern "C" __declspec(section ".rodata") const f64 IwamizuIntBias     = 4503601774854144.0;
extern "C" __declspec(section ".rodata") const f32 IwamizuZero        = 0.0f;
extern "C" __declspec(section ".rodata") const f32 IwamizuOne         = 1.0f;
