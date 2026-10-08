// Complete C++ enemy/e_shockwave.cpp, reconstructed from GC and symbolic metadata.
#include "game/enemy/e_shockwave.h"
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
struct RwRGBAReal {
	f32 red, green, blue, alpha;
};
struct ShockModeView {
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
extern ShockModeView* lbl_8042C180;
extern TObject* lbl_8042C10C;
extern RwCamera** lbl_8042C9A4;
extern RwV3d AxisY;
f32 AdjustFloat__Ffff(f32, f32, f32);
void IncreaseTimer__7nSystemFRi(s32*);
s32 fn_8019CE34(RwCamera*, const RwSphere*);
RwFrame* fn_8019EC30(RwFrame*, const RwV3d*, s32);
RwFrame* fn_8019ED68(RwFrame*, const RwV3d*, f32, s32);
RwFrame* fn_8019EB94(RwFrame*, const RwV3d*, s32);
void SaveRenderState__7nRenderFv();
void SetRenderStateForBlendAdd__7nRenderFv();
void SetLightNum__7nRenderFUi(s32);
void LoadRenderState__7nRenderFv();
s32 fn_8011B844(RpUVAnimAnimation*, f32);
RpAtomic* SetAtomicCustomFXData__FP8RpAtomicPv(RpAtomic*, void*);
RpClump* fn_8014FFBC(RpClump*, RpAtomic* (*)(RpAtomic*, void*), void*);
RpClump* fn_8014FF2C(RpClump*);
void SetClumpCustomFXTexture__FP7RpClumpP8UVFXInfo(RpClump*, UVFXInfo*);
void objRpClumpForAllMaterialsToChangeMaterialColor__FP7RpClumpP10RwRGBAReal(RpClump*, RwRGBAReal*);
void objRpClumpForAllGeometrysToModulateMaterialColor__FP7RpClump(RpClump*);
RpClump* fn_80150588(RpClump*);
s32 fn_80150958(RpClump*);
}
namespace nRenderWare
{
RwFrame* SearchFrameFromFrameID(RwFrame*, s32);
}
static RpClump* pClumpStatic;
static RpUVAnimAnimation* pUVAnimStatic;
static UVFXInfo uvfxinfo;
static s32 TemporaryTmr;
char* CL_TEnemyShockWave = "TEnemyShockWave";

sShockWave::sShockWave()
{
	pos.x = pos.y = pos.z = 0.0f;
}

void TEnemyShockWave::Create(const sShockWave* param)
{
	new TEnemyShockWave(lbl_8042C10C, param);
}

void TEnemyShockWave::Initialize()
{
	pClumpStatic  = TEnemyDataBase::GetInstance()->SearchClump(ENEMY_DB_COMMON, 2);
	pUVAnimStatic = TEnemyDataBase::GetInstance()->SearchUVAnim(ENEMY_DB_COMMON, 3);
	if (pClumpStatic && pUVAnimStatic) {
		uvfxinfo.uvAnim = pUVAnimStatic;
		SetClumpCustomFXTexture__FP7RpClumpP8UVFXInfo(pClumpStatic, &uvfxinfo);
	}
	TemporaryTmr = 0;
	if (pClumpStatic)
		objRpClumpForAllGeometrysToModulateMaterialColor__FP7RpClump(pClumpStatic);
}

void TEnemyShockWave::Finalize()
{
	TemporaryTmr  = 0;
	pClumpStatic  = 0;
	pUVAnimStatic = 0;
}

TEnemyShockWave::TEnemyShockWave(TObject* parent, const sShockWave* param)
    : TObject(parent)
{
	ClassName = CL_TEnemyShockWave;
	DispTime  = sizeof(TEnemyShockWave);
	mParam    = *param;
	ResetVariable();
	CloneClump();
	InitShockWaveModelParam();
}

TEnemyShockWave::~TEnemyShockWave()
{
	DestroyClump();
}

void TEnemyShockWave::ResetVariable()
{
	mpClump    = 0;
	mTimer     = 0;
	mpFrame[0] = 0;
	mpFrame[1] = 0;
	mpFrame[2] = 0;
	mpFrame[3] = 0;
}

void TEnemyShockWave::CloneClump()
{
	mpClump = fn_80150588(pClumpStatic);
	if (mpClump) {
		RwFrame* pFrame = (RwFrame*)mpClump->object.parent;
		mpFrame[0]      = nRenderWare::SearchFrameFromFrameID(pFrame, 3000);
		mpFrame[1]      = nRenderWare::SearchFrameFromFrameID(pFrame, 3001);
		mpFrame[2]      = nRenderWare::SearchFrameFromFrameID(pFrame, 3002);
		mpFrame[3]      = nRenderWare::SearchFrameFromFrameID(pFrame, 3003);
	}
}

void TEnemyShockWave::DestroyClump()
{
	if (mpClump) {
		fn_80150958(mpClump);
		mpClump = 0;
	}
	mpFrame[0] = 0;
	mpFrame[1] = 0;
	mpFrame[2] = 0;
	mpFrame[3] = 0;
}

void TEnemyShockWave::Exec()
{
	IncreaseTimer__7nSystemFRi(&mTimer);
	if (mTimer > 20) {
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
	if (!canAdvance)
		return;
	UpdateShockWaveModelParam();
	for (s32 i = 0; i < 4; i++) {
		if (mpFrame[i]) {
			fn_8019EC30(mpFrame[i], &ShockWaveModelParam[i].scale, 0);
			fn_8019ED68(mpFrame[i], &AxisY, ShockWaveModelParam[i].rotate, 2);
		}
	}
}

void TEnemyShockWave::TDisp()
{
	if (!mpClump)
		return;
	RwSphere sphere;
	sphere.center.x = mParam.pos.x;
	sphere.center.y = mParam.pos.y;
	sphere.center.z = mParam.pos.z;
	sphere.radius   = 50.0f;
	if (fn_8019CE34(*lbl_8042C9A4, &sphere) == 0)
		return;
	fn_8019EB94((RwFrame*)mpClump->object.parent, &mParam.pos, 0);
	SaveRenderState__7nRenderFv();
	SetRenderStateForBlendAdd__7nRenderFv();
	SetLightNum__7nRenderFUi(16);
	s32 tmr = lbl_8042C180->modeswitchlws[2];
	if (TemporaryTmr != tmr) {
		TemporaryTmr = tmr;
		fn_8011B844(pUVAnimStatic, 1.2f);
		fn_8014FFBC(pClumpStatic, SetAtomicCustomFXData__FP8RpAtomicPv, &uvfxinfo);
	}
	RwRGBAReal color = { 1, 1, 1, 1 };
	color.alpha      = ShockWaveModelParam[0].alpha;
	objRpClumpForAllMaterialsToChangeMaterialColor__FP7RpClumpP10RwRGBAReal(pClumpStatic, &color);
	fn_8014FF2C(mpClump);
	LoadRenderState__7nRenderFv();
}

void TEnemyShockWave::InitShockWaveModelParam()
{
	ShockWaveModelParam[0].scale.x = 1.0f;
	ShockWaveModelParam[0].scale.y = 1.0f;
	ShockWaveModelParam[0].scale.z = 1.0f;
	ShockWaveModelParam[0].alpha   = 1.0f;
	ShockWaveModelParam[0].rotate  = 0.0f;
	ShockWaveModelParam[1].scale.x = 0.5f;
	ShockWaveModelParam[1].scale.y = 0.5f;
	ShockWaveModelParam[1].scale.z = 0.5f;
	ShockWaveModelParam[1].alpha   = 1.0f;
	ShockWaveModelParam[1].rotate  = 0.0f;
	ShockWaveModelParam[2].scale.x = 0.5f;
	ShockWaveModelParam[2].scale.y = 0.5f;
	ShockWaveModelParam[2].scale.z = 0.5f;
	ShockWaveModelParam[2].alpha   = 1.0f;
	ShockWaveModelParam[2].rotate  = 0.0f;
	ShockWaveModelParam[3].scale.x = 1.0f;
	ShockWaveModelParam[3].scale.y = 0.2f;
	ShockWaveModelParam[3].scale.z = 1.0f;
	ShockWaveModelParam[3].alpha   = 1.0f;
	ShockWaveModelParam[3].rotate  = 0.0f;
}

void TEnemyShockWave::UpdateShockWaveModelParam()
{
	const s32& timer = mTimer;
	if (mTimer >= 0 && mTimer < 4) {
		ShockWaveModelParam[0].scale.x
		    = AdjustFloat__Ffff(ShockWaveModelParam[0].scale.x, 1.4f, 0.02f);
		ShockWaveModelParam[0].scale.y
		    = AdjustFloat__Ffff(ShockWaveModelParam[0].scale.y, 1.4f, 0.02f);
		ShockWaveModelParam[0].scale.z
		    = AdjustFloat__Ffff(ShockWaveModelParam[0].scale.z, 1.4f, 0.02f);
		ShockWaveModelParam[1].scale.x
		    = AdjustFloat__Ffff(ShockWaveModelParam[1].scale.x, 1.0f, 0.05f);
		ShockWaveModelParam[1].scale.y
		    = AdjustFloat__Ffff(ShockWaveModelParam[1].scale.y, 1.0f, 0.05f);
		ShockWaveModelParam[1].scale.z
		    = AdjustFloat__Ffff(ShockWaveModelParam[1].scale.z, 1.0f, 0.05f);
		ShockWaveModelParam[2].scale.x
		    = AdjustFloat__Ffff(ShockWaveModelParam[2].scale.x, 1.0f, 0.0625f);
		ShockWaveModelParam[2].scale.y
		    = AdjustFloat__Ffff(ShockWaveModelParam[2].scale.y, 1.0f, 0.0625f);
		ShockWaveModelParam[2].scale.z
		    = AdjustFloat__Ffff(ShockWaveModelParam[2].scale.z, 1.0f, 0.0625f);
		ShockWaveModelParam[2].rotate
		    = AdjustFloat__Ffff(ShockWaveModelParam[2].rotate, 120.0f, 6.0f);
		ShockWaveModelParam[3].scale.y
		    = AdjustFloat__Ffff(ShockWaveModelParam[3].scale.y, 1.2f, 0.25f);
		ShockWaveModelParam[3].rotate
		    = AdjustFloat__Ffff(ShockWaveModelParam[3].rotate, -120.0f, 6.0f);
	} else if (mTimer >= 4 && timer < 8) {
		ShockWaveModelParam[0].scale.x
		    = AdjustFloat__Ffff(ShockWaveModelParam[0].scale.x, 1.4f, 0.02f);
		ShockWaveModelParam[0].scale.y
		    = AdjustFloat__Ffff(ShockWaveModelParam[0].scale.y, 1.4f, 0.02f);
		ShockWaveModelParam[0].scale.z
		    = AdjustFloat__Ffff(ShockWaveModelParam[0].scale.z, 1.4f, 0.02f);
		ShockWaveModelParam[1].scale.x
		    = AdjustFloat__Ffff(ShockWaveModelParam[1].scale.x, 1.0f, 0.05f);
		ShockWaveModelParam[1].scale.y
		    = AdjustFloat__Ffff(ShockWaveModelParam[1].scale.y, 1.0f, 0.05f);
		ShockWaveModelParam[1].scale.z
		    = AdjustFloat__Ffff(ShockWaveModelParam[1].scale.z, 1.0f, 0.05f);
		ShockWaveModelParam[2].scale.x
		    = AdjustFloat__Ffff(ShockWaveModelParam[2].scale.x, 1.0f, 0.0625f);
		ShockWaveModelParam[2].scale.y
		    = AdjustFloat__Ffff(ShockWaveModelParam[2].scale.y, 1.0f, 0.0625f);
		ShockWaveModelParam[2].scale.z
		    = AdjustFloat__Ffff(ShockWaveModelParam[2].scale.z, 1.0f, 0.0625f);
		ShockWaveModelParam[2].rotate
		    = AdjustFloat__Ffff(ShockWaveModelParam[2].rotate, 120.0f, 6.0f);
		ShockWaveModelParam[3].scale.y
		    = AdjustFloat__Ffff(ShockWaveModelParam[3].scale.y, 1.4f, 0.034f);
		ShockWaveModelParam[3].rotate
		    = AdjustFloat__Ffff(ShockWaveModelParam[3].rotate, -120.0f, 6.0f);
	} else if (mTimer >= 8 && timer < 10) {
		ShockWaveModelParam[0].scale.x
		    = AdjustFloat__Ffff(ShockWaveModelParam[0].scale.x, 1.4f, 0.02f);
		ShockWaveModelParam[0].scale.y
		    = AdjustFloat__Ffff(ShockWaveModelParam[0].scale.y, 1.4f, 0.02f);
		ShockWaveModelParam[0].scale.z
		    = AdjustFloat__Ffff(ShockWaveModelParam[0].scale.z, 1.4f, 0.02f);
		ShockWaveModelParam[1].scale.x
		    = AdjustFloat__Ffff(ShockWaveModelParam[1].scale.x, 1.0f, 0.05f);
		ShockWaveModelParam[1].scale.y
		    = AdjustFloat__Ffff(ShockWaveModelParam[1].scale.y, 1.0f, 0.05f);
		ShockWaveModelParam[1].scale.z
		    = AdjustFloat__Ffff(ShockWaveModelParam[1].scale.z, 1.0f, 0.05f);
		ShockWaveModelParam[2].scale.x
		    = AdjustFloat__Ffff(ShockWaveModelParam[2].scale.x, 1.4f, 0.034f);
		ShockWaveModelParam[2].scale.y
		    = AdjustFloat__Ffff(ShockWaveModelParam[2].scale.y, 1.4f, 0.034f);
		ShockWaveModelParam[2].scale.z
		    = AdjustFloat__Ffff(ShockWaveModelParam[2].scale.z, 1.4f, 0.034f);
		ShockWaveModelParam[2].rotate
		    = AdjustFloat__Ffff(ShockWaveModelParam[2].rotate, 120.0f, 6.0f);
		ShockWaveModelParam[3].scale.y
		    = AdjustFloat__Ffff(ShockWaveModelParam[3].scale.y, 1.4f, 0.034f);
		ShockWaveModelParam[3].rotate
		    = AdjustFloat__Ffff(ShockWaveModelParam[3].rotate, -120.0f, 6.0f);
	} else if (mTimer >= 10 && timer < 16) {
		ShockWaveModelParam[0].scale.x
		    = AdjustFloat__Ffff(ShockWaveModelParam[0].scale.x, 1.4f, 0.02f);
		ShockWaveModelParam[0].scale.y
		    = AdjustFloat__Ffff(ShockWaveModelParam[0].scale.y, 1.4f, 0.02f);
		ShockWaveModelParam[0].scale.z
		    = AdjustFloat__Ffff(ShockWaveModelParam[0].scale.z, 1.4f, 0.02f);
		ShockWaveModelParam[1].scale.x
		    = AdjustFloat__Ffff(ShockWaveModelParam[1].scale.x, 1.2f, 0.02f);
		ShockWaveModelParam[1].scale.y
		    = AdjustFloat__Ffff(ShockWaveModelParam[1].scale.y, 1.2f, 0.02f);
		ShockWaveModelParam[1].scale.z
		    = AdjustFloat__Ffff(ShockWaveModelParam[1].scale.z, 1.2f, 0.02f);
		ShockWaveModelParam[1].alpha = AdjustFloat__Ffff(ShockWaveModelParam[1].alpha, 0.0f, 0.1f);
		ShockWaveModelParam[2].scale.x
		    = AdjustFloat__Ffff(ShockWaveModelParam[2].scale.x, 1.4f, 0.034f);
		ShockWaveModelParam[2].scale.y
		    = AdjustFloat__Ffff(ShockWaveModelParam[2].scale.y, 1.4f, 0.034f);
		ShockWaveModelParam[2].scale.z
		    = AdjustFloat__Ffff(ShockWaveModelParam[2].scale.z, 1.4f, 0.034f);
		ShockWaveModelParam[2].rotate
		    = AdjustFloat__Ffff(ShockWaveModelParam[2].rotate, 120.0f, 6.0f);
		ShockWaveModelParam[3].scale.y
		    = AdjustFloat__Ffff(ShockWaveModelParam[3].scale.y, 0.6f, 0.08f);
		ShockWaveModelParam[3].rotate
		    = AdjustFloat__Ffff(ShockWaveModelParam[3].rotate, -120.0f, 6.0f);
	} else if (mTimer >= 16 && timer < 20) {
		ShockWaveModelParam[0].scale.x
		    = AdjustFloat__Ffff(ShockWaveModelParam[0].scale.x, 1.4f, 0.02f);
		ShockWaveModelParam[0].scale.y
		    = AdjustFloat__Ffff(ShockWaveModelParam[0].scale.y, 1.4f, 0.02f);
		ShockWaveModelParam[0].scale.z
		    = AdjustFloat__Ffff(ShockWaveModelParam[0].scale.z, 1.4f, 0.02f);
		ShockWaveModelParam[0].alpha = AdjustFloat__Ffff(ShockWaveModelParam[0].alpha, 0.0f, 0.25f);
		ShockWaveModelParam[1].scale.x
		    = AdjustFloat__Ffff(ShockWaveModelParam[1].scale.x, 1.2f, 0.02f);
		ShockWaveModelParam[1].scale.y
		    = AdjustFloat__Ffff(ShockWaveModelParam[1].scale.y, 1.2f, 0.02f);
		ShockWaveModelParam[1].scale.z
		    = AdjustFloat__Ffff(ShockWaveModelParam[1].scale.z, 1.2f, 0.02f);
		ShockWaveModelParam[1].alpha = AdjustFloat__Ffff(ShockWaveModelParam[1].alpha, 0.0f, 0.1f);
		ShockWaveModelParam[2].scale.x
		    = AdjustFloat__Ffff(ShockWaveModelParam[2].scale.x, 1.4f, 0.034f);
		ShockWaveModelParam[2].scale.y
		    = AdjustFloat__Ffff(ShockWaveModelParam[2].scale.y, 1.4f, 0.034f);
		ShockWaveModelParam[2].scale.z
		    = AdjustFloat__Ffff(ShockWaveModelParam[2].scale.z, 1.4f, 0.034f);
		ShockWaveModelParam[2].rotate
		    = AdjustFloat__Ffff(ShockWaveModelParam[2].rotate, 120.0f, 6.0f);
		ShockWaveModelParam[3].scale.y
		    = AdjustFloat__Ffff(ShockWaveModelParam[3].scale.y, 0.6f, 0.08f);
		ShockWaveModelParam[3].alpha = AdjustFloat__Ffff(ShockWaveModelParam[3].alpha, 0.0f, 0.25f);
		ShockWaveModelParam[3].rotate
		    = AdjustFloat__Ffff(ShockWaveModelParam[3].rotate, -120.0f, 6.0f);
	}
}
