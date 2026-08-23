#include "types.h"

// PS2 beta symbols identify the original o_sample.cpp translation unit and
// TObjSample method family. The retail GameCube vtable, class and editor
// strings, registration record, constructor entry, and contiguous section
// ownership independently establish this C++ TU boundary.

struct Vec3 {
	f32 x;
	f32 y;
	f32 z;
};

struct Rot3 {
	s32 x;
	s32 y;
	s32 z;
};

struct PathParams {
	f32 distance;
	s8 speed;
};

struct SETDATA_PARAM {
	Vec3 position;
	u8 field0C[0xC];
	u32 flags;
	u8 field1C[0x10];
	PathParams* params;
};

struct TObject {
	char* className;
	u16 signal;
	u16 tag;
	TObject* prev;
	TObject* next;
	TObject* parent;
	TObject* child;
	void** vtable;
	s16 field1C;
	s16 objectSize;
	s16 field20;
	s16 field22;
	s16 field24;
	s16 field26;
};

struct TMotion {
	SETDATA_PARAM* frame;
	void** vtable;
};

struct FlagWord {
	u32 value;
};

struct SETOBJ_PARAM {
	char* name;
	void (*load)();
	void (*unload)();
	void (*create)();
	void (*reset)(SETOBJ_PARAM*);
	FlagWord flags;
	FlagWord field18;
	u16 objectId;
	u16 field1E;
	u8 field20;
	u8 field21;
	u8 padding22[2];
	char* fieldTypes;
	char** fieldNames;
	u8 padding2C[4];
};

class TObjSample;

class SampleObjectBase
{
public:
	u8 storage[0x24];

	virtual TObjSample* Destroy(s16 flags) = 0;
	virtual void Exec()                    = 0;
	virtual void Disp()                    = 0;
	virtual void Hook0()                   = 0;
	virtual void Hook1()                   = 0;
	virtual void Hook2()                   = 0;
	virtual void Hook3()                   = 0;
	virtual void EngineHook();
	virtual void Hook4() = 0;
};

class SampleMotionBase
{
public:
	SETDATA_PARAM* frame;

	virtual void EditOnChange(SETDATA_PARAM* frame) = 0;
};

class TObjSample : public SampleObjectBase, public SampleMotionBase
{
public:
	Vec3 position;
	s32 angle;
	s32 timer;

	virtual TObjSample* Destroy(s16 flags);
	virtual void Exec();
	virtual void Disp();
	virtual void Hook0();
	virtual void Hook1();
	virtual void Hook2();
	virtual void Hook3();
	virtual void Hook4();
	virtual void EditOnChange(SETDATA_PARAM* frame);

	void* operator new(unsigned long size);
	void operator delete(void* object);
};

extern "C" {
void setSampleWord38(TObjSample* object, u32 value);
void setSampleWord30(TObjSample* object, u32 value);
void sampleHook0();
void sampleHook1();
void sampleHook2();
void sampleHook3();
void sampleHook4();
void setFlagBits(FlagWord* word, u32 bits);
void copyVec3(Vec3* destination, const Vec3* source);
void markSampleForDeletion(TObjSample* object);
TObjSample* constructObjSample(TObjSample* object, TObject* owner);
void sampleReset(SETOBJ_PARAM*);
void sampleUnload();
void sampleLoad();
void startObjSample();
void* allocSampleObject(u32 size);
void registerObjSample();
SETOBJ_PARAM* setupObjClass(SETOBJ_PARAM* param, char* name, void (*load)(), void (*unload)(),
    void (*create)(), void (*reset)(SETOBJ_PARAM*), u32 flags, u32 field18, u8 field20,
    u16 objectId, u16 field1E, u8 field21, char* fieldTypes, char** fieldNames);
void clearFlagBits(FlagWord* word, u32 bits);
void assignFlagWord(FlagWord* word, u32 value);
FlagWord* initFlagWord(FlagWord* word);
void zeroFlagWord(FlagWord* word);
void drawSample(void* display, Vec3* position, f32 scaleX, f32 scaleY, void* model);

void Error__7TObjectFPc();
void* fn_80018A34(void* heap, u32 size);
void fn_800189A4(void* heap, void* object);
void fn_80051EF0(void* context, Vec3* vector, const Rot3* rotation);
s32 fn_8005B8BC(TMotion* motion);
s32 fn_8005B8D8(TMotion* motion);
s32 fn_8005B9F0(TMotion* motion);
void dtor_8005BD3C(TMotion* motion, s16 flags);
void fn_8005BE6C(TMotion* motion);
void fn_800D72F4(const Vec3* first, const Vec3* second, Vec3* result);
void __ct__7TObjectFP7TObject(TObject* object, TObject* owner);
void __dt__7TObjectFv(TObject* object, s16 flags);

extern void* lbl_8042B020;
extern void* lbl_8042B088;
extern TObject* lbl_8042C110;
extern void* lbl_8042C148;
extern void* __vt__10TObjSample[];
}

char SampleFieldRadius[]              = "hankei";
char SampleFieldSpeed[]               = "kaiten sokudo";
char* SampleFieldNames[]              = { SampleFieldRadius, SampleFieldSpeed };
char TObjSampleClassName[]            = "TObjSample";
char* CL_TObjSample                   = TObjSampleClassName;
f32 SampleDisplayScaleX               = 1.0f;
f32 SampleDisplayScaleY               = 1.0f;
extern "C" void* __vt__10TObjSample[] = { 0 };

extern "C" void setSampleWord38(TObjSample* object, u32 value)
{
	*(u32*)((u8*)object + 0x38) = value;
}

extern "C" void setSampleWord30(TObjSample* object, u32 value)
{
	*(u32*)((u8*)object + 0x30) = value;
}

void TObjSample::Hook0() { }

void TObjSample::Hook1() { }

void TObjSample::Hook2() { }

void TObjSample::Hook3() { }

void TObjSample::Hook4() { }

char TObjSampleDisplayName[] = "SAMPLE OBJECT";
char TObjSampleFieldTypes[]  = "fc";

SETOBJ_PARAM ObjSampleParam;

void TObjSample::Disp()
{
	drawSample(lbl_8042B020, &position, SampleDisplayScaleX, SampleDisplayScaleY,
	    (void*)((u8*)frame + 0xC));
}

void TObjSample::Exec()
{
	Vec3 offset;
	Rot3 rotation;
	PathParams* params = frame->params;

	if (fn_8005B9F0((TMotion*)&frame) != 0 || fn_8005B8BC((TMotion*)&frame) != 0) {
		markSampleForDeletion(this);
	} else if (fn_8005B8D8((TMotion*)&frame) != 0) {
		copyVec3(&position, &frame->position);
	} else {
		angle += (s32)(182.04445f * params->speed);
		offset.x = offset.y = 0.0f;
		offset.z            = params->distance;
		rotation.x = rotation.z = 0;
		rotation.y              = angle;
		fn_80051EF0(lbl_8042B088, &offset, &rotation);
		fn_800D72F4(&frame->position, &offset, &position);
		timer++;
		if (timer > 600) {
			setFlagBits((FlagWord*)&frame->flags, 0x10000);
		}
	}
}

extern "C" void setFlagBits(FlagWord* word, u32 bits)
{
	word->value |= bits;
}

extern "C" void copyVec3(Vec3* destination, const Vec3* source)
{
	destination->x = source->x;
	destination->y = source->y;
	destination->z = source->z;
}

extern "C" void markSampleForDeletion(TObjSample* object)
{
	((TObject*)object)->signal |= 1;
}

TObjSample* TObjSample::Destroy(s16 flags)
{
	if (this != 0) {
		((TObject*)this)->vtable   = __vt__10TObjSample;
		((TMotion*)&frame)->vtable = __vt__10TObjSample + 11;
		dtor_8005BD3C((TMotion*)&frame, 0);
		__dt__7TObjectFv((TObject*)this, 0);
		if (flags > 0) {
			TObjSample::operator delete(this);
		}
	}
	return this;
}

void TObjSample::operator delete(void* object)
{
	fn_800189A4(lbl_8042C148, object);
}

extern "C" TObjSample* constructObjSample(TObjSample* sample, TObject* owner)
{
	__ct__7TObjectFP7TObject((TObject*)sample, owner);
	fn_8005BE6C((TMotion*)&sample->frame);
	((TObject*)sample)->vtable         = __vt__10TObjSample;
	((TMotion*)&sample->frame)->vtable = __vt__10TObjSample + 11;
	((TObject*)sample)->className      = CL_TObjSample;
	((TObject*)sample)->objectSize     = sizeof(TObjSample);
	copyVec3(&sample->position, &sample->frame->position);
	sample->angle = 0;
	sample->timer = 0;
	return sample;
}

extern const f32 SampleMinimumRadius = 1.0f;
static const f32 SampleLimits[5]     = { 10.0f, 0.0f, 1.5f, 0.0f, 0.0f };

void TObjSample::EditOnChange(SETDATA_PARAM* frame)
{
	PathParams* params = frame->params;

	if (params->distance < SampleMinimumRadius) {
		params->distance = SampleMinimumRadius;
	}
	if (params->distance > SampleLimits[0]) {
		params->distance = SampleLimits[0];
	}
	if (params->speed < 1) {
		params->speed = 1;
	}
	if (params->speed > 5) {
		params->speed = 5;
	}
}

extern "C" void sampleReset(SETOBJ_PARAM*) { }

extern "C" void sampleUnload() { }

extern "C" void sampleLoad() { }

extern "C" void startObjSample()
{
	TObjSample* object = (TObjSample*)TObjSample::operator new(sizeof(TObjSample));
	if (object != 0) {
		object = constructObjSample(object, lbl_8042C110);
	}
}

void* TObjSample::operator new(unsigned long size)
{
	return fn_80018A34(lbl_8042C148, size);
}

extern "C" void registerObjSample()
{
	setupObjClass(&ObjSampleParam, TObjSampleDisplayName, sampleLoad, sampleUnload, startObjSample,
	    sampleReset, 0x20000, 0, 0x1E, 0xFFFF, 2, 0, TObjSampleFieldTypes, SampleFieldNames);
}

extern "C" SETOBJ_PARAM* setupObjClass(SETOBJ_PARAM* param, char* name, void (*load)(),
    void (*unload)(), void (*create)(), void (*reset)(SETOBJ_PARAM*), u32 flags, u32 field18,
    u8 field20, u16 objectId, u16 field1E, u8 field21, char* fieldTypes, char** fieldNames)
{
	initFlagWord(&param->flags);
	initFlagWord(&param->field18);
	param->name   = name;
	param->load   = load;
	param->unload = unload;
	param->create = create;
	param->reset  = reset;
	assignFlagWord(&param->flags, flags);
	assignFlagWord(&param->field18, field18);
	param->field20    = field20;
	param->objectId   = objectId;
	param->field1E    = field1E;
	param->field21    = field21;
	param->fieldTypes = fieldTypes;
	param->fieldNames = fieldNames;
	if (param->fieldTypes != 0) {
		setFlagBits(&param->flags, 8);
	} else {
		clearFlagBits(&param->flags, 8);
	}
	return param;
}

extern "C" void clearFlagBits(FlagWord* word, u32 bits)
{
	word->value &= ~bits;
}

extern "C" void assignFlagWord(FlagWord* word, u32 value)
{
	word->value = value;
}

extern "C" FlagWord* initFlagWord(FlagWord* word)
{
	zeroFlagWord(word);
	return word;
}

extern "C" void zeroFlagWord(FlagWord* word)
{
	word->value = 0;
}

extern "C" void drawSample(void*, Vec3*, f32, f32, void*) { }

__declspec(section ".ctors") void (*const TObjSampleCtorEntry)() = registerObjSample;
