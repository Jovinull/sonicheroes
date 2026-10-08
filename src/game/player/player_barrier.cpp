// Complete player/player_barrier.cpp; GC behavior and symbolic C++ metadata.
// Partial external views name only corroborated fields; team+206 remains provisional.
// Reversed ordinary definitions with whole-TU deferred inlining recover emission
// order; historical source order/flags are unknown. See docs/player-barrier-unit-evidence.md.
#include "game/player/player_barrier.h"
struct RwObject {
	u8 type, subType, flags, privateFlags;
	void* parent;
};
struct RpClump {
	RwObject object;
};
struct RpAtomic;
struct RpUVAnimAnimation;
struct RwTexture;
struct RpWorld;
struct RpMaterial {
	RwTexture* texture;
	RwRGBA color;
};
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
struct RwFrame {
	RwObject object;
	void* dirtyNext;
	void* dirtyPrev;
	RwMatrix modelling, ltm;
};
struct UVFXInfo {
	RpUVAnimAnimation* uvAnim;
	RwMatrix uvMatrix;
};
struct BarrierPlayerView {
	u8 unknown0[0x1D4];
	RwV3d pos;
	u8 unknown1[0x760 - 0x1E0];
	s8 playerno, characterno;
	u8 unknown2[0x8B0 - 0x762];
	s16 thismotdat;
	u8 unknown3[0x8E0 - 0x8B2];
	RpClump* pClump;
};
struct BarrierTeamView {
	u8 unknown0[0x3B];
	s8 leaderNo_Backup;
	u8 unknown1[0x114 - 0x3C];
	BarrierPlayerView* member_class_ptr[3];
	u8 unknown2[0x206 - 0x120];
	s16 barrierFlags206;
};
struct BarrierLandView {
	u8 unknown[0x72A0];
	RpWorld* world;
};
struct BarrierModeView {
	s8 flags[0x28];
	s32 modeswitchlws[6];
};
extern "C" {
extern BarrierPlayerView* lbl_802AD070[];
extern BarrierTeamView* lbl_80303DC8[];
extern BarrierLandView* lbl_8042C1D0;
extern BarrierModeView* lbl_8042C180;
extern TObject* lbl_8042C2A0;
extern TObject* lbl_8042C110;
extern RwV3d AxisY, AxisZ;
f64 floor(f64);
RpClump* fn_80150588(RpClump*);
s32 fn_80150958(RpClump*);
RpAtomic* objRpClumpGetAtomic__FP7RpClumpP8RpAtomic(RpClump*, RpAtomic*);
RpAtomic* fn_801491A8(RpAtomic*);
void objRpClumpForAllGeometrysToIgnoreLights__FP7RpClump(RpClump*);
void objRpClumpForAllGeometrysToModulateMaterialColor__FP7RpClump(RpClump*);
RpWorld* fn_8015BB08(RpWorld*, RpClump*);
RpWorld* fn_8015BBF8(RpWorld*, RpClump*);
s32 fn_8011B844(RpUVAnimAnimation*, f32);
RpClump* fn_8014FFBC(RpClump*, RpAtomic* (*)(RpAtomic*, void*), void*);
RpAtomic* SetAtomicCustomFXData__FP8RpAtomicPv(RpAtomic*, void*);
void* objPointerReadFromClumpAnim__FPc(char*);
RpMaterial* objRpClumpGetMaterialWithSpecificTexture__FP7RpClumpP10RpMaterialPc(
    RpClump*, RpMaterial*, char*);
RpAtomic* objRpClumpGetAtomicWithTexture__FP7RpClumpP8RpAtomicPc(RpClump*, RpAtomic*, char*);
void AtomicSetCustomFXTexture__FP8RpAtomicPv(RpAtomic*, UVFXInfo*);
RwFrame* fn_8019EB94(RwFrame*, const RwV3d*, s32);
RwFrame* fn_8019EC30(RwFrame*, const RwV3d*, s32);
RwFrame* fn_8019ED68(RwFrame*, const RwV3d*, f32, s32);
}
char* CL_TObjPlayerBarrier = "TObjPlayerBarrier";
static RpClump* pClumpPlayerBarrier;
static RpMaterial* pMaterialPlayerBarrier;
static RpUVAnimAnimation* pUVAnimPlayerBarrier;
static UVFXInfo PlayerBarrierUvInfo;
static s32 time_previous;
void InitPlayerBarrier()
{
	if (!pClumpPlayerBarrier) {
		pClumpPlayerBarrier = (RpClump*)objPointerReadFromClumpAnim__FPc("EF_BARRIER.DFF");
		if (pClumpPlayerBarrier) {
			pMaterialPlayerBarrier
			    = objRpClumpGetMaterialWithSpecificTexture__FP7RpClumpP10RpMaterialPc(
			        pClumpPlayerBarrier, 0, "ef_chbl");
			objRpClumpForAllGeometrysToIgnoreLights__FP7RpClump(pClumpPlayerBarrier);
			objRpClumpForAllGeometrysToModulateMaterialColor__FP7RpClump(pClumpPlayerBarrier);
		}
	}
	if (!pUVAnimPlayerBarrier) {
		pUVAnimPlayerBarrier
		    = (RpUVAnimAnimation*)objPointerReadFromClumpAnim__FPc("EF_BARRIER.UVB");
		if (pUVAnimPlayerBarrier && pMaterialPlayerBarrier) {
			PlayerBarrierUvInfo.uvAnim = pUVAnimPlayerBarrier;
			AtomicSetCustomFXTexture__FP8RpAtomicPv(
			    objRpClumpGetAtomicWithTexture__FP7RpClumpP8RpAtomicPc(
			        pClumpPlayerBarrier, 0, "ef_chbl"),
			    &PlayerBarrierUvInfo);
		}
	}
}
void EndPlayerBarrier()
{
	pClumpPlayerBarrier    = 0;
	pMaterialPlayerBarrier = 0;
	pUVAnimPlayerBarrier   = 0;
}
void SetPlayerBarrier(s32 teamno)
{
	BarrierTeamView* pTeam = lbl_80303DC8[teamno];
	if (pTeam) {
		switch (pTeam->barrierFlags206 & 1) {
			case 0:
				break;
			default:
				return;
		}
		TObject* pTO_Parent = lbl_8042C2A0;
		if (!pTO_Parent)
			pTO_Parent = lbl_8042C110;
		if (new TObjPlayerBarrier(pTO_Parent, teamno)) {
			pTeam->barrierFlags206 &= ~2;
			pTeam->barrierFlags206 |= 1;
		}
	}
}
TObjPlayerBarrier::TObjPlayerBarrier(TObject* pTO_Parent, s32 teamno)
    : TObject(pTO_Parent)
{
	team       = (s8)teamno;
	rgba.alpha = rgba.blue = rgba.green = rgba.red = 255;
	rotate                                         = 0;
	color_change_timer                             = 0;
	for (s32 i = 0; i < 2; ++i) {
		pClumpInstance[i] = fn_80150588(pClumpPlayerBarrier);
		if (pClumpInstance[i]) {
			RpAtomic* pAtomic_Temp
			    = objRpClumpGetAtomic__FP7RpClumpP8RpAtomic(pClumpInstance[i], 0);
			fn_801491A8(pAtomic_Temp);
			objRpClumpForAllGeometrysToIgnoreLights__FP7RpClump(pClumpInstance[i]);
			objRpClumpForAllGeometrysToModulateMaterialColor__FP7RpClump(pClumpInstance[i]);
			fn_8015BB08(lbl_8042C1D0->world, pClumpInstance[i]);
		}
	}
	ClassName = CL_TObjPlayerBarrier;
	DispTime  = sizeof(*this);
}
TObjPlayerBarrier::~TObjPlayerBarrier()
{
	for (s32 i = 0; i < 2; ++i)
		if (pClumpInstance[i]) {
			fn_8015BBF8(lbl_8042C1D0->world, pClumpInstance[i]);
			fn_80150958(pClumpInstance[i]);
			pClumpInstance[i] = 0;
		}
}
void TObjPlayerBarrier::Exec()
{
	static RwRGBA rgba_table[9]     = { { 255, 0, 0, 0 }, { 255, 128, 0, 0 }, { 255, 255, 0, 0 },
		{ 128, 255, 0, 0 }, { 0, 180, 80, 0 }, { 0, 255, 255, 0 }, { 0, 128, 255, 0 },
		{ 0, 0, 255, 0 }, { 255, 0, 255, 0 } };
	static RwV3d pos_table_Temp[12] = { { 0, 5.5f, -1.5f }, { 0, 5.5f, -1.5f }, { 0, 5, -1.5f },
		{ 0, 5.5f, -1.5f }, { 0, 9, -1.5f }, { 0, 5, -1.5f }, { 0, 5.5f, -1.5f }, { 0, 9, -1.5f },
		{ 0, 5, -1.5f }, { 0, 5.5f, -1.5f }, { 0, 4, -4.5f }, { 0, 5, -1.5f } };
	static f32 scl_table_Temp[12]
	    = { 1, 1, 0.9090909361839294f, 1, 1.1818181276321411f, 0.9090909361839294f, 1,
		      1.454545497894287f, 0.9090909361839294f, 1, 1.454545497894287f, 0.8181818127632141f };
	while (rotate > 360)
		rotate -= 360;
	BarrierTeamView* pTeam = lbl_80303DC8[team];
	if (!pTeam) {
		Signal |= 1;
		return;
	}
	s32 playerno = pTeam->member_class_ptr[pTeam->leaderNo_Backup]->playerno;
	color_change_timer += 0.1f;
	if (color_change_timer >= 9.0f)
		color_change_timer = 0.0f;
	s32 pat      = (s32)floor(color_change_timer);
	f32 rate     = color_change_timer - pat;
	f32 _rate    = 1.0f - rate;
	s32 pat_last = pat - 1;
	if (pat_last < 0)
		pat_last = 8;
	RwRGBA* pRGBA1 = &rgba_table[pat_last];
	RwRGBA* pRGBA0 = &rgba_table[pat];
	rgba.red       = (u8)(pRGBA0->red * rate + pRGBA1->red * _rate);
	rgba.green     = (u8)(pRGBA0->green * rate + pRGBA1->green * _rate);
	rgba.blue      = (u8)(pRGBA0->blue * rate + pRGBA1->blue * _rate);
	if (!(pTeam->barrierFlags206 & 1)) {
		s32 alpha_Temp = rgba.alpha;
		alpha_Temp -= 32;
		if (alpha_Temp < 0)
			alpha_Temp = 0;
		rgba.alpha = (u8)alpha_Temp;
	}
	if (!rgba.alpha) {
		Signal |= 1;
		return;
	}
	RwFrame* pFrame_Temp          = (RwFrame*)pClumpInstance[0]->object.parent;
	RwMatrix* pMatrix_Effect      = &pFrame_Temp->modelling;
	BarrierPlayerView* pTO_Player = lbl_802AD070[playerno];
	*pMatrix_Effect               = ((RwFrame*)pTO_Player->pClump->object.parent)->modelling;
	switch (pTO_Player->thismotdat) {
		case 9:
		case 10:
		case 55:
			fn_8019EB94(pFrame_Temp, &pos_table_Temp[pTO_Player->characterno], 1);
			break;
		default:
			pMatrix_Effect->pos = pTO_Player->pos;
			break;
	}
	RwV3d vScale_Temp;
	vScale_Temp.x = vScale_Temp.y = vScale_Temp.z = scl_table_Temp[pTO_Player->characterno];
	fn_8019EC30(pFrame_Temp, &vScale_Temp, 1);
	fn_8019ED68(pFrame_Temp, &AxisY, (f32)rotate, 1);
	RwFrame* pFrame_Temp2   = (RwFrame*)pClumpInstance[1]->object.parent;
	pFrame_Temp2->modelling = *pMatrix_Effect;
	fn_8019ED68(pFrame_Temp, &AxisZ, 90.0f, 1);
	fn_8019ED68(pFrame_Temp2, &AxisZ, -90.0f, 1);
	RwV3d vOffset_Temp;
	switch (pTO_Player->characterno) {
		case 7:
			vOffset_Temp.y = -2.5f;
			break;
		case 4:
			vOffset_Temp.y = -2.5f;
			break;
		case 10:
			vOffset_Temp.y = -2.2f;
			break;
		default:
			return;
	}
	vOffset_Temp.x = vOffset_Temp.z = 0.0f;
	fn_8019EB94(pFrame_Temp, &vOffset_Temp, 1);
	fn_8019EB94(pFrame_Temp2, &vOffset_Temp, 1);
}
void TObjPlayerBarrier::TDisp()
{
	s32 time_current;
	RpClump* pClump_Current = pClumpInstance[0];
	if (pMaterialPlayerBarrier) {
		RwRGBA rgba_Temp;
		rgba_Temp.red                 = rgba.red;
		rgba_Temp.green               = rgba.green;
		rgba_Temp.blue                = rgba.blue;
		rgba_Temp.alpha               = rgba.alpha;
		pMaterialPlayerBarrier->color = rgba_Temp;
		time_current                  = lbl_8042C180->modeswitchlws[2];
		if (time_previous != time_current) {
			f32 deltaTime_Temp = time_current - time_previous;
			if (pMaterialPlayerBarrier && pUVAnimPlayerBarrier) {
				fn_8011B844(pUVAnimPlayerBarrier, deltaTime_Temp);
				fn_8014FFBC(
				    pClump_Current, SetAtomicCustomFXData__FP8RpAtomicPv, &PlayerBarrierUvInfo);
			}
			time_previous = time_current;
		}
	}
}
