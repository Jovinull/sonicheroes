// Complete effect/eff_dush.cpp, using GC behavior and symbolic C++ metadata.
// Capturing playerno through the first history call is an inferred lifetime form:
// no intervening writes/calls precede that use; the second call rereads the member.
// Explicit float radians preserve the observed angle-rounding boundary. Original
// local spelling and definition order are unknown; see docs/eff-dush-unit-evidence.md.
#include "game/effect/eff_dush.h"
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
struct RwLLLink {
	RwLLLink* next;
	RwLLLink* prev;
};
struct RwFrame {
	RwObject object;
	RwLLLink inDirtyListLink;
	RwMatrix modelling, ltm;
};
// GC matrix offset4/size68 differs from the aligned PS2 UVFXInfo.
struct UVFXInfo {
	RpUVAnimAnimation* uvAnim;
	RwMatrix uvMatrix;
};
struct DushModeView {
	s8 modeswitchflags[0x28];
	s32 modeswitchlws[6];
};
// Referenced PLAYERWK fields: characterno@1 and mm.pClump@14C+34=180.
struct DushMotionView {
	u8 unknown[0x34];
	RpClump* pClump;
};
struct DushPlayerView {
	s8 playerno, characterno;
	u8 unknown[0x14A];
	DushMotionView mm;
};
enum RwBlendFunction {
	rwBLENDNA                       = 0,
	rwBLENDZERO                     = 1,
	rwBLENDONE                      = 2,
	rwBLENDSRCCOLOR                 = 3,
	rwBLENDINVSRCCOLOR              = 4,
	rwBLENDSRCALPHA                 = 5,
	rwBLENDINVSRCALPHA              = 6,
	rwBLENDDESTALPHA                = 7,
	rwBLENDINVDESTALPHA             = 8,
	rwBLENDDESTCOLOR                = 9,
	rwBLENDINVDESTCOLOR             = 10,
	rwBLENDSRCALPHASAT              = 11,
	rwBLENDFUNCTIONFORCEENUMSIZEINT = 0x7fffffff
};
enum RwCullMode {
	rwCULLMODENACULLMODE       = 0,
	rwCULLMODECULLNONE         = 1,
	rwCULLMODECULLBACK         = 2,
	rwCULLMODECULLFRONT        = 3,
	rwCULLMODEFORCEENUMSIZEINT = 0x7fffffff
};
extern "C" {
extern DushPlayerView* lbl_802AD0D0[8];
extern DushModeView* lbl_8042C180;
extern TObject* lbl_8042C2A0;
extern TObject* lbl_8042C110;
extern RwV3d lbl_80239978, lbl_80239984;
RpClump* fn_80150588(RpClump*);
s32 fn_80150958(RpClump*);
RpAtomic* fn_8005E394(RpClump*, RpAtomic*);
RpAtomic* fn_801491A8(RpAtomic*);
void fn_8005DA34(RpClump*);
void fn_8005D9F4(RpClump*);
s32 fn_8003E2E4(s32, s32, RwV3d*, sAngle*);
f32 fn_801990E0(RwV3d*, const RwV3d*);
f64 asin(f64);
f64 atan2(f64, f64);
f32 fn_800D7B00(s32);
f32 fn_800D7AE4(s32);
RwMatrix* fn_80195E44(RwMatrix*, const RwV3d*, s32);
RwMatrix* fn_80196050(RwMatrix*, const RwV3d*, s32);
RwMatrix* fn_80195790(RwMatrix*, const RwV3d*, f32, f32, s32);
RwFrame* fn_8019EB94(RwFrame*, const RwV3d*, s32);
RwFrame* fn_8019E880(RwFrame*);
}
static RpClump* pClump;
static RpMaterial* pMaterial;
static RpUVAnimAnimation* pUVAnim;
static UVFXInfo EffDushUvInfo;
static RwRGBA default_color[12]
    = { { 0, 0x5A, 0xAA, 0xFF }, { 0xF0, 0x19, 0x3C, 0xFF }, { 0xFA, 0xA5, 0x19, 0xFF },
	      { 0xFF, 0x80, 0, 0xFF }, { 0x60, 0, 0xFF, 0xFF }, { 0xFF, 0, 0xFF, 0xFF },
	      { 0xFF, 0, 0x60, 0xFF }, { 0x80, 0, 0xFF, 0xFF }, { 0xFF, 0x8C, 0x60, 0xFF },
	      { 0, 0xA0, 0xFF, 0xFF }, { 0, 0xA0, 0, 0xFF }, { 0xFF, 0, 0, 0xFF } };
static s32 time_previous;
char* CL_TObjEffDash = "TObjEffDash";

extern "C" {
s32 fn_80194294(s32, void*);    // render-state get
s32 fn_80194234(s32, void*);    // render-state set
s32 fn_8014FEF4(RpClump*);      // light count, verified GC lightList traversal
RpClump* fn_8014FF2C(RpClump*); // render
RpClump* fn_8014FFBC(RpClump*, RpAtomic* (*)(RpAtomic*, void*), void*);
RpAtomic* fn_8005BF88(RpAtomic*, void*);
s32 fn_8011B844(RpUVAnimAnimation*, f32);
void* fn_8005EA04(char*);
RpMaterial* fn_8005E410(RpClump*, RpMaterial*, char*);
void fn_8005DA34(RpClump*);
void fn_8005D9F4(RpClump*);
void fn_8005BF5C(RpClump*, UVFXInfo*);
extern void* lbl_8042C170;
}

void InitEffDush()
{
	if (!pClump) {
		pClump = (RpClump*)fn_8005EA04("EF_DUSH.DFF");
		if (pClump) {
			pMaterial = fn_8005E410(pClump, 0, "ef_chbl");
			fn_8005DA34(pClump);
			fn_8005D9F4(pClump);
		}
		pUVAnim = (RpUVAnimAnimation*)fn_8005EA04("EF_DUSH.UVB");
		if (pUVAnim && pMaterial) {
			EffDushUvInfo.uvAnim = pUVAnim;
			fn_8005BF5C(pClump, &EffDushUvInfo);
		}
	}
}

void EndEffDush()
{
	pClump    = 0;
	pMaterial = 0;
	pUVAnim   = 0;
}

EffDush::EffDush()
{
	SetEffDushMaterialColor(&default_color[0]);
	pClumpInstance = fn_80150588(pClump);
	if (pClumpInstance) {
		RpAtomic* pAtomic_Temp = fn_8005E394((RpClump*)pClumpInstance, 0);
		fn_801491A8(pAtomic_Temp);
		fn_8005DA34((RpClump*)pClumpInstance);
		fn_8005D9F4((RpClump*)pClumpInstance);
	}
}

EffDush::~EffDush()
{
	if (pClumpInstance) {
		fn_80150958((RpClump*)pClumpInstance);
		pClumpInstance = 0;
	}
}

void EffDush::SetEffDushMaterialColor(const RwRGBA* pVal)
{
	rgba = *pVal;
}

void EffDush::RenderEffDush()
{
	RwBlendFunction src, dst;
	RwCullMode cullmode;
	u32 ztest;
	s32 fog;
	fn_80194294(10, &src);
	fn_80194294(11, &dst);
	fn_80194294(20, &cullmode);
	fn_80194294(14, &fog);
	fn_80194234(10, (void*)5);
	fn_80194234(11, (void*)2);
	fn_80194234(20, (void*)1);
	fn_80194234(14, 0);
	fn_80194294(6, &ztest);
	if (lbl_8042C170)
		fn_80194234(6, (void*)1);
	else
		fn_80194234(6, 0);
	RpClump* pClump_Current = (RpClump*)pClumpInstance;
	// GC genuinely traps forever when this clump contains any lights.
	if (fn_8014FEF4(pClump_Current) > 0) {
		for (;;) {
		}
	}
	if (pMaterial) {
		pMaterial->color = rgba;
		s32 time_current = lbl_8042C180->modeswitchlws[2] + lbl_8042C180->modeswitchlws[3];
		if (time_previous != time_current) {
			f32 deltaTime_Temp = (f32)(time_current - time_previous);
			if (pMaterial && pUVAnim) {
				fn_8011B844(pUVAnim, deltaTime_Temp);
				fn_8014FFBC(pClump_Current, fn_8005BF88, &EffDushUvInfo);
			}
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

EffDash::EffDash(TObject* pTO, s32 pno)
    : TObject(pTO)
{
	ClassName = CL_TObjEffDash;
	DispTime  = sizeof(EffDash);
	playerno  = (s8)pno;
	alpha     = 255;
	timer     = 0;
	SetEffDushMaterialColor(&default_color[lbl_802AD0D0[pno]->characterno]);
}

EffDash::~EffDash() { }

void EffDash::Exec()
{
	if (timer > 10) {
		s32 alpha_Temp = alpha;
		alpha_Temp -= 48;
		if (alpha_Temp < 0)
			alpha_Temp = 0;
		alpha            = (u8)alpha_Temp;
		RwRGBA rgba_Temp = rgba;
		rgba_Temp.alpha  = alpha;
		SetEffDushMaterialColor(&rgba_Temp);
	} else
		++timer;
	if (alpha == 0) {
		Signal |= 1;
		return;
	}
	RwFrame* pFrame_Temp     = (RwFrame*)((RpClump*)pClumpInstance)->object.parent;
	RwMatrix* pMatrix_Effect = &pFrame_Temp->modelling;
	const s32 pno            = playerno;
	RwMatrix* pMatrix_Player = &((RwFrame*)lbl_802AD0D0[pno]->mm.pClump->object.parent)->modelling;
	RwV3d pos0, pos1, vSub_Temp, vScale_Temp;
	fn_8003E2E4(pno, 0, &pos0, 0);
	fn_8003E2E4(playerno, 1, &pos1, 0);
	vSub_Temp.x   = pos0.x - pos1.x;
	vSub_Temp.y   = pos0.y - pos1.y;
	vSub_Temp.z   = pos0.z - pos1.z;
	vScale_Temp.x = 1.0f;
	vScale_Temp.y = 1.0f;
	vScale_Temp.z = 1.0f;
	if (vSub_Temp.z * vSub_Temp.z + (vSub_Temp.x * vSub_Temp.x + vSub_Temp.y * vSub_Temp.y)
	    > 0.01f) {
		fn_801990E0(&vSub_Temp, &vSub_Temp);
		if (vSub_Temp.y >= 1.0f)
			ang3.x = -90.0f;
		else if (vSub_Temp.y <= -1.0f)
			ang3.x = 90.0f;
		else {
			f32 radians = (f32)asin(-vSub_Temp.y);
			ang3.x      = 0.005493164f * (s32)(10430.381f * radians);
		}
		f32 radians = (f32)atan2(vSub_Temp.x, vSub_Temp.z);
		ang3.y      = 0.005493164f * (s32)(10430.381f * radians);
		ang3.z      = 0.0f;
	}
	fn_80195E44(pMatrix_Effect, &vScale_Temp, 0);
	fn_80195790(pMatrix_Effect, &lbl_80239978, 1.0f - fn_800D7AE4((s32)(182.04445f * ang3.x)),
	    fn_800D7B00((s32)(182.04445f * ang3.x)), 2);
	fn_80195790(pMatrix_Effect, &lbl_80239984, 1.0f - fn_800D7AE4((s32)(182.04445f * ang3.y)),
	    fn_800D7B00((s32)(182.04445f * ang3.y)), 2);
	fn_80196050(pMatrix_Effect, &pMatrix_Player->pos, 2);
	RwV3d vOffset_Temp = { 0, 0, 0 };
	fn_8019EB94(pFrame_Temp, &vOffset_Temp, 1);
	fn_80195790(&pFrame_Temp->modelling, &lbl_80239984, 2.0f, 0.0f, 1);
	fn_8019E880(pFrame_Temp);
}

void EffDash::TDisp()
{
	RenderEffDush();
}

void SetEffectDash(s32 playerno)
{
	TObject* pTO_Parent = lbl_8042C2A0;
	if (!pTO_Parent)
		pTO_Parent = lbl_8042C110;
	new EffDash(pTO_Parent, playerno);
}
