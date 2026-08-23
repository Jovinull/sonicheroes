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
	u8 unk18[0x12];
	u8 type;
	u8 unk2B;
	RwV3d* member;
};

class TEnemyAppearSPBossPosPrimary
{
public:
	virtual ~TEnemyAppearSPBossPosPrimary();
	virtual void Exec();
	virtual void Virtual2();
	virtual void Virtual3();
	virtual void Virtual4();
	virtual void Virtual5();
	virtual void Virtual6();
	virtual void Virtual7();
	virtual void Virtual8();
	u8 data[0x24];
};

class TEnemyAppearSPBossPosEditor
{
public:
	virtual void EditOnChange(SETDATA_PARAM*);
};

class TEnemyAppearSPBossPos : public TEnemyAppearSPBossPosPrimary,
                              public TEnemyAppearSPBossPosEditor
{
public:
	u8 tail[0xB0];

	void EditOnChange(SETDATA_PARAM*);
	virtual ~TEnemyAppearSPBossPos();
	void Exec();
	void Finalize();
	void Initialize();

	static TEnemyAppearSPBossPos* Create();
	static void* operator new(unsigned long size) { return __nw__10TObjSampleFUl(size); }
};

#define OBJECT_BYTES  ((u8*)this)
#define SET_DATA      (*(SETDATA_PARAM**)(OBJECT_BYTES + 0x28))
#define AUX_OBJECT    (OBJECT_BYTES + 0x30)
#define CURRENT_POS   (*(RwV3d*)(OBJECT_BYTES + 0xC0))
#define TARGET_POS    (*(RwV3d*)(OBJECT_BYTES + 0xCC))
#define INTERPOLATION (*(f32*)(OBJECT_BYTES + 0xD8))

extern "C" {
void __dl__10TObjSampleFPv(void*);
void markSampleForDeletion(void*);
void copyVec3(RwV3d*, SETDATA_PARAM*);
void setupObjClass(void*, char*, void (*)(), void (*)(), void*, void*, void*, void*, u32, u32, u32,
    u32, char*, void*);
int fn_16_F20(void*, int);
void* fn_16_7738(void*, int);
void fn_16_1180(void*, SETDATA_PARAM*, RwV3d*);
void fn_16_5F55C(TEnemyAppearSPBossPos*, int);
void fn_16_5F608(TEnemyAppearSPBossPos*, TObject*);
f32 fn_16_4D18C(RwV3d*, RwV3d*);
f32 fn_16_5932C(void*, RwV3d*, f32);
f32 fn_16_59490(void*, RwV3d*);
void fn_16_59580(void*, void*);
f32 fn_16_596B0(void*, f32);
void fn_16_59E88(void*);
void fn_16_5A0F0(void*);
void* fn_16_62FBC(int);
void fn_16_900(RwV3d*, RwV3d*);
void fn_16_DB4(void*);

int fn_8005B8BC(void*);
int fn_8005B8D8(void*);
int fn_8005B9F0(void*);
void fn_8003C200(void*, void*, int, int);
void fn_80021384(void*);

extern void* lbl_8042C180;
extern void* lbl_8042C1F8;
extern void* lbl_8042C208;
extern TObject* lbl_16_bss_1058;
extern u8 lbl_16_data_40138[];

TEnemyAppearSPBossPos* __ct__21TEnemyAppearSPBossPosFP7TObject(TEnemyAppearSPBossPos*, TObject*);
TEnemyAppearSPBossPos* __dt__21TEnemyAppearSPBossPosFv(TEnemyAppearSPBossPos*, s16);
void Exec__21TEnemyAppearSPBossPosFv();
void EditOnChange__21TEnemyAppearSPBossPosFP13SETDATA_PARAM(TEnemyAppearSPBossPos*, SETDATA_PARAM*);
void Finalize__21TEnemyAppearSPBossPosFv();
void Initialize__21TEnemyAppearSPBossPosFv();
void fn_16_11640();
void fn_16_5F3B0();
void sampleHook1();
void sampleHook2();
void sampleHook3();
void Error__7TObjectFPc();
void sampleHook4();
}

extern "C" char TEnemyAppearSPBossPosClassName[]   = "TEnemyAppearSPBossPos";
extern "C" char* TEnemyAppearSPBossPosClassNamePtr = TEnemyAppearSPBossPosClassName;
extern "C" char TEnemyAppearSPBossPosScaleX[]      = "SCALE X";
extern "C" char TEnemyAppearSPBossPosScaleY[]      = "SCALE Y";
extern "C" char TEnemyAppearSPBossPosScaleZ[]      = "SCALE Z";
extern "C" char TEnemyAppearSPBossPosDoNotEdit[]   = "DONOT EDIT";
extern "C" char* TEnemyAppearSPBossPosFieldNames[];
extern "C" u32 TEnemyAppearSPBossPosResourceParams[12] = { 0x0004F00C };
extern "C" void* TEnemyAppearSPBossPosVtable[];

extern "C" char ObjS40EnemyAppearSPBossPosName[];
extern "C" char TEnemyAppearSPBossPosFieldTypes[];
extern "C" {
u8 ObjS40EnemyAppearSPBossPos[0x2C];
u8 TEnemyAppearSPBossPosInterpolator[0x6C];
}
extern "C" const f32 TEnemyAppearSPBossPosZero;
extern "C" const f32 TEnemyAppearSPBossPosHalf;

#pragma optimization_level 0
void TEnemyAppearSPBossPos::Exec()
{
	RwV3d* member = SET_DATA->member;
	if (fn_8005B9F0(OBJECT_BYTES + 0x28) || fn_8005B8BC(OBJECT_BYTES + 0x28)) {
		markSampleForDeletion(this);
		return;
	}

	RwV3d previous = TARGET_POS;
	copyVec3(&TARGET_POS, SET_DATA);
	if (fn_16_F20(lbl_8042C180, 0x1F))
		return;

	if (fn_8005B8D8(OBJECT_BYTES + 0x28)) {
		CURRENT_POS = *member;
		if (INTERPOLATION <= TEnemyAppearSPBossPosZero) {
			member[1].x = INTERPOLATION
			    = fn_16_59490(TEnemyAppearSPBossPosInterpolator, &TARGET_POS);
		} else {
			f32 distance = fn_16_4D18C(&previous, &TARGET_POS);
			fn_16_596B0(TEnemyAppearSPBossPosInterpolator, INTERPOLATION);
			member[1].x = INTERPOLATION
			    = fn_16_5932C(TEnemyAppearSPBossPosInterpolator, &TARGET_POS, distance);
		}
		if (lbl_8042C1F8 != 0) {
			register void* player = lbl_8042C208;
			if (player != 0)
				fn_16_900((RwV3d*)((u8*)SET_DATA + 0xC), (RwV3d*)((u8*)player + 0xC));
		}
		return;
	}

	if (fn_16_7738(AUX_OBJECT, 0) == 0) {
		fn_8003C200(AUX_OBJECT, TEnemyAppearSPBossPosResourceParams, 1, 4);
		register void* handle       = fn_16_7738(AUX_OBJECT, 0);
		*(f32*)((u8*)handle + 0x14) = TEnemyAppearSPBossPosHalf * CURRENT_POS.x;
		*(f32*)((u8*)handle + 0x18) = TEnemyAppearSPBossPosHalf * CURRENT_POS.y;
		*(f32*)((u8*)handle + 0x1C) = TEnemyAppearSPBossPosHalf * CURRENT_POS.z;
		fn_80021384(AUX_OBJECT);
		fn_16_DB4(AUX_OBJECT);
	}
	if (!fn_8005B8D8(OBJECT_BYTES + 0x28))
		fn_16_1180(AUX_OBJECT, SET_DATA, (RwV3d*)((u8*)SET_DATA + 0xC));
}

void TEnemyAppearSPBossPos::EditOnChange(SETDATA_PARAM* setData)
{
	if (setData->type == 0)
		setData->type = 1;
}

extern "C" TEnemyAppearSPBossPos* __dt__21TEnemyAppearSPBossPosFv(
    TEnemyAppearSPBossPos* object, s16 flags)
{
	if (object != 0) {
		*(void**)((u8*)object + 0x18) = TEnemyAppearSPBossPosVtable;
		*(void**)((u8*)object + 0x2C) = TEnemyAppearSPBossPosVtable + 11;
		fn_16_5F55C(object, 0);
		if (flags > 0)
			__dl__10TObjSampleFPv(object);
	}
	return object;
}

#pragma dont_inline on
extern "C" TEnemyAppearSPBossPos* __ct__21TEnemyAppearSPBossPosFP7TObject(
    TEnemyAppearSPBossPos* object, TObject* parent)
{
	fn_16_5F608(object, parent);
	*(void**)((u8*)object + 0x18) = TEnemyAppearSPBossPosVtable;
	*(void**)((u8*)object + 0x2C) = TEnemyAppearSPBossPosVtable + 11;
	*(char**)object               = TEnemyAppearSPBossPosClassNamePtr;
	*(u16*)((u8*)object + 0x1E)   = 0xDC;
	*(u32*)((u8*)object + 0xBC)   = 0x60FF0000;
	RwV3d* member                 = (*(SETDATA_PARAM**)((u8*)object + 0x28))->member;
	*(f32*)((u8*)object + 0xD8)   = member[1].x;
	return object;
}
#pragma dont_inline reset

void TEnemyAppearSPBossPos::Finalize()
{
	fn_16_59E88(TEnemyAppearSPBossPosInterpolator);
}

void TEnemyAppearSPBossPos::Initialize()
{
	void* object = fn_16_62FBC(0);
	fn_16_59580(TEnemyAppearSPBossPosInterpolator, object);
}

TEnemyAppearSPBossPos* TEnemyAppearSPBossPos::Create()
{
	TEnemyAppearSPBossPos* object
	    = (TEnemyAppearSPBossPos*)__nw__10TObjSampleFUl(sizeof(TEnemyAppearSPBossPos));
	if (object != 0)
		object = __ct__21TEnemyAppearSPBossPosFP7TObject(object, lbl_16_bss_1058);
}

extern "C" void __sinit_e_appear_spboss_pos_cpp()
{
	setupObjClass(ObjS40EnemyAppearSPBossPos, ObjS40EnemyAppearSPBossPosName, 0, 0,
	    (void*)TEnemyAppearSPBossPos::Create, 0, 0, 0, 50, 5607, 2, 0,
	    TEnemyAppearSPBossPosFieldTypes, TEnemyAppearSPBossPosFieldNames);
	fn_16_5A0F0(TEnemyAppearSPBossPosInterpolator);
}

extern "C" char* TEnemyAppearSPBossPosFieldNames[] = {
	TEnemyAppearSPBossPosScaleX,
	TEnemyAppearSPBossPosScaleY,
	TEnemyAppearSPBossPosScaleZ,
	TEnemyAppearSPBossPosDoNotEdit,
};
extern "C" char ObjS40EnemyAppearSPBossPosName[]  = "SPBOSS APPEAR POS";
extern "C" char TEnemyAppearSPBossPosFieldTypes[] = "FFFF";

__declspec(section ".ctors") void (*const TEnemyAppearSPBossPosCtorEntry)()
    = __sinit_e_appear_spboss_pos_cpp;

__declspec(section ".rodata") const f32 TEnemyAppearSPBossPosZero = 0.0f;
__declspec(section ".rodata") const f32 TEnemyAppearSPBossPosHalf = 0.5f;
