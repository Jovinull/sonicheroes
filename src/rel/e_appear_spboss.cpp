#include "types.h"

struct RwV3d {
	f32 x, y, z;
};

struct sAngle {
	s32 x, y, z;
};

extern "C" void* __nw__10TObjSampleFUl(u32);

struct SETDATA_PARAM {
	RwV3d position;
	sAngle angle;
	u8 unk18[0x12];
	u8 type;
	u8 unk2B;
	RwV3d* member;
};

class TObject
{
public:
	const char* className;
	u16 signal, tag;
	TObject *prev, *next, *parent, *child;
	virtual ~TObject();
	virtual void Exec();
	virtual void PDisp();
	virtual void Disp();
	virtual void TDisp();
	virtual void ImmAftSetRaster();
	virtual void Debug();
	virtual void Error(char*);
	virtual void Render();
};
struct TObjectTail {
	s16 values[6];
};
class TEditMotion
{
public:
	SETDATA_PARAM* frame;
	virtual void EditOnChange(SETDATA_PARAM*);
};

class TEnemyAppearSPBoss : public TObject, public TObjectTail, public TEditMotion
{
public:
	u8 collisionArea[0xA8];
	u8 updater[8];

	virtual ~TEnemyAppearSPBoss();
	virtual void Exec();
	virtual void EditOnChange(SETDATA_PARAM*);
	TEnemyAppearSPBoss(TObject*);

	static TEnemyAppearSPBoss* Create();
	static void* operator new(unsigned long size) { return __nw__10TObjSampleFUl(size); }
	static void operator delete(void*);
};

extern "C" {
void __dl__10TObjSampleFPv(void*);
void markSampleForDeletion(TEnemyAppearSPBoss*);
void setupObjClass(void*, char*, void (*)(), void (*)(), void*, void*, void*, void*, u32, u32, u32,
    u32, char*, void*);
u32 fn_16_D10(void*);
int fn_16_F20(void*, int);
void fn_16_1180(void*, SETDATA_PARAM*, sAngle*);
void fn_16_5F3C8(TEnemyAppearSPBoss*);
void fn_16_5F55C(TEnemyAppearSPBoss*, int);
void fn_16_5F608(TEnemyAppearSPBoss*, TObject*);
void fn_16_682D4(int, u8);
void fn_16_93BE8(void*, int);
void fn_16_93C3C(void*);
int fn_16_93ACC(void*, SETDATA_PARAM*, f32);

int fn_8005B8BC(void*);
int fn_8005B8D8(void*);
int fn_8005B9F0(void*);
void fn_8005BC04(void*);
void fn_80021824(void*);

extern void* lbl_8042C180;
extern u8 lbl_8042C1A4[];
extern TObject* lbl_16_bss_1058;
extern u8 lbl_16_data_40138[];

TEnemyAppearSPBoss* __ct__18TEnemyAppearSPBossFP7TObject(TEnemyAppearSPBoss*, TObject*);
void Exec__18TEnemyAppearSPBossFv();
void EditOnChange__18TEnemyAppearSPBossFP13SETDATA_PARAM(TEnemyAppearSPBoss*, SETDATA_PARAM*);
}

extern "C" char TEnemyAppearSPBossClassName[]   = "TEnemyAppearSPBoss\0";
extern "C" char* TEnemyAppearSPBossClassNamePtr = TEnemyAppearSPBossClassName;
// clang-format off
#pragma section data_type ".appear_strings" ".appear_strings_bss"
// clang-format on
extern "C" char ObjS40EnemyAppearSPBossName[];
extern "C" char TEnemyAppearSPBossFieldTypes[];
#pragma section data_type ".data"
extern "C" {
u8 ObjS40EnemyAppearSPBoss[0x30];
}

extern "C" const f32 TEnemyAppearSPBossTen;
extern "C" const f32 TEnemyAppearSPBossZero;
extern "C" void* __vt__18TEnemyAppearSPBoss[];

#pragma optimization_level 0
void TEnemyAppearSPBoss::Exec()
{
	RwV3d* member = frame->member;

	if (!fn_16_93ACC(updater, frame, TEnemyAppearSPBossTen)) {
		fn_8005BC04((u8*)this + 0x28);
		markSampleForDeletion(this);
		return;
	}
	if (fn_8005B9F0((u8*)this + 0x28) || fn_8005B8BC((u8*)this + 0x28)) {
		markSampleForDeletion(this);
		return;
	}
	if (fn_16_F20(lbl_8042C180, 0x1F))
		return;
	fn_16_5F3C8(this);
	if (!fn_8005B8D8((u8*)this + 0x28)) {
		fn_80021824(lbl_8042C1A4);
		if (fn_16_D10((u8*)this + 0x30))
			fn_16_682D4(0, frame->type);
		fn_16_1180((u8*)this + 0x30, frame, &frame->angle);
	}
}

void TEnemyAppearSPBoss::EditOnChange(SETDATA_PARAM* setData)
{
	if (setData->type == 0)
		setData->type = 1;
	register RwV3d* member = setData->member;
	if (member->x < TEnemyAppearSPBossZero)
		member->x = TEnemyAppearSPBossZero;
	if (member->y < TEnemyAppearSPBossZero)
		member->y = TEnemyAppearSPBossZero;
	if (member->z < TEnemyAppearSPBossZero)
		member->z = TEnemyAppearSPBossZero;
}

TEnemyAppearSPBoss::~TEnemyAppearSPBoss()
{
	RwV3d* member = frame->member;
	fn_16_93BE8(updater, 0);
}

extern "C" TEnemyAppearSPBoss* __ct__18TEnemyAppearSPBossFP7TObject(
    register TEnemyAppearSPBoss* object, TObject* parent)
{
	fn_16_5F608(object, parent);
	fn_16_93C3C(object->updater);
	*(void**)((u8*)object + 0x18) = __vt__18TEnemyAppearSPBoss;
	*(void**)((u8*)object + 0x2C) = __vt__18TEnemyAppearSPBoss + 11;
	*(char**)object               = TEnemyAppearSPBossClassNamePtr;
	*(u16*)((u8*)object + 0x1E)   = 0xE0;
	RwV3d* member                 = object->frame->member;
	*(u32*)((u8*)object + 0xBC)   = 0x60000000 + 0xFF;
	return object;
}

TEnemyAppearSPBoss* TEnemyAppearSPBoss::Create()
{
	TEnemyAppearSPBoss* object
	    = (TEnemyAppearSPBoss*)__nw__10TObjSampleFUl(sizeof(TEnemyAppearSPBoss));
	if (object != 0)
		object = __ct__18TEnemyAppearSPBossFP7TObject(object, lbl_16_bss_1058);
}

extern "C" void __sinit_e_appear_spboss_cpp()
{
	setupObjClass(ObjS40EnemyAppearSPBoss, ObjS40EnemyAppearSPBossName, 0, 0,
	    (void*)TEnemyAppearSPBoss::Create, 0, 0, 0, 0x32, 0x15E5, 2, 0,
	    TEnemyAppearSPBossFieldTypes, lbl_16_data_40138);
}

__declspec(section ".ctors") void (*const TEnemyAppearSPBossCtorEntry)()
    = __sinit_e_appear_spboss_cpp;

// clang-format off
#pragma section data_type ".appear_strings" ".appear_strings_bss"
// clang-format on
extern "C" char ObjS40EnemyAppearSPBossName[] = "SPBOSS APPEAR\0FFF";
#pragma section data_type ".data"

__declspec(section ".rodata") const f32 TEnemyAppearSPBossTen  = 10.0f;
__declspec(section ".rodata") const f32 TEnemyAppearSPBossZero = 0.0f;
