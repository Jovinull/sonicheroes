#include "types.h"

struct RwV3d {
	f32 x;
	f32 y;
	f32 z;
};

struct sAngle {
	s32 x;
	s32 y;
	s32 z;
};

extern "C" void* __nw__10TObjSampleFUl(u32 size);

struct SETDATA_PARAM {
	RwV3d position;
	sAngle angle;
	u8 unk18[0x14];
	RwV3d* member;
};

struct CollisionInfo {
	u8 unk0[0x14];
	RwV3d scale;
};

struct RawTEndSPStage {
	u8 base[0xE4];
};

class TObject
{
public:
	const char* className;
	u16 signal;
	u16 tag;
	TObject* prev;
	TObject* next;
	TObject* parent;
	TObject* child;

	virtual ~TObject();
	virtual void Exec();
	virtual void PDisp();
	virtual void Disp();
	virtual void TDisp();
	virtual void ImmAftSetRaster();
	virtual void Debug();
	virtual void Error(char* message);
	virtual void Render();
};

struct TObjectTail {
	s16 unk1C;
	s16 objectSize;
	s16 unk20;
	s16 unk22;
	s16 unk24;
	s16 unk26;
};

class TEditMotion
{
public:
	SETDATA_PARAM* frame;

	virtual void EditOnChange(SETDATA_PARAM* setData);
};

class TEndSPStage : public TObject, public TObjectTail, public TEditMotion
{
public:
	u8 collisionArea[0x90];
	RwV3d ringScale;
	u8 unkCC[0xC];
	u8 controller[8];
	void* goalRing;

	virtual ~TEndSPStage();
	virtual void Exec();
	virtual void EditOnChange(SETDATA_PARAM* setData);
	void SetGoalRingParam();
	TEndSPStage(TObject* parent);

	static void Create();
	static void Finalize();
	static void Initialize();
	static void* operator new(unsigned long size) { return __nw__10TObjSampleFUl(size); }
	static void operator delete(void* object);
};

class TObjGoalring
{
public:
	u8 base[0x10C];
};

extern "C" {
void copyVec3(RwV3d* out, SETDATA_PARAM* setData);
void markSampleForDeletion(TEndSPStage* object);
void setupObjClass(void* entry, char* name, void (*initialize)(), void (*finalize)(), void* create,
    void*, void*, void*, u32, u32, u32, u32, char*, void*);
void __dl__10TObjSampleFPv(void* object);
void fn_16_900(sAngle* out, sAngle* in);
void fn_16_DB4(void* collision);
u32 fn_16_D10(void* collision);
int fn_16_F20(void* game, int flag);
void fn_16_1180(void* collision, SETDATA_PARAM* setData, sAngle* angle);
int fn_16_61460(void* state);
void fn_16_61504(void* state);
void* fn_16_67EDC();
CollisionInfo* fn_16_7738(void* collision, int index);
void fn_16_5F608(TEndSPStage* object, TObject* parent);
void fn_16_5F55C(TEndSPStage* object, int flags);
void fn_16_8DA38(void* goalRing, f32 scale);
void fn_16_8DA7C(void* goalRing, sAngle* angle);
void fn_16_8DAB0(void* goalRing, RwV3d* position);
void fn_16_8DE1C();
void fn_16_8DE9C();
void fn_16_93BE8(void* object, int flags);
void fn_16_93C3C(void* object);

int fn_8005B8BC(void* motion);
int fn_8005B8D8(void* motion);
void fn_8003C200(void* collision, void* info, int one, int four);
void fn_80019898(void* stage, int value);
void fn_80021384(void* collision);
void fn_80021824(void* collision);

extern void* lbl_8042C180;
extern u8 lbl_8042C1A4[];
extern void* lbl_8042C1F8;
extern void* lbl_8042C208;
extern u8 lbl_8029C310[];
extern TObject* lbl_16_bss_1058;
extern u8 lbl_16_data_40138[0xC];
extern f32 lbl_16_data_42040;
extern f32 lbl_16_data_42044;

TEndSPStage* __ct__11TEndSPStageFP7TObject(TEndSPStage*, TObject*);
TObjGoalring* __ct__12TObjGoalringFP11TEndSPStage(TObjGoalring*, TEndSPStage*);
void __dt__11TEndSPStageFv();
void Exec__11TEndSPStageFv();
void PDisp__7TObjectFv();
void Disp__7TObjectFv();
void TDisp__7TObjectFv();
void ImmAftSetRaster__7TObjectFv();
void Debug__7TObjectFv();
void Render__7TObjectFv();
void EditOnChange__11TEndSPStageFP13SETDATA_PARAM();
}

extern "C" char TEndSPStageClassName[]   = "TEndSPStage";
extern "C" char* TEndSPStageClassNamePtr = TEndSPStageClassName;

extern "C" u32 sColInfo[12] = {
	0x1E04F00C,
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
	0,
};

extern "C" {
u8 ObjS40EndSPStage[0x30];
}

#pragma section data_type ".endsp_strings"                                                         \
                          ".endsp_strings_bss"
extern "C" char ObjS40EndSPStageName[]  = "SPSTAGE END";
extern "C" char TEndSPStageFieldTypes[] = "FFF\0\0\0\0";
#pragma section data_type ".data"

extern "C" const volatile f32 TEndSPStageConstants[9];
extern "C" void* __vt__11TEndSPStage[];
#pragma optimization_level 0
#pragma opt_common_subs off
void TEndSPStage::EditOnChange(SETDATA_PARAM* setData)
{
	volatile RwV3d* member = setData->member;

	if (member->x < 0.0f)
		member->x = 0.0f;
	if (member->y < 0.0f)
		member->y = 0.0f;
	if (member->z < 0.0f)
		member->z = 0.0f;
}
#pragma opt_common_subs reset
#pragma optimization_level reset

extern "C" const volatile f32 TEndSPStageConstants[9] = {
	0.5f,
	-1.0f,
	-2.0f,
	-3.0f,
	-3.0f,
	-2.0f,
	-4.0f,
	-6.0f,
	-6.0f,
};

void TEndSPStage::SetGoalRingParam()
{
	RwV3d position;
	sAngle angle;
	if (goalRing != 0) {
		copyVec3(&position, frame);
		position.y += lbl_16_data_42044;
		fn_16_8DAB0(goalRing, &position);

		fn_16_900(&angle, &frame->angle);
		fn_16_8DA7C(goalRing, &angle);
		fn_16_8DA38(goalRing, lbl_16_data_42040);
	}
}

#pragma optimization_level 0
#pragma opt_common_subs off
void TEndSPStage::Exec()
{
	RwV3d* member = (*(SETDATA_PARAM**)(((RawTEndSPStage*)this)->base + 0x28))->member;
	CollisionInfo* info;
	SETDATA_PARAM* stageObject;

	if (fn_8005B8BC(((RawTEndSPStage*)this)->base + 0x28)) {
		markSampleForDeletion(this);
		return;
	}

	if (fn_16_F20(lbl_8042C180, 0x1F))
		return;

	if (fn_8005B8D8((u8*)goalRing + 0x28)) {
		SetGoalRingParam();
		ringScale = *member;

		if (lbl_8042C1F8 != 0) {
			stageObject = (SETDATA_PARAM*)lbl_8042C208;
			if (stageObject != 0)
				fn_16_900(&(*(SETDATA_PARAM**)(((RawTEndSPStage*)this)->base + 0x28))->angle,
				    &stageObject->angle);
		}
		return;
	}

	if (fn_16_7738(((RawTEndSPStage*)this)->base + 0x30, 0) == 0) {
		fn_8003C200(((RawTEndSPStage*)this)->base + 0x30, sColInfo, 1, 4);
		info          = fn_16_7738(((RawTEndSPStage*)this)->base + 0x30, 0);
		info->scale.x = TEndSPStageConstants[0] * ringScale.x;
		info->scale.y = TEndSPStageConstants[0] * ringScale.y;
		info->scale.z = TEndSPStageConstants[0] * ringScale.z;
		fn_80021384(((RawTEndSPStage*)this)->base + 0x30);
		fn_16_DB4(((RawTEndSPStage*)this)->base + 0x30);
	}

	if (!fn_8005B8D8((u8*)goalRing + 0x28)) {
		fn_80021824(lbl_8042C1A4);
		if (fn_16_D10(((RawTEndSPStage*)this)->base + 0x30)) {
			if (fn_16_67EDC() != 0) {
				if (!fn_16_61460(fn_16_67EDC())) {
					fn_80019898(lbl_8029C310, 0);
					fn_16_61504(fn_16_67EDC());
				}
			} else {
				fn_80019898(lbl_8029C310, 0);
			}
		}
		fn_16_1180(((RawTEndSPStage*)this)->base + 0x30,
		    *(SETDATA_PARAM* volatile*)(((RawTEndSPStage*)this)->base + 0x28),
		    &(*(SETDATA_PARAM* volatile*)(((RawTEndSPStage*)this)->base + 0x28))->angle);
	}
}
#pragma opt_common_subs reset
#pragma optimization_level reset

#pragma optimization_level 0
TEndSPStage::~TEndSPStage()
{
	fn_16_93BE8((u8*)this + 0xD8, 0);
}
#pragma optimization_level reset

#pragma optimization_level 0
extern "C" TEndSPStage* __ct__11TEndSPStageFP7TObject(register TEndSPStage* object, TObject* parent)
{
	fn_16_5F608(object, parent);
	fn_16_93C3C((u8*)object + 0xD8);
	*(void**)((u8*)object + 0x18) = __vt__11TEndSPStage;
	*(void**)((u8*)object + 0x2C) = __vt__11TEndSPStage + 11;
	*(char**)object               = TEndSPStageClassNamePtr;
	*(u16*)((u8*)object + 0x1E)   = 0xE4;
	RwV3d* volatile member        = object->frame->member;
	*(u32*)((u8*)object + 0xBC)   = 0x60000000;

	TObjGoalring* goal = (TObjGoalring*)__nw__10TObjSampleFUl(sizeof(TObjGoalring));
	if (goal != 0)
		goal = __ct__12TObjGoalringFP11TEndSPStage(goal, object);
	object->goalRing = goal;
	object->SetGoalRingParam();
	return object;
}
#pragma optimization_level reset

#pragma optimization_level 0
void TEndSPStage::Create()
{
	register TEndSPStage* object = (TEndSPStage*)__nw__10TObjSampleFUl(sizeof(TEndSPStage));
	if (object != 0)
		object = __ct__11TEndSPStageFP7TObject(object, lbl_16_bss_1058);
}
#pragma optimization_level reset

void TEndSPStage::Finalize()
{
	fn_16_8DE1C();
}

void TEndSPStage::Initialize()
{
	fn_16_8DE9C();
}

extern "C" void __sinit_TEndSPStage_cpp()
{
	setupObjClass(ObjS40EndSPStage, ObjS40EndSPStageName, TEndSPStage::Initialize,
	    TEndSPStage::Finalize, (void*)TEndSPStage::Create, 0, 0, 0, 0x7F, 0x15ED, 2, 0,
	    TEndSPStageFieldTypes, lbl_16_data_40138);
}

__declspec(section ".ctors") void (*const TEndSPStageCtorEntry)() = __sinit_TEndSPStage_cpp;
