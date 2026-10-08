// Complete effect/eff_ball.cpp, reconstructed from GC and symbolic C++ metadata.
// Ordinary definitions use auto,deferred so the earlier float-angle wrapper can
// inline the later integer-angle overload. Reversed definition emission and
// storage placement reproduce the owned layout; original source order is unknown.
#include "game/effect/eff_ball.h"
struct RwObject {
	u8 type, subType, flags, privateFlags;
	void* parent;
};
struct RpClump {
	RwObject object;
};
struct RpAtomic;
struct RwFrame;
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
struct RpMaterial {
	void* texture;
	RwRGBA color;
};
struct UVFXInfo {
	RpUVAnimAnimation* uvAnim;
	RwMatrix uvMatrix;
};
struct BallModeView {
	s8 flags[0x28];
	s32 modeswitchlws[6];
};
extern "C" {
extern BallModeView* lbl_8042C180;
RwMatrix* fn_8019E8EC(RwFrame*);
RwFrame* fn_8019ECCC(RwFrame*, const RwMatrix*, s32);
RwFrame* fn_8019EC30(RwFrame*, const RwV3d*, s32);
s32 fn_80194294(s32, void*);
s32 fn_80194234(s32, void*);
s32 fn_8014FEF4(RpClump*);
RpClump* fn_8014FF2C(RpClump*);
RpClump* fn_8014FFBC(RpClump*, RpAtomic* (*)(RpAtomic*, void*), void*);
RpAtomic* SetAtomicCustomFXData__FP8RpAtomicPv(RpAtomic*, void*);
s32 fn_8011B844(RpUVAnimAnimation*, f32);
s32 fn_8003E2E4(s32, s32, RwV3d*, sAngle*);
f32 fn_801990E0(RwV3d*, const RwV3d*);
f64 asin(f64);
f64 atan2(f64, f64);
RpClump* fn_80150588(RpClump*);
s32 fn_80150958(RpClump*);
RpAtomic* objRpClumpGetAtomic__FP7RpClumpP8RpAtomic(RpClump*, RpAtomic*);
RpAtomic* fn_801491A8(RpAtomic*);
void objRpClumpForAllGeometrysToIgnoreLights__FP7RpClump(RpClump*);
void objRpClumpForAllGeometrysToModulateMaterialColor__FP7RpClump(RpClump*);
RpMaterial* objRpClumpGetMaterialWithSpecificTexture__FP7RpClumpP10RpMaterialPc(
    RpClump*, RpMaterial*, char*);
RpAtomic* objRpClumpGetAtomicWithTexture__FP7RpClumpP8RpAtomicPc(RpClump*, RpAtomic*, char*);
void AtomicSetCustomFXTexture__FP8RpAtomicPv(RpAtomic*, UVFXInfo*);
void* objPointerReadFromClumpAnim__FPc(char*);
}
RpClump* EffBall::pClump[6]            = { 0 };
static RpMaterial* pMaterial[6]        = { 0 };
RpUVAnimAnimation* EffBall::pUVAnim[6] = { 0 };
static UVFXInfo EffBallUvInfo[6];
static RwRGBA default_color = { 255, 255, 255, 255 };
void InitEffBall()
{
	static char* dff_name[6] = { "EF_CHRBALL.DFF", "EF_CHRBALL2.DFF", "EF_CHRBALL3.DFF",
		"SP_BLALL.DFF", "SP_BALL2.DFF", "SP_CHRBALL.DFF" };
	static char* uvb_name[6] = { "EF_CHRBALL.UVB", "EF_CHRBALL2.UVB", "EF_CHRBALL3.UVB",
		"SP_BALL.UVB", "SP_DOME.UVB", "SP_CHRBALL.UVB" };
	for (s32 i = 0; i < 6; ++i) {
		if (!EffBall::pClump[i]) {
			RpClump* pClump_Temp = (RpClump*)objPointerReadFromClumpAnim__FPc(dff_name[i]);
			if (pClump_Temp)
				EffBall::SetOriginalEffBallClumpPointer(i, pClump_Temp);
			RpUVAnimAnimation* pUVAnim_Temp
			    = (RpUVAnimAnimation*)objPointerReadFromClumpAnim__FPc(uvb_name[i]);
			EffBall::SetOriginalEffBallUVAnimPointer(i, pUVAnim_Temp);
		}
	}
}
static s32 time_previous[6] = { 0 };

void EffBall::SetOriginalEffBallClumpPointer(s32 noClump, RpClump* pClump_Set)
{
	pClump[noClump] = pClump_Set;
	if (pClump_Set) {
		objRpClumpForAllGeometrysToModulateMaterialColor__FP7RpClump(pClump_Set);
		if (!pMaterial[noClump])
			pMaterial[noClump]
			    = objRpClumpGetMaterialWithSpecificTexture__FP7RpClumpP10RpMaterialPc(
			        pClump_Set, 0, "ef_chbl");
		if (!pMaterial[noClump])
			pMaterial[noClump]
			    = objRpClumpGetMaterialWithSpecificTexture__FP7RpClumpP10RpMaterialPc(
			        pClump_Set, 0, "ef_chbl_y");
		objRpClumpForAllGeometrysToIgnoreLights__FP7RpClump(pClump_Set);
		objRpClumpForAllGeometrysToModulateMaterialColor__FP7RpClump(pClump_Set);
	}
}
void EffBall::SetOriginalEffBallUVAnimPointer(s32 noClump, RpUVAnimAnimation* pUVAnim_Set)
{
	pUVAnim[noClump] = pUVAnim_Set;
	if (pUVAnim_Set) {
		RpClump* pClump_Temp = pClump[noClump];
		if (pUVAnim_Set && pMaterial[noClump]) {
			EffBallUvInfo[noClump].uvAnim = pUVAnim_Set;
			RpAtomic* pAtomic_Temp
			    = objRpClumpGetAtomicWithTexture__FP7RpClumpP8RpAtomicPc(pClump_Temp, 0, "ef_chbl");
			if (!pAtomic_Temp)
				pAtomic_Temp = objRpClumpGetAtomicWithTexture__FP7RpClumpP8RpAtomicPc(
				    pClump_Temp, 0, "ef_chbl_y");
			AtomicSetCustomFXTexture__FP8RpAtomicPv(pAtomic_Temp, &EffBallUvInfo[noClump]);
		}
	}
}
void EndEffBall()
{
	RpClump** c           = EffBall::pClump;
	RpUVAnimAnimation** u = EffBall::pUVAnim;
	RpMaterial** m        = pMaterial;
	for (s32 i = 0; i < 6; ++i, ++c, ++u, ++m) {
		*c = 0;
		*u = 0;
		*m = 0;
	}
}
EffBall::EffBall()
{
	rgba.red   = default_color.red;
	rgba.green = default_color.green;
	rgba.blue  = default_color.blue;
	rgba.alpha = default_color.alpha;
	for (s32 i = 0; i < 6; ++i) {
		pClumpInstance[i] = 0;
		if (pClump[i]) {
			RpClump* pClump_Temp = fn_80150588(pClump[i]);
			pClumpInstance[i]    = pClump_Temp;
			if (pClump_Temp) {
				switch (i) {
					case 0:
					case 1:
					case 2:
					case 3:
					case 4:
					case 5:
						fn_801491A8(objRpClumpGetAtomic__FP7RpClumpP8RpAtomic(pClump_Temp, 0));
						objRpClumpForAllGeometrysToIgnoreLights__FP7RpClump(pClump_Temp);
						objRpClumpForAllGeometrysToModulateMaterialColor__FP7RpClump(pClump_Temp);
						break;
				}
			}
		}
	}
}
EffBall::~EffBall()
{
	for (s32 i = 0; i < 6; ++i)
		if (pClumpInstance[i]) {
			fn_80150958(pClumpInstance[i]);
			pClumpInstance[i] = 0;
		}
}
void EffBall::ResetEffBallClump()
{
	for (s32 i = 0; i < 6; ++i) {
		if (!pClumpInstance[i] && pClump[i]) {
			RpClump* pClump_Temp = fn_80150588(pClump[i]);
			pClumpInstance[i]    = pClump_Temp;
			if (pClump_Temp) {
				switch (i) {
					case 0:
					case 1:
					case 2:
					case 5:
						fn_801491A8(objRpClumpGetAtomic__FP7RpClumpP8RpAtomic(pClump_Temp, 0));
						objRpClumpForAllGeometrysToIgnoreLights__FP7RpClump(pClump_Temp);
						break;
				}
			}
		}
	}
}
void EffBall::SetEffBallMaterialColor(const RwRGBA* c)
{
	rgba.red   = c->red;
	rgba.green = c->green;
	rgba.blue  = c->blue;
	rgba.alpha = c->alpha;
	rgba.alpha = 255;
}
s32 SetEffBallAnglesByDifferenceOfPlayersPositions(s32 pno, sAngle* ang)
{
	RwV3d pos0, pos1, v;
	fn_8003E2E4(pno, 0, &pos0, 0);
	fn_8003E2E4(pno, 1, &pos1, 0);
	v.x = pos0.x - pos1.x;
	v.y = pos0.y - pos1.y;
	v.z = pos0.z - pos1.z;
	if (v.z * v.z + (v.x * v.x + v.y * v.y) > 0.01f) {
		fn_801990E0(&v, &v);
		if (v.y >= 1.0f) {
			ang->x = -0x4000;
			ang->y = 0;
		} else if (v.y <= -1.0f) {
			ang->x = 0x4000;
			ang->y = 0;
		} else {
			ang->x = (s32)(10430.380859375f * (f32)asin(-v.y));
			ang->y = (s32)(10430.380859375f * (f32)atan2(v.x, v.z));
		}
		ang->z = 0;
	} else
		return 0;
	return 1;
}
s32 SetEffBallAnglesByDifferenceOfPlayersPositions(s32 pno, sRealAngle3* ang)
{
	sAngle a;
	s32 ret = SetEffBallAnglesByDifferenceOfPlayersPositions(pno, &a);
	if (ret) {
		ang->x = a.x * 0.0054931640625f;
		ang->y = a.y * 0.0054931640625f;
		ang->z = 0;
	}
	return ret;
}
void EffBall::RenderEffBall(s32 noClump)
{
	RpClump* pClump_Current = pClumpInstance[noClump];
	RpClump* pClump_Current2;
	if (pClump_Current) {
		pClump_Current2 = pClumpInstance[3];
		if (pClump_Current2 && noClump == 0) {
			fn_8019ECCC((RwFrame*)pClump_Current2->object.parent,
			    fn_8019E8EC((RwFrame*)pClump_Current->object.parent), 0);
			noClump        = 3;
			pClump_Current = pClump_Current2;
		}
		pClump_Current2 = pClumpInstance[4];
		if (pClump_Current2 && noClump == 1) {
			fn_8019ECCC((RwFrame*)pClump_Current2->object.parent,
			    fn_8019E8EC((RwFrame*)pClump_Current->object.parent), 0);
			noClump        = 4;
			pClump_Current = pClump_Current2;
		}
		if (pClump_Current) {
			if (noClump == 5) {
				RwFrame* pFrame_Temp = (RwFrame*)pClump_Current->object.parent;
				RwV3d scale_Temp     = { 1.1f, 1.1f, 1.1f };
				fn_8019EC30(pFrame_Temp, &scale_Temp, 1);
			}
			s32 src, dst, cullmode, fog, va;
			fn_80194294(10, &src);
			fn_80194294(11, &dst);
			fn_80194294(20, &cullmode);
			fn_80194294(14, &fog);
			fn_80194294(12, &va);
			fn_80194234(10, (void*)5);
			fn_80194234(11, (void*)2);
			fn_80194234(20, (void*)1);
			fn_80194234(14, 0);
			fn_80194234(12, (void*)1);
			// Retail deliberately stops here when this clump query reports a positive result.
			if (fn_8014FEF4(pClump_Current) > 0)
				for (;;) {
				}
			if (pMaterial[noClump]) {
				RpMaterial* pMaterial_Current = pMaterial[noClump];
				switch (noClump) {
					case 0:
					case 1:
					case 2:
						pMaterial_Current->color.red   = rgba.red;
						pMaterial_Current->color.green = rgba.green;
						pMaterial_Current->color.blue  = rgba.blue;
						pMaterial_Current->color.alpha = rgba.alpha;
						break;
				}
				s32 time_current = lbl_8042C180->modeswitchlws[2] + lbl_8042C180->modeswitchlws[3];
				if (time_previous[noClump] != time_current) {
					f32 deltaTime_Temp = time_current - time_previous[noClump];
					if (pMaterial[noClump] && pUVAnim[noClump]) {
						fn_8011B844(pUVAnim[noClump], deltaTime_Temp);
						fn_8014FFBC(pClump_Current, SetAtomicCustomFXData__FP8RpAtomicPv,
						    &EffBallUvInfo[noClump]);
						time_previous[noClump] = time_current;
					}
				}
			}
			fn_8014FF2C(pClump_Current);
			fn_80194234(12, (void*)va);
			fn_80194234(14, (void*)fog);
			fn_80194234(20, (void*)cullmode);
			fn_80194234(10, (void*)src);
			fn_80194234(11, (void*)dst);
		}
	}
}