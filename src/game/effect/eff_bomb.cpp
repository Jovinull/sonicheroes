// Complete effect/eff_bomb.cpp, reconstructed from GC behavior and symbolic C++ metadata.
// Ordinary helper definitions, declaration lifetimes and a scaled-alpha temporary
// recover all bodies except six constructor loop-allocation words (eight GPR fields).
// tools/fix_eff_bomb_registers.py guards that r28/r31 permutation; remove it when
// source/compiler lifetime choices recover the allocation naturally. See
// docs/eff-bomb-unit-evidence.md for the bounded source trials and live-range proof.
#include "game/effect/eff_bomb.h"

struct RwObject {
	u8 type, subType, flags, privateFlags;
	void* parent;
};
struct RwLLLink {
	RwLLLink* next;
	RwLLLink* prev;
};
struct RwFrame;
struct RpWorld;
struct RpUVAnimAnimation;
struct RwTexture;
struct RwRGBA {
	u8 red, green, blue, alpha;
};
struct RwSurfaceProperties {
	f32 ambient, specular, diffuse;
};
struct RpMaterial {
	RwTexture* texture;
	RwRGBA color;
	void* pipeline;
	RwSurfaceProperties surfaceProps;
	s16 refCount;
	s16 pad;
};
struct RpMaterialList {
	RpMaterial** materials;
	s32 numMaterials, space;
};
struct RpGeometry {
	RwObject object;
	u32 flags;
	u16 lockedSinceLastInst;
	s16 refCount;
	s32 numTriangles, numVertices, numMorphTargets, numTexCoordSets;
	RpMaterialList matList;
};
struct RwObjectHasFrame {
	RwObject object;
	RwLLLink lFrame;
	void* sync;
};
struct RwSphere {
	RwV3d center;
	f32 radius;
};
struct RpClump {
	RwObject object;
};
struct RpAtomic {
	RwObjectHasFrame object;
	void* repEntry;
	RpGeometry* geometry;
	RwSphere boundingSphere, worldBoundingSphere;
	RpClump* clump;
	RwLLLink inClumpLink;
	RpAtomic* (*renderCallBack)(RpAtomic*);
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
// GC matrix alignment is four bytes, unlike the PS2 type's sixteen-byte alignment.
struct UVFXInfo {
	RpUVAnimAnimation* uvAnim;
	RwMatrix uvMatrix;
};
struct BombModeView {
	s8 modeswitchflags[0x28];
	s32 modeswitchlws[6];
};
struct BombActionView {
	u8 unknown[0x18];
	s32 restartFlag;
};
// Only the externally accessed GC LandManager world pointer is represented here.
struct BombLandView {
	u8 unknown[0x72A0];
	RpWorld* world;
};
extern "C" {
extern BombModeView* lbl_8042C180;
extern BombLandView* lbl_8042C1D0;
extern BombActionView lbl_8029C310;
extern TObject* lbl_8042C110;
extern TObject* lbl_8042C2A0;
extern RwV3d lbl_80239984;
s32 setobjCheckRangeOut2__FPC5RwV3df(const RwV3d*, f32);
f32 fn_800D7328(f32, f32, f32);
void fn_80021384(C_COLLI*);
s32 fn_8003C200(C_COLLI*, CCL_INFO*, s32, u8);
s32 fn_8003BC38(C_COLLI*);
RwFrame* fn_8005DF98(RwFrame*, RwFrame*);
RwFrame* fn_8019EB94(RwFrame*, const RwV3d*, s32);
RwFrame* fn_8019EC30(RwFrame*, const RwV3d*, s32);
RwFrame* fn_8019ED68(RwFrame*, const RwV3d*, f32, s32);
RpClump* fn_80150588(RpClump*);
s32 fn_80150958(RpClump*);
RpWorld* fn_8015BB08(RpWorld*, RpClump*);
RpWorld* fn_8015BBF8(RpWorld*, RpClump*);
RpAtomic* fn_8005E394(RpClump*, RpAtomic*);
RpAtomic* fn_801491A8(RpAtomic*);
s32 fn_8005F670(RpAtomic*, RpMaterial*);
s32 fn_8005F694(RpAtomic*, RwRGBA*);
s32 fn_8005F64C(RpAtomic*, s32);
RpAtomic* fn_8014F1B0(RpAtomic*);
s32 fn_8011B844(RpUVAnimAnimation*, f32);
RpAtomic* fn_8005BF88(RpAtomic*, void*);
RpClump* fn_8014FFBC(RpClump*, RpAtomic* (*)(RpAtomic*, void*), void*);
}

static RpClump* pClump;
static RpMaterial* pMaterial[3] = { 0, 0, 0 };
static RpUVAnimAnimation* pUVAnim;
static RpAtomic* (*pAtomicRenderCallBack)(RpAtomic*);
static UVFXInfo EffDushUvInfo;
static CCL_INFO ci_bomb[1]
    = { { 7, 0, 0xF0, 0xE2, 0x00802400, { 0, 0, 0 }, 30, 0, 0, 0, 0, 0, 0 } };
char* CL_TObjEffBomb = "TObjEffBomb";
static s32 time_previous;
static RpAtomic* callbackSetMaterial(RpAtomic*);

extern "C" {
void* fn_8005EA04(char*);
void fn_8005DA34(RpClump*);
RpMaterial* fn_8005E410(RpClump*, RpMaterial*, char*);
void fn_8005D6DC(RpClump*);
RpAtomic* fn_8005E394(RpClump*, RpAtomic*);
void fn_8005BF5C(RpClump*, UVFXInfo*);
RpMaterial* fn_8005F6D4(RpAtomic*);
RwRGBA* fn_8005F6F4(RpAtomic*);
s32 fn_80194294(s32, void*);
s32 fn_80194234(s32, void*);
extern TObject* lbl_8042C2A0;
extern TObject* lbl_8042C110;
}

void SetEffectBomb(TObject* pTO, RwV3d* pPosition0, sAngle* pAngle0, ENUM_EFF_BOMB_TYPE typeEffBomb,
    s32 teamNo_Current)
{
	if (!pTO) {
		pTO = lbl_8042C2A0;
		if (!pTO)
			pTO = lbl_8042C110;
	}
	new TObjEffBomb(pTO, teamNo_Current, pPosition0, pAngle0, typeEffBomb);
}

void InitEffBomb()
{
	if (!pClump) {
		pClump = (RpClump*)fn_8005EA04("EF_BOMB.DFF");
		if (pClump) {
			fn_8005DA34(pClump);
			pMaterial[0] = fn_8005E410(pClump, 0, "ef_exp");
			pMaterial[1] = fn_8005E410(pClump, pMaterial[0], "ef_exp");
			pMaterial[2] = fn_8005E410(pClump, 0, 0);
			fn_8005D6DC(pClump);
			RpAtomic* pAtomic_Temp = fn_8005E394(pClump, 0);
			pAtomicRenderCallBack  = pAtomic_Temp->renderCallBack;
		}
	}
	if (!pUVAnim) {
		pUVAnim = (RpUVAnimAnimation*)fn_8005EA04("EF_BOMB.UVB");
		if (pUVAnim && pMaterial[0]) {
			EffDushUvInfo.uvAnim = pUVAnim;
			fn_8005BF5C(pClump, &EffDushUvInfo);
		}
	}
}

void EndEffBomb()
{
	pAtomicRenderCallBack = 0;
	if (pUVAnim)
		pUVAnim = 0;
	if (pClump) {
		pClump       = 0;
		pMaterial[0] = 0;
		pMaterial[1] = 0;
		pMaterial[2] = 0;
	}
}

static RpAtomic* callbackSetMaterial(RpAtomic* pCurrentAtomic)
{
	RpMaterial* pCurrentMaterial = fn_8005F6D4(pCurrentAtomic);
	pCurrentMaterial->color      = *fn_8005F6F4(pCurrentAtomic);
	if (pAtomicRenderCallBack) {
		s32 fog;
		fn_80194294(14, &fog);
		fn_80194234(14, 0);
		pAtomicRenderCallBack(pCurrentAtomic);
		fn_80194234(14, (void*)fog);
	}
	return pCurrentAtomic;
}

TObjEffBomb::TObjEffBomb(TObject* ptp, s32 teamNo_Current, RwV3d* pPosition0, sAngle* pAngle0,
    ENUM_EFF_BOMB_TYPE typeEffBomb)
    : TObject(ptp)
{
	ClassName = CL_TObjEffBomb;
	DispTime  = sizeof(TObjEffBomb);
	if (lbl_8042C180->modeswitchflags[0x1F])
		flagTimeStop = 1;
	else
		flagTimeStop = 0;
	if (pPosition0)
		pos = *pPosition0;
	else
		pos.x = pos.y = pos.z = 0.0f;
	if (pAngle0)
		ang = *pAngle0;
	else
		ang.x = ang.y = ang.z = 0;
	timer          = 0;
	alpha[0]       = 1.0f;
	alpha[1]       = 1.0f;
	alpha[2]       = 1.0f;
	scale[0]       = 0.1f;
	scale[1]       = 0.001f;
	scale[2]       = 0.001f;
	rotation       = 0.0f;
	teamNo         = (s8)teamNo_Current;
	type           = typeEffBomb;
	mode           = BOMB_EffBombMode;
	pClumpInstance = fn_80150588(pClump);
	if (pClumpInstance) {
		pAtomicInstance[0] = fn_8005E394((RpClump*)pClumpInstance, 0);
		pAtomicInstance[1] = fn_8005E394((RpClump*)pClumpInstance, pAtomicInstance[0]);
		pAtomicInstance[2] = fn_8005E394((RpClump*)pClumpInstance, pAtomicInstance[1]);
		for (s32 i = 0; i < 3; i++) {
			RpAtomic* pAtomic_Temp     = pAtomicInstance[i];
			RpGeometry* pGeometry_Temp = pAtomic_Temp->geometry;
			if (pGeometry_Temp->flags & 4)
				fn_801491A8(pAtomic_Temp);
			RpMaterial* pMaterial_Temp = pGeometry_Temp->matList.materials[0];
			fn_8005F670(pAtomic_Temp, pMaterial_Temp);
			fn_8005F694(pAtomic_Temp, &pMaterial_Temp->color);
			fn_8005F64C(pAtomic_Temp, 1);
			pAtomic_Temp->renderCallBack = callbackSetMaterial;
			if (!pAtomic_Temp->renderCallBack)
				pAtomic_Temp->renderCallBack = fn_8014F1B0;
			pGeometry_Temp->flags |= 0x60;
		}
		fn_8015BB08(lbl_8042C1D0->world, (RpClump*)pClumpInstance);
	}
	SetPosition();
	switch (type) {
		case ENUM_EFF_BOMB_TYPE_SBOMB:
		case ENUM_EFF_BOMB_TYPE_LBOMB:
			fn_8003C200(&static_cast<C_COLLI&>(*this), ci_bomb, 1, 1);
			SetCollisionParameter();
			if (teamNo != -1)
				strength = 3;
			break;
		case ENUM_EFF_BOMB_TYPE_GC4:
			fn_8003C200(&static_cast<C_COLLI&>(*this), ci_bomb, 1, 1);
			SetCollisionParameter();
			if (teamNo != -1) {
				strength   = 9;
				info->kind = 12;
			}
			break;
	}
}

void TObjEffBomb::SetCollisionParameter()
{
	character_id = GetCCLCharacterIdFromTeamNoOfBomb(teamNo);
	if (info) {
		info->a = 20.0f * scale[2];
		fn_80021384(&static_cast<C_COLLI&>(*this));
	}
}

TObjEffBomb::~TObjEffBomb()
{
	if (pClumpInstance) {
		fn_8015BBF8(lbl_8042C1D0->world, (RpClump*)pClumpInstance);
		fn_80150958((RpClump*)pClumpInstance);
		pClumpInstance = 0;
	}
}

void TObjEffBomb::SetPosition()
{
	RwFrame *second, *first, *pFrame;
	pFrame = (RwFrame*)((RpClump*)pClumpInstance)->object.parent;
	RwV3d scale_Temp;
	fn_8019EB94(pFrame, &pos, 0);
	pFrame       = fn_8005DF98(pFrame, 0);
	first        = fn_8005DF98(pFrame, 0);
	second       = fn_8005DF98(pFrame, first);
	pFrame       = fn_8005DF98(pFrame, second);
	scale_Temp.x = scale_Temp.y = scale_Temp.z = scale[0];
	fn_8019EC30(first, &scale_Temp, 0);
	scale_Temp.x = scale_Temp.y = scale_Temp.z = scale[1];
	fn_8019EC30(second, &scale_Temp, 0);
	scale_Temp.x = scale_Temp.y = scale_Temp.z = scale[2];
	fn_8019EC30(pFrame, &scale_Temp, 0);
	fn_8019ED68(pFrame, &lbl_80239984, rotation, 2);
}

void TObjEffBomb::Exec()
{
	if (setobjCheckRangeOut2__FPC5RwV3df(&pos, 1000000.0f)) {
		Signal |= 1;
		return;
	}
	switch (mode) {
		case BOMB_EffBombMode:
			if (!lbl_8042C180->modeswitchflags[0x1F] || flagTimeStop == 1) {
				++timer;
				scale[0] = fn_800D7328(scale[0], 22.0f, 1.2222222f);
				if (timer >= 18)
					alpha[0] = fn_800D7328(alpha[0], 0.0f, 0.33333334f);
				if (timer < 24)
					scale[1] = fn_800D7328(scale[1], 0.4f, 0.014125f);
				else
					scale[1] = fn_800D7328(scale[1], 2.0f, 0.044444446f);
				if (timer >= 48)
					alpha[1] = fn_800D7328(alpha[1], 0.0f, 0.083333336f);
				if (timer < 24)
					scale[2] = fn_800D7328(scale[2], 0.5f, 0.020791667f);
				else
					scale[2] = fn_800D7328(scale[2], 1.5f, 0.030303031f);
				if (timer >= 45)
					alpha[2] = fn_800D7328(alpha[2], 0.0f, 0.083333336f);
			}
			if (alpha[1] <= 0.0f) {
				mode  = END_EffBombMode;
				timer = 0;
			}
			SetPosition();
			SetCollisionParameter();
			break;
		case END_EffBombMode:
			if (Parent == lbl_8042C110 || Parent == lbl_8042C2A0)
				Signal |= 1;
			return;
	}
	if (!lbl_8042C180->modeswitchflags[0x1F] && flagTimeStop == 1)
		rotation += 11.0f;
	if (alpha[2] > 0.5f && info) {
		if (lbl_8029C310.restartFlag == 0) {
			C_COLLI::pre_pos = C_COLLI::pos;
			C_COLLI::pos     = pos;
			C_COLLI::ang     = ang;
			fn_8003BC38(&static_cast<C_COLLI&>(*this));
		} else
			ClearInfo();
	}
}

void TObjEffBomb::TDisp()
{
	RpClump* pClump_Current;
	RwRGBA rgba_Temp;
	s32 i;
	for (i = 0; i < 3; i++) {
		if (alpha[i] > 0.0f) {
			f32 value = alpha[i];
			value *= 255.0f;
			rgba_Temp.alpha = (u8)value;
			rgba_Temp.blue = rgba_Temp.red = rgba_Temp.green = (u8)value;
			fn_8005F694(pAtomicInstance[i], &rgba_Temp);
			pAtomicInstance[i]->object.object.flags |= 4;
		} else
			pAtomicInstance[i]->object.object.flags &= ~4;
	}
	pClump_Current   = (RpClump*)pClumpInstance;
	s32 time_current = lbl_8042C180->modeswitchlws[2] + lbl_8042C180->modeswitchlws[3];
	if (time_previous != time_current) {
		f32 deltaTime_Temp = 0.5f * (time_current - time_previous);
		if (pMaterial[0] && pUVAnim) {
			fn_8011B844(pUVAnim, deltaTime_Temp);
			fn_8014FFBC(pClump_Current, fn_8005BF88, &EffDushUvInfo);
		}
		time_previous = time_current;
	}
}

CHARACTER_ID GetCCLCharacterIdFromTeamNoOfBomb(s32 teamNo_Current)
{
	CHARACTER_ID cid;
	switch (teamNo_Current) {
		case 0:
			cid = TEAM_0;
			break;
		case 1:
			cid = TEAM_1;
			break;
		case 2:
			cid = TEAM_2;
			break;
		case 3:
			cid = TEAM_3;
			break;
		default:
			cid = NO_CHARACTER_ID;
			break;
	}
	return cid;
}
