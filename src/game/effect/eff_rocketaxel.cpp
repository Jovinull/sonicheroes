// Complete effect/eff_rocketaxel.cpp reconstructed from GC behavior and symbolic C++ metadata.
// Reversed ordinary definitions with whole-TU deferred emission preserve the owned
// layout; original source order and flags are unknown. See docs/eff-rocketaxel-unit-evidence.md.
#include "game/effect/eff_rocketaxel.h"
struct RwRGBA {
	u8 red, green, blue, alpha;
};
struct RwObject {
	u8 type, subType, flags, privateFlags;
	void* parent;
};
struct RpClump {
	RwObject object;
};
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
	RwLLLink *next, *prev;
};
struct RwFrame {
	RwObject object;
	RwLLLink inDirtyListLink;
	RwMatrix modelling, ltm;
};
// Only the referenced PLAYERWK and task-work members are modeled.
struct RocketPlayerView {
	u8 unknown[0x180];
	RpClump* pClump;
};
struct RocketMotionView {
	s16 mode;
};
struct RocketTaskPositionView {
	u8 unknown[8];
	RwV3d pos;
};
struct RocketTaskView {
	u8 unknown[0x38];
	RocketTaskPositionView* pWork;
};
extern "C" {
extern RocketPlayerView* lbl_802AD0D0[8];
extern RocketMotionView* lbl_802AD090[8];
extern RocketTaskView* lbl_802AD070[8];
extern TObject *lbl_8042C2A0, *lbl_8042C110;
extern RwV3d AxisX, AxisY, AxisZ;
s32 fn_80194294(s32, void*);
s32 fn_80194234(s32, void*);
RpClump* fn_8014FF2C(RpClump*);
RpClump* fn_80150588(RpClump*);
s32 fn_80150958(RpClump*);
void objRpClumpForAllGeometrysToIgnoreLights__FP7RpClump(RpClump*);
void objRpClumpForAllGeometrysToModulateMaterialColor__FP7RpClump(RpClump*);
void* objPointerReadFromClumpAnim__FPc(const char*);
RpMaterial* objRpClumpGetMaterialWithSpecificTexture__FP7RpClumpP10RpMaterialPc(
    RpClump*, RpMaterial*, char*);
RwFrame* fn_8019EB94(RwFrame*, const RwV3d*, s32);
RwFrame* fn_8019EC30(RwFrame*, const RwV3d*, s32);
RwFrame* fn_8019ED68(RwFrame*, const RwV3d*, f32, s32);
f32 AdjustFloat__Ffff(f32, f32, f32);
f32 fn_801990E0(RwV3d*, const RwV3d*);
s32 fn_8003E2E4(s32, s32, RwV3d*, sAngle*);
f64 asin(f64);
f64 atan2(f64, f64);
s32 rand();
}
static RpClump *pClumpRocketAxel, *pClumpRocketHit, *pClumpRocketHitB;
static RpMaterial *pMaterialRocketAxel, *pMaterialRocketHit, *pMaterialRocketHitB;
char* CL_EffRocketHit  = "EffRocketHit";
char* CL_EffRocketHitB = "EffRocketHitB";
char* CL_EffRocketAxel = "EffRocketAxel";
char* CL_EffRocketJump = "EffRocketJump";

void InitEffRocketAxel()
{
	if (!pClumpRocketAxel) {
		pClumpRocketAxel = (RpClump*)objPointerReadFromClumpAnim__FPc("EF_ROCKET_HITB.DFF");
		if (pClumpRocketAxel) {
			pMaterialRocketAxel
			    = objRpClumpGetMaterialWithSpecificTexture__FP7RpClumpP10RpMaterialPc(
			        pClumpRocketAxel, 0, 0);
			objRpClumpForAllGeometrysToIgnoreLights__FP7RpClump(pClumpRocketAxel);
			objRpClumpForAllGeometrysToModulateMaterialColor__FP7RpClump(pClumpRocketAxel);
		}
	}
	if (!pClumpRocketHit) {
		pClumpRocketHit = (RpClump*)objPointerReadFromClumpAnim__FPc("EF_ROCKET_HITA.DFF");
		if (pClumpRocketHit) {
			pMaterialRocketHit
			    = objRpClumpGetMaterialWithSpecificTexture__FP7RpClumpP10RpMaterialPc(
			        pClumpRocketHit, 0, 0);
			objRpClumpForAllGeometrysToIgnoreLights__FP7RpClump(pClumpRocketHit);
			objRpClumpForAllGeometrysToModulateMaterialColor__FP7RpClump(pClumpRocketHit);
		}
	}
	if (!pClumpRocketHitB) {
		pClumpRocketHitB = (RpClump*)objPointerReadFromClumpAnim__FPc("EF_ROCKET_HITC.DFF");
		if (pClumpRocketHitB) {
			pMaterialRocketHitB
			    = objRpClumpGetMaterialWithSpecificTexture__FP7RpClumpP10RpMaterialPc(
			        pClumpRocketHitB, 0, 0);
			objRpClumpForAllGeometrysToIgnoreLights__FP7RpClump(pClumpRocketHitB);
			objRpClumpForAllGeometrysToModulateMaterialColor__FP7RpClump(pClumpRocketHitB);
		}
	}
}
void EndEffRocketAxel()
{
	pClumpRocketAxel    = 0;
	pClumpRocketHit     = 0;
	pClumpRocketHitB    = 0;
	pMaterialRocketAxel = 0;
	pMaterialRocketHit  = 0;
	pMaterialRocketHitB = 0;
}
void SetEffectRocketHit(s32 playerno)
{
	TObject* parent = lbl_8042C2A0;
	if (!parent)
		parent = lbl_8042C110;
	new EffRocketHit(parent, playerno);
}
void SetEffectRocketAxel(s32 playerno)
{
	TObject* parent = lbl_8042C2A0;
	if (!parent)
		parent = lbl_8042C110;
	new EffRocketAxel(parent, playerno);
}
void SetEffectRocketJump(s32 playerno)
{
	TObject* parent = lbl_8042C2A0;
	if (!parent)
		parent = lbl_8042C110;
	new EffRocketJump(parent, playerno);
}
EffRocketHit::EffRocketHit(TObject* parent, s32 pno)
    : TObject(parent)
{
	playerno       = (s8)pno;
	alpha          = 255;
	rotate         = 0;
	scale          = 0.6f;
	pClumpInstance = fn_80150588(pClumpRocketHit);
	if (pClumpInstance) {
		objRpClumpForAllGeometrysToIgnoreLights__FP7RpClump((RpClump*)pClumpInstance);
		objRpClumpForAllGeometrysToModulateMaterialColor__FP7RpClump((RpClump*)pClumpInstance);
	}
	ClassName = CL_EffRocketHit;
	DispTime  = sizeof(EffRocketHit);
}
EffRocketHit::~EffRocketHit()
{
	if (pClumpInstance) {
		fn_80150958((RpClump*)pClumpInstance);
		pClumpInstance = 0;
	}
}
void EffRocketHit::Exec()
{
	rotate += 60;
	if (rotate > 360) {
		if (GetChildCount() > 0)
			return;
		Signal |= 1;
		return;
	}
	scale = AdjustFloat__Ffff(scale, 2.0f, 0.28f);
	if (rotate > 180) {
		s32 a = alpha;
		a -= 128;
		if (a < 0)
			a = 0;
		alpha = (u8)a;
	}
	if (rotate == 120) {
		new EffRocketHitB(this, playerno);
		new EffRocketHitB(this, playerno);
		new EffRocketHitB(this, playerno);
	}
	RwFrame* pFrame   = (RwFrame*)((RpClump*)pClumpInstance)->object.parent;
	pFrame->modelling = ((RwFrame*)lbl_802AD0D0[playerno]->pClump->object.parent)->modelling;
	RwV3d offset      = { 0.0f, 8.0f, 0.0f };
	fn_8019EB94(pFrame, &offset, 1);
	fn_8019ED68(pFrame, &AxisZ, (f32)rotate, 1);
}
void EffRocketHit::TDisp()
{
	s32 src, dst, cull;
	fn_80194294(10, &src);
	fn_80194294(11, &dst);
	fn_80194294(20, &cull);
	fn_80194234(10, (void*)5);
	fn_80194234(11, (void*)2);
	fn_80194234(20, (void*)1);
	RpClump* pClump = (RpClump*)pClumpInstance;
	if (pMaterialRocketHit) {
		RwRGBA rgba_Temp;
		rgba_Temp.red             = pMaterialRocketHit->color.red;
		rgba_Temp.green           = pMaterialRocketHit->color.green;
		rgba_Temp.blue            = pMaterialRocketHit->color.blue;
		rgba_Temp.alpha           = alpha;
		pMaterialRocketHit->color = rgba_Temp;
	}
	fn_8014FF2C(pClump);
	fn_80194234(20, (void*)cull);
	fn_80194234(10, (void*)src);
	fn_80194234(11, (void*)dst);
}
EffRocketHitB::EffRocketHitB(TObject* parent, s32 pno)
    : TObject(parent)
{
	playerno       = (s8)pno;
	alpha          = 255;
	rotate         = 0;
	rotateBase     = (s16)(360.0f * (0.000030517578125f * rand()));
	scale          = 1.0f + 0.25f * (0.000030517578125f * rand());
	scaleMax       = 1.4f + scale;
	vOffset.x      = 0.0f;
	vOffset.y      = 8.0f;
	vOffset.z      = 0.0f;
	pClumpInstance = fn_80150588(pClumpRocketHitB);
	if (pClumpInstance) {
		objRpClumpForAllGeometrysToIgnoreLights__FP7RpClump((RpClump*)pClumpInstance);
		objRpClumpForAllGeometrysToModulateMaterialColor__FP7RpClump((RpClump*)pClumpInstance);
	}
	ClassName = CL_EffRocketHitB;
	DispTime  = sizeof(EffRocketHitB);
}
EffRocketHitB::~EffRocketHitB()
{
	if (pClumpInstance) {
		fn_80150958((RpClump*)pClumpInstance);
		pClumpInstance = 0;
	}
}
void EffRocketHitB::Exec()
{
	rotate += 30;
	if (rotate > 360) {
		Signal |= 1;
		return;
	}
	scale = AdjustFloat__Ffff(scale, scaleMax, 0.083f);
	if (rotate > 300) {
		s32 a = alpha;
		a -= 128;
		if (a < 0)
			a = 0;
		alpha = (u8)a;
	}
	RwFrame* pFrame   = (RwFrame*)((RpClump*)pClumpInstance)->object.parent;
	pFrame->modelling = ((RwFrame*)lbl_802AD0D0[playerno]->pClump->object.parent)->modelling;
	fn_8019EB94(pFrame, &vOffset, 1);
	fn_8019ED68(pFrame, &AxisZ, (f32)(rotate + rotateBase), 1);
}
void EffRocketHitB::TDisp()
{
	s32 src, dst, cull;
	fn_80194294(10, &src);
	fn_80194294(11, &dst);
	fn_80194294(20, &cull);
	fn_80194234(10, (void*)5);
	fn_80194234(11, (void*)2);
	fn_80194234(20, (void*)1);
	RpClump* pClump = (RpClump*)pClumpInstance;
	if (pMaterialRocketHitB) {
		RwRGBA rgba_Temp;
		rgba_Temp.red              = pMaterialRocketHitB->color.red;
		rgba_Temp.green            = pMaterialRocketHitB->color.green;
		rgba_Temp.blue             = pMaterialRocketHitB->color.blue;
		rgba_Temp.alpha            = alpha;
		pMaterialRocketHitB->color = rgba_Temp;
	}
	fn_8014FF2C(pClump);
	fn_80194234(20, (void*)cull);
	fn_80194234(10, (void*)src);
	fn_80194234(11, (void*)dst);
}
EffRocketAxel::EffRocketAxel(TObject* parent, s32 pno)
    : TObject(parent)
{
	playerno       = (s8)pno;
	alpha          = 255;
	rotate         = 0;
	pClumpInstance = fn_80150588(pClumpRocketAxel);
	if (pClumpInstance) {
		objRpClumpForAllGeometrysToIgnoreLights__FP7RpClump((RpClump*)pClumpInstance);
		objRpClumpForAllGeometrysToModulateMaterialColor__FP7RpClump((RpClump*)pClumpInstance);
	}
	ClassName = CL_EffRocketAxel;
	DispTime  = sizeof(EffRocketAxel);
}
EffRocketAxel::~EffRocketAxel()
{
	if (pClumpInstance) {
		fn_80150958((RpClump*)pClumpInstance);
		pClumpInstance = 0;
	}
}
void EffRocketAxel::Exec()
{
	rotate += 60;
	while (rotate > 360)
		rotate -= 360;
	RocketMotionView* pMotion = lbl_802AD090[playerno];
	if (pMotion && pMotion->mode != 54) {
		s32 a = alpha;
		a -= 32;
		if (a < 0)
			a = 0;
		alpha = (u8)a;
	}
	if (!alpha) {
		Signal |= 1;
		return;
	}
	RwFrame* pFrame   = (RwFrame*)((RpClump*)pClumpInstance)->object.parent;
	pFrame->modelling = ((RwFrame*)lbl_802AD0D0[playerno]->pClump->object.parent)->modelling;
	RwV3d offset      = { 0.0f, 6.0f, -5.0f };
	fn_8019EB94(pFrame, &offset, 1);
	fn_8019ED68(pFrame, &AxisZ, (f32)rotate, 1);
	fn_8019ED68(pFrame, &AxisY, 180.0f, 1);
}
void EffRocketAxel::TDisp()
{
	s32 src, dst, cull;
	fn_80194294(10, &src);
	fn_80194294(11, &dst);
	fn_80194294(20, &cull);
	fn_80194234(10, (void*)5);
	fn_80194234(11, (void*)2);
	fn_80194234(20, (void*)1);
	RpClump* pClump = (RpClump*)pClumpInstance;
	if (pMaterialRocketAxel) {
		RwRGBA rgba_Temp;
		rgba_Temp.red              = pMaterialRocketAxel->color.red;
		rgba_Temp.green            = pMaterialRocketAxel->color.green;
		rgba_Temp.blue             = pMaterialRocketAxel->color.blue;
		rgba_Temp.alpha            = alpha;
		pMaterialRocketAxel->color = rgba_Temp;
	}
	fn_8014FF2C(pClump);
	fn_80194234(20, (void*)cull);
	fn_80194234(10, (void*)src);
	fn_80194234(11, (void*)dst);
}
EffRocketJump::EffRocketJump(TObject* parent, s32 pno)
    : TObject(parent)
{
	playerno       = (s8)pno;
	alpha          = 255;
	rotate         = 0;
	pClumpInstance = fn_80150588(pClumpRocketAxel);
	if (pClumpInstance) {
		objRpClumpForAllGeometrysToIgnoreLights__FP7RpClump((RpClump*)pClumpInstance);
		objRpClumpForAllGeometrysToModulateMaterialColor__FP7RpClump((RpClump*)pClumpInstance);
	}
	ClassName = CL_EffRocketJump;
	DispTime  = sizeof(EffRocketJump);
}
EffRocketJump::~EffRocketJump()
{
	if (pClumpInstance) {
		fn_80150958((RpClump*)pClumpInstance);
		pClumpInstance = 0;
	}
}
void EffRocketJump::Exec()
{
	RocketMotionView* twp;
	s32 alpha_Temp;
	RwFrame* pFrame_Temp;
	RwV3d pos0, pos1, vSub_Temp;

	rotate += 60;
	while (rotate > 360)
		rotate -= 360;
	twp = lbl_802AD090[playerno];
	if (twp && twp->mode != 7 && twp->mode != 15) {
		alpha_Temp = alpha;
		alpha_Temp -= 32;
		if (alpha_Temp < 0)
			alpha_Temp = 0;
		alpha = (u8)alpha_Temp;
	}
	if (alpha == 0) {
		Signal |= 1;
		return;
	}
	pFrame_Temp = (RwFrame*)((RpClump*)pClumpInstance)->object.parent;
	fn_8003E2E4(playerno, 0, &pos0, 0);
	fn_8003E2E4(playerno, 1, &pos1, 0);
	vSub_Temp.x = pos0.x - pos1.x;
	vSub_Temp.y = pos0.y - pos1.y;
	vSub_Temp.z = pos0.z - pos1.z;
	if (vSub_Temp.z * vSub_Temp.z + (vSub_Temp.x * vSub_Temp.x + vSub_Temp.y * vSub_Temp.y)
	    > 0.01f) {
		f32 pitch, yaw;
		fn_801990E0(&vSub_Temp, &vSub_Temp);
		if (vSub_Temp.y >= 1.0f) {
			pitch = -90.0f;
			yaw   = 0.0f;
		} else if (vSub_Temp.y <= -1.0f) {
			pitch = 90.0f;
			yaw   = 0.0f;
		} else {
			f32 radians = (f32)asin(-vSub_Temp.y);
			pitch       = (360.0f / 65536.0f) * (s32)(10430.380859375f * radians);
			radians     = (f32)atan2(vSub_Temp.x, vSub_Temp.z);
			yaw         = (360.0f / 65536.0f) * (s32)(10430.380859375f * radians);
		}
		fn_8019EB94(pFrame_Temp, &lbl_802AD070[playerno]->pWork->pos, 0);
		fn_8019ED68(pFrame_Temp, &AxisY, yaw, 1);
		fn_8019ED68(pFrame_Temp, &AxisX, pitch, 1);
		RwV3d vOffset_Temp = { 0.0f, 0.0f, 5.0f };
		fn_8019EB94(pFrame_Temp, &vOffset_Temp, 1);
	} else {
		pFrame_Temp->modelling
		    = ((RwFrame*)lbl_802AD0D0[playerno]->pClump->object.parent)->modelling;
		RwV3d vOffset_Temp = { 0.0f, 5.0f, 5.0f };
		fn_8019EB94(pFrame_Temp, &vOffset_Temp, 1);
	}
	fn_8019ED68(pFrame_Temp, &AxisZ, (f32)rotate, 1);
	RwV3d vScale_Temp = { 0.6f, 0.6f, 0.6f };
	fn_8019EC30(pFrame_Temp, &vScale_Temp, 1);
}
void EffRocketJump::TDisp()
{
	s32 src, dst, cull;
	fn_80194294(10, &src);
	fn_80194294(11, &dst);
	fn_80194294(20, &cull);
	fn_80194234(10, (void*)5);
	fn_80194234(11, (void*)2);
	fn_80194234(20, (void*)1);
	RpClump* pClump = (RpClump*)pClumpInstance;
	if (pMaterialRocketAxel) {
		RwRGBA rgba_Temp;
		rgba_Temp.red              = pMaterialRocketAxel->color.red;
		rgba_Temp.green            = pMaterialRocketAxel->color.green;
		rgba_Temp.blue             = pMaterialRocketAxel->color.blue;
		rgba_Temp.alpha            = alpha;
		pMaterialRocketAxel->color = rgba_Temp;
	}
	fn_8014FF2C(pClump);
	fn_80194234(20, (void*)cull);
	fn_80194234(10, (void*)src);
	fn_80194234(11, (void*)dst);
}