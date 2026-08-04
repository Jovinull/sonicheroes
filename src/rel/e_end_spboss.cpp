#include "types.h"

struct RwV3d {
	f32 x, y, z;
};

struct sAngle {
	s32 x, y, z;
};

struct TObject;
extern "C" void* __nw__10TObjSampleFUl(u32);

struct SETDATA_PARAM {
	RwV3d position;
	sAngle angle;
	u8 unk18[0x14];
	RwV3d* member;
};

class TEnemyEndSPBossPrimary
{
public:
	virtual ~TEnemyEndSPBossPrimary();
	virtual void Exec();
	virtual void Virtual2();
	virtual void Virtual3();
	virtual void Virtual4();
	virtual void Virtual5();
	virtual void Virtual6();
	virtual void Virtual7();
	virtual void Virtual8();
	u8 primaryData[0x24];
};

class TEnemyEndSPBossEditor
{
public:
	virtual void EditOnChange(SETDATA_PARAM*);
};

class TEnemyEndSPBoss : public TEnemyEndSPBossPrimary, public TEnemyEndSPBossEditor
{
public:
	u8 derivedData[0xAC];

	void EditOnChange(SETDATA_PARAM*);
	virtual ~TEnemyEndSPBoss();
	void Exec();

	static TEnemyEndSPBoss* Create();
	static void* operator new(unsigned long size) { return __nw__10TObjSampleFUl(size); }
};

#define base ((u8*)this)

extern "C" {
void __dl__10TObjSampleFPv(void*);
void markSampleForDeletion(void*);
void setupObjClass(void*, char*, void (*)(), void (*)(), void*, void*, void*, void*, u32, u32, u32,
    u32, char*, void*);
u32 fn_16_D10(void*);
int fn_16_F20(void*, int);
void fn_16_1180(void*, SETDATA_PARAM*, sAngle*);
void fn_16_5F55C(TEnemyEndSPBoss*, int);
void fn_16_5F608(TEnemyEndSPBoss*, TObject*);
void fn_16_5F3C8(TEnemyEndSPBoss*);
void* fn_16_8C05C();
int fn_16_8BE40(void*, SETDATA_PARAM*, f32);
void fn_16_67FE0();

int fn_8005B8BC(void*);
int fn_8005B8D8(void*);
int fn_8005B9F0(void*);
void fn_8005BC04(void*);
void fn_80021824(void*);

extern void* lbl_8042C180;
extern u8 lbl_8042C1A4[];
extern TObject* lbl_16_bss_1058;
extern u8 lbl_16_data_40138[];

TEnemyEndSPBoss* __ct__15TEnemyEndSPBossFP7TObject(TEnemyEndSPBoss*, TObject*);
TEnemyEndSPBoss* __dt__15TEnemyEndSPBossFv(TEnemyEndSPBoss*, s16);
void Exec__15TEnemyEndSPBossFv();
void EditOnChange__15TEnemyEndSPBossFP13SETDATA_PARAM(TEnemyEndSPBoss*, SETDATA_PARAM*);
void fn_16_11640();
void fn_16_5F3B0();
void sampleHook1();
void sampleHook2();
void sampleHook3();
void fn_80017854();
void sampleHook4();
}

extern "C" char TEnemyEndSPBossClassName[]   = "TEnemyEndSPBoss";
extern "C" char* TEnemyEndSPBossClassNamePtr = TEnemyEndSPBossClassName;
extern "C" void* TEnemyEndSPBossVtable[];

extern "C" char ObjS40EndSPBossName[] = "SPBOSS END";
#pragma force_active on
extern "C" char TEnemyEndSPBossFieldTypes       = 'F';
extern "C" char TEnemyEndSPBossFieldTypesTail[] = "FF";
#pragma force_active reset
extern "C" {
u8 ObjS40EndSPBoss[0x30];
}
extern "C" const f32 TEnemyEndSPBossHundred;
extern "C" const f32 TEnemyEndSPBossZero;

#pragma optimization_level 0
void TEnemyEndSPBoss::Exec()
{
	RwV3d* member = (*(SETDATA_PARAM**)(base + 0x28))->member;

	if (fn_16_8C05C() != 0
	    && !fn_16_8BE40(fn_16_8C05C(), *(SETDATA_PARAM**)(base + 0x28), TEnemyEndSPBossHundred)) {
		fn_8005BC04(base + 0x28);
		markSampleForDeletion(this);
		return;
	}
	if (fn_8005B9F0(base + 0x28) || fn_8005B8BC(base + 0x28)) {
		markSampleForDeletion(this);
		return;
	}
	if (fn_16_F20(lbl_8042C180, 0x1F))
		return;
	fn_16_5F3C8(this);
	if (fn_8005B8D8(base + 0x28))
		return;
	fn_80021824(lbl_8042C1A4);
	if (fn_16_D10(base + 0x30))
		fn_16_67FE0();
	fn_16_1180(
	    base + 0x30, *(SETDATA_PARAM**)(base + 0x28), &(*(SETDATA_PARAM**)(base + 0x28))->angle);
}

void TEnemyEndSPBoss::EditOnChange(SETDATA_PARAM* setData)
{
	RwV3d* member = setData->member;
	if (member->x < TEnemyEndSPBossZero)
		member->x = TEnemyEndSPBossZero;
	if (member->y < TEnemyEndSPBossZero)
		member->y = TEnemyEndSPBossZero;
	if (member->z < TEnemyEndSPBossZero)
		member->z = TEnemyEndSPBossZero;
}

extern "C" TEnemyEndSPBoss* __dt__15TEnemyEndSPBossFv(TEnemyEndSPBoss* object, s16 flags)
{
	if (object != 0) {
		*(void**)((u8*)object + 0x18) = TEnemyEndSPBossVtable;
		*(void**)((u8*)object + 0x2C) = TEnemyEndSPBossVtable + 11;
		RwV3d* member                 = (*(SETDATA_PARAM**)((u8*)object + 0x28))->member;
		fn_16_5F55C(object, 0);
		if (flags > 0)
			__dl__10TObjSampleFPv(object);
	}
	return object;
}

#pragma dont_inline on
extern "C" TEnemyEndSPBoss* __ct__15TEnemyEndSPBossFP7TObject(
    TEnemyEndSPBoss* object, TObject* parent)
{
	fn_16_5F608(object, parent);
	*(void**)((u8*)object + 0x18) = TEnemyEndSPBossVtable;
	*(void**)((u8*)object + 0x2C) = TEnemyEndSPBossVtable + 11;
	*(char**)object               = TEnemyEndSPBossClassNamePtr;
	*(u16*)((u8*)object + 0x1E)   = 0xD8;
	RwV3d* member                 = (*(SETDATA_PARAM**)((u8*)object + 0x28))->member;
	*(u32*)((u8*)object + 0xBC)   = 0x6000FF00;
	return object;
}
#pragma dont_inline reset

TEnemyEndSPBoss* TEnemyEndSPBoss::Create()
{
	TEnemyEndSPBoss* object = (TEnemyEndSPBoss*)__nw__10TObjSampleFUl(sizeof(TEnemyEndSPBoss));
	if (object != 0)
		object = __ct__15TEnemyEndSPBossFP7TObject(object, lbl_16_bss_1058);
}

extern "C" void __sinit_e_end_spboss_cpp()
{
	setupObjClass(ObjS40EndSPBoss, ObjS40EndSPBossName, 0, 0, (void*)TEnemyEndSPBoss::Create, 0, 0,
	    0, 50, 5606, 2, 0, &TEnemyEndSPBossFieldTypes, lbl_16_data_40138);
}

__declspec(section ".ctors") void (*const TEnemyEndSPBossCtorEntry)() = __sinit_e_end_spboss_cpp;

__declspec(section ".rodata") const f32 TEnemyEndSPBossHundred = 100.0f;
__declspec(section ".rodata") const f32 TEnemyEndSPBossZero    = 0.0f;
