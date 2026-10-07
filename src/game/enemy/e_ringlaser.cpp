// Complete C++ enemy/e_ringlaser.cpp; GC behavior and symbolic type metadata.
#include "game/enemy/e_ringlaser.h"
struct RwObject {
	u8 type, subType, flags, privateFlags;
	void* parent;
};
struct RpClump {
	RwObject object;
};
struct RpAtomic;
struct RwFrame;
struct RwCamera;
struct RpUVAnimAnimation;
struct RwMatrix {
	RwV3d right;
	u32 flags;
	RwV3d up;
	u32 pad1;
	RwV3d at;
	u32 pad2;
	RwV3d pos;
	u32 pad3;
};
struct UVFXInfo {
	RpUVAnimAnimation* uvAnim;
	RwMatrix uvMatrix;
};
struct RwSphere {
	RwV3d center;
	f32 radius;
};
enum ACTIONMODE_TURN {
	ACTIONMODE_TURN_NONE,
	ACTIONMODE_TURN_CONTINUE,
	ACTIONMODE_TURN_RESTART,
	ACTIONMODE_TURN_GIVEUP,
	ACTIONMODE_TURN_MAX
};
struct RingActionView {
	u8 unknown[0x18];
	ACTIONMODE_TURN restartFlag;
};
struct RingModeView {
	s8 modeswitchflags[0x28];
	s32 modeswitchlws[6];
};
// Referenced public database contract, independently recovered in e_database.cpp.
enum eEnemyDataBase { ENEMY_DB_COMMON = 0 };
struct EnemyDataBaseEntry {
	void* addr;
	s32 filenum;
};
class TEnemyDataBase
{
public:
	TEnemyDataBase();
	static TEnemyDataBase* mpDataBase;
	static TEnemyDataBase* GetInstance()
	{
		if (!mpDataBase)
			new TEnemyDataBase;
		return mpDataBase;
	}
	RpClump* SearchClump(eEnemyDataBase, u32);
	RpUVAnimAnimation* SearchUVAnim(eEnemyDataBase, u32);
	EnemyDataBaseEntry entries[14];
};

extern "C" {
extern RingActionView lbl_8029C310;
extern RingModeView* lbl_8042C180;
extern TObject* lbl_8042C10C;
extern RwCamera** lbl_8042C9A4;
extern RwV3d lbl_80239984;
s32 fn_8003C200(C_COLLI*, CCL_INFO*, s32, u8);
s32 fn_8003BC38(C_COLLI*);
s32 fn_80017800(TObject*);
s32 fn_8019CE34(RwCamera*, const RwSphere*);
RwFrame* fn_8019EC30(RwFrame*, const RwV3d*, s32);
RwFrame* fn_8019ED68(RwFrame*, const RwV3d*, f32, s32);
RwFrame* fn_8019EB94(RwFrame*, const RwV3d*, s32);
void fn_80113940();
void fn_801138B4();
void fn_80113874(s32);
void fn_801138F4();
s32 fn_8011B844(RpUVAnimAnimation*, f32);
RpAtomic* fn_8005BF88(RpAtomic*, void*);
RpClump* fn_8014FFBC(RpClump*, RpAtomic* (*)(RpAtomic*, void*), void*);
RpClump* fn_8014FF2C(RpClump*);
void fn_8005BF5C(RpClump*, UVFXInfo*);
}
static CCL_INFO ci_ringlaser[1]
    = { { 0, 11, 0xf0, 0xa2, 0x00080000, { 0, 0, 0 }, 30, 10, 20, 0, 0x4000, 0, 0 } };
static RpClump* pClumpStatic;
static RpUVAnimAnimation* pUVAnimStatic;
static UVFXInfo uvfxinfo;
static s32 TemporaryTmr;
char* CL_TObjEnemyRingLaser = "TObjEnemyRingLaser";

// Reconstruction of the shared restart predicate; the original helper name is unknown.
static inline s32 RingIsRestarting()
{
	ACTIONMODE_TURN restartFlag = lbl_8029C310.restartFlag;
	return (restartFlag == ACTIONMODE_TURN_CONTINUE || restartFlag == ACTIONMODE_TURN_RESTART)
	    || restartFlag == ACTIONMODE_TURN_GIVEUP;
}

sRingLaserParam::sRingLaserParam()
{
	pos.x = pos.y = pos.z = 0.0f;
	spd.x = spd.y = 0.0f;
	spd.z         = -1.0f;
	ang.x = ang.y = ang.z = 0;
	scl                   = 0.1f;
	scl_acc               = 0.02f;
	life                  = 600;
}

void sRingLaserParam::Calc()
{
	pos.x += spd.x;
	pos.y += spd.y;
	pos.z += spd.z;
	scl += scl_acc;
	if (scl > 1.0f)
		scl = 1.0f;
	--life;
}

s32 sRingLaserParam::Alive()
{
	return life > 0;
}

void TObjEnemyRingLaser::Initialize()
{
	pClumpStatic  = TEnemyDataBase::GetInstance()->SearchClump(ENEMY_DB_COMMON, 10);
	pUVAnimStatic = TEnemyDataBase::GetInstance()->SearchUVAnim(ENEMY_DB_COMMON, 11);
	if (pClumpStatic && pUVAnimStatic) {
		uvfxinfo.uvAnim = pUVAnimStatic;
		fn_8005BF5C(pClumpStatic, &uvfxinfo);
	}
	TemporaryTmr = 0;
}

void TObjEnemyRingLaser::Finalize() { }

TObjEnemyRingLaser* TObjEnemyRingLaser::Create(const sRingLaserParam* param)
{
	return new TObjEnemyRingLaser(lbl_8042C10C, param);
}

TObjEnemyRingLaser::TObjEnemyRingLaser(TObject* parent, const sRingLaserParam* param)
    : TObject(parent)
{
	ClassName = CL_TObjEnemyRingLaser;
	DispTime  = sizeof(TObjEnemyRingLaser);
	mParam    = *param;
	mpClump   = 0;
	CloneClump();
	mParam.Calc();
	if (info) {
		info->a = 30.0f * mParam.scl;
		info->c = 20.0f * mParam.scl;
	}
	fn_8003C200(&static_cast<C_COLLI&>(*this), ci_ringlaser, 1, 3);
	flag &= ~0x40;
}

TObjEnemyRingLaser::~TObjEnemyRingLaser()
{
	DestroyClump();
}

void TObjEnemyRingLaser::CloneClump()
{
	mpClump = pClumpStatic;
}

void TObjEnemyRingLaser::DestroyClump() { }

void TObjEnemyRingLaser::SetPosition()
{
	if (info) {
		pre_pos.x = pos.x;
		pre_pos.y = pos.y;
		pre_pos.z = pos.z;
		pos.x     = mParam.pos.x;
		pos.y     = mParam.pos.y;
		pos.z     = mParam.pos.z;
		ang.x     = mParam.ang.x;
		ang.y     = mParam.ang.y;
		ang.z     = mParam.ang.z;
		fn_8003BC38(&static_cast<C_COLLI&>(*this));
	}
}

void TObjEnemyRingLaser::Exec()
{
	s32 restarting = RingIsRestarting();
	if (restarting) {
		Signal |= 1;
		return;
	}
	s32 canAdvance;
	if (lbl_8042C180->modeswitchflags[0x1f])
		canAdvance = 0;
	else if (lbl_8042C180->modeswitchflags[0x20])
		canAdvance = 0;
	else if (lbl_8042C180->modeswitchflags[0x21])
		canAdvance = 0;
	else
		canAdvance = 1;
	if (!canAdvance) {
		ClearInfo();
		return;
	}
	mParam.Calc();
	if (info) {
		info->a = 30.0f * mParam.scl;
		info->c = 20.0f * mParam.scl;
	}
	if ((long)mParam.Alive() == 0L) {
		Signal |= 1;
		return;
	}
	if (fn_80017800(this))
		SetPosition();
}

void TObjEnemyRingLaser::TDisp()
{
	if (!mpClump)
		return;
	if (!CheckCameraFrustumTest())
		return;
	RwFrame* frame = (RwFrame*)mpClump->object.parent;
	RwV3d scale    = { 0, 0, 1 };
	scale.x        = mParam.scl;
	scale.y        = mParam.scl;
	fn_8019EC30(frame, &scale, 0);
	fn_8019ED68(frame, &lbl_80239984, 180.0f + 0.0054931640625f * mParam.ang.y, 2);
	fn_8019EB94(frame, &mParam.pos, 2);
	fn_80113940();
	fn_801138B4();
	fn_80113874(16);
	s32 tmr = lbl_8042C180->modeswitchlws[2];
	if (TemporaryTmr != tmr) {
		TemporaryTmr = tmr;
		fn_8011B844(pUVAnimStatic, 1.2f);
		fn_8014FFBC(pClumpStatic, fn_8005BF88, &uvfxinfo);
	}
	fn_8014FF2C(mpClump);
	fn_801138F4();
}

s32 TObjEnemyRingLaser::CheckCameraFrustumTest()
{
	RwSphere sphere;
	sphere.center.x = mParam.pos.x;
	sphere.center.y = mParam.pos.y;
	sphere.center.z = mParam.pos.z;
	sphere.radius   = 30.0f;
	if (fn_8019CE34(*lbl_8042C9A4, &sphere) == 0)
		return 0;
	return 1;
}
