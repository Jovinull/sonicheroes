#include "types.h"

// Retained PS2 symbols name this object TObjS11Spider and give its method
// family in the order the GameCube text keeps: SetPosition, DestroyClump,
// CloneClump, SetParameter, TDisp, Exec, the destructor, the TObject*
// constructor, EditOnChange and the endObj/initObj/startObj lifecycle
// functions. The "TObjS11Spider" class-name string in this unit's .data
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

struct SETDATA_PARAM {
	Vec3 position;
	sAngle angle;
	u32 flags;
	u8 pad1C[0x10];
	s32* params;
};

struct RwFrame;

struct RpClump {
	u8 pad00[4];
	RwFrame* frame;
};

struct GameState {
	u8 pad00[0x1F];
	s8 paused;
	s8 editMode;
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
s32 CheckRangeOut__10TObjSetObjFv(void*);
}

class TObjSetObj : public SetObjHdr
{
public:
	TObjSetObj();
	virtual void EditOnChange(SETDATA_PARAM*);

	s32 CheckRangeOut() { return CheckRangeOut__10TObjSetObjFv(this); }
	s32 CheckMustKill() { return CheckMustKill__10TObjSetObjFv(this); }
};

class C_COLLI
{
public:
	u8 pad00[0x88];
	C_COLLI();
	~C_COLLI();
};

class DealMaterial
{
public:
	u8 pad00[0x14];

	DealMaterial(RpClump*);
	~DealMaterial();
	void MulColor(f32*);
	void DefaultColor();
};

extern "C" {
extern void* lbl_8042C110;
extern void* lbl_8042C148;
extern GameState* lbl_8042C180;
extern void* lbl_8042C1D0;
extern void* lbl_8042C298;
extern u8 AxisY;
extern u8 lbl_802FF5A0;

void __ct__7TObjectFP7TObject(void*, void*);
void __dt__7TObjectFv(void*, s16);
void __ct__10TObjSetObjFv(void*);
void __dt__10TObjSetObjFv(void*, s16);
void __ct__7C_COLLIFv(void*);
void __dt__7C_COLLIFv(void*, s16);
void* Malloc__9THeapCtrlFUi(void*, u32);
void Free__9THeapCtrlFPv(void*, void*);
void objRpClumpForAllAtomicsToSetRenderCallbackToUseLight__FP7RpClumpUi(RpClump*, u32);
RpClump* LoadClumpEx__7ONEFILEFUiPc(void*, s32, void*);
s32 CheckFileID__7ONEFILEFPc(void*, const char*);
void LoadOneFile__7ONEFILEFPc(void*, void*);
f32 fn_800D7AE4(s32);
f32 fn_800D7B00(s32);
void fn_8014FF2C(RpClump*);
RpClump* fn_80150588(RpClump*);
void fn_80150958(RpClump*);
void fn_80194234(s32, s32);
void fn_80194294(s32, s32*);
void fn_80195790(void*, void*, f32, f32, s32);
void fn_8019E880(RwFrame*);
void fn_8019EB94(RwFrame*, Vec3*, s32);
void fn_801A4C84(void*);
int rand();
}

class TObjS11Spider : public TObject, public TObjSetObj, public C_COLLI
{
public:
	Vec3 position;
	sAngle angle;
	s32 type;
	s32 counter;
	f32 scale;
	f32 target;
	RpClump* clump;
	DealMaterial* material;
	RpClump* lights[4];
	DealMaterial* lightMaterials[4];

	void SetPosition();
	void DestroyClump();
	void CloneClump(RpClump*);
	void SetParameter();
	TObjS11Spider(TObject*);
	virtual void TDisp();
	virtual void Exec();
	inline virtual ~TObjS11Spider();
	virtual void EditOnChange(SETDATA_PARAM*);

	static void* operator new(unsigned long size, void* heap)
	{
		return Malloc__9THeapCtrlFUi(heap, size);
	}
};

// The constructor and destructor are written against the object's storage:
// retail constructs and destroys the TObjSetObj and C_COLLI members through
// out-of-line functions that keep their address names, which a C++ member
// call would rename. The compiler still generates the class vtable and its
// adjustor thunk from the virtual declarations above.
extern "C" {
TObjS11Spider* __dt__13TObjS11SpiderFv(TObjS11Spider*, s16);
extern void* __vt__13TObjS11Spider[];
}

#define SETOBJ(self) ((void*)((u8*)(self) + 0x28))

// The data names below are address names; their roles are descriptive guesses.
extern "C" {
char lbl_8_data_18120[] = "s11_k_spiderlight1.dff";
char lbl_8_data_18138[] = "s11_k_spiderlight2.dff";
char lbl_8_data_18150[] = "s11_k_spiderlight3.dff";
char lbl_8_data_18168[] = "s11_k_spiderlight4.dff";
char* lbl_8_data_18180[4]
    = { lbl_8_data_18120, lbl_8_data_18138, lbl_8_data_18150, lbl_8_data_18168 };
f32 lbl_8_data_18190               = 35.0f;
f32 lbl_8_data_18194               = 0.6f;
f32 lbl_8_data_18198               = 0.8f;
f32 lbl_8_data_1819C               = 0.5f;
s32 lbl_8_data_181A0               = 5;
f32 lbl_8_data_181A4               = 0.55f;
f32 lbl_8_data_181A8               = 0.4f;
f32 lbl_8_data_181AC               = 0.35f;
char* s11spiderObjectFieldNames[1] = { "type" };
char* lbl_8_data_181CC             = "TObjS11Spider";
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
RpClump* lbl_8_bss_1BD0[4];
SETOBJ_PARAM s11spiderObjectEntry;
void endObjS11Spider();
void initObjS11Spider();
void startObjS11Spider();
}

extern "C" void s11spiderObjectRegister()
{
	s11spiderObjectEntry.flags       = 0;
	s11spiderObjectEntry.field18     = 0;
	s11spiderObjectEntry.displayName = "S11SPIDER OBJECT";
	s11spiderObjectEntry.init        = initObjS11Spider;
	s11spiderObjectEntry.end         = endObjS11Spider;
	s11spiderObjectEntry.create      = startObjS11Spider;
	s11spiderObjectEntry.field10     = 0;
	s11spiderObjectEntry.flags       = 0x20000;
	s11spiderObjectEntry.field18     = 0;
	s11spiderObjectEntry.field20     = 0x1E;
	s11spiderObjectEntry.id          = 0x1189;
	s11spiderObjectEntry.count       = 2;
	s11spiderObjectEntry.field21     = 0;
	s11spiderObjectEntry.fieldTypes  = "i";
	s11spiderObjectEntry.fields      = s11spiderObjectFieldNames;
	if (s11spiderObjectEntry.fieldTypes != NULL)
		s11spiderObjectEntry.flags |= 8;
	else
		s11spiderObjectEntry.flags &= ~8;
}

__declspec(section ".ctors") void (*const s11spiderObjectCtorEntry)() = s11spiderObjectRegister;

extern "C" void startObjS11Spider()
{
	new (lbl_8042C148) TObjS11Spider((TObject*)lbl_8042C110);
}

extern "C" void initObjS11Spider()
{
	void* stage = *(void**)((u8*)lbl_8042C1D0 + 0x8C18);
	if (stage != NULL) {
		fn_801A4C84(stage);
	} else {
		return;
	}
	LoadOneFile__7ONEFILEFPc(*(void**)((u8*)lbl_8042C298 + 0xA50), &lbl_802FF5A0);
	for (int i = 0; i < 4; i++) {
		lbl_8_bss_1BD0[i] = LoadClumpEx__7ONEFILEFUiPc(*(void**)((u8*)lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)((u8*)lbl_8042C298 + 0xA50), lbl_8_data_18180[i]),
		    &lbl_802FF5A0);
	}
}

extern "C" void endObjS11Spider()
{
	for (int i = 0; i < 4; i++) {
		fn_80150958(lbl_8_bss_1BD0[i]);
		lbl_8_bss_1BD0[i] = NULL;
	}
}

void TObjS11Spider::EditOnChange(SETDATA_PARAM* data)
{
	s32* value = data->params;
	if (*value < 0) {
		*value = 0;
	}
	if (*value >= 4) {
		*value = 3;
	}
}

TObjS11Spider::TObjS11Spider(TObject* parent)
    : TObject(parent)
{
	className  = lbl_8_data_181CC;
	objectSize = sizeof(TObjS11Spider);
	SetParameter();
	clump     = NULL;
	lights[0] = NULL;
	lights[1] = NULL;
	lights[2] = NULL;
	lights[3] = NULL;
	counter   = 0;
	target    = 1.0f;
	CloneClump(lbl_8_bss_1BD0[type]);
}

extern "C" TObjS11Spider* __dt__13TObjS11SpiderFv(TObjS11Spider* self, s16 flags)
{
	if (self != NULL) {
		*(void***)((u8*)self + 0x18) = __vt__13TObjS11Spider;
		*(void***)((u8*)self + 0x2C) = __vt__13TObjS11Spider + 11;
		self->DestroyClump();
		__dt__7C_COLLIFv((u8*)self + 0x30, 0);
		__dt__10TObjSetObjFv(SETOBJ(self), 0);
		__dt__7TObjectFv(self, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, self);
		}
	}
	return self;
}

void TObjS11Spider::Exec()
{
	if (CheckRangeOut() != 0 || CheckMustKill() != 0) {
		signal |= 1;
		return;
	}
	SetPosition();
	if (lbl_8042C180->paused == 0) {
		counter++;
	}
	if (counter >= lbl_8_data_181A0 * 2) {
		counter = 0;
		f32 max = lbl_8_data_181A4;
		target  = max - (max - lbl_8_data_181A8) * (3.0517578125e-05f * rand());
	}
	s32 phase = counter / lbl_8_data_181A0;
	s32 step  = counter % lbl_8_data_181A0;
	f32 rate  = (target - lbl_8_data_181AC) / lbl_8_data_181A0;
	switch (phase) {
		case 0:
			scale = lbl_8_data_181AC + rate * step;
			break;
		case 1:
			scale = lbl_8_data_181AC + rate * (lbl_8_data_181A0 - step);
			break;
	}
}

void TObjS11Spider::TDisp()
{
	if (lbl_8042C180->editMode == 0) {
		f32 color[4];
		s32 state10;
		s32 state11;
		s32 state20;
		color[0] = color[1] = color[2] = scale;
		color[3]                       = 1.0f;
		fn_80194294(10, &state10);
		fn_80194294(11, &state11);
		fn_80194294(20, &state20);
		fn_80194234(10, 2);
		fn_80194234(11, 2);
		fn_80194234(20, 1);
		if (clump != NULL && material != NULL) {
			material->MulColor(color);
			fn_8014FF2C(clump);
			material->DefaultColor();
		}
		for (int i = 0; i < 4; i++) {
			if (i == 0) {
				color[0] *= lbl_8_data_18194;
				color[1] *= lbl_8_data_18194;
				color[2] *= lbl_8_data_18194;
			} else {
				color[0] *= lbl_8_data_18198;
				color[1] *= lbl_8_data_18198;
				color[2] *= lbl_8_data_18198;
			}
			if (lights[i] != NULL && lightMaterials[i] != NULL) {
				lightMaterials[i]->MulColor(color);
				fn_8014FF2C(lights[i]);
				lightMaterials[i]->DefaultColor();
			}
		}
		fn_80194234(20, state20);
		fn_80194234(10, state10);
		fn_80194234(11, state11);
	}
}

void TObjS11Spider::SetParameter()
{
	SETDATA_PARAM* data = frame;
	s32* params         = data->params;
	position            = data->position;
	data                = frame;
	angle               = data->angle;
	angle.z             = 0;
	angle.x             = 0;
	type                = *params;
}

void TObjS11Spider::CloneClump(RpClump* source)
{
	if (source != NULL) {
		if (clump == NULL) {
			clump = fn_80150588(source);
			if (clump != NULL) {
				objRpClumpForAllAtomicsToSetRenderCallbackToUseLight__FP7RpClumpUi(clump, 0x10);
				material = new DealMaterial(clump);
			}
		}
		for (int i = 0; i < 4; i++) {
			if (lights[i] == NULL) {
				lights[i] = fn_80150588(source);
				if (lights[i] != NULL) {
					objRpClumpForAllAtomicsToSetRenderCallbackToUseLight__FP7RpClumpUi(
					    lights[i], 0x10);
					lightMaterials[i] = new DealMaterial(lights[i]);
				}
			}
		}
	}
}

void TObjS11Spider::DestroyClump()
{
	if (material != NULL) {
		delete material;
		material = NULL;
	}
	if (clump != NULL) {
		fn_80150958(clump);
		clump = NULL;
	}
	for (int i = 0; i < 4; i++) {
		if (lightMaterials[i] != NULL) {
			delete lightMaterials[i];
			lightMaterials[i] = NULL;
		}
		if (lights[i] != NULL) {
			fn_80150958(lights[i]);
			lights[i] = NULL;
		}
	}
}

void TObjS11Spider::SetPosition()
{
	if (clump != NULL) {
		RwFrame* frame = clump->frame;
		Vec3 pos       = position;
		fn_8019EB94(frame, &position, 0);
		fn_80195790(
		    (u8*)frame + 0x10, &AxisY, 1.0f - fn_800D7AE4(angle.y), fn_800D7B00(angle.y), 1);
		fn_8019E880(frame);
		for (int i = 0; i < 4; i++) {
			pos.y += lbl_8_data_1819C;
			frame = lights[i]->frame;
			fn_8019EB94(frame, &pos, 0);
			fn_80195790(
			    (u8*)frame + 0x10, &AxisY, 1.0f - fn_800D7AE4(angle.y), fn_800D7B00(angle.y), 1);
			fn_8019E880(frame);
		}
	}
}
