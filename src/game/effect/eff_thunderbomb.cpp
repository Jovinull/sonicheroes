// Complete effect/eff_thunderbomb.cpp; GC behavior and symbolic C++ declarations.
// The ordinary pointer factory is reconstructed through its inlined DRB use.
// Reversed ordinary definitions with whole-TU deferred emission preserve the
// observed helper expansion/layout; original flags and order are unknown.
// See docs/eff-thunderbomb-unit-evidence.md for source forms and remaining limits.
#include "game/effect/eff_thunderbomb.h"
struct RwObject {
	u8 type, subType, flags, privateFlags;
	void* parent;
};
struct RpClump {
	RwObject object;
};
struct RwTexture;
struct RwTexDictionary;
struct RpMaterial {
	RwTexture* texture;
	RwRGBA color;
};
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
struct RwLLLink {
	RwLLLink *next, *prev;
};
struct RwFrame {
	RwObject object;
	RwLLLink inDirtyListLink;
	RwMatrix modelling, ltm;
};
struct UVFXInfo {
	RpUVAnimAnimation* uvAnim;
	RwMatrix uvMatrix;
};
struct ThunderPlayerView {
	u8 unknown[0x180];
	RpClump* pClump;
};
struct ThunderModeView {
	s8 modeswitchflags[0x28];
	s32 modeswitchlws[6];
};
struct ThunderStageView {
	u8 unknown[0x18];
	s32 mode;
};
struct EffThunderBombTexture {
	char* pTexName;
	RwTexture* pTexture;
};
extern "C" {
extern TObject *lbl_8042C2A0, *lbl_8042C110;
extern ThunderPlayerView* lbl_802AD0D0[8];
extern ThunderModeView* lbl_8042C180;
extern ThunderStageView lbl_8029C310;
RpClump* fn_80150588(RpClump*);
s32 fn_80150958(RpClump*);
RpClump* fn_8014FF2C(RpClump*);
s32 fn_8014FEF4(RpClump*);
RpAtomic* objRpClumpGetAtomic__FP7RpClumpP8RpAtomic(RpClump*, RpAtomic*);
RpAtomic* fn_801491A8(RpAtomic*);
void objRpClumpForAllGeometrysToIgnoreLights__FP7RpClump(RpClump*);
void objRpClumpForAllGeometrysToModulateMaterialColor__FP7RpClump(RpClump*);
f32 AdjustFloat__Ffff(f32, f32, f32);
RwFrame* fn_8019EC30(RwFrame*, const RwV3d*, s32);
RwFrame* fn_8019EB94(RwFrame*, const RwV3d*, s32);
void* objPointerReadFromClumpAnim__FPc(const char*);
RpMaterial* objRpClumpGetMaterialWithSpecificTexture__FP7RpClumpP10RpMaterialPc(
    RpClump*, RpMaterial*, char*);
RwTexDictionary* objRwTexDictionaryGetPointer__Fv();
RwTexture* fn_801A4BBC(RwTexDictionary*, const char*);
void SetClumpCustomFXTexture__FP7RpClumpP8UVFXInfo(RpClump*, UVFXInfo*);
s32 fn_80194294(s32, void*);
s32 fn_80194234(s32, void*);
s32 fn_8011B844(RpUVAnimAnimation*, f32);
RpAtomic* SetAtomicCustomFXData__FP8RpAtomicPv(RpAtomic*, void*);
RpClump* fn_8014FFBC(RpClump*, RpAtomic* (*)(RpAtomic*, void*), void*);
RpMaterial* fn_8015498C(RpMaterial*, RwTexture*);
}
static RpClump* pClump;
static RpMaterial* pMaterial;
static RpUVAnimAnimation* pUVAnim;
static UVFXInfo EffThunderBombUvInfo;
static RwRGBA default_color                             = { 255, 255, 255, 255 };
static EffThunderBombTexture textable_EffThunderBomb[9] = { { "ef_tnd00", 0 }, { "ef_tnd01", 0 },
	{ "ef_tnd02", 0 }, { "ef_tnd03", 0 }, { "ef_tnd04", 0 }, { "ef_tnd05", 0 }, { "ef_tnd06", 0 },
	{ "ef_tnd07", 0 }, { "ef_tnd08", 0 } };
static s32 time_previous, tno_previous;
char* CL_TObjEffThunderSphere = "TObjEffThunderSphere";
static CCL_INFO ci_ETB[1]
    = { { 15, 0, 240, 226, 0x00600000, { 0.0f, 0.0f, 0.0f }, 20.0f, 0.0f, 0.0f, 0, 0, 0, 0 } };

void InitEffThunderBomb()
{
	RwTexDictionary* pDictionary;
	s32 i;
	char* pStr;
	EffThunderBombTexture* p;
	pDictionary = objRwTexDictionaryGetPointer__Fv();
	for (i = 0; i < sizeof(textable_EffThunderBomb) / sizeof(textable_EffThunderBomb[0]); ++i) {
		pStr = textable_EffThunderBomb[i].pTexName;
		if (pStr)
			textable_EffThunderBomb[i].pTexture = fn_801A4BBC(pDictionary, pStr);
	}
	if (!pClump) {
		pClump = (RpClump*)objPointerReadFromClumpAnim__FPc("EF_THD_DAMAGE.DFF");
		if (pClump) {
			p         = textable_EffThunderBomb;
			pMaterial = 0;
			while (!pMaterial) {
				pMaterial = objRpClumpGetMaterialWithSpecificTexture__FP7RpClumpP10RpMaterialPc(
				    pClump, 0, p->pTexName);
				++p; // Retail search has no table-end guard.
			}
			objRpClumpForAllGeometrysToIgnoreLights__FP7RpClump(pClump);
			objRpClumpForAllGeometrysToModulateMaterialColor__FP7RpClump(pClump);
		}
		pUVAnim = (RpUVAnimAnimation*)objPointerReadFromClumpAnim__FPc("EF_THD_DAMAGE.UVB");
		if (pUVAnim && pMaterial) {
			EffThunderBombUvInfo.uvAnim = pUVAnim;
			SetClumpCustomFXTexture__FP7RpClumpP8UVFXInfo(pClump, &EffThunderBombUvInfo);
		}
	}
}
void EndEffThunderBomb()
{
	pClump    = 0;
	pMaterial = 0;
	pUVAnim   = 0;
	for (s32 i = 0; i < sizeof(textable_EffThunderBomb) / sizeof(textable_EffThunderBomb[0]); ++i)
		textable_EffThunderBomb[i].pTexture = 0;
}
EffThunderBomb::EffThunderBomb()
{
	SetEffThunderBombMaterialColor(&default_color);
	pClumpInstance = fn_80150588(pClump);
	if (pClumpInstance) {
		fn_801491A8(objRpClumpGetAtomic__FP7RpClumpP8RpAtomic((RpClump*)pClumpInstance, 0));
		objRpClumpForAllGeometrysToIgnoreLights__FP7RpClump((RpClump*)pClumpInstance);
		objRpClumpForAllGeometrysToModulateMaterialColor__FP7RpClump((RpClump*)pClumpInstance);
	}
}
EffThunderBomb::~EffThunderBomb()
{
	if (pClumpInstance) {
		fn_80150958((RpClump*)pClumpInstance);
		pClumpInstance = 0;
	}
}
void EffThunderBomb::SetEffThunderBombMaterialColor(const RwRGBA* pVal)
{
	rgba = *pVal;
}
void EffThunderBomb::RenderEffThunderBomb()
{
	s32 src, dst, cullmode;
	u32 ztest;
	s32 fog;
	RpClump* pClump_Current;
	s32 time_current;
	f32 deltaTime_Temp;
	s32 tno;
	fn_80194294(10, &src);
	fn_80194294(11, &dst);
	fn_80194294(20, &cullmode);
	fn_80194294(14, &fog);
	fn_80194234(10, (void*)5);
	fn_80194234(11, (void*)2);
	fn_80194234(20, (void*)1);
	fn_80194234(14, 0);
	fn_80194294(6, &ztest);
	pClump_Current = (RpClump*)pClumpInstance;
	if (fn_8014FEF4(pClump_Current) > 0) {
		for (;;) {
		} // Explicit retail self-branch at8010BF80.
	}
	if (pMaterial) {
		pMaterial->color = rgba;
		time_current     = lbl_8042C180->modeswitchlws[2];
		if (time_previous != time_current) {
			deltaTime_Temp = (f32)(time_current - time_previous);
			if (pMaterial && pUVAnim) {
				fn_8011B844(pUVAnim, deltaTime_Temp);
				fn_8014FFBC(
				    pClump_Current, SetAtomicCustomFXData__FP8RpAtomicPv, &EffThunderBombUvInfo);
			}
			tno = tno_previous + 1;
			if ((u32)tno >= sizeof(textable_EffThunderBomb) / sizeof(textable_EffThunderBomb[0]))
				tno = 0;
			else if (tno < 0)
				tno = 0;
			fn_8015498C(pMaterial, textable_EffThunderBomb[tno].pTexture);
			tno_previous  = tno;
			time_previous = time_current;
		}
	}
	fn_8014FF2C(pClump_Current);
	fn_80194234(14, (void*)fog);
	fn_80194234(20, (void*)cullmode);
	fn_80194234(10, (void*)src);
	fn_80194234(11, (void*)dst);
	fn_80194234(6, (void*)ztest);
}
TObjEffThunderSphere::TObjEffThunderSphere(TObject* pTO, s32 pno)
    : TObject(pTO)
    , EffThunderBomb()
{
	ClassName = CL_TObjEffThunderSphere;
	DispTime  = sizeof(TObjEffThunderSphere);
	playerno  = (s8)pno;
	alpha     = 255;
	scl       = 1.0f;
	timer     = 0;
	SetEffThunderBombMaterialColor(&default_color);
}
TObjEffThunderSphere::~TObjEffThunderSphere() { }
void TObjEffThunderSphere::UpdateFrame()
{
	RwFrame* pFrame_Temp = (RwFrame*)((RpClump*)pClumpInstance)->object.parent;
	if (playerno >= 0)
		pos = ((RwFrame*)lbl_802AD0D0[playerno]->pClump->object.parent)->modelling.pos;
	RwV3d vScale_Temp;
	vScale_Temp.x = vScale_Temp.y = vScale_Temp.z = scl;
	fn_8019EC30(pFrame_Temp, &vScale_Temp, 0);
	fn_8019EB94(pFrame_Temp, &pos, 2);
}
void TObjEffThunderSphere::Exec()
{
	if (timer > 10) {
		s32 alpha_Temp = alpha;
		alpha_Temp -= 48;
		if (alpha_Temp < 0)
			alpha_Temp = 0;
		alpha            = (u8)alpha_Temp;
		RwRGBA rgba_Temp = rgba;
		rgba_Temp.alpha  = alpha;
		SetEffThunderBombMaterialColor(&rgba_Temp);
	} else
		++timer;
	if (!alpha) {
		Signal |= 1;
		return;
	}
	UpdateFrame();
}
void TObjEffThunderSphere::TDisp()
{
	RenderEffThunderBomb();
}
TObjEffThunderBomb::TObjEffThunderBomb(TObject* pTO, s32 pno)
    : TObjEffThunderSphere(pTO, pno)
    , C_COLLI()
{
	ClassName = CL_TObjEffThunderSphere;
	DispTime  = sizeof(TObjEffThunderBomb);
	scl       = 0.2f;
	timer     = 0;
	SetEffThunderBombMaterialColor(&default_color);
	Init(ci_ETB, 1, 1);
	strength = 0;
}
TObjEffThunderBomb::~TObjEffThunderBomb() { }
void TObjEffThunderBomb::SetCharcterCollisionID(s32 team)
{
	CHARACTER_ID team_ID;
	switch (team) {
		case 0:
			team_ID = TEAM_0;
			break;
		case 1:
			team_ID = TEAM_1;
			break;
		case 2:
			team_ID = TEAM_2;
			break;
		case 3:
			team_ID = TEAM_3;
			break;
		default:
			return;
	}
	character_id = team_ID;
}
void TObjEffThunderBomb::Exec()
{
	scl = AdjustFloat__Ffff(scl, 1.0f, 0.1f);
	if (timer > 10) {
		s32 alpha_Temp = alpha;
		alpha_Temp -= 16;
		if (alpha_Temp < 0)
			alpha_Temp = 0;
		alpha            = (u8)alpha_Temp;
		RwRGBA rgba_Temp = rgba;
		rgba_Temp.alpha  = alpha;
		SetEffThunderBombMaterialColor(&rgba_Temp);
	} else
		++timer;
	if (!alpha) {
		Signal |= 1;
		return;
	}
	UpdateFrame();
	if (alpha > 127) {
		info->a = 20.0f * scl;
		SetRange(info->a);
		if (lbl_8029C310.mode == 0) {
			pre_pos                 = C_COLLI::pos;
			C_COLLI::pos            = TObjEffThunderSphere::pos;
			static sAngle ang3_Temp = { 0, 0, 0 };
			C_COLLI::ang            = ang3_Temp;
			Entry();
		} else
			ClearInfo();
	}
}
void TObjEffThunderBomb::TDisp()
{
	RenderEffThunderBomb();
}
TObjEffThunderBomb* SetEffectThunderBomb(s32 pno)
{
	TObject* pTO_Parent = lbl_8042C2A0;
	if (!pTO_Parent)
		pTO_Parent = lbl_8042C110;
	return new TObjEffThunderBomb(pTO_Parent, pno);
}
void SetEffectThunderBombForDRB(s32 team, RwV3d* pPos)
{
	TObjEffThunderBomb* pTO        = SetEffectThunderBomb(-1);
	pTO->TObjEffThunderSphere::pos = *pPos;
	pTO->SetCharcterCollisionID(team);
}