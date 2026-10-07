// Complete C++ enemy/e_powercore.cpp. GC layout and behavior, symbolic metadata names.
#include "game/enemy/e_powercore.h"
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
struct RwRGBAReal {
	f32 red, green, blue, alpha;
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
struct PowerActionView {
	u8 unknown[0x18];
	ACTIONMODE_TURN restartFlag;
};
struct PowerModeView {
	u8 unknown[0x30];
	s32 totalTime;
};
struct PowerPlayerView {
	u8 unknown[0x25c];
	s8 teamNo;
};
struct PowerOldPlayerView {
	u8 unknown[0x9b4];
	s32 player_type;
};
struct PowerTeamView {
	u8 unknown[0x3a];
	s8 leaderNo;
	u8 unknown3b[0x114 - 0x3b];
	PowerOldPlayerView* member_class_ptr[3];
	s8 numFormationMembers;
	u8 unknown121[7];
	PowerOldPlayerView* formation_class_ptr[3];
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
extern PowerActionView lbl_8029C310;
extern PowerModeView* lbl_8042C180;
extern PowerPlayerView* lbl_802AD0D0[8];
extern PowerTeamView* lbl_80303DC8[4];
extern TObject* lbl_8042C0FC;
extern TObject* lbl_8042C10C;
extern sAngle lbl_8023AAA0;
extern u8 lbl_8042C1A4;
extern RwCamera** lbl_8042C9A4;
s32 rand();
s32 fn_80091FAC(PowerTeamView*);
s32 fn_8003C200(C_COLLI*, CCL_INFO*, s32, u8);
f32 fn_800D8BC4(RwV3d*, s32, s32);
RpClump* fn_80150588(RpClump*);
s32 fn_80150958(RpClump*);
void fn_80113940();
void fn_801138B4();
void fn_80113874(s32);
void fn_801138F4();
s32 fn_8011B844(RpUVAnimAnimation*, f32);
RpAtomic* fn_8005BF88(RpAtomic*, void*);
RpClump* fn_8014FFBC(RpClump*, RpAtomic* (*)(RpAtomic*, void*), void*);
void fn_8005DABC(RpClump*, RwRGBAReal*);
RpClump* fn_8014FF2C(RpClump*);
s32 fn_8019CE34(RwCamera*, const RwSphere*);
void fn_80021824(void*);
CCL_HIT_INFO* fn_800211A8(C_COLLI*);
s32 fn_800418A8(CHARACTER_ID);
s32 fn_80090790(PowerTeamView*, s32, s32);
void fn_80066A14(PARAM_SCORE*, s32, s32, s32);
RwFrame* fn_8019EB94(RwFrame*, const RwV3d*, s32);
s32 fn_80017800(TObject*);
s32 fn_8003BC38(C_COLLI*);
void fn_8005DA34(RpClump*);
void fn_8005BF5C(RpClump*, UVFXInfo*);
}
static RpClump* pClumpStatic[2] = { 0, 0 };
static RpUVAnimAnimation* pUVAnimStatic;
static UVFXInfo uvfxinfo[2];
static s32 TemporaryTmr[2]          = { 0, 0 };
static RwRGBAReal powercore_rgba[3] = { { 0.0f, 90.0f / 255.0f, 170.0f / 255.0f, 1.0f },
	{ 240.0f / 255.0f, 25.0f / 255.0f, 60.0f / 255.0f, 1.0f },
	{ 250.0f / 255.0f, 165.0f / 255.0f, 25.0f / 255.0f, 1.0f } };
static CCL_INFO ci_powercore[1]
    = { { 0, 0, 0xf0, 0, 0x00708000, { 0, 0, 0 }, 10, 10, 10, 0, 0, 0, 0 } };
char* CL_TEnemyPowerCore = "TEnemyPowerCore";
TEnemyPowerCoreMan* TEnemyPowerCoreMan::EnemyPowerCoreMan;
char* CL_TEnemyPowerCoreMan = "TEnemyPowerCoreMan";
static inline s32 PowerIsRestarting()
{
	ACTIONMODE_TURN flag = lbl_8029C310.restartFlag;
	return (flag == ACTIONMODE_TURN_CONTINUE || flag == ACTIONMODE_TURN_RESTART)
	    || flag == ACTIONMODE_TURN_GIVEUP;
}
inline sEnemyPowerCore::sEnemyPowerCore()
{
	pos.x = pos.y = pos.z = 0.0f;
	// GC repeats pos.z here and leaves spd.z uninitialized; preserve that behavior.
	spd.x = pos.z = 0.0f;
	spd.y         = 2.5f;
	max_pos_y     = 0.0f;
	floor         = 0.0f;
	type          = 0;
}
inline void TEnemyPowerCore::CloneClump()
{
	mpClump[0] = fn_80150588(pClumpStatic[0]);
	mpClump[1] = fn_80150588(pClumpStatic[1]);
}
inline TEnemyPowerCore::TEnemyPowerCore(TObject* ptp, const sEnemyPowerCore* param)
    : TObject(ptp)
{
	ClassName  = CL_TEnemyPowerCore;
	DispTime   = sizeof(TEnemyPowerCore);
	mParam     = *param;
	mpClump[0] = 0;
	mpClump[1] = 0;
	mMode      = 0;
	mPlayerID  = NO_CHARACTER_ID;
	CloneClump();
	fn_8003C200(&static_cast<C_COLLI&>(*this), ci_powercore, 1, 4);
	mTimer    = 25;
	RwV3d pos = mParam.pos;
	pos.y += 10.0f;
	mParam.floor = fn_800D8BC4(&pos, 0, 0);
	mParam.floor += 8.0f;
}
inline void TEnemyPowerCore::Create(const sEnemyPowerCore* param)
{
	new TEnemyPowerCore(lbl_8042C10C, param);
}
void TEnemyPowerCore::Initialize()
{
	pClumpStatic[0] = TEnemyDataBase::GetInstance()->SearchClump(ENEMY_DB_COMMON, 12);
	pClumpStatic[1] = TEnemyDataBase::GetInstance()->SearchClump(ENEMY_DB_COMMON, 14);
	pUVAnimStatic   = TEnemyDataBase::GetInstance()->SearchUVAnim(ENEMY_DB_COMMON, 13);
	if (pClumpStatic[0])
		fn_8005DA34(pClumpStatic[0]);
	if (pClumpStatic[0] && pUVAnimStatic) {
		uvfxinfo[0].uvAnim = pUVAnimStatic;
		fn_8005BF5C(pClumpStatic[0], &uvfxinfo[0]);
	}
	if (pClumpStatic[1] && pUVAnimStatic) {
		uvfxinfo[1].uvAnim = pUVAnimStatic;
		fn_8005BF5C(pClumpStatic[1], &uvfxinfo[1]);
	}
	TemporaryTmr[0] = 0;
	TemporaryTmr[1] = 0;
}
void TEnemyPowerCore::Finalize()
{
	pClumpStatic[0] = 0;
	pClumpStatic[1] = 0;
	pUVAnimStatic   = 0;
}
TEnemyPowerCore::~TEnemyPowerCore()
{
	DestroyClump();
}
void TEnemyPowerCore::Exec()
{
	if (PowerIsRestarting()) {
		Signal |= 1;
		return;
	}
	switch (mMode) {
		case 0:
			mParam.max_pos_y = 50.0f + mParam.pos.y;
			mMode            = 1;
			break;
		case 1:
			mParam.spd.y *= 0.97f;
			mParam.pos.y += mParam.spd.y;
			if (mParam.pos.y > mParam.max_pos_y)
				mParam.pos.y = mParam.max_pos_y;
			if (CheckHitCollision())
				mMode = 3;
			if (--mTimer < 0)
				mMode = 2;
			break;
		case 2:
			mParam.pos.y -= 0.15f;
			if (mParam.pos.y < mParam.floor)
				mParam.pos.y = mParam.floor;
			if (CheckHitCollision())
				mMode = 3;
			break;
		case 3:
			if (mPlayerID != NO_CHARACTER_ID) {
				s32 team = fn_800418A8(mPlayerID);
				if (team != -1) {
					switch (mParam.type) {
						case 0:
							if (fn_80090790(lbl_80303DC8[team], 0, 1))
								fn_80066A14(&static_cast<PARAM_SCORE&>(*this), team, 0, 100);
							else
								fn_80066A14(&static_cast<PARAM_SCORE&>(*this), team, 0, 500);
							break;
						case 1:
							if (fn_80090790(lbl_80303DC8[team], 2, 1))
								fn_80066A14(&static_cast<PARAM_SCORE&>(*this), team, 2, 100);
							else
								fn_80066A14(&static_cast<PARAM_SCORE&>(*this), team, 2, 500);
							break;
						case 2:
							if (fn_80090790(lbl_80303DC8[team], 1, 1))
								fn_80066A14(&static_cast<PARAM_SCORE&>(*this), team, 1, 100);
							else
								fn_80066A14(&static_cast<PARAM_SCORE&>(*this), team, 1, 500);
							break;
					}
				}
			}
			Signal |= 1;
			break;
	}
	if (mpClump[0])
		fn_8019EB94((RwFrame*)mpClump[0]->object.parent, &mParam.pos, 0);
	if (mpClump[1])
		fn_8019EB94((RwFrame*)mpClump[1]->object.parent, &mParam.pos, 0);
	if (fn_80017800(this)) {
		sAngle angle = lbl_8023AAA0;
		pre_pos      = pos;
		pos          = mParam.pos;
		ang          = angle;
		fn_8003BC38(&static_cast<C_COLLI&>(*this));
	}
}
void TEnemyPowerCore::Disp()
{
	if (!mpClump[0]) {
		boolFrustumReturn = 0;
		return;
	}
	RwSphere sphere;
	sphere.center.x = mParam.pos.x;
	sphere.center.y = mParam.pos.y;
	sphere.center.z = mParam.pos.z;
	sphere.radius   = 8.0f;
	if (fn_8019CE34(*lbl_8042C9A4, &sphere) == 0)
		boolFrustumReturn = 0;
	else
		boolFrustumReturn = 1;
	if (boolFrustumReturn) {
		s32 timer = lbl_8042C180->totalTime;
		if (TemporaryTmr[0] != timer) {
			TemporaryTmr[0] = timer;
			fn_8011B844(pUVAnimStatic, 0.25f);
			fn_8014FFBC(pClumpStatic[0], fn_8005BF88, &uvfxinfo[0]);
		}
		fn_8005DABC(mpClump[0], &powercore_rgba[mParam.type]);
		fn_8014FF2C(mpClump[0]);
	}
}
inline TEnemyPowerCoreMan::TEnemyPowerCoreMan(TObject* ptp)
    : TObject(ptp)
{
	ClassName         = CL_TEnemyPowerCoreMan;
	DispTime          = sizeof(TEnemyPowerCoreMan);
	mEnemyDestroyNum  = 0;
	EnemyPowerCoreMan = this;
}
void TEnemyPowerCore::TDisp()
{
	if (mpClump[1] && boolFrustumReturn) {
		fn_80113940();
		fn_801138B4();
		fn_80113874(16);
		s32 timer     = lbl_8042C180->totalTime;
		s32& previous = TemporaryTmr[1];
		if (previous != timer) {
			previous = timer;
			fn_8011B844(pUVAnimStatic, 0.25f);
			fn_8014FFBC(pClumpStatic[1], fn_8005BF88, &uvfxinfo[1]);
		}
		fn_8005DABC(mpClump[1], &powercore_rgba[mParam.type]);
		fn_8014FF2C(mpClump[1]);
		fn_801138F4();
	}
}
void TEnemyPowerCoreMan::CreateInstance()
{
	if (!EnemyPowerCoreMan)
		new TEnemyPowerCoreMan(lbl_8042C0FC);
}
TEnemyPowerCoreMan* TEnemyPowerCoreMan::GetInstance()
{
	if (!EnemyPowerCoreMan)
		CreateInstance();
	return EnemyPowerCoreMan;
}
void TEnemyPowerCoreMan::DeleteInstance()
{
	if (EnemyPowerCoreMan)
		EnemyPowerCoreMan->Signal |= 1;
}
TEnemyPowerCoreMan::~TEnemyPowerCoreMan()
{
	EnemyPowerCoreMan = 0;
}
inline s32 TEnemyPowerCore::CheckHitCollision()
{
	if (flag & 1) {
		fn_80021824(&lbl_8042C1A4);
		CCL_HIT_INFO* hit = fn_800211A8(&static_cast<C_COLLI&>(*this));
		C_COLLI* ccl;
		if (hit)
			ccl = hit->hit_ccl;
		else
			ccl = 0;
		if (ccl) {
			mPlayerID = ccl->character_id;
			return 1;
		}
	}
	return 0;
}
void TEnemyPowerCoreMan::Exec()
{
	if (PowerIsRestarting()) {
		mEnemyDestroyNum = 0;
		return;
	}
	if (mEnemyDestroyNum > 4) {
		mEnemyDestroyNum     = 0;
		mPowerCoreParam.type = DecideTypeFromLeaderPlayerNumber(mLeaderPlayerNum);
		TEnemyPowerCore::Create(&mPowerCoreParam);
	}
}
inline void TEnemyPowerCore::DestroyClump()
{
	if (mpClump[1]) {
		fn_80150958(mpClump[1]);
		mpClump[1] = 0;
	}
	if (mpClump[0]) {
		fn_80150958(mpClump[0]);
		mpClump[0] = 0;
	}
}
void TEnemyPowerCoreMan::Entry(const RwV3d* pos, s32 playernumber)
{
	++mEnemyDestroyNum;
	mPowerCoreParam.pos  = *pos;
	mPowerCoreParam.type = 0;
	mLeaderPlayerNum     = playernumber;
}
void TEnemyPowerCoreMan::EntryEx(const RwV3d* pos, s32 playernumber)
{
	mEnemyDestroyNum     = 0;
	mLeaderPlayerNum     = playernumber;
	mPowerCoreParam.pos  = *pos;
	mPowerCoreParam.type = DecideTypeFromLeaderPlayerNumber(mLeaderPlayerNum);
	TEnemyPowerCore::Create(&mPowerCoreParam);
}
s32 TEnemyPowerCoreMan::DecideTypeFromLeaderPlayerNumber(s32 playernumber)
{
	if (playernumber == -1)
		return 0;
	PowerTeamView* pteam = lbl_80303DC8[lbl_802AD0D0[playernumber]->teamNo];
	if (!pteam)
		return 0;
	s32 type = 0;
	switch (pteam->numFormationMembers) {
		case 1:
			type = fn_80091FAC(pteam);
			break;
		case 2: {
			PowerOldPlayerView* p0 = pteam->formation_class_ptr[0];
			PowerOldPlayerView* p1 = pteam->formation_class_ptr[1];
			s32 player_type;
			if (p0 == pteam->member_class_ptr[pteam->leaderNo])
				player_type = p1->player_type;
			else
				player_type = p0->player_type;
			switch (player_type) {
				case 0:
					type = 0;
					break;
				case 1:
					type = 2;
					break;
				case 2:
					type = 1;
					break;
			}
			break;
		}
		case 3:
			switch (fn_80091FAC(pteam)) {
				case 0:
					if ((1.0f / 32768.0f) * rand() < 0.5f)
						type = 1;
					else
						type = 2;
					break;
				case 1:
					if ((1.0f / 32768.0f) * rand() < 0.5f)
						type = 0;
					else
						type = 2;
					break;
				case 2:
					if ((1.0f / 32768.0f) * rand() < 0.5f)
						type = 0;
					else
						type = 1;
					break;
			}
			break;
	}
	return type;
}
