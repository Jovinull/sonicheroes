#include "types.h"

// stage11D's egg mobile strategy: the TEnemyStrategy TObjEnemyEggMobile
// (rel/e_eggmobile_stage11.cpp) runs, its per-mode handlers, the mode
// transition test (9E510), the state dispatcher with the unit's one switch
// table, and the strategy's ctor/dtors with its three vtables.

/* Retail builds this module without fused multiply-adds. */
#pragma fp_contract off

typedef s32 M2C_UNK;
typedef struct HAnimClass HAnimClass;
#define M2C_FIELD(base, type, offset) (*(type)((u8*)(base) + (offset)))
#define M2C_ERROR(...)

typedef struct TObject {
	/* 0x000 */ const char* unk0; /* inferred */
	/* 0x004 */ char pad4[0x14];  /* maybe part of unk0[6]? */
	/* 0x018 */ M2C_UNK* unk18;   /* inferred */
	/* 0x01C */ char pad1C[2];
	/* 0x01E */ s16 unk1E;         /* inferred */
	/* 0x020 */ char pad20[8];     /* maybe part of unk1E[5]? */
	/* 0x028 */ s32 unk28;         /* inferred */
	/* 0x02C */ s32 unk2C;         /* inferred */
	/* 0x030 */ s32 unk30;         /* inferred */
	/* 0x034 */ s8 unk34;          /* inferred */
	/* 0x035 */ char pad35[0x7B];  /* maybe part of unk34[0x7C]? */
	/* 0x0B0 */ void* unkB0;       /* inferred */
	/* 0x0B4 */ void* unkB4;       /* inferred */
	/* 0x0B8 */ char padB8[0x1C];  /* maybe part of unkB4[8]? */
	/* 0x0D4 */ s32 unkD4;         /* inferred */
	/* 0x0D8 */ char padD8[0xC];   /* maybe part of unkD4[4]? */
	/* 0x0E4 */ M2C_UNK* unkE4;    /* inferred */
	/* 0x0E8 */ void* unkE8;       /* inferred */
	/* 0x0EC */ char padEC[0x54];  /* maybe part of unkE8[0x16]? */
	/* 0x140 */ f32 unk140;        /* inferred */
	/* 0x144 */ f32 unk144;        /* inferred */
	/* 0x148 */ f32 unk148;        /* inferred */
	/* 0x14C */ s32 unk14C;        /* inferred */
	/* 0x150 */ s32 unk150;        /* inferred */
	/* 0x154 */ s32 unk154;        /* inferred */
	/* 0x158 */ f32 unk158;        /* inferred */
	/* 0x15C */ f32 unk15C;        /* inferred */
	/* 0x160 */ f32 unk160;        /* inferred */
	/* 0x164 */ char pad164[0x1C]; /* maybe part of unk160[8]? */
	/* 0x180 */ s32 unk180;        /* inferred */
	/* 0x184 */ char pad184[0x18]; /* maybe part of unk180[7]? */
	/* 0x19C */ s32 unk19C;        /* inferred */
	/* 0x1A0 */ char pad1A0[0x20]; /* maybe part of unk19C[9]? */
	/* 0x1C0 */ f32 unk1C0;        /* inferred */
	/* 0x1C4 */ f32 unk1C4;        /* inferred */
	/* 0x1C8 */ f32 unk1C8;        /* inferred */
	/* 0x1CC */ f32 unk1CC;        /* inferred */
	/* 0x1D0 */ f32 unk1D0;        /* inferred */
	/* 0x1D4 */ f32 unk1D4;        /* inferred */
	/* 0x1D8 */ char pad1D8[0x68]; /* maybe part of unk1D4[0x1B]? */
	/* 0x240 */ void** unk240;     /* inferred */
	/* 0x244 */ s32 unk244;        /* inferred */
	/* 0x248 */ u32 unk248;        /* inferred */
	/* 0x24C */ f32 unk24C;        /* inferred */
	/* 0x250 */ f32 unk250;        /* inferred */
	/* 0x254 */ f32 unk254;        /* inferred */
	/* 0x258 */ f32 unk258;        /* inferred */
	/* 0x25C */ f32 unk25C;        /* inferred */
	/* 0x260 */ s32 unk260;        /* inferred */
	/* 0x264 */ s32 unk264;        /* inferred */
	/* 0x268 */ s32 unk268;        /* inferred */
	/* 0x26C */ s32 unk26C;        /* inferred */
	/* 0x270 */ char pad270[4];
	/* 0x274 */ s32 unk274;       /* inferred */
	/* 0x278 */ s32 unk278;       /* inferred */
	/* 0x27C */ void* unk27C;     /* inferred */
	/* 0x280 */ void* unk280;     /* inferred */
	/* 0x284 */ void* unk284;     /* inferred */
	/* 0x288 */ u32 unk288;       /* inferred */
	/* 0x28C */ char pad28C[0xC]; /* maybe part of unk288[4]? */
	/* 0x298 */ s32 unk298;       /* inferred */
	/* 0x29C */ s32 unk29C;       /* inferred */
	/* 0x2A0 */ s32 unk2A0;       /* inferred */
	/* 0x2A4 */ void* unk2A4;     /* inferred */
	/* 0x2A8 */ void* unk2A8;     /* inferred */
	/* 0x2AC */ void* unk2AC;     /* inferred */
	/* 0x2B0 */ void** unk2B0;    /* inferred */
} TObject;                        /* size >= 0x2B4 */

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

/* PATHINFO: where a path puts a point at a given distance along it. */
struct PathInfo {
	u8 pad00[0x10];
	f32 dist;  /* 0x10 */
	RwV3d pos; /* 0x14 */
	u8 pad20[0x24];
};

/* Dispatch view of the object handed to the state jumptable: retail reads the
 * vtable through the incoming `this` in r3 and calls the slot with the state
 * argument in r4, so the call has to go through a class. Slot numbers are the
 * retail vtable offsets, and the two implicit destructor slots occupy 0 and 4. */
class TStateDispatch
{
public:
	virtual void vslot2();
	virtual void vslot3();
	virtual void vslot4();
	virtual void vslot5();
	virtual void Slot18(s32);
	virtual void Slot1C(s32);
	virtual void Slot20(s32);
	virtual void Slot24(s32);
	virtual void Slot28(s32);
	virtual void Slot2C(s32);
	virtual void Slot30(s32);
	virtual void Slot34(s32);
	virtual void Slot38(s32);
	virtual void Slot3C(s32);
	virtual void Slot40(s32);
	virtual void Slot44(s32);
	virtual void Slot48(s32);
	virtual void Slot4C(s32);
	virtual void Slot50(s32);
};

extern "C" {
void* __ct__10HAnimClassFv(void* self);                             /* extern */
void* __ct__7TObjectFP7TObject(TObject* self, TObject* arg0);       /* extern */
M2C_UNK __dl__FPv(void* arg0);                                      /* extern */
void* __dt__10HAnimClassFv(void* self, s16 destroyFlag);            /* extern */
void* __dt__7TObjectFv(TObject* self, s16 destroyFlag);             /* extern */
M2C_UNK __dt__11ENEMYMTNMANFv(void*, M2C_UNK);                      /* extern */
M2C_UNK Free__9THeapCtrlFPv(s32, TObject*);                         /* extern */
TObject* Malloc__9THeapCtrlFUi(s32, M2C_UNK);                       /* extern */
M2C_UNK fn_80018C4C(M2C_UNK*);                                      /* extern */
M2C_UNK fn_80018C64(M2C_UNK*);                                      /* extern */
s32 fn_80018C98();                                                  /* extern */
M2C_UNK fn_80019898(M2C_UNK*, M2C_UNK);                             /* extern */
M2C_UNK fn_8003C640(void*);                                         /* extern */
void* __nw__FUl(u32);                                               /* extern */
s32 CheckMustKill__10TObjSetObjFv(s32);                             /* extern */
M2C_UNK SetEnd__10TObjSetObjFv(void*);                              /* extern */
M2C_UNK SetClumpCustomFXTexture__FP7RpClumpP8UVFXInfo(u32*);        /* extern */
M2C_UNK objRpClumpForAllGeometrysToIgnoreLights__FP7RpClump(void*); /* extern */
M2C_UNK objChangeTextureFilterMode__FP15RwTexDictionary19RwTextureFilterMode(
    u32, M2C_UNK);                      /* extern */
s32 fn_800A2BE0(void*, u8);             /* extern */
M2C_UNK fn_800A31B8(void*, s32);        /* extern */
M2C_UNK fn_800A3D48(void*);             /* extern */
s32 fn_800A3ED4(void*);                 /* extern */
s32 fn_800A5A54(void*);                 /* extern */
s32 fn_800A6334(void*);                 /* extern */
M2C_UNK fn_800A7088(TObject*, M2C_UNK); /* extern */
void fn_800A714C(void*, void*);         /* TObjEnemy::TObjEnemy(TObject*) */
struct PathInfo;
s32 GetStatusOnPath__FP7PATHTAGP8PATHINFO(void*, PathInfo*);                /* extern */
M2C_UNK fn_800B4A38(u32, M2C_UNK, void*, void*, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK fn_800CCC6C(const char*);                                           /* extern */
s32 AdjustAngle__Fiii(s32, s32, s32);                                       /* extern */
f32 fn_800D7B00(s32);                                                       /* extern */
M2C_UNK fn_800F46B0(void*);                                                 /* extern */
M2C_UNK ReleaseAnimationDataFromONEFILE__12nEnemyMotionF14eEnemyDataBaseP12ENEMY_MOTION(
    M2C_UNK, M2C_UNK*); /* extern */
M2C_UNK LoadAnimationDataFromONEFILE__12nEnemyMotionF14eEnemyDataBaseP12ENEMY_MOTION(
    M2C_UNK, M2C_UNK*);                                                             /* extern */
void* __ct__11ENEMYMTNMANFv(void*);                                                 /* extern */
M2C_UNK UpdateMotion__11ENEMYMTNMANFv(void*);                                       /* extern */
s32 SearchCameraMotion__14TEnemyDataBaseF14eEnemyDataBaseUi(u32, M2C_UNK, M2C_UNK); /* extern */
u32 SearchUVAnim__14TEnemyDataBaseF14eEnemyDataBaseUi(u32, M2C_UNK, M2C_UNK);       /* extern */
u32 SearchTexDictonary__14TEnemyDataBaseF14eEnemyDataBaseUi(u32, M2C_UNK, M2C_UNK); /* extern */
u32 SearchClump__14TEnemyDataBaseF14eEnemyDataBaseUi(u32, M2C_UNK, M2C_UNK);        /* extern */
M2C_UNK Delete__14TEnemyDataBaseF14eEnemyDataBase(u32, M2C_UNK);                    /* extern */
M2C_UNK Add__14TEnemyDataBaseF14eEnemyDataBasePc(u32, M2C_UNK, const void*);        /* extern */
M2C_UNK __ct__14TEnemyDataBaseFv();                                                 /* extern */
s32 IsExistSummonEnemy__19nEnemyCommunicationFUc(u8);                               /* extern */
s32 IsAnnihilated__19nEnemyCommunicationFUc(u8);                                    /* extern */
s32 fn_80103178(M2C_UNK);                                                           /* extern */
M2C_UNK fn_80111260(void*, M2C_UNK, M2C_UNK);                                       /* extern */
M2C_UNK SetLightNum__7nRenderFUi(M2C_UNK);                                          /* extern */
M2C_UNK SetRenderStateForBlendAdd__7nRenderFv();                                    /* extern */
M2C_UNK LoadRenderState__7nRenderFv();                                              /* extern */
M2C_UNK SaveRenderState__7nRenderFv();                                              /* extern */
void* SearchFrameFromFrameID__11nRenderWareFP7RwFramei(s32, s32);                   /* extern */
M2C_UNK fn_8011B844(u32, f32);                                                      /* extern */
M2C_UNK fn_8012D9D0();                                                              /* extern */
s32 fn_8012DA08();                                                                  /* extern */
M2C_UNK Create__12TEnemySummonFUc(u8);                                              /* extern */
f32 fn_80132958(M2C_UNK);                                                           /* extern */
M2C_UNK fn_801329AC();                                                              /* extern */
M2C_UNK fn_80133090(M2C_UNK*, M2C_UNK*);                                            /* extern */
M2C_UNK DecreaseTimer__7nSystemFRi(void*);                                          /* extern */
M2C_UNK fn_8014FF2C(u32);                                                           /* extern */
M2C_UNK fn_8014FFBC(u32, M2C_UNK*, u32*);                                           /* extern */
void* fn_80150588(void*);                                                           /* extern */
M2C_UNK fn_80150958(void*);                                                         /* extern */
M2C_UNK fn_80194234(M2C_UNK, M2C_UNK);                                              /* extern */
void* fn_8019E8EC(void*);                                                           /* extern */
void fn_8019EB94(s32, RwV3d*, s32);       /* RwFrameTranslate */
M2C_UNK fn_8019ECCC(s32, void*, M2C_UNK); /* extern */
void fn_8019ED68(s32, RwV3d*, f32, s32);  /* RwFrameRotate */

s32 rand();                    /* extern */
s32 fn_8_9832C(s32);           /* extern */
s32 fn_8_98464(u32);           /* extern */
M2C_UNK fn_8_98480(void*);     /* extern */
M2C_UNK fn_8_9897C();          /* extern */
s32 fn_8_98B08(u32);           /* extern */
s32 fn_8_98B94(u32);           /* extern */
M2C_UNK fn_8_9D81C(s32);       /* extern */
void fn_8_A2A00(void*, void*); /* TEnemyFlyer_Strategy setup (rel/e_flyer_stage11.cpp) */
void fn_8_A2A78(void*, void*);
void* fn_8_A31D4(void*);                       /* TEnemyFlyer_Strategy::TEnemyFlyer_Strategy() */
M2C_UNK EventRewind__12EventManagerFv(u32);    /* extern */
M2C_UNK EventStart__12EventManagerFv(u32);     /* extern */
s32 Exist__12EventManagerFv(u32);              /* extern */
M2C_UNK fn_8_D8E90(M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
}
extern M2C_UNK SetAtomicCustomFXData__FP8RpAtomicPv;
extern RwV3d AxisY;
extern M2C_UNK lbl_8029BBD0;
extern M2C_UNK lbl_8029C310;
extern void* lbl_80303DC8;
extern TObject* lbl_8042C0FC;
extern TObject* lbl_8042C10C;
extern s32 lbl_8042C148;
extern void* lbl_8042C180;
extern void* lbl_8042C380;
extern u32 lbl_8042C388;
extern u32 mpDataBase__14TEnemyDataBase;
extern void* lbl_8042C610;
extern u32 lbl_8042C6E4;
extern "C" {
/* The strategy's data, defined where retail emits it (around the one switch
 * table, fn_8_9E924's). */
extern void* lbl_8_data_15A70[21];
extern void* lbl_8_data_15B0C[6];
extern void* lbl_8_data_15B24[21];
}
/* The {0, 1.5, 0} vector the stage 11 object units carry unreferenced at the
 * head of their .rodata (see e_capture_collision_stage11.cpp). */
#pragma force_active on
static const f32 lbl_8_rodata_17C0[3] = { 0.0f, 1.5f, 0.0f };
#pragma force_active reset

/* Dispatch view of the object's vtable. The handler at vtable offset 0x10 is
 * reached through genuine virtual dispatch in retail: the target loads the
 * vtable through the already-materialised `this` in r3 and keeps the slot in
 * r12, which manual vtable indexing does not reproduce. Two implicit
 * destructor slots plus the two placeholders below put Release at slot 4. */
class TObjectDispatch
{
public:
	virtual void vslot2();
	virtual void vslot3();
	virtual void Release(s32, s32);
	virtual s32 vslot5();
};

extern "C" {

void fn_8_9DA08(void* arg0, s32 arg1)
{
	switch (arg1) {
		case 0:
			M2C_FIELD(arg0, s32*, 0x10) = 0x15;
			break;
		case 1:
		case 2:
		case 3:
			break;
	}
}

void fn_8_9DA28(void* arg0, s32 arg1)
{
	switch (arg1) {
		case 0:
			M2C_FIELD(arg0, s32*, 0x10) = 0x2F;
			break;
		case 1:
		case 2:
		case 3:
			break;
	}
}

void fn_8_9DA48(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x18) = 0xF0;
			M2C_FIELD(arg0, s32*, 0x10) = 0x2E;
			return;
		case 1:
			DecreaseTimer__7nSystemFRi((u8*)((u32)arg0 + 0x18));
			if ((s32)M2C_FIELD(arg0, s32*, 0x18) < 0) {
				if (fn_8_9832C(M2C_FIELD(arg0, s32*, 0x14)) != 0) {
					M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
					((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
					M2C_FIELD(arg0, s32*, 4) = 0xE;
					((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
					return;
				}
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 0xF;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
			} else {
				return;
			}
			break;
		case 2:
		case 3:
			break;
	}
}

#pragma opt_common_subs off
void fn_8_9DB5C(void* arg0, s32 arg1)
{
	s32 state;

	switch (arg1) {
		case 0:
			M2C_FIELD(arg0, s32*, 0x18) = 0x258;
			M2C_FIELD(arg0, s32*, 0x10) = 0x2D;
			break;
		case 1:
			state = M2C_FIELD(M2C_FIELD(arg0, void**, 0x14), s32*, 0x570);
			if (state == 1) {
				DecreaseTimer__7nSystemFRi((u8*)arg0 + 0x18);
				if (M2C_FIELD(arg0, s32*, 0x18) < 0) {
					M2C_FIELD(arg0, s32*, 8) = M2C_FIELD(arg0, s32*, 4);
					((TObjectDispatch*)arg0)->Release(M2C_FIELD(arg0, s32*, 4), 3);
					M2C_FIELD(arg0, s32*, 4) = 7;
					((TObjectDispatch*)arg0)->Release(M2C_FIELD(arg0, s32*, 4), 0);
				}
			} else if (state == 2) {
				M2C_FIELD(arg0, s32*, 8) = M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release(M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 0xD;
				((TObjectDispatch*)arg0)->Release(M2C_FIELD(arg0, s32*, 4), 0);
			}
			break;
		case 2:
		case 3:
			break;
	}
}
#pragma opt_common_subs reset

/* The strategy's destructor, with both bases' inlined. */
M2C_UNK** fn_8_9DC74(M2C_UNK** arg0, s16 arg1)
{
	if (arg0 != NULL) {
		*arg0 = (M2C_UNK*)lbl_8_data_15A70;
		if (arg0 != NULL) {
			*arg0 = (M2C_UNK*)lbl_8_data_15B24;
			if (arg0 != NULL) {
				*arg0 = (M2C_UNK*)lbl_8_data_15B0C;
			}
		}
		if (arg1 > 0) {
			__dl__FPv(arg0);
		}
	}
	return arg0;
}

void fn_8_9DCE8(void* arg0)
{
	M2C_FIELD(arg0, M2C_UNK**, 0) = (M2C_UNK*)lbl_8_data_15B0C;
	M2C_FIELD(arg0, s32*, 4)      = 0;
	M2C_FIELD(arg0, s32*, 8)      = 0;
	M2C_FIELD(arg0, s32*, 0xC)    = 0;
	M2C_FIELD(arg0, s32*, 0x14)   = 0;
	M2C_FIELD(arg0, s32*, 0x10)   = 0;
	M2C_FIELD(arg0, M2C_UNK**, 0) = (M2C_UNK*)lbl_8_data_15B24;
	M2C_FIELD(arg0, M2C_UNK**, 0) = (M2C_UNK*)lbl_8_data_15A70;
}

void fn_8_9DD28(void* arg0, s32 arg1)
{
	switch (arg1) {
		case 0:
			M2C_FIELD(arg0, s32*, 0x10) = 6;
			break;
		case 1:
		case 2:
		case 3:
			break;
	}
}

void fn_8_9DD48(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x18) = 0xB4;
			M2C_FIELD(arg0, s32*, 0x10) = 9;
			return;
		case 1:
			DecreaseTimer__7nSystemFRi((u8*)((u32)arg0 + 0x18));
			if ((s32)M2C_FIELD(arg0, s32*, 0x18) < 0) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 0x11;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
			}
			return;
		case 2:
		case 3:
			break;
	}
}

void fn_8_9DE00(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x18) = 0x258;
			M2C_FIELD(arg0, s32*, 0x10) = 0x2D;
			return;
		case 1:
			if ((s32)M2C_FIELD(M2C_FIELD(arg0, void**, 0x14), s32*, 0x570) == 1) {
				DecreaseTimer__7nSystemFRi((u8*)((u32)arg0 + 0x18));
				if ((s32)M2C_FIELD(arg0, s32*, 0x18) < 0) {
					M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
					((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
					M2C_FIELD(arg0, s32*, 4) = 7;
					((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
				}
			}
			return;
		case 2:
		case 3:
			break;
	}
}

void fn_8_9DEC8(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x10) = 0x2C;
			return;
		case 1:
			if (((u32)M2C_FIELD(arg0, u32*, 0x14) != 0U)
			    && (fn_800A6334((void*)M2C_FIELD(arg0, u32*, 0x14)) == 0)) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 1;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
			}
			return;
		case 2:
		case 3:
			break;
	}
}

void fn_8_9DF7C(void* arg0, s32 arg1)
{
	switch (arg1) {
		case 0:
			M2C_FIELD(arg0, s32*, 0x10) = 0x25;
			break;
		case 1:
		case 2:
		case 3:
			break;
	}
}

void fn_8_9DF9C(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x18) = 0xF0;
			M2C_FIELD(arg0, s32*, 0x10) = 0x24;
			return;
		case 1:
			DecreaseTimer__7nSystemFRi((u8*)((u32)arg0 + 0x18));
			if ((s32)M2C_FIELD(arg0, s32*, 0x18) < 0) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 0xA;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
			}
			return;
		case 2:
		case 3:
			break;
	}
}

void fn_8_9E054(void* arg0, s32 arg1)
{
	switch (arg1) {
		case 0:
			M2C_FIELD(arg0, s32*, 0x10) = 0x1A;
			break;
		case 1:
		case 2:
		case 3:
			break;
	}
}

void fn_8_9E074(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x18) = 0xF0;
			M2C_FIELD(arg0, s32*, 0x10) = 0x20;
			return;
		case 1:
			DecreaseTimer__7nSystemFRi((u8*)((u32)arg0 + 0x18));
			if ((s32)M2C_FIELD(arg0, s32*, 0x18) < 0) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 1;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
			}
			return;
		case 2:
		case 3:
			break;
	}
}

void fn_8_9E12C(void* arg0, s32 arg1)
{
	void* temp_r3;

	switch (arg1) { /* irregular */
		case 0:
			temp_r3 = M2C_FIELD(arg0, void**, 0x14);
			if (temp_r3 != NULL) {
				M2C_FIELD(arg0, s32*, 0x18) = (s32)M2C_FIELD(temp_r3, s32*, 0x584);
			}
			M2C_FIELD(arg0, s32*, 0x10) = 0x1F;
			return;
		case 1:
			if (((void*)M2C_FIELD(arg0, void**, 0x14) != NULL)
			    && (fn_8_98B08(M2C_FIELD(arg0, u32*, 0x14)) == 0)) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 1;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
			}
			DecreaseTimer__7nSystemFRi((u8*)((u32)arg0 + 0x18));
			if ((s32)M2C_FIELD(arg0, s32*, 0x18) < 0) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 7;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
			}
			return;
		case 2:
		case 3:
			break;
	}
}

void fn_8_9E250(void* arg0, s32 arg1)
{
	switch (arg1) {
		case 0:
			M2C_FIELD(arg0, s32*, 0x10) = 0x1D;
			break;
		case 1:
		case 2:
		case 3:
			break;
	}
}

void fn_8_9E270(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x10) = 2;
			return;
		case 1:
			if (((u32)M2C_FIELD(arg0, u32*, 0x14) != 0U)
			    && (fn_8_98B08(M2C_FIELD(arg0, u32*, 0x14)) != 0)) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 0xB;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
			}
			return;
		case 2:
		case 3:
			break;
	}
}

void fn_8_9E324(void* arg0, s32 arg1)
{
	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x10) = 1;
			return;
		case 1:
			if (((u32)M2C_FIELD(arg0, u32*, 0x14) != 0U)
			    && (fn_8_98B94(M2C_FIELD(arg0, u32*, 0x14)) != 0)) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 1;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
				return;
			}
			if (((u32)M2C_FIELD(arg0, u32*, 0x14) != 0U)
			    && (fn_8_98464(M2C_FIELD(arg0, u32*, 0x14)) != 0)) {
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 1;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
			}
			return;
		case 2:
		case 3:
			break;
	}
}

void fn_8_9E43C(void* arg0, void* arg1)
{
	void* temp_r4;
	s32 temp_r0;

	M2C_FIELD(arg0, void**, 0x14) = arg1;
	temp_r4                       = M2C_FIELD(arg0, void**, 0x14);
	if (temp_r4 != NULL) {
		temp_r0 = M2C_FIELD(temp_r4, s32*, 0x580);
		switch (temp_r0) { /* irregular */
			case 0:
				M2C_FIELD(arg0, s32*, 0xC)  = 0;
				M2C_FIELD(arg0, s32*, 0x10) = 0;
				M2C_FIELD(arg0, s32*, 4)    = 0;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
				if ((s32)M2C_FIELD(arg0, s32*, 0x10) != 0) {
					fn_800A31B8(M2C_FIELD(arg0, void**, 0x14), M2C_FIELD(arg0, s32*, 0x10));
					return;
				}
				break;
			case 1:
				M2C_FIELD(arg0, s32*, 0xC)  = 1;
				M2C_FIELD(arg0, s32*, 0x10) = 0;
				M2C_FIELD(arg0, s32*, 4)    = 1;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
				if ((s32)M2C_FIELD(arg0, s32*, 0x10) != 0) {
					fn_800A31B8(M2C_FIELD(arg0, void**, 0x14), M2C_FIELD(arg0, s32*, 0x10));
				}
				break;
		}
	}
}

/* TEnemyStrategy::ChangeMode: leaves the current mode (phase 3), remembers
 * it and enters the new one (phase 0). */
static inline void eggChangeMode(void* arg0, s32 mode)
{
	M2C_FIELD(arg0, s32*, 8) = M2C_FIELD(arg0, s32*, 4);
	((TObjectDispatch*)arg0)->Release(M2C_FIELD(arg0, s32*, 4), 3);
	M2C_FIELD(arg0, s32*, 4) = mode;
	((TObjectDispatch*)arg0)->Release(M2C_FIELD(arg0, s32*, 4), 0);
}

/* TEnemyEggMobile_Strategy::IsReqChangeMode: picks the strategy mode the egg
 * mobile's state (the owner at 0x14) asks for. */
s32 fn_8_9E510(void* arg0)
{
	s32 changed;
	u32 flags;
	s32 mode;

	fn_8_98480(M2C_FIELD(arg0, void**, 0x14));
	if (fn_800A3ED4(M2C_FIELD(arg0, void**, 0x14)) != 0
	    && M2C_FIELD(M2C_FIELD(arg0, void**, 0x14), s32*, 0x19C) != 0x1D) {
		eggChangeMode(arg0, 5);
		return 1;
	}
	if (M2C_FIELD(M2C_FIELD(arg0, void**, 0x14), s32*, 0x280) != 0) {
		switch (M2C_FIELD(M2C_FIELD(arg0, void**, 0x14), s32*, 0x19C)) {
			case 1:
			case 2:
			case 6:
			case 9:
			case 0x2C:
				eggChangeMode(arg0, 0xC);
				return 1;
		}
		fn_8_9897C();
	}
	if (M2C_FIELD(M2C_FIELD(arg0, void**, 0x14), s32*, 0x248) != 0) {
		changed = 0;
		switch (M2C_FIELD(M2C_FIELD(arg0, void**, 0x14), s32*, 0x248)) {
			case 2:
				eggChangeMode(arg0, 1);
				changed = 1;
				break;
			case 0x2E:
				eggChangeMode(arg0, 0xD);
				changed = 1;
				break;
			case 9:
				eggChangeMode(arg0, 0x10);
				changed = 1;
				break;
		}
		M2C_FIELD(M2C_FIELD(arg0, void**, 0x14), s32*, 0x248) = 0;
		return changed;
	}
	flags = M2C_FIELD(M2C_FIELD(arg0, void**, 0x14), u32*, 0x18C);
	if (flags & 0x1000) {
		switch (M2C_FIELD(M2C_FIELD(arg0, void**, 0x14), s32*, 0x19C)) {
			case 0x1A:
			case 0x1D:
			case 0x24:
			case 0x25:
				return 0;
		}
		eggChangeMode(arg0, 8);
		return 1;
	}
	mode = M2C_FIELD(M2C_FIELD(arg0, void**, 0x14), s32*, 0x19C);
	switch (mode) {
		case 0x1A:
			eggChangeMode(arg0, M2C_FIELD(arg0, s32*, 8));
			return 1;
	}
	if (flags & 0x2000) {
		switch (mode) {
			case 1:
			case 2:
			case 6:
			case 9:
			case 0x2C:
				eggChangeMode(arg0, 9);
				return 1;
		}
		return 0;
	}
	return 0;
}

/* TObjEnemyEggMobile's strategy vtable (the derived class's, the base's at
 * 15B0C and the shared mode table at 15B24 follow the switch table). */
M2C_UNK** fn_8_9DC74(M2C_UNK** arg0, s16 arg1);
void fn_8_9D3C4();
void fn_8_9E924(void** arg0, u32 arg1, s32 arg2);
s32 fn_8_9E510(void* arg0);
void fn_8_9E324(void* arg0, s32 arg1);
void fn_8_9E270(void* arg0, s32 arg1);
void fn_8_9E250(void* arg0, s32 arg1);
void fn_8_9E12C(void* arg0, s32 arg1);
void fn_8_9E074(void* arg0, s32 arg1);
void fn_8_9E054(void* arg0, s32 arg1);
void fn_8_9DF9C(void* arg0, s32 arg1);
void fn_8_9DF7C(void* arg0, s32 arg1);
void fn_8_9DEC8(void* arg0, s32 arg1);
void fn_8_9DB5C(void* arg0, s32 arg1);
void fn_8_9DA48(void* arg0, s32 arg1);
void fn_8_9DA28(void* arg0, s32 arg1);
void fn_8_9DA08(void* arg0, s32 arg1);
void fn_8_9DD48(void* arg0, s32 arg1);
void fn_8_9DD28(void* arg0, s32 arg1);

void* lbl_8_data_15A70[21] = {
	NULL,
	NULL,
	(void*)fn_8_9DC74,
	(void*)fn_8_9D3C4,
	(void*)fn_8_9E924,
	(void*)fn_8_9E510,
	(void*)fn_8_9E324,
	(void*)fn_8_9E270,
	(void*)fn_8_9E250,
	(void*)fn_8_9E12C,
	(void*)fn_8_9E074,
	(void*)fn_8_9E054,
	(void*)fn_8_9DF9C,
	(void*)fn_8_9DF7C,
	(void*)fn_8_9DEC8,
	(void*)fn_8_9DB5C,
	(void*)fn_8_9DA48,
	(void*)fn_8_9DA28,
	(void*)fn_8_9DA08,
	(void*)fn_8_9DD48,
	(void*)fn_8_9DD28,
};

void fn_8_9E924(void** arg0, u32 arg1, s32 arg2)
{
	switch (arg1) {
		case 0:
			((TStateDispatch*)arg0)->Slot18(arg2);
			return;
		case 1:
			((TStateDispatch*)arg0)->Slot1C(arg2);
			return;
		case 5:
			((TStateDispatch*)arg0)->Slot20(arg2);
			return;
		case 6:
			((TStateDispatch*)arg0)->Slot24(arg2);
			return;
		case 7:
			((TStateDispatch*)arg0)->Slot28(arg2);
			return;
		case 8:
			((TStateDispatch*)arg0)->Slot2C(arg2);
			return;
		case 9:
			((TStateDispatch*)arg0)->Slot30(arg2);
			return;
		case 10:
			((TStateDispatch*)arg0)->Slot34(arg2);
			return;
		case 11:
			((TStateDispatch*)arg0)->Slot38(arg2);
			return;
		case 12:
			((TStateDispatch*)arg0)->Slot3C(arg2);
			return;
		case 13:
			((TStateDispatch*)arg0)->Slot40(arg2);
			return;
		case 14:
			((TStateDispatch*)arg0)->Slot44(arg2);
			return;
		case 15:
			((TStateDispatch*)arg0)->Slot48(arg2);
			return;
		case 17:
			((TStateDispatch*)arg0)->Slot50(arg2);
			return;
		case 16:
			((TStateDispatch*)arg0)->Slot4C(arg2);
			/* fallthrough */
		default:
			return;
	}
}

M2C_UNK** fn_8_9EB5C(M2C_UNK** arg0, s16 arg1);
M2C_UNK** fn_8_9EAC4(M2C_UNK** arg0, s16 arg1);
void fn_8_9DE00(void* arg0, s32 arg1);
void fn_8_9EBB4();
void fn_8_9EBB0();
void fn_8_9EBAC();

void* lbl_8_data_15B0C[6] = { NULL, NULL, (void*)fn_8_9EB5C, (void*)fn_8_9D3C4, NULL, NULL };

void* lbl_8_data_15B24[21] = {
	NULL,
	NULL,
	(void*)fn_8_9EAC4,
	(void*)fn_8_9D3C4,
	(void*)fn_8_9E924,
	(void*)fn_8_9E510,
	(void*)fn_8_9E324,
	(void*)fn_8_9E270,
	(void*)fn_8_9E250,
	(void*)fn_8_9E12C,
	(void*)fn_8_9E074,
	(void*)fn_8_9E054,
	(void*)fn_8_9DF9C,
	(void*)fn_8_9DF7C,
	(void*)fn_8_9DEC8,
	(void*)fn_8_9DE00,
	(void*)fn_8_9EBB4,
	(void*)fn_8_9EBB0,
	(void*)fn_8_9EBAC,
	(void*)fn_8_9DD48,
	(void*)fn_8_9DD28,
};

M2C_UNK** fn_8_9EAC4(M2C_UNK** arg0, s16 arg1)
{
	if (arg0 != NULL) {
		*arg0 = (M2C_UNK*)lbl_8_data_15B24;
		if (arg0 != NULL) {
			*arg0 = (M2C_UNK*)lbl_8_data_15B0C;
		}
		if (arg1 > 0) {
			__dl__FPv(arg0);
		}
	}
	return arg0;
}

void fn_8_9EB28(void* arg0)
{
	M2C_FIELD(arg0, M2C_UNK**, 0) = (M2C_UNK*)lbl_8_data_15B0C;
	M2C_FIELD(arg0, s32*, 4)      = 0;
	M2C_FIELD(arg0, s32*, 8)      = 0;
	M2C_FIELD(arg0, s32*, 0xC)    = 0;
	M2C_FIELD(arg0, s32*, 0x14)   = 0;
	M2C_FIELD(arg0, s32*, 0x10)   = 0;
	M2C_FIELD(arg0, M2C_UNK**, 0) = (M2C_UNK*)lbl_8_data_15B24;
}

M2C_UNK** fn_8_9EB5C(M2C_UNK** arg0, s16 arg1)
{
	if (arg0 != NULL) {
		*arg0 = (M2C_UNK*)lbl_8_data_15B0C;
		if (arg1 > 0) {
			__dl__FPv(arg0);
		}
	}
	return arg0;
}

void fn_8_9EBAC(void) { }

void fn_8_9EBB0(void) { }

void fn_8_9EBB4(void) { }
}
