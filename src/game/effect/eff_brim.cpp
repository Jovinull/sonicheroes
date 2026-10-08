// Complete effect/eff_brim.cpp: GC behavior/layout and symbolic C++ metadata.
// Source recipe and bounded lifetime/emission trials: docs/eff-brim-unit-evidence.md.
// Original source order and inline qualifiers are unknown; retail expands FlyJump2 construction.
#include "game/effect/eff_brim.h"
struct RwObject {
	u8 type, subType, flags, privateFlags;
	void* parent;
};
struct RwFrame {
	RwObject object;
	void* dirtyNext;
	void* dirtyPrev;
	RwMatrix modelling, ltm;
};
struct RpClump {
	RwObject object;
};
struct RpMaterial {
	void* texture;
	RwRGBA color;
};
struct RpAtomic {
	RwObject object;
	u8 unaccessed08[0x40];
	RpAtomic* (*renderCallBack)(RpAtomic*);
};
struct RpUVAnimAnimation;
struct RpWorld;
struct CLIGHT;
struct BrimParticleView {
	u8 task[0x28];
	u8 particle[1];
};
struct UVFXInfo {
	RpUVAnimAnimation* uvAnim;
	RwMatrix uvMatrix;
};
struct BrimModeView {
	s8 modeswitchflags[0x28];
	s32 modeswitchlws[6];
};
struct BrimTaskWorkView {
	u8 unaccessed00[8];
	RwV3d pos;
};
struct BrimTeamView;
struct BrimPlayerTaskView {
	u8 unaccessed00[0x2c];
	s16 strength;
	u8 unaccessed2E[0xa];
	BrimTaskWorkView* pWork;
	u8 unaccessed3C[0x58];
	sAngle ang;
	u8 unaccessedA0[0x65c];
	sAngle angle6FC;
	RwV3d position708;
	u8 unaccessed714[0x194];
	f32 height8A8;
	u8 unaccessed8AC[0x34];
	RpClump* pClump;
	u8 unaccessed8E4[0xd4];
	BrimTeamView* team;
	s8 teamIndex;
};
struct BrimPlayerWorkView {
	s8 playerno, characterno;
	u8 unaccessed02[0x25a];
	s8 teamNo, memberNo;
};
struct BrimTeamView {
	u8 unaccessed00[0x121];
	s8 count121;
	u8 unaccessed122[0x12];
	BrimPlayerTaskView* members[3];
	s32 formation;
	u8 unaccessed144[0xc4];
	s8 level[3];
};
struct BrimLandView {
	u8 unaccessed00[0x72a0];
	RpWorld* world;
};
extern "C" {
extern CLIGHT lbl_802D5E80;
void fn_800523F4(CLIGHT*, RpWorld*);
void fn_80052184(CLIGHT*, RpWorld*);
s32 fn_80041C00(BrimPlayerTaskView*);
s32 fn_800419BC(s32);
extern BrimModeView* lbl_8042C180;
extern BrimLandView* lbl_8042C1D0;
extern BrimPlayerTaskView* lbl_802AD070[6];
extern void* lbl_802AD090[6];
extern BrimPlayerWorkView* lbl_802AD0D0[6];
extern BrimTeamView* lbl_80303DC8[4];
extern RwV3d lbl_80239978, lbl_80239984, lbl_80239990;
extern TObject* lbl_8042C110;
extern TObject* lbl_8042C2A0;
f32 fn_800D7328(f32, f32, f32);
f32 fn_800D7B00(s32);
f32 fn_800D7AE4(s32);
f64 asin(f64);
f64 atan2(f64, f64);
s32 rand();
BrimParticleView* fn_8006298C(u32, RwV3d*, sAngle*);
void fn_80064380(void*);
RwIm3DVertex* fn_801B2934(RwIm3DVertex*, s32, RwMatrix*, u32);
s32 fn_801B2C00(s32);
s32 fn_801B2A14();
s32 fn_8003E2E4(s32, s32, RwV3d*, sAngle*);
void fn_8003E9B4(void*, RwV3d*);
void fn_800EC828(BrimPlayerTaskView*, const RwV3d*, sAngle*);
f32 fn_801990E0(RwV3d*, const RwV3d*);
RwMatrix* fn_80195790(RwMatrix*, const RwV3d*, f32, f32, s32);
RwFrame* fn_8019EB94(RwFrame*, const RwV3d*, s32);
RwFrame* fn_8019EC30(RwFrame*, const RwV3d*, s32);
RwFrame* fn_8019E880(RwFrame*);
RwMatrix* fn_8019E8EC(RwFrame*);
RwMatrix* fn_80195E44(RwMatrix*, const RwV3d*, s32);
RwMatrix* fn_80196050(RwMatrix*, const RwV3d*, s32);
RwV3d* fn_8019941C(RwV3d*, const RwV3d*, s32, const RwMatrix*);
RpClump* fn_80150588(RpClump*);
s32 fn_80150958(RpClump*);
RpClump* fn_8014FF2C(RpClump*);
RpClump* fn_8014FFBC(RpClump*, RpAtomic* (*)(RpAtomic*, void*), void*);
RpAtomic* fn_8005BF88(RpAtomic*, void*);
RpAtomic* fn_8014F1B0(RpAtomic*);
s32 fn_8011B844(RpUVAnimAnimation*, f32);
void fn_8005DA34(RpClump*);
void fn_8005D9F4(RpClump*);
RpAtomic* fn_8005E1DC(RpClump*, RpAtomic*, char*);
RpMaterial* fn_8005E410(RpClump*, RpMaterial*, char*);
RpAtomic* fn_801491A8(RpAtomic*);
s32 fn_8005F670(RpAtomic*, RpMaterial*);
s32 fn_8005F694(RpAtomic*, RwRGBA*);
s32 fn_8005F64C(RpAtomic*, s32);
RpMaterial* fn_8005F6D4(RpAtomic*);
RwRGBA* fn_8005F6F4(RpAtomic*);
RpWorld* fn_8015BB08(RpWorld*, RpClump*);
RpWorld* fn_8015BBF8(RpWorld*, RpClump*);
void* fn_8005EA04(char*);
void fn_8005BF5C(RpClump*, UVFXInfo*);
s32 fn_80194294(s32, void*);
s32 fn_80194234(s32, void*);
}
static RwRGBA default_color[12]
    = { { 24, 174, 0, 255 }, { 150, 12, 0, 255 }, { 125, 82, 12, 255 }, { 180, 0, 112, 255 },
	      { 127, 127, 32, 255 }, { 127, 0, 127, 255 }, { 0, 80, 200, 255 }, { 64, 0, 127, 255 },
	      { 127, 70, 48, 255 }, { 180, 96, 0, 255 }, { 0, 80, 0, 255 }, { 127, 0, 0, 255 } };
static f32 default_radius[12] = { 20.0f, 30.0f, 30.0f, 20.0f, 30.0f, 30.0f, 20.0f,
	7.800000190734863f, 30.0f, 20.0f, 7.199999809265137f, 30.0f };
static f32 default_y_offset[12]
    = { 10.0f, 10.0f, 10.0f, 10.0f, 15.0f, 10.0f, 10.0f, 20.0f, 10.0f, 10.0f, 18.0f, 10.0f };
static CCL_INFO ci_eff_brim[1]
    = { { 12, 1, 240, 226, 0x2402, { 0.0f, 0.0f, 0.0f }, 30.0f, 5.0f, 0.0f, 0, 0, 0, 0 } };

char* CL_TObjEffBrim = "TObjEffBrim";

static RpClump* pClumpFlyJump;
static RpAtomic* pAtomicFlyJump;
static RpMaterial* pMaterialFlyJump;
static RpUVAnimAnimation* pUVAnimFlyJump;
static RpClump* pClumpFlyJump2;
static RpAtomic* pAtomicFlyJump2;
static RpMaterial* pMaterialFlyJump2;
static RpUVAnimAnimation* pUVAnimFlyJump2;
static UVFXInfo FlyJumpUvInfo, FlyJump2UvInfo;
static s32 time_previousUV, time2_previousUV;
static RpAtomic* callbackSetMaterial(RpAtomic*);

EffBrim_Node* TObjEffBrim::GetCurrentNode()
{
	return &node[GetCurrentNodeNum()];
}
EffBrim_Node* TObjEffBrim::GetPreviousNode()
{
	return &node[GetPreviousNodeNum()];
}
RwRGBA* TObjEffBrim::GetEffBrimMaterialColor()
{
	return &rgba;
}
RwRGBA* TObjEffFlyJump::GetMaterialColor()
{
	return &rgba;
}
RwRGBA* TObjEffFlyJump2::GetMaterialColor()
{
	return &rgba;
}
RwRGBA* TObjEffBrimS::GetMaterialColor()
{
	return &rgba;
}
void InitEffBrim()
{
	if (!pClumpFlyJump) {
		pClumpFlyJump = (RpClump*)fn_8005EA04("EF_FLYJUMP.DFF");
		if (pClumpFlyJump) {
			pAtomicFlyJump   = fn_8005E1DC(pClumpFlyJump, 0, "ef_chbl");
			pMaterialFlyJump = fn_8005E410(pClumpFlyJump, 0, "ef_chbl");
			fn_8005DA34(pClumpFlyJump);
			fn_8005D9F4(pClumpFlyJump);
		}
	}
	pUVAnimFlyJump = (RpUVAnimAnimation*)fn_8005EA04("EF_FLYJUMP.UVB");
	if (pUVAnimFlyJump && pMaterialFlyJump) {
		FlyJumpUvInfo.uvAnim = pUVAnimFlyJump;
		fn_8005BF5C(pClumpFlyJump, &FlyJumpUvInfo);
	}
	if (!pClumpFlyJump2) {
		pClumpFlyJump2 = (RpClump*)fn_8005EA04("EF_FLYJUMP2.DFF");
		if (pClumpFlyJump2) {
			pAtomicFlyJump2   = fn_8005E1DC(pClumpFlyJump2, 0, "ef_chbl");
			pMaterialFlyJump2 = fn_8005E410(pClumpFlyJump2, 0, "ef_chbl");
			fn_8005DA34(pClumpFlyJump2);
			fn_8005D9F4(pClumpFlyJump2);
		}
	}
	pUVAnimFlyJump2 = (RpUVAnimAnimation*)fn_8005EA04("EF_FLYJUMP2.UVB");
	if (pUVAnimFlyJump2 && pMaterialFlyJump2) {
		FlyJump2UvInfo.uvAnim = pUVAnimFlyJump2;
		fn_8005BF5C(pClumpFlyJump2, &FlyJump2UvInfo);
	}
}
void EndEffBrim()
{
	pClumpFlyJump     = 0;
	pAtomicFlyJump    = 0;
	pMaterialFlyJump  = 0;
	pUVAnimFlyJump    = 0;
	pClumpFlyJump2    = 0;
	pAtomicFlyJump2   = 0;
	pMaterialFlyJump2 = 0;
	pUVAnimFlyJump2   = 0;
}
void SetEffectBrim(s32 no_player)
{
	TObject* ptp = lbl_8042C2A0;
	if (!ptp)
		ptp = lbl_8042C110;
	new TObjEffBrim(ptp, no_player);
}
void SetEffectFlyJump(s32 no_player)
{
	TObject* ptp = lbl_8042C2A0;
	if (!ptp)
		ptp = lbl_8042C110;
	new TObjEffFlyJump(ptp, no_player);
}
void SetEffectBrimForSpeed(s32 no_player)
{
	TObject* ptp = lbl_8042C2A0;
	if (!ptp)
		ptp = lbl_8042C110;
	new TObjEffBrimS(ptp, no_player);
}
static RpAtomic* callbackSetMaterial(RpAtomic* pCurrentAtomic)
{
	RpMaterial* pCurrentMaterial  = fn_8005F6D4(pCurrentAtomic);
	RwRGBA* pColor                = fn_8005F6F4(pCurrentAtomic);
	pCurrentMaterial->color.red   = pColor->red;
	pCurrentMaterial->color.green = pColor->green;
	pCurrentMaterial->color.blue  = pColor->blue;
	pCurrentMaterial->color.alpha = pColor->alpha;
	fn_800523F4(&lbl_802D5E80, lbl_8042C1D0->world);
	pAtomicFlyJump2->renderCallBack(pCurrentAtomic);
	fn_80052184(&lbl_802D5E80, lbl_8042C1D0->world);
	return pCurrentAtomic;
}
TObjEffBrim::TObjEffBrim(TObject* pTO, s32 pno)
    : TObject(pTO)
    , C_COLLI()
{
	ClassName = CL_TObjEffBrim;
	DispTime  = sizeof(TObjEffBrim);
	playerno  = (s8)pno;
	s32 cno   = lbl_802AD0D0[pno]->characterno;
	SetEffBrimMaterialColor(&default_color[cno]);
	characterno = (s8)cno;
	rad_Max     = default_radius[cno];
	rad         = 5.0f;
	num_node    = 0;
	rotation    = 0.0f;
	Init(ci_eff_brim, 1, 1);
	character_id = (CHARACTER_ID)fn_800419BC(fn_80041C00(lbl_802AD070[pno]));
	strength     = lbl_802AD070[pno]->strength;
}
TObjEffBrim::~TObjEffBrim() { }
void TObjEffBrim::SetEffBrimMaterialColor(const RwRGBA* pVal)
{
	rgba.red   = pVal->red;
	rgba.green = pVal->green;
	rgba.blue  = pVal->blue;
	rgba.alpha = pVal->alpha;
}
void TObjEffBrim::AddVertexes()
{
	BrimPlayerTaskView* pTO = lbl_802AD070[playerno];
	if (pTO) {
		RwMatrix* pMatrix = fn_8019E8EC((RwFrame*)pTO->pClump->object.parent);
		RwV3d src[2], dst[2];
		const f32& negativeRadius = -rad;
		src[0].x                  = negativeRadius;
		src[0].y                  = pTO->height8A8;
		src[0].z                  = 0.0f;
		src[1].x                  = 0.4f * negativeRadius;
		src[1].y                  = src[0].y;
		src[1].z                  = 0.0f;
		s32 i = 0, angle = 0, angleMax = (s32)(182.04444885253906f * rotation);
		while (angle <= angleMax) {
			s32 added = 0;
			if (i >= num_node) {
				num_node += 2;
				added = 1;
			}
			fn_8019941C(dst, src, 2, pMatrix);
			node[i].pos.x           = dst[0].x;
			node[i].pos.y           = dst[0].y;
			node[i].pos.z           = dst[0].z;
			node[i].color.red       = rgba.red;
			node[i].color.green     = rgba.green;
			node[i].color.blue      = rgba.blue;
			node[i].color.alpha     = rgba.alpha;
			node[i + 1].pos.x       = dst[1].x;
			node[i + 1].pos.y       = dst[1].y;
			node[i + 1].pos.z       = dst[1].z;
			node[i + 1].color.red   = rgba.red;
			node[i + 1].color.green = rgba.green;
			node[i + 1].color.blue  = rgba.blue;
			node[i + 1].color.alpha = rgba.alpha;
			node[i + 1].color.alpha = (u8)(rgba.alpha >> 1);
			if (added == 1 && num_node > 4 && characterno == 4) {
				sAngle zero             = { 0, 0, 0 };
				BrimParticleView* pPtcl = 0;
				if (3.0517578125e-5f * rand() > 0.75f)
					pPtcl = fn_8006298C(8, &dst[0], &zero);
				if (pPtcl) {
					s32 mask = ~(1 << pTO->teamIndex);
					if (!(mask & lbl_8042C180->modeswitchflags[0x1f])
					    && !(mask & lbl_8042C180->modeswitchflags[0x20]))
						fn_80064380(pPtcl->particle);
				}
			}
			if (added == 1 && num_node > 4 && characterno == 1) {
				sAngle zero             = { 0, 0, 0 };
				BrimParticleView* pPtcl = 0;
				if (3.0517578125e-5f * rand() > 0.75f)
					pPtcl = fn_8006298C(36, &dst[0], &zero);
				if (pPtcl) {
					s32 mask = ~(1 << pTO->teamIndex);
					if (!(mask & lbl_8042C180->modeswitchflags[0x1f])
					    && !(mask & lbl_8042C180->modeswitchflags[0x20]))
						fn_80064380(pPtcl->particle);
				}
			}
			angle += 0x555;
			fn_80195790(pMatrix, &lbl_80239984, 1.0f - fn_800D7AE4(-0x555), fn_800D7B00(-0x555), 1);
			i += 2;
		}
	}
}
void TObjEffBrim::UpdateVertexes()
{
	RwIm3DVertex* pVtx = vtx;
	for (s32 i = 0; i < num_node; ++pVtx, ++i) {
		f32 x = node[i].pos.x, y = node[i].pos.y, z = node[i].pos.z;
		pVtx->objVertex.x = x;
		pVtx->objVertex.y = y;
		pVtx->objVertex.z = z;
		RwRGBA color;
		color.red         = node[i].color.red;
		color.green       = node[i].color.green;
		color.blue        = node[i].color.blue;
		color.alpha       = node[i].color.alpha;
		pVtx->color.red   = color.red;
		pVtx->color.green = color.green;
		pVtx->color.blue  = color.blue;
		pVtx->color.alpha = color.alpha;
	}
}
void TObjEffBrim::RenderEffBrim()
{
	if (num_node > 2) {
		s32 src, dst, cullmode, va, fog;
		fn_80194294(10, &src);
		fn_80194294(11, &dst);
		fn_80194294(20, &cullmode);
		fn_80194294(12, &va);
		fn_80194294(14, &fog);
		fn_80194234(10, (void*)5);
		fn_80194234(11, (void*)2);
		fn_80194234(20, (void*)1);
		fn_80194234(1, 0);
		fn_80194234(12, (void*)1);
		fn_80194234(14, 0);
		UpdateVertexes();
		if (fn_801B2934(vtx, num_node, 0, 0x18))
			fn_801B2C00(4);
		fn_801B2A14();
		fn_80194234(14, (void*)fog);
		fn_80194234(12, (void*)va);
		fn_80194234(20, (void*)cullmode);
		fn_80194234(10, (void*)src);
		fn_80194234(11, (void*)dst);
	}
}
s32 TObjEffBrim::GetCurrentNodeNum()
{
	return num_node - 1;
}
s32 TObjEffBrim::GetPreviousNodeNum()
{
	return num_node - 2;
}
void TObjEffBrim::Exec()
{
	BrimPlayerTaskView* pTO = lbl_802AD070[playerno];
	s32 mask                = ~(1 << pTO->teamIndex);
	if ((mask & lbl_8042C180->modeswitchflags[0x1f])
	    || (mask & lbl_8042C180->modeswitchflags[0x20]))
		return;
	if (num_node < 120) {
		rotation += 22.5f;
		if (rotation > 270.0f)
			rad = fn_800D7328(rad, rad_Max, characterno == 1 ? 1.0f : 2.5f);
		AddVertexes();
	} else {
		if (rgba.alpha >= 255) {
			rgba.alpha = 254;
			if (characterno == 4) {
				RwV3d pos_Temp          = pTO->pWork->pos;
				sAngle ang_Temp         = pTO->angle6FC;
				BrimParticleView* pPtcl = fn_8006298C(20, &pos_Temp, &ang_Temp);
				if (pPtcl) {
					s32 m = ~(1 << pTO->teamIndex);
					if (!(m & lbl_8042C180->modeswitchflags[0x1f])
					    && !(m & lbl_8042C180->modeswitchflags[0x20]))
						fn_80064380(pPtcl->particle);
				}
			}
			if (characterno == 1) {
				RwV3d pos_Temp          = pTO->pWork->pos;
				sAngle ang_Temp         = pTO->angle6FC;
				BrimParticleView* pPtcl = fn_8006298C(3, &pos_Temp, &ang_Temp);
				if (pPtcl) {
					s32 m = ~(1 << pTO->teamIndex);
					if (!(m & lbl_8042C180->modeswitchflags[0x1f])
					    && !(m & lbl_8042C180->modeswitchflags[0x20]))
						fn_80064380(pPtcl->particle);
				}
			}
		}
		if (characterno == 1) {
			rad = fn_800D7328(rad, rad_Max, 4.0f);
			AddVertexes();
		}
	}
	if (rgba.alpha <= 254) {
		s32 alpha_Temp = rgba.alpha;
		alpha_Temp -= 8;
		if (alpha_Temp < 0)
			alpha_Temp = 0;
		RwRGBA rgba_Temp = *GetEffBrimMaterialColor();
		rgba_Temp.alpha  = (u8)alpha_Temp;
		SetEffBrimMaterialColor(&rgba_Temp);
	}
	if (rgba.alpha == 0) {
		Signal |= 1;
		return;
	}
	s32 i;
	EffBrim_Node* pNode                 = &node[2];
	s32 rnd                             = ((s32)(7.99f * (3.0517578125e-5f * rand()))) & 7;
	static RwRGBA color_random_table[8] = { { 255, 64, 128, 255 }, { 196, 128, 32, 255 },
		{ 224, 224, 196, 255 }, { 128, 196, 160, 255 }, { 255, 128, 128, 255 },
		{ 196, 224, 32, 255 }, { 224, 64, 196, 255 }, { 128, 128, 160, 255 } };
	for (i = 2; i < num_node - 2; pNode += 2, i += 2) {
		pNode[0].color.red   = rgba.red;
		pNode[0].color.green = rgba.green;
		pNode[0].color.blue  = rgba.blue;
		pNode[0].color.alpha = rgba.alpha;
		if (rgba.alpha >= 254) {
			pNode[0].color.red += 64.0f * (3.0517578125e-5f * rand());
			pNode[0].color.green += 128.0f * (3.0517578125e-5f * rand());
			pNode[0].color.blue += 128.0f * (3.0517578125e-5f * rand());
		} else if (characterno == 1) {
			pNode[0].color.red   = color_random_table[rnd].red;
			pNode[0].color.green = color_random_table[rnd].green;
			pNode[0].color.blue  = color_random_table[rnd].blue;
			rnd                  = (rnd + 1) & 7;
		}
		pNode[1].color.red   = rgba.red;
		pNode[1].color.green = rgba.green;
		pNode[1].color.blue  = rgba.blue;
		pNode[1].color.alpha = rgba.alpha;
		if (i & 2)
			pNode[1].color.alpha >>= 1;
		else
			pNode[1].color.alpha = 0;
	}
	node[0].color.alpha  = 0;
	node[1].color.alpha  = 0;
	pNode                = GetPreviousNode();
	pNode[0].color.alpha = 0;
	pNode[1].color.alpha = 0;
	if (info) {
		BrimPlayerTaskView* player = lbl_802AD070[playerno];
		const RwV3d& playerPos     = player->pWork->pos;
		pos.x                      = playerPos.x;
		pos.y                      = playerPos.y;
		pos.z                      = playerPos.z;
		const sAngle& playerAngle  = lbl_802AD070[playerno]->ang;
		ang.x                      = playerAngle.x;
		ang.y                      = playerAngle.y;
		ang.z                      = playerAngle.z;
		info->a                    = rad;
		pre_pos.x                  = C_COLLI::pos.x;
		pre_pos.y                  = C_COLLI::pos.y;
		pre_pos.z                  = C_COLLI::pos.z;
		C_COLLI::pos.x             = pos.x;
		C_COLLI::pos.y             = pos.y;
		C_COLLI::pos.z             = pos.z;
		C_COLLI::ang.x             = ang.x;
		C_COLLI::ang.y             = ang.y;
		C_COLLI::ang.z             = ang.z;
		Entry();
	}
}
static CCL_INFO ci_eff_flyjump[1]
    = { { 15, 0, 240, 225, 0x2402, { 0.0f, -15.0f, 0.0f }, 30.0f, 0.0f, 0.0f, 0, 0, 0, 0 } };
char* CL_TObjEffFlyJump  = "TObjEffFlyJump";
char* CL_TObjEffFlyJump2 = "TObjEffFlyJump2";
char* CL_TObjEffBrimS    = "TObjEffBrimS";

void TObjEffBrim::TDisp()
{
	if (characterno == 1)
		RenderEffBrim();
}
void TObjEffBrim::Disp() { }
TObjEffFlyJump::TObjEffFlyJump(TObject* pTO, s32 pno)
    : TObject(pTO)
    , C_COLLI()
{
	ClassName = CL_TObjEffFlyJump;
	DispTime  = sizeof(TObjEffFlyJump);
	playerno  = (s8)pno;
	s32 cno   = lbl_802AD0D0[pno]->characterno;
	SetMaterialColor(&default_color[cno]);
	rad_Max  = default_radius[cno];
	rad      = 0.0f;
	rotation = 0.0f;
	y_offset = default_y_offset[cno];
	scaleH   = 1.0f;
	scaleV   = 1.0f;
	timer    = 0;
	counter  = 0;
	spd.x = spd.y = spd.z = 0.0f;
	Init(ci_eff_flyjump, 1, 1);
	character_id   = (CHARACTER_ID)fn_800419BC(fn_80041C00(lbl_802AD070[pno]));
	strength       = lbl_802AD070[pno]->strength;
	pClumpInstance = fn_80150588(pClumpFlyJump);
	if (pClumpInstance) {
		fn_8005DA34(pClumpInstance);
		fn_8005D9F4(pClumpInstance);
		RpAtomic* pAtomic_Temp = fn_8005E1DC(pClumpInstance, 0, "ef_chbl");
		fn_801491A8(pAtomic_Temp);
	}
}
TObjEffFlyJump::~TObjEffFlyJump()
{
	if (pClumpInstance) {
		fn_80150958(pClumpInstance);
		pClumpInstance = 0;
	}
}
void TObjEffFlyJump::UpdateFrame()
{
	rad                     = 30.0f;
	BrimPlayerTaskView* pTO = lbl_802AD070[playerno];
	const RwV3d& playerPos  = pTO->pWork->pos;
	pos.x                   = playerPos.x;
	pos.y                   = playerPos.y;
	pos.z                   = playerPos.z;
	ang.x                   = pTO->ang.x;
	ang.y                   = pTO->ang.y;
	ang.z                   = pTO->ang.z;
	s32 count;
	BrimTeamView* team = pTO->team;
	count              = team->count121;
	if (count > 1) {
		const s32& memberIndex    = count - 1;
		BrimPlayerTaskView* other = team->members[memberIndex];
		RwV3d v;
		v.x = pTO->position708.x - other->position708.x;
		v.y = pTO->position708.y - other->position708.y;
		v.z = pTO->position708.z - other->position708.z;
		sAngle angle;
		if (v.z * v.z + (v.x * v.x + v.y * v.y) > 0.25f) {
			fn_801990E0(&v, &v);
			fn_800EC828(pTO, &v, &angle);
		} else {
			angle.x = pTO->angle6FC.x;
			angle.y = pTO->angle6FC.y;
			angle.z = pTO->angle6FC.z;
		}
		angle.y = 0x4000 - pTO->angle6FC.y;
		ang.x   = angle.x;
		ang.y   = angle.y;
		ang.z   = angle.z;
		fn_80195790(&matrix, &lbl_80239984,
		    1.0f - fn_800D7AE4(ang.y + (s32)(182.04444885253906f * rotation)),
		    fn_800D7B00(ang.y + (s32)(182.04444885253906f * rotation)), 0);
		fn_80195790(&matrix, &lbl_80239978, 1.0f - fn_800D7AE4(ang.x), fn_800D7B00(ang.x), 2);
		fn_80195790(&matrix, &lbl_80239990, 1.0f - fn_800D7AE4(ang.z), fn_800D7B00(ang.z), 2);
		fn_80196050(&matrix, &pTO->position708, 2);
	} else
		matrix = *fn_8019E8EC((RwFrame*)pTO->pClump->object.parent);
	RwV3d trans;
	trans.x = 0.0f;
	trans.y = y_offset;
	trans.z = 0.0f;
	fn_80196050(&matrix, &trans, 1);
	RwV3d scale;
	scale.x = scaleH;
	scale.y = scaleV;
	scale.z = scaleH;
	fn_80195E44(&matrix, &scale, 1);
	RwFrame* pFrame   = (RwFrame*)pClumpInstance->object.parent;
	pFrame->modelling = matrix;
	fn_8019E880(pFrame);
}
void TObjEffFlyJump::Exec()
{
	if (lbl_802AD070[playerno]->team->formation != 3) {
		Signal |= 1;
		return;
	}
	UpdateFrame();
	if (rgba.alpha > 128 && counter-- <= 0) {
		new TObjEffFlyJump2(this, playerno);
		counter = 9;
	}
	if (timer-- <= 0 && rgba.alpha >= 255)
		rgba.alpha = 254;
	if (rgba.alpha <= 254) {
		s32 alpha_Temp = rgba.alpha;
		alpha_Temp -= 8;
		if (alpha_Temp < 0)
			alpha_Temp = 0;
		RwRGBA rgba_Temp = *GetMaterialColor();
		rgba_Temp.alpha  = (u8)alpha_Temp;
		SetMaterialColor(&rgba_Temp);
	}
	if (rgba.alpha == 0) {
		Signal |= 1;
		return;
	}
	if (info) {
		info->a        = rad;
		info->center.y = -rad;
		CalcRange();
		pre_pos.x      = C_COLLI::pos.x;
		pre_pos.y      = C_COLLI::pos.y;
		pre_pos.z      = C_COLLI::pos.z;
		C_COLLI::pos.x = pos.x;
		C_COLLI::pos.y = pos.y;
		C_COLLI::pos.z = pos.z;
		C_COLLI::ang.x = ang.x;
		C_COLLI::ang.y = ang.y;
		C_COLLI::ang.z = ang.z;
		Entry();
	}
}
void TObjEffFlyJump::SetMaterialColor(const RwRGBA* pVal)
{
	rgba.red   = pVal->red;
	rgba.green = pVal->green;
	rgba.blue  = pVal->blue;
	rgba.alpha = pVal->alpha;
}
void TObjEffFlyJump::TDisp()
{
	s32 src, dst, cullmode, va, fog;
	fn_80194294(10, &src);
	fn_80194294(11, &dst);
	fn_80194294(20, &cullmode);
	fn_80194294(12, &va);
	fn_80194294(14, &fog);
	fn_80194234(10, (void*)5);
	fn_80194234(11, (void*)2);
	fn_80194234(20, (void*)1);
	fn_80194234(12, (void*)1);
	fn_80194234(14, 0);
	if (pMaterialFlyJump) {
		RwRGBA rgba_Temp;
		rgba_Temp               = rgba;
		pMaterialFlyJump->color = rgba_Temp;
	}
	s32 time_current;
	RpClump* pClump_Temp = pClumpInstance;
	time_current         = lbl_8042C180->modeswitchlws[2];
	if (time_previousUV != time_current) {
		f32 delta = time_current - time_previousUV;
		if (pUVAnimFlyJump) {
			fn_8011B844(pUVAnimFlyJump, delta);
			fn_8014FFBC(pClump_Temp, fn_8005BF88, &FlyJumpUvInfo);
		}
		time_previousUV = time_current;
	}
	fn_8014FF2C(pClump_Temp);
	fn_80194234(14, (void*)fog);
	fn_80194234(12, (void*)va);
	fn_80194234(20, (void*)cullmode);
	fn_80194234(10, (void*)src);
	fn_80194234(11, (void*)dst);
}
inline TObjEffFlyJump2::TObjEffFlyJump2(TObjEffFlyJump* pTO, s32 pno)
    : TObject(pTO->Parent)
    , C_COLLI()
{
	ClassName               = CL_TObjEffFlyJump2;
	DispTime                = sizeof(TObjEffFlyJump2);
	playerno                = (s8)pno;
	const RwV3d& sourcePos  = pTO->GetPos();
	pos.x                   = sourcePos.x;
	pos.y                   = sourcePos.y;
	pos.z                   = sourcePos.z;
	const sAngle& sourceAng = pTO->GetAng();
	ang.x                   = sourceAng.x;
	ang.y                   = sourceAng.y;
	ang.z                   = sourceAng.z;
	pClumpInstance          = fn_80150588(pClumpFlyJump2);
	if (pClumpInstance) {
		fn_8005DA34(pClumpInstance);
		fn_8005D9F4(pClumpInstance);
		pAtomicInstance = fn_8005E1DC(pClumpInstance, 0, "ef_chbl");
		fn_801491A8(pAtomicInstance);
		fn_8005F670(pAtomicInstance, pMaterialFlyJump2);
		fn_8005F694(pAtomicInstance, &rgba);
		fn_8005F64C(pAtomicInstance, 1);
		pAtomicInstance->renderCallBack = callbackSetMaterial;
		if (!pAtomicInstance->renderCallBack)
			pAtomicInstance->renderCallBack = fn_8014F1B0;
		fn_8015BB08(lbl_8042C1D0->world, pClumpInstance);
	}
	s32 cno = lbl_802AD0D0[pno]->characterno;
	SetMaterialColor(&default_color[cno]);
	scaleH_Max = 0.1f * default_radius[cno];
	rotation   = 0.0f;
	scaleV = scaleH = 1.0f;
}
TObjEffFlyJump2::~TObjEffFlyJump2()
{
	if (pClumpInstance) {
		fn_8015BBF8(lbl_8042C1D0->world, pClumpInstance);
		fn_80150958(pClumpInstance);
		pClumpInstance = 0;
	}
}
void TObjEffFlyJump2::UpdateFrame()
{
	RwFrame* pFrame = (RwFrame*)pClumpInstance->object.parent;
	fn_80195790(&pFrame->modelling, &lbl_80239984,
	    1.0f - fn_800D7AE4(ang.y + (s32)(182.04444885253906f * rotation)),
	    fn_800D7B00(ang.y + (s32)(182.04444885253906f * rotation)), 0);
	fn_80195790(
	    &pFrame->modelling, &lbl_80239978, 1.0f - fn_800D7AE4(ang.x), fn_800D7B00(ang.x), 2);
	fn_80195790(
	    &pFrame->modelling, &lbl_80239990, 1.0f - fn_800D7AE4(ang.z), fn_800D7B00(ang.z), 2);
	fn_8019EB94(pFrame, &pos, 2);
	RwV3d scale;
	scale.x = scaleH;
	scale.y = scaleV;
	scale.z = scaleH;
	fn_8019EC30(pFrame, &scale, 1);
	fn_8019E880(pFrame);
}
void TObjEffFlyJump2::Exec()
{
	scaleV = fn_800D7328(scaleV, 2.0f, 0.2f);
	scaleH = fn_800D7328(scaleH, scaleH_Max, 0.25f);
	UpdateFrame();
	rotation += 22.0f;
	s32 alpha_Temp = rgba.alpha;
	alpha_Temp -= 32;
	if (alpha_Temp < 0)
		alpha_Temp = 0;
	RwRGBA rgba_Temp = *GetMaterialColor();
	rgba_Temp.alpha  = (u8)alpha_Temp;
	SetMaterialColor(&rgba_Temp);
	if (rgba.alpha == 0)
		Signal |= 1;
}
void TObjEffFlyJump2::SetMaterialColor(const RwRGBA* pVal)
{
	rgba.red   = pVal->red;
	rgba.green = pVal->green;
	rgba.blue  = pVal->blue;
	rgba.alpha = pVal->alpha;
	if (rgba.alpha >= 255)
		rgba.alpha = 254;
	fn_8005F694(pAtomicInstance, &rgba);
}
void TObjEffFlyJump2::TDisp()
{
	s32 time_current;
	RpClump* pClump_Temp = pClumpInstance;
	time_current         = lbl_8042C180->modeswitchlws[2];
	if (time_previousUV != time_current) {
		f32 delta = time_current - time2_previousUV;
		if (pUVAnimFlyJump2) {
			fn_8011B844(pUVAnimFlyJump2, delta);
			fn_8014FFBC(pClump_Temp, fn_8005BF88, &FlyJump2UvInfo);
		}
		time2_previousUV = time_current;
	}
}
TObjEffBrimS::TObjEffBrimS(TObject* pTO, s32 pno)
    : TObject(pTO)
{
	ClassName              = CL_TObjEffBrimS;
	DispTime               = sizeof(TObjEffBrimS);
	playerno               = (s8)pno;
	const RwV3d& playerPos = lbl_802AD070[pno]->pWork->pos;
	pos.x                  = playerPos.x;
	pos.y                  = playerPos.y;
	pos.z                  = playerPos.z;
	RwV3d pos0, pos1, v;
	fn_8003E2E4(playerno, 0, &pos0, 0);
	fn_8003E2E4(playerno, 1, &pos1, 0);
	v.x = pos0.x - pos1.x;
	v.y = pos0.y - pos1.y;
	v.z = pos0.z - pos1.z;
	if (v.z * v.z + (v.x * v.x + v.y * v.y) < 0.01f) {
		v.x = lbl_80239978.x;
		v.y = lbl_80239978.y;
		v.z = lbl_80239978.z;
		fn_8003E9B4(lbl_802AD090[pno], &v);
	}
	fn_801990E0(&v, &v);
	if (v.y >= 1.0f) {
		ang.x = -90.0f;
		ang.y = 0.0f;
	} else if (v.y <= -1.0f) {
		ang.x = 90.0f;
		ang.y = 0.0f;
	} else {
		f32 ax = (f32)asin(-v.y);
		ang.x  = 0.0054931640625f * (s32)(10430.380859375f * ax);
		f32 ay = (f32)atan2(v.x, v.z);
		ang.y  = 0.0054931640625f * (s32)(10430.380859375f * ay);
	}
	ang.z          = 0.0f;
	pClumpInstance = fn_80150588(pClumpFlyJump2);
	if (pClumpInstance) {
		fn_8005DA34(pClumpInstance);
		fn_8005D9F4(pClumpInstance);
		pAtomicInstance = fn_8005E1DC(pClumpInstance, 0, "ef_chbl");
		fn_801491A8(pAtomicInstance);
		fn_8005F670(pAtomicInstance, pMaterialFlyJump2);
		fn_8005F694(pAtomicInstance, &rgba);
		fn_8005F64C(pAtomicInstance, 1);
		pAtomicInstance->renderCallBack = callbackSetMaterial;
		if (!pAtomicInstance->renderCallBack)
			pAtomicInstance->renderCallBack = fn_8014F1B0;
		fn_8015BB08(lbl_8042C1D0->world, pClumpInstance);
	}
	BrimPlayerWorkView* pwp = lbl_802AD0D0[pno];
	s32 cno                 = pwp->characterno;
	SetMaterialColor(&default_color[cno]);
	scaleH_Max = 0.1f * default_radius[cno];
	rotation   = 0.0f;
	scaleV = scaleH = 0.5f;
	if (lbl_80303DC8[pwp->teamNo]->level[pwp->memberNo] < 2)
		scaleH_Max *= 0.4f;
}
TObjEffBrimS::~TObjEffBrimS()
{
	if (pClumpInstance) {
		fn_8015BBF8(lbl_8042C1D0->world, pClumpInstance);
		fn_80150958(pClumpInstance);
		pClumpInstance = 0;
	}
}
void TObjEffBrimS::UpdateFrame()
{
	RwFrame* pFrame = (RwFrame*)pClumpInstance->object.parent;
	fn_80195790(&pFrame->modelling, &lbl_80239984,
	    1.0f - fn_800D7AE4((s32)(182.04444885253906f * rotation)),
	    fn_800D7B00((s32)(182.04444885253906f * rotation)), 0);
	fn_80195790(&pFrame->modelling, &lbl_80239978,
	    1.0f - fn_800D7AE4((s32)(182.04444885253906f * (90.0f + ang.x))),
	    fn_800D7B00((s32)(182.04444885253906f * (90.0f + ang.x))), 2);
	fn_80195790(&pFrame->modelling, &lbl_80239984,
	    1.0f - fn_800D7AE4((s32)(182.04444885253906f * ang.y)),
	    fn_800D7B00((s32)(182.04444885253906f * ang.y)), 2);
	fn_8019EB94(pFrame, &pos, 2);
	RwV3d scale;
	scale.x = scaleH;
	scale.y = scaleV;
	scale.z = scaleH;
	fn_8019EC30(pFrame, &scale, 1);
	fn_8019E880(pFrame);
}
void TObjEffBrimS::Exec()
{
	scaleV = fn_800D7328(scaleV, 4.0f * scaleH_Max, 0.2f);
	scaleH = fn_800D7328(scaleH, scaleH_Max, 0.125f);
	UpdateFrame();
	rotation += 22.0f;
	if (scaleH >= 0.5f * scaleH_Max) {
		s32 alpha_Temp = rgba.alpha;
		alpha_Temp -= 16;
		if (alpha_Temp < 0)
			alpha_Temp = 0;
		RwRGBA rgba_Temp = *GetMaterialColor();
		rgba_Temp.alpha  = (u8)alpha_Temp;
		SetMaterialColor(&rgba_Temp);
	}
	if (rgba.alpha == 0)
		Signal |= 1;
}
void TObjEffBrimS::SetMaterialColor(const RwRGBA* pVal)
{
	rgba.red   = pVal->red;
	rgba.green = pVal->green;
	rgba.blue  = pVal->blue;
	rgba.alpha = pVal->alpha;
	if (rgba.alpha >= 255)
		rgba.alpha = 254;
	fn_8005F694(pAtomicInstance, &rgba);
}
void TObjEffBrimS::TDisp()
{
	s32 time_current;
	RpClump* pClump_Temp = pClumpInstance;
	time_current         = lbl_8042C180->modeswitchlws[2];
	if (time_previousUV != time_current) {
		f32 delta = time_current - time2_previousUV;
		if (pUVAnimFlyJump2) {
			fn_8011B844(pUVAnimFlyJump2, delta);
			fn_8014FFBC(pClump_Temp, fn_8005BF88, &FlyJump2UvInfo);
		}
		time2_previousUV = time_current;
	}
}