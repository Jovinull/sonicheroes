#include "types.h"

struct Vec3 {
	f32 x, y, z;
};

struct Vec4 {
	f32 x, y, z, w;
};

struct RpClump;
struct THeapCtrl;

struct Frame {
	Vec3 position;
	s32 angleX;
	s32 angleY;
	s32 angleZ;
	u32 flags;
	u8 pad1C[0x10];
	void* params;
};

struct TObject {
	const char* className;
	u16 signal;
	u16 tag;
	TObject* prev;
	TObject* next;
	TObject* parent;
	TObject* child;
	void** vtable;
	s16 unk1C;
	s16 objectSize;
	u8 pad20[8];

	static void* operator new(unsigned long size);
	static void* operator new(unsigned long size, THeapCtrl* heap);
	TObject(TObject* parent);
	~TObject();
};

struct Motion {
	Frame* frame;
	void** vtable;
};

struct FlowerParams {
	s8 type;
	u8 pad1[3];
	f32 scale;
};

struct FlowerThunkPrimary {
	u8 pad04[0x24];
	virtual void PrimarySlot();
};

struct FlowerThunkSecondary {
	virtual void EditOnChange(Frame*);
};

struct FlowerThunk : FlowerThunkPrimary, FlowerThunkSecondary {
	virtual void EditOnChange(Frame*);
};

struct ObjectEntry {
	const char* name;
	void (*load)();
	void (*unload)();
	void (*create)();
	void (*reset)(void*);
	u32 flags;
	u32 unk18;
	s16 id;
	s16 count;
	u8 category;
	u8 unk21;
	u8 pad22[2];
	const char* fieldTypes;
	const char** fieldNames;
	u32 pad2C;
};

struct TObjS01Flower : TObject {
	Motion motion;
	s8 type;
	u8 pad31[3];
	void* clump;

	TObjS01Flower(TObject* parent);
};

extern "C" TObject* lbl_8042C110;
extern "C" THeapCtrl* lbl_8042C148;
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_8029C310[];
extern "C" u8 lbl_802FF5A0[];
extern "C" Vec3 lbl_80239978;
extern "C" Vec3 lbl_80239984;
extern "C" Vec3 lbl_80239990;
extern "C" s8 flowerTypeCount;
extern "C" RpClump* flowerModels[9];
extern "C" const char* flowerAssetNames[9];
extern "C" const char* flowerTypeNames[9];
extern "C" const char flowerFormat[];
extern "C" const char* flowerClassName;
extern "C" void* flowerVtable[];
extern "C" const char* flowerFieldNames[2];
extern "C" void* flowerResources[2];
extern "C" ObjectEntry flowerEntry;

extern "C" TObject* __ct__7TObjectFP7TObject(TObject*, TObject*);
extern "C" void __dt__7TObjectFv(TObject*, s32);
extern "C" void fn_800189A4(void*, void*);
extern "C" void* fn_80018A34(THeapCtrl*, u32);
extern "C" const char* fn_800194C4(void*);
extern "C" s32 fn_8005B8BC(Motion*);
extern "C" s32 fn_8005B8D8(Motion*);
extern "C" s32 fn_8005B9F0(Motion*);
extern "C" void dtor_8005BD3C(Motion*, s32);
extern "C" void fn_8005BE6C(Motion*);
extern "C" void* fn_800BC6CC(void*, const char*);
extern "C" RpClump* fn_800BB92C(void*, void*, void*);
extern "C" void fn_800BC9F4(void*, void*);
extern "C" void* fn_80150588(RpClump*);
extern "C" void fn_80150958(void*);
extern "C" void fn_8015BB08(void*, void*);
extern "C" void fn_8015BBF8(void*, void*);
extern "C" void* fn_8015BD78(void*);
extern "C" void fn_8019EB94(void*, Frame*, s32);
extern "C" void fn_8019EC30(void*, const Vec3*, s32);
extern "C" void fn_8019ED68(void*, const Vec3*, f32, s32);
extern "C" void fn_801A4C84(void*);
extern "C" s32 sprintf(char*, const char*, ...);

inline TObject::TObject(TObject* parent)
{
	__ct__7TObjectFP7TObject(this, parent);
}

extern "C" const Vec4 flowerZeroConstants[3] = {
	{ 0.0f, 0.0f, 0.0f, 1.0f },
	{ 0.0f, 0.0f, 0.0f, 1.0f },
	{ 0.0f, 0.0f, 0.0f, 1.0f },
};

static inline void setFlowerPosition(TObjS01Flower* object, const Vec3& zero)
{
	FlowerParams* params = (FlowerParams*)object->motion.frame->params;
	void* model          = *(void**)((u8*)object->clump + 4);
	Vec3 scale           = zero;

	scale.x = params->scale;
	scale.y = scale.x;
	scale.z = scale.x;
	fn_8019EC30(model, &scale, 0);
	fn_8019ED68(model, &lbl_80239984, 0.0054931640625f * (f32)object->motion.frame->angleY, 2);
	fn_8019ED68(model, &lbl_80239978, 0.0054931640625f * (f32)object->motion.frame->angleX, 2);
	fn_8019ED68(model, &lbl_80239990, 0.0054931640625f * (f32)object->motion.frame->angleZ, 2);
	fn_8019EB94(model, object->motion.frame, 2);
}

#pragma force_active on
extern "C" void flowerSetPosition(TObjS01Flower* object)
{
	setFlowerPosition(object, *(const Vec3*)&flowerZeroConstants[0]);
}
#pragma force_active reset

extern "C" void flowerDisp() { }

extern "C" void flowerExec(TObjS01Flower* object)
{
	s32 result = fn_8005B9F0(&object->motion);
	if (result != 0 || fn_8005B8BC(&object->motion) != 0) {
		object->signal |= 1;
	} else if (fn_8005B8D8(&object->motion) != 0) {
		setFlowerPosition(object, *(const Vec3*)&flowerZeroConstants[0]);
	}
}

extern "C" TObjS01Flower* flowerDtor(TObjS01Flower* object, s16 flags)
{
	if (object != NULL) {
		object->vtable        = flowerVtable;
		object->motion.vtable = flowerVtable + 11;
		if (object->clump != NULL) {
			void* clump  = object->clump;
			void* atomic = fn_8015BD78(clump);
			fn_8015BBF8(atomic, clump);
			fn_80150958(object->clump);
			object->clump = NULL;
		}
		dtor_8005BD3C(&object->motion, 0);
		__dt__7TObjectFv(object, 0);
		if (flags > 0)
			fn_800189A4(lbl_8042C148, object);
	}
	return object;
}

#pragma force_active on
TObjS01Flower::TObjS01Flower(TObject* parent)
    : TObject(parent)
{
	TObjS01Flower* object = this;
	fn_8005BE6C(&object->motion);
	vtable                = flowerVtable;
	object->motion.vtable = flowerVtable + 11;
	FlowerParams& params  = *(FlowerParams*)object->motion.frame->params;
	className             = flowerClassName;
	objectSize            = 0x38;
	if (params.type >= flowerTypeCount || params.type < 0)
		params.type = 0;
	object->type  = params.type;
	object->clump = fn_80150588(flowerModels[object->type]);
	fn_8015BB08(*(void**)(lbl_8042C1D0 + 0x7278), object->clump);
	if (params.scale == 0.0f)
		params.scale = 1.0f;
	setFlowerPosition(object, *(const Vec3*)&flowerZeroConstants[0]);
}
#pragma force_active reset

void FlowerThunk::EditOnChange(Frame* frame)
{
	TObjS01Flower* object = (TObjS01Flower*)this;
	FlowerParams* params  = (FlowerParams*)frame->params;
	if (params->type < 0)
		params->type = 0;
	if (params->type >= flowerTypeCount)
		params->type = flowerTypeCount - 1;
	f32 scale        = params->scale;
	f32 minimumScale = 0.0f;
	if (scale < minimumScale)
		params->scale = minimumScale;
	if (object->type != params->type) {
		if (object->clump != NULL) {
			void* clump  = object->clump;
			void* atomic = fn_8015BD78(clump);
			fn_8015BBF8(atomic, clump);
			fn_80150958(object->clump);
		}
		object->clump = fn_80150588(flowerModels[params->type]);
		fn_8015BB08(*(void**)(lbl_8042C1D0 + 0x7278), object->clump);
		object->type = params->type;
	}
	flowerFieldNames[0] = flowerTypeNames[object->type];
}

extern "C" void flowerEnd()
{
	for (s8 i = 0; i < flowerTypeCount; ++i) {
		if (flowerModels[i] != NULL) {
			fn_80150958(flowerModels[i]);
			flowerModels[i] = NULL;
		}
	}
}

extern "C" void flowerInit()
{
	char path[64];
	register const char* stage = fn_800194C4(lbl_8029C310);
	if (*(s32*)(lbl_8029C310 + 0x2C) == 0x19)
		flowerTypeCount = 1;
	else
		flowerTypeCount = 9;
	void* resource = *(void**)(lbl_8042C1D0 + 0x8C18);
	if (resource != NULL) {
		flowerResources[0] = resource;
		fn_801A4C84(resource);
	} else {
		return;
	}
	fn_800BC9F4(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	s32 i = 0;
	while (i < flowerTypeCount) {
		sprintf(path, flowerFormat, stage, flowerAssetNames[i]);
		flowerModels[i] = fn_800BB92C(*(void**)(lbl_8042C298 + 0xA50),
		    fn_800BC6CC(*(void**)(lbl_8042C298 + 0xA50), path), lbl_802FF5A0);
		++i;
	}
}

inline void* TObject::operator new(unsigned long size)
{
	return fn_80018A34(lbl_8042C148, size);
}

inline void* TObject::operator new(unsigned long size, THeapCtrl* heap)
{
	return fn_80018A34(heap, size);
}

extern "C" void flowerCreate()
{
	// The original uses TObject's heap-placement new.  Keeping the heap as the
	// placement argument and TObject's non-trivial destructor visible makes
	// GC/1.3.2 null-test the allocator result before assigning the constructed
	// object's long-lived register.
	new (lbl_8042C148) TObjS01Flower(lbl_8042C110);
}

extern "C" s8 flowerTypeCount       = 9;
extern "C" RpClump* flowerModels[9] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };

extern "C" char flowerAsset0[] = "pn_hana1_1.dff";
extern "C" char flowerAsset1[] = "pn_hana1_2.dff";
extern "C" char flowerAsset2[] = "pn_hana1_3.dff";
extern "C" char flowerAsset3[] = "pn_hana2.dff";
extern "C" char flowerAsset4[] = "pn_hana3_1.dff";
extern "C" char flowerAsset5[] = "pn_hana3_2.dff";
extern "C" char flowerAsset6[] = "pn_hana4_1.dff";
extern "C" char flowerAsset7[] = "pn_hana4_2.dff";
extern "C" char flowerAsset8[] = "pn_hana5.dff";

extern "C" const char* flowerAssetNames[9] = {
	flowerAsset0,
	flowerAsset1,
	flowerAsset2,
	flowerAsset3,
	flowerAsset4,
	flowerAsset5,
	flowerAsset6,
	flowerAsset7,
	flowerAsset8,
};

extern "C" char flowerTypeField[]          = "Type   ";
extern "C" char flowerScaleField[]         = "SCALE";
extern "C" const char* flowerFieldNames[2] = { flowerTypeField, flowerScaleField };

extern "C" char flowerType0[]             = "TYPE1 1";
extern "C" char flowerType1[]             = "TYPE1 2";
extern "C" char flowerType2[]             = "TYPE1 3";
extern "C" char flowerType3[]             = "TYPE2";
extern "C" char flowerType4[]             = "TYPE1 3 1";
extern "C" char flowerType5[]             = "TYPE1 3 2";
extern "C" char flowerType6[]             = "TYPE1 4 1";
extern "C" char flowerType7[]             = "TYPE1 4 2";
extern "C" char flowerType8[]             = "TYPE1 5";
extern "C" const char* flowerTypeNames[9] = {
	flowerType0,
	flowerType1,
	flowerType2,
	flowerType3,
	flowerType4,
	flowerType5,
	flowerType6,
	flowerType7,
	flowerType8,
};

extern "C" char flowerClassNameString[] = "TObjS01Flower";
extern "C" const char* flowerClassName  = flowerClassNameString;

extern "C" void objDefaultTDisp();
extern "C" void PDisp__7TObjectFv();
extern "C" void ImmAftSetRaster__7TObjectFv();
extern "C" void Debug__7TObjectFv();
extern "C" void Error__7TObjectFPc();
extern "C" void Render__7TObjectFv();
extern "C" void EditOnChange__11FlowerThunkFP5Frame(FlowerThunk*, Frame*);
extern "C" void AdjustorEditOnChange__11FlowerThunkFP5Frame(FlowerThunk*, Frame*);

extern "C" void* flowerVtable[15] = {
	NULL,
	NULL,
	(void*)flowerDtor,
	(void*)flowerExec,
	(void*)flowerDisp,
	(void*)objDefaultTDisp,
	(void*)PDisp__7TObjectFv,
	(void*)ImmAftSetRaster__7TObjectFv,
	(void*)Debug__7TObjectFv,
	(void*)Error__7TObjectFPc,
	(void*)Render__7TObjectFv,
	NULL,
	NULL,
	(void*)AdjustorEditOnChange__11FlowerThunkFP5Frame,
	(void*)EditOnChange__11FlowerThunkFP5Frame,
};

extern "C" const char flowerFormat[8] = "%s_%s";
extern "C" char flowerDisplayName[]   = "S01 FLOWER";
extern "C" char flowerFieldTypes[]    = "cF";
extern "C" {
void* flowerResources[2];
ObjectEntry flowerEntry;
}

extern "C" void __sinit_o_s01_hana_cpp()
{
	flowerEntry.flags      = 0;
	flowerEntry.unk18      = 0;
	flowerEntry.name       = flowerDisplayName;
	flowerEntry.load       = flowerInit;
	flowerEntry.unload     = flowerEnd;
	flowerEntry.create     = flowerCreate;
	flowerEntry.reset      = NULL;
	flowerEntry.flags      = 0x21000;
	flowerEntry.unk18      = 0;
	flowerEntry.category   = 0x14;
	flowerEntry.id         = 0x180;
	flowerEntry.count      = 2;
	flowerEntry.unk21      = 0;
	flowerEntry.fieldTypes = flowerFieldTypes;
	flowerEntry.fieldNames = flowerFieldNames;
	if (flowerEntry.fieldTypes != NULL)
		flowerEntry.flags |= 8;
	else
		flowerEntry.flags &= ~8;
}

__declspec(section ".ctors") void (*const flowerCtorEntry)() = __sinit_o_s01_hana_cpp;
