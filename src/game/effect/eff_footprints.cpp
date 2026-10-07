#include "game/effect/eff_footprints.h"
#include "dolphin/gx/GXPixel.h"
// eff_footprints.cpp: complete C++ unit. Symbolic metadata supplies identities;
// GameCube code and data determine platform layouts and behavior.
// Deferred whole-unit emission preserves the ordinary helper definitions.
// Disp retains a 12-register-field allocation remainder across 11 instructions;
// a source-only replacement must preserve all bodies, relocations and storage.
// Cursor/index/color-lifetime source trials are recorded in
// docs/eff-footprints-unit-evidence.md; replace the bounded step when those
// source/compiler choices recover the same allocation naturally.
// Historical definition order and local-variable spelling are not established.
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
struct RwV2d {
	f32 x, y;
};
struct RwTexDictionary;
struct RwTexture {
	void* raster;
};
// GC places color after the normal, unlike the PS2 vertex layout.
struct RxObjSpace3DVertex {
	RwV3d objVertex, objNormal;
	RwRGBA c;
	f32 u, v;
};
struct FootprintMode {
	u8 pad[0x20];
	s8 hidden;
};
struct FootprintStage {
	u8 pad[0x2C];
	s32 stage;
};
struct FootprintTeam {
	u8 pad[0x34];
	s32 teamKind;
};
extern "C" {
extern TObject *lbl_8042C2A0, *lbl_8042C110;
extern FootprintMode* lbl_8042C180;
extern FootprintStage lbl_8029C310;
extern FootprintTeam* lbl_80303DC8[4];
extern RwV3d lbl_80239978, lbl_80239984, lbl_80239990;
f32 fn_800D7B00(s32);
f32 fn_800D7AE4(s32);
RwMatrix* fn_80195E44(RwMatrix*, const RwV3d*, s32);
RwMatrix* fn_80195790(RwMatrix*, const RwV3d*, f32, f32, s32);
RwMatrix* fn_80196050(RwMatrix*, const RwV3d*, s32);
RwV3d* fn_8019941C(RwV3d*, const RwV3d*, s32, const RwMatrix*);
void* fn_801B2934(RxObjSpace3DVertex*, u32, RwMatrix*, u32);
s32 fn_801B2C00(s32);
s32 fn_801B2A14();
s32 fn_80194294(s32, void*);
s32 fn_80194234(s32, void*);
RwTexture* fn_801A4BBC(RwTexDictionary*, const char*);
s32 fn_801A46D0(RwTexDictionary*);
}
RwTexDictionary* texLoadTexDictionaryFile(char*);
static RwTexDictionary* pTexDict_EffFootPrints[4];
static RwTexture* pTex_EffFootPrints[4];
static EffFootPrintsManager* pMan_EffFootPrints[4];
static EffFootPrints* Create(RwV3d*, sAngle*, s32, s32, RwRGBA*, s32);
s32 EffFootPrintsManager::EraseEffect(EffFootPrints* pEff_Current)
{
	UnlinkClass(pEff_Current);
	return 0;
}

s32 EffFootPrintsManager::InsertEffect(EffFootPrints* pEff_Current)
{
	if (LinkClass(pEff_Current)) {
		pEff_Current->pData = pEff_Current;
		return 1;
	}
	return 0;
}

void InitEffFootPrints()
{
	static char* fname[4]   = { "./textures/eff_footPrintsS.txd", "./textures/eff_footPrintsD.txd",
		"./textures/eff_footPrintsR.txd", "./textures/eff_footPrintsC.txd" };
	static char* texname[4] = { "he_foot_sand", "da_foot_sand", "ro_foot_sand", "co_foot_sand" };
	switch (lbl_8029C310.stage) { // actual signed field at +0x2c; use chosen truthful source view
		case 2:
		case 3:
		case 12:
		case 13:
		case 16:
		case 25:
		case 37:
			for (s32 i = 0; i < 4; ++i) {
				pMan_EffFootPrints[i]     = 0;
				pTexDict_EffFootPrints[i] = 0;
				pTex_EffFootPrints[i]     = 0;
				if (lbl_80303DC8[i]) {
					s32 teamkind              = lbl_80303DC8[i]->teamKind; // signed field +0x34
					pTexDict_EffFootPrints[i] = texLoadTexDictionaryFile(fname[teamkind]);
					pTex_EffFootPrints[i]
					    = fn_801A4BBC(pTexDict_EffFootPrints[i], texname[teamkind]);
				}
			}
			break;
	}
}
char* CL_EffFootPrintsManager = "EffFootPrintsManager";
static RwV2d uv_table[12][4]  = {
	{ { 0.412698418f, 0.111111112f }, { 0.412698418f, 0.873015881f },
	    { 0.682539701f, 0.111111112f }, { 0.682539701f, 0.873015881f } },
	{ { 0.0317460336f, 0.0793650821f }, { 0.0317460336f, 0.90476191f },
	    { 0.365079373f, 0.0793650821f }, { 0.365079373f, 0.90476191f } },
	{ { 0.714285731f, 0.111111112f }, { 0.714285731f, 0.825396836f },
	    { 0.984126985f, 0.111111112f }, { 0.984126985f, 0.825396836f } },
	{ { 0.365079373f, 0.111111112f }, { 0.365079373f, 0.920634925f },
	    { 0.666666687f, 0.111111112f }, { 0.666666687f, 0.920634925f } },
	{ { 0.730158746f, 0.0317460336f }, { 0.730158746f, 0.984126985f },
	    { 0.984126985f, 0.0317460336f }, { 0.984126985f, 0.984126985f } },
	{ { 0.0476190485f, 0.174603179f }, { 0.0476190485f, 0.841269851f },
	    { 0.317460328f, 0.174603179f }, { 0.317460328f, 0.841269851f } },
	{ { 0.333333343f, 0.206349209f }, { 0.333333343f, 0.825396836f },
	    { 0.555555582f, 0.206349209f }, { 0.555555582f, 0.825396836f } },
	{ { 0.619047642f, 0.0476190485f }, { 0.619047642f, 1.0f }, { 0.984126985f, 0.0476190485f },
	    { 0.984126985f, 1.0f } },
	{ { 0.0476190485f, 0.253968269f }, { 0.0476190485f, 0.793650806f },
	    { 0.285714298f, 0.253968269f }, { 0.285714298f, 0.793650806f } },
	{ { 0.317460328f, 0.174603179f }, { 0.317460328f, 0.888888896f },
	    { 0.603174627f, 0.174603179f }, { 0.603174627f, 0.888888896f } },
	{ { 0.650793672f, 0.111111112f }, { 0.650793672f, 0.984126985f },
	    { 0.984126985f, 0.0317460336f }, { 0.984126985f, 0.984126985f } },
	{ { 0.0476190485f, 0.253968269f }, { 0.0476190485f, 0.809523821f },
	    { 0.269841284f, 0.253968269f }, { 0.269841284f, 0.809523821f } },
};
static RwV3d size_table[12] = {
	{ 1.0f, 1.0f, 1.0f },
	{ 1.0f, 1.0f, 1.0f },
	{ 1.0f, 1.0f, 1.0f },
	{ 1.0f, 1.0f, 1.0f },
	{ 1.29999995f, 1.0f, 1.29999995f },
	{ 1.0f, 1.0f, 1.0f },
	{ 1.0f, 1.0f, 1.0f },
	{ 1.5f, 1.0f, 1.5f },
	{ 1.0f, 1.0f, 1.0f },
	{ 1.0f, 1.0f, 1.0f },
	{ 1.29999995f, 1.0f, 1.29999995f },
	{ 1.0f, 1.0f, 1.0f },
};
static RwV3d pos_table[12][4] = {
	{ { -0.850000024f, 0.0f, 0.5f }, { -0.850000024f, 0.0f, -3.5f }, { 0.850000024f, 0.0f, 0.5f },
	    { 0.850000024f, 0.0f, -3.5f } },
	{ { -1.04999995f, 0.0f, 0.400000006f }, { -1.04999995f, 0.0f, -3.5999999f },
	    { 1.04999995f, 0.0f, 0.400000006f }, { 1.04999995f, 0.0f, -3.5999999f } },
	{ { -0.850000024f, 0.0f, 0.5f }, { -0.850000024f, 0.0f, -3.4000001f },
	    { 0.850000024f, 0.0f, 0.5f }, { 0.850000024f, 0.0f, -3.4000001f } },
	{ { -0.949999988f, 0.0f, 1.0f }, { -0.949999988f, 0.0f, -4.0999999f },
	    { 0.949999988f, 0.0f, 1.0f }, { 0.949999988f, 0.0f, -4.0999999f } },
	{ { -0.800000012f, 0.0f, 0.800000012f }, { -0.800000012f, 0.0f, -5.19999981f },
	    { 0.800000012f, 0.0f, 0.800000012f }, { 0.800000012f, 0.0f, -5.19999981f } },
	{ { -0.850000024f, 0.0f, 0.800000012f }, { -0.850000024f, 0.0f, -3.4000001f },
	    { 0.850000024f, 0.0f, 0.800000012f }, { 0.850000024f, 0.0f, -3.4000001f } },
	{ { -0.75f, 0.0f, 0.400000006f }, { -0.75f, 0.0f, -3.0f }, { 0.75f, 0.0f, 0.400000006f },
	    { 0.75f, 0.0f, -3.0f } },
	{ { -1.14999998f, 0.0f, 1.0f }, { -1.14999998f, 0.0f, -5.0f }, { 1.14999998f, 0.0f, 1.0f },
	    { 1.14999998f, 0.0f, -5.0f } },
	{ { -0.75f, 0.0f, 0.400000006f }, { -0.75f, 0.0f, -3.0f }, { 0.75f, 0.0f, 0.400000006f },
	    { 0.75f, 0.0f, -3.0f } },
	{ { -0.899999976f, 0.0f, 0.600000024f }, { -0.899999976f, 0.0f, -3.9000001f },
	    { 0.899999976f, 0.0f, 0.600000024f }, { 0.899999976f, 0.0f, -3.9000001f } },
	{ { -1.04999995f, 0.0f, 0.800000012f }, { -1.04999995f, 0.0f, -5.19999981f },
	    { 1.04999995f, 0.0f, 0.800000012f }, { 1.04999995f, 0.0f, -5.19999981f } },
	{ { -0.699999988f, 0.0f, 0.5f }, { -0.699999988f, 0.0f, -3.4000001f },
	    { 0.699999988f, 0.0f, 0.5f }, { 0.699999988f, 0.0f, -3.4000001f } },
};

void EndEffFootPrints()
{
	for (s32 i = 0; i < 4; ++i) {
		if (pMan_EffFootPrints[i]) {
			delete pMan_EffFootPrints[i];
			pMan_EffFootPrints[i] = 0;
		}
		if (pTexDict_EffFootPrints[i]) {
			fn_801A46D0(pTexDict_EffFootPrints[i]);
			pTexDict_EffFootPrints[i] = 0;
			pTex_EffFootPrints[i]     = 0;
		}
	}
}

EffFootPrintsManager::EffFootPrintsManager(TObject* pTO, s32 team)
    : TObject(pTO)
    , CLASS_LINK_MANAGER()
{
	ClassName = CL_EffFootPrintsManager;
	DispTime  = sizeof(*this);
	teamNo    = team;
}

EffFootPrintsManager::~EffFootPrintsManager()
{
	pCurrent = pHead;
	while (pCurrent) {
		EffFootPrints* pEFP = (EffFootPrints*)pCurrent->pData;
		pCurrent            = pCurrent->pNext;
		if (pEFP)
			delete pEFP;
	}
	if (pMan_EffFootPrints[teamNo] == this)
		pMan_EffFootPrints[teamNo] = 0;
}

void EffFootPrintsManager::Exec()
{
	pCurrent = pHead;
	while (pCurrent) {
		EffFootPrints* pEFP = (EffFootPrints*)pCurrent->pData;
		pCurrent            = pCurrent->pNext;
		if (pEFP && pEFP->Exec())
			delete pEFP;
	}
}

void EffFootPrintsManager::TDisp()
{
	if (!pTex_EffFootPrints[teamNo])
		return;
	if (lbl_8042C180->hidden)
		return;
	s32 src, dst, cullmode;
	fn_80194294(10, &src);
	fn_80194294(11, &dst);
	fn_80194294(20, &cullmode);
	fn_80194234(10, (void*)5);
	fn_80194234(11, (void*)2);
	fn_80194234(20, (void*)1);
	fn_80194234(1, pTex_EffFootPrints[teamNo]->raster);
	GXSetBlendMode((GXBlendMode)3, (GXBlendFactor)4, (GXBlendFactor)1, (GXLogicOp)0);
	pCurrent = pHead;
	while (pCurrent) {
		EffFootPrints* pEFP = (EffFootPrints*)pCurrent->pData;
		if (pEFP)
			pEFP->Disp();
		pCurrent = pCurrent->pNext;
	}
	fn_801B2A14();
	fn_80194234(20, (void*)cullmode);
	fn_80194234(10, (void*)src);
	fn_80194234(11, (void*)dst);
}

EffFootPrints::EffFootPrints(s32 teamno)
    : CLASS_LINK()
{
	teamNo = teamno;
	pMan_EffFootPrints[teamNo]->InsertEffect(this);
}

EffFootPrints::~EffFootPrints()
{
	pMan_EffFootPrints[teamNo]->EraseEffect(this);
}

s32 EffFootPrints::Exec()
{
	if (nowAlpha > 200.0f)
		nowAlpha -= 0.16f;
	else
		nowAlpha -= 0.48f;
	if (nowAlpha > 0.0f) {
		if (nowAlpha >= 255.0f)
			rgba.alpha = 255;
		else
			rgba.alpha = (u8)nowAlpha;
	} else {
		nowAlpha   = 0.0f;
		rgba.alpha = 0;
		return 1;
	}
	return 0;
}

s32 EffFootPrints::Disp()
{
	if (nowAlpha <= 0.0f)
		return 0;
	u8 green, blue, alpha;
	f32 y, z;
	f32 _a = 0.003921f * nowAlpha;
	RxObjSpace3DVertex vtx_fp[4];
	RxObjSpace3DVertex* pI3DV = vtx_fp;
	f32* pUV                  = flagLeft ? (f32*)&uv_table[noFoot][2] : (f32*)&uv_table[noFoot][0];
	for (s32 i = 0; i < 4; ++i) {
		y                  = pos[i].y;
		z                  = pos[i].z;
		pI3DV->objVertex.x = pos[i].x;
		pI3DV->objVertex.y = y;
		pI3DV->objVertex.z = z;
		pI3DV->u           = pUV[0];
		pI3DV->v           = pUV[1];
		pUV += 2;
		green          = (u8)(rgba.green * _a);
		blue           = (u8)(rgba.blue * _a);
		alpha          = rgba.alpha;
		pI3DV->c.red   = (u8)(rgba.red * _a);
		pI3DV->c.green = green;
		pI3DV->c.blue  = blue;
		pI3DV->c.alpha = alpha;
		++pI3DV;
		if (flagLeft && i == 1)
			pUV -= 8;
	}
	if (fn_801B2934(vtx_fp, 4, 0, 0x19))
		fn_801B2C00(4);
	return 1;
}

static EffFootPrints* Create(RwV3d* pPos_Org, sAngle* pAng_Org, s32 teamno, s32 characterno,
    RwRGBA* pRGBA_Set, s32 left_flag)
{
	if (!pMan_EffFootPrints[teamno]) {
		TObject* pTO = lbl_8042C2A0;
		if (!pTO)
			pTO = lbl_8042C110;
		pMan_EffFootPrints[teamno] = new EffFootPrintsManager(pTO, teamno);
	}
	EffFootPrints* pEFP = new EffFootPrints(teamno);
	if (!pEFP)
		return 0;
	RwMatrix mat_Temp;
	fn_80195E44(&mat_Temp, &size_table[characterno], 0);
	fn_80195790(&mat_Temp, &lbl_80239984, 1.0f - fn_800D7AE4(0xC000 - pAng_Org->y),
	    fn_800D7B00(0xC000 - pAng_Org->y), 2);
	fn_80195790(
	    &mat_Temp, &lbl_80239978, 1.0f - fn_800D7AE4(pAng_Org->x), fn_800D7B00(pAng_Org->x), 2);
	fn_80195790(
	    &mat_Temp, &lbl_80239990, 1.0f - fn_800D7AE4(pAng_Org->z), fn_800D7B00(pAng_Org->z), 2);
	fn_80196050(&mat_Temp, pPos_Org, 2);
	fn_8019941C(pEFP->pos, pos_table[characterno], 4, &mat_Temp);
	pEFP->flagLeft = left_flag;
	pEFP->noFoot   = characterno;
	pEFP->rgba     = *pRGBA_Set;
	pEFP->nowAlpha = pEFP->rgba.alpha;
	return pEFP;
}

void CreateEffFootPrints(RwV3d* pPos_Org, sAngle* pAng_Org, s32 teamno, s32 characterno,
    RwRGBA* pRGBA_Set, s32 left_flag)
{
	EffFootPrints* pEFP = Create(pPos_Org, pAng_Org, teamno, characterno, pRGBA_Set, left_flag);
	if (!pEFP)
		return;
}
