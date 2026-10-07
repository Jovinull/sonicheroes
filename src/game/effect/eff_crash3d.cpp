// Complete effect/eff_crash3d.cpp reconstruction from GC behavior and C++ metadata.
// Definition ordering and deferred inlining reconstruct the surviving emission order.
// Bounded source/literal-order trials leave one compiler-pool atom permutation;
// see docs/eff-crash3d-unit-evidence.md for the guarded remainder and source path out.
#include "game/effect/eff_crash3d.h"
struct RwObject {
	u8 type, subType, flags, privateFlags;
	void* parent;
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
struct RpClump {
	RwObject object;
};
struct RwSphere {
	RwV3d center;
	f32 radius;
};
struct RpAtomic {
	RwObject object;
	u8 unaccessed08[0x14];
	RwSphere boundingSphere, worldBoundingSphere;
	RpClump* clump;
	void* linkNext;
	void* linkPrev;
	void* renderCallBack;
	s32 interpolatorFlags;
};
struct RpHAnimNodeInfo {
	s32 nodeID, nodeIndex, flags;
	RwFrame* pFrame;
};
struct RpHAnimHierarchy {
	s32 flags, numNodes;
	RwMatrix* pMatrixArray;
	void* pMatrixArrayUnaligned;
	RpHAnimNodeInfo* pNodeInfo;
	RwFrame* parentFrame;
};
struct CrashModeView {
	s8 modeswitchflags[0x28];
	s32 modeswitchlws[6];
};
struct CrashStageView {
	u8 unknown[0x18];
	s32 state;
};
extern "C" {
extern CrashModeView* lbl_8042C180;
extern CrashStageView lbl_8029C310;
extern RwMatrix* lbl_8042C178;
extern RwV3d lbl_80239978, lbl_80239984, lbl_80239990;
extern TObject* lbl_8042C2A0;
extern TObject* lbl_8042C110;
f64 __fabs(f64);
s32 rand();
f32 fn_801991B4(const RwV3d*);
f32 fn_800D7B00(s32);
f32 fn_800D7AE4(s32);
RwMatrix* fn_80195790(RwMatrix*, const RwV3d*, f32, f32, s32);
RwMatrix* fn_80196050(RwMatrix*, const RwV3d*, s32);
RwMatrix* fn_80195E44(RwMatrix*, const RwV3d*, s32);
RwMatrix* fn_80195674(RwMatrix*, const RwMatrix*, const RwMatrix*);
RwFrame* fn_8019EB94(RwFrame*, const RwV3d*, s32);
RwFrame* fn_8019EC30(RwFrame*, const RwV3d*, s32);
RwFrame* fn_8019E880(RwFrame*);
void fn_800D1288(RwMatrix*, s32*, s32*, s32*);
void fn_8014F854(RpAtomic*);
RpClump* fn_80150588(RpClump*);
s32 fn_80150958(RpClump*);
RpClump* fn_8014FF2C(RpClump*);
RpClump* fn_8014FFBC(RpClump*, RpAtomic* (*)(RpAtomic*, void*), void*);
void fn_8005D5C8(RpClump*, u32);
RpHAnimHierarchy* fn_800F3074(RpClump*);
RpHAnimHierarchy* fn_8013F3A4(RpHAnimHierarchy*);
s32 fn_80194294(s32, void*);
s32 fn_80194234(s32, void*);
void fn_8001F2EC();
void fn_8001F2D4();
void fn_8001F404(RwMatrix*);
void fn_8001F144(RwMatrix*, s32);
void fn_8001F1C8(RwMatrix*, s32);
void fn_8001F088(RwMatrix*, RwV3d*, RwV3d*);
}
s32 gMoveTime                   = 160;
f32 gMoveTimeRnd                = 55.0f;
s32 gBlinkTime                  = 45;
char* CL_TObjEffCrash3D         = "TObjEffCrash3D";
char* CL_TObjEffCrash3DChildObj = "TObjEffCrash3DChildObj";
static RpAtomic* sFindAtomic;
static RpAtomic* SearchAtomicFromFrameCallBack(RpAtomic*, void*);

extern "C" {
extern TObject* lbl_8042C2A0;
extern TObject* lbl_8042C110;
s32 fn_80017830(TObject*); // GC return observed, metadata method name not established here.

s32 fn_80150958(RpClump*);
}

s32 setobjCheckRangeOut2(const RwV3d*, f32);

// Normal ctor signature below assumes GC lightNo inserted after type. This is
// a documented GC contract extension, not a recovered PS2 mangled signature.

void SetEffectCrash3D(TObject* ptp, RwV3d* pPosition0, sAngle* pAngle0, f32 spd0,
    ENUM_EFF_CRASH3D_TYPE type, f32 fParam, f32 yGroundPos, RpClump** pClumps, Crash3DObjs* pObjs,
    s16 numKinds)
{
	if (!ptp) {
		ptp = lbl_8042C2A0;
		if (!ptp)
			ptp = lbl_8042C110;
	}
	new TObjEffCrash3D(
	    ptp, pPosition0, pAngle0, spd0, type, -1, fParam, yGroundPos, pClumps, pObjs, numKinds);
}
extern "C" void fn_80102DEC(TObject* ptp, RwV3d* pPosition0, sAngle* pAngle0, f32 spd0,
    ENUM_EFF_CRASH3D_TYPE type, f32 fParam, f32 yGroundPos, s16 lightNo, RpClump** pClumps,
    Crash3DObjs* pObjs, s16 numKinds)
{
	if (!ptp) {
		ptp = lbl_8042C2A0;
		if (!ptp)
			ptp = lbl_8042C110;
	}
	new TObjEffCrash3D(ptp, pPosition0, pAngle0, spd0, type, lightNo, fParam, yGroundPos, pClumps,
	    pObjs, numKinds);
}
void SetEffectCrash3D_R(TObject* ptp, RwV3d* pPosition0, sAngle* pAngle0, RwV3d* pPower0, f32 spd0,
    f32 yGroundPos, RpClump* pClumpCrashObj)
{
	if (!ptp) {
		ptp = lbl_8042C2A0;
		if (!ptp)
			ptp = lbl_8042C110;
	}
	new TObjEffCrash3DR(ptp, pPosition0, pAngle0, pPower0, 0, spd0, yGroundPos, 1, 0, -1,
	    (RwBlendFunction)-1, pClumpCrashObj);
}
void SetEffectCrash3D_R(TObject* ptp, RwV3d* pPosition0, sAngle* pAngle0, RwV3d* pPower0,
    RwV3d* pScale0, f32 spd0, f32 yGroundPos, s32 checkGroundFlag, s16 time0,
    RpClump* pClumpCrashObj)
{
	if (!ptp) {
		ptp = lbl_8042C2A0;
		if (!ptp)
			ptp = lbl_8042C110;
	}
	new TObjEffCrash3DR(ptp, pPosition0, pAngle0, pPower0, pScale0, spd0, yGroundPos,
	    checkGroundFlag, time0, -1, (RwBlendFunction)-1, pClumpCrashObj);
}
void SetEffectCrash3D_R(TObject* ptp, RwV3d* pPosition0, sAngle* pAngle0, RwV3d* pPower0,
    RwV3d* pScale0, f32 spd0, f32 yGroundPos, s32 checkGroundFlag, s16 time0, s16 lightNo,
    RwBlendFunction blend, RpClump* pClumpCrashObj)
{
	if (!ptp) {
		ptp = lbl_8042C2A0;
		if (!ptp)
			ptp = lbl_8042C110;
	}
	new TObjEffCrash3DR(ptp, pPosition0, pAngle0, pPower0, pScale0, spd0, yGroundPos,
	    checkGroundFlag, time0, lightNo, blend, pClumpCrashObj);
}
TObjEffCrash3D::TObjEffCrash3D(TObject* ptp, RwV3d* pPosition0, sAngle* pAngle0, f32 spd0,
    ENUM_EFF_CRASH3D_TYPE typeEffCrash3D, s16 lightNo, f32 fParam, f32 yGroundPos,
    RpClump** pClumpCrashObjs, Crash3DObjs* pCrash3DObjs, s16 numKindsObjs)
    : TObject(ptp)
{
	ClassName = CL_TObjEffCrash3D;
	DispTime  = sizeof(*this);
	if (pPosition0) {
		pos.x = pPosition0->x;
		pos.y = pPosition0->y;
		pos.z = pPosition0->z;
	} else
		pos.x = pos.y = pos.z = 0;
	if (pAngle0) {
		ang.x = pAngle0->x;
		ang.y = pAngle0->y;
		ang.z = pAngle0->z;
	} else
		ang.x = ang.y = ang.z = 0;
	for (s32 i = 0; i < numKindsObjs; ++i) {
		for (s32 j = 0; j < pCrash3DObjs[i].num_objs; ++j) {
			new TObjEffCrash3DChildObj(this, pPosition0, pAngle0, spd0, pClumpCrashObjs[i],
			    typeEffCrash3D, fParam, yGroundPos, lightNo);
		}
	}
}
TObjEffCrash3D::~TObjEffCrash3D() { }
void TObjEffCrash3D::Exec()
{
	if (setobjCheckRangeOut2(&pos, 225000000.0f))
		Signal |= 1;
	else if (!fn_80017830(this))
		Signal |= 1;
}
TObjEffCrash3DChildObj::TObjEffCrash3DChildObj(TObject* ptp, RwV3d* pPos, sAngle* pAng, f32 spd0,
    RpClump* pClump, ENUM_EFF_CRASH3D_TYPE typeEffCrash3D, f32 fParam, f32 yGroundPos, s16 lightNo)
    : TObject(ptp)
{
	ClassName = CL_TObjEffCrash3DChildObj;
	DispTime  = sizeof(*this);
	if (pPos) {
		pos.x = pPos->x;
		pos.y = pPos->y;
		pos.z = pPos->z;
	} else
		pos.x = pos.y = pos.z = 0;
	if (pAng) {
		ang.x = pAng->x;
		ang.y = pAng->y;
		ang.z = pAng->z;
	} else
		ang.x = ang.y = ang.z = 0;
	mode         = CRASH_EffCrash3DMode;
	timer        = (s16)(gMoveTime + (s32)(gMoveTimeRnd * (0.000030517578125f * rand())));
	alpha        = 1;
	y_ground_pos = yGroundPos;
	ang_spd.x    = (f32)(s32)(182.04444885253906f * (0.1f * (0.000030517578125f * rand() - 0.5f)));
	ang_spd.y    = (f32)(s32)(182.04444885253906f * (0.06f * (0.000030517578125f * rand() - 0.5f)));
	ang_spd.z    = (f32)(s32)(182.04444885253906f * (0.05f * (0.000030517578125f * rand() - 0.5f)));
	RwV3d vec;
	f32 f;
	switch (typeEffCrash3D) {
		case ENUM_EFF_CRASH3D_TYPE_CUBE:
			ang.x = (s32)(182.04444885253906f
			    * (90.0f * (s32)(36.0f * (2.0f * (0.000030517578125f * rand() - 0.5f)))));
			ang.y = pAng->y
			    + (s32)(182.04444885253906f
			        * (90.0f * (s32)(36.0f * (2.0f * (0.000030517578125f * rand() - 0.5f)))));
			ang.z = 0;
			vec.x = 0;
			vec.y = fParam;
			vec.z = 0;
			fn_8001F2EC();
			fn_8001F404(0);
			fn_80196050(lbl_8042C178, pPos, 1);
			fn_8001F144(0, pAng->y);
			{

				fn_8001F144(0,
				    (s32)(182.04444885253906f
				        * (30.0f * (2.0f * (0.000030517578125f * rand() - 0.5f))))
				        + (s32)(180.0f * (0.000030517578125f * rand() - 0.5f)) * 16384);
			}
			{

				fn_8001F1C8(0,
				    (s32)(182.04444885253906f
				        * (30.0f * (2.0f * (0.000030517578125f * rand() - 0.5f))))
				        + (s32)(180.0f * (0.000030517578125f * rand() - 0.5f)) * 16384);
			}
			fn_8001F088(0, &vec, &pos);
			fn_8001F2D4();
			break;
		case ENUM_EFF_CRASH3D_TYPE_SPHERE:
		default:
			ang.x = (s32)(182.04444885253906f
			    * (360.0f * (2.0f * (0.000030517578125f * rand() - 0.5f))));
			ang.y = (s32)(182.04444885253906f
			    * (360.0f * (2.0f * (0.000030517578125f * rand() - 0.5f))));
			ang.z = 0;
			vec.x = 0;
			vec.y = fParam;
			vec.z = 0;
			fn_8001F2EC();
			fn_8001F404(0);
			fn_80196050(lbl_8042C178, pPos, 1);
			fn_8001F144(0, pAng->y);
			fn_8001F144(0,
			    (s32)(182.04444885253906f
			        * (360.0f * (2.0f * (0.000030517578125f * rand() - 0.5f)))));
			fn_8001F1C8(0,
			    (s32)(182.04444885253906f
			        * (360.0f * (2.0f * (0.000030517578125f * rand() - 0.5f)))));
			fn_8001F088(0, &vec, &pos);
			fn_8001F2D4();
			break;
	}
	vec.x = pos.x - pPos->x;
	vec.y = pos.y - pPos->y;
	vec.z = pos.z - pPos->z;
	f     = spd0 / fn_801991B4(&vec);
	vec.x *= f;
	vec.y *= f;
	vec.z *= f;
	spd.x            = vec.x;
	spd.y            = vec.y;
	spd.z            = vec.z;
	mode             = CRASH_EffCrash3DMode;
	p_clump_instance = fn_80150588(pClump);
	if (!p_clump_instance) {
		Signal |= 1;
		return;
	}
	if (lightNo == -1)
		fn_8005D5C8((RpClump*)p_clump_instance, 4);
	else
		fn_8005D5C8((RpClump*)p_clump_instance, lightNo);
	SetPosition();
	ignore_time_stop_flag = lbl_8042C180->modeswitchflags[0x1F] != 0;
}
TObjEffCrash3DChildObj::~TObjEffCrash3DChildObj()
{
	if (p_clump_instance) {
		fn_80150958((RpClump*)p_clump_instance);
		p_clump_instance = 0;
	}
}
void TObjEffCrash3DChildObj::SetPosition()
{
	RwFrame* frame = (RwFrame*)((RpClump*)p_clump_instance)->object.parent;
	fn_8019EB94(frame, &pos, 0);
	fn_80195790(&frame->modelling, &lbl_80239990, 1.0f - fn_800D7AE4(ang.z), fn_800D7B00(ang.z), 1);
	fn_8019E880(frame);
	fn_80195790(&frame->modelling, &lbl_80239984, 1.0f - fn_800D7AE4(ang.y), fn_800D7B00(ang.y), 1);
	fn_8019E880(frame);
	fn_80195790(&frame->modelling, &lbl_80239978, 1.0f - fn_800D7AE4(ang.x), fn_800D7B00(ang.x), 1);
	fn_8019E880(frame);
}
void TObjEffCrash3DChildObj::Exec()
{
	s32 stageMode = lbl_8029C310.state;
	if (stageMode == 1 || (u32)(stageMode - 2) <= 3 || (Parent->Signal & 1)) {
		Signal |= 1;
		return;
	}
	if (!ignore_time_stop_flag && lbl_8042C180->modeswitchflags[0x1F])
		return;
	switch (lbl_8042C180->modeswitchflags[0x20]) {
		case 0:
			break;
		default:
			return;
	}
	pos.x += spd.x;
	pos.y += spd.y;
	pos.z += spd.z;
	if (y_ground_pos >= pos.y) {
		spd.x *= 0.989f;
		spd.z *= 0.989f;
		pos.y = y_ground_pos;
		if ((f32)__fabs(spd.y) < 0.445f) {
			spd.y = 0;
			spd.x *= 0.6f;
			spd.z *= 0.6f;
			ang_spd.x = ang_spd.y = ang_spd.z = 0;
		} else {
			spd.y *= -0.6f;
			ang_spd.x *= 0.6f;
			ang_spd.y *= 0.6f;
			ang_spd.z *= 0.6f;
		}
	} else {
		spd.x *= 0.989f;
		spd.y = 0.989f * spd.y - 0.089f;
		spd.z *= 0.989f;
	}
	ang.x += (s32)(182.04444885253906f * ang_spd.x);
	ang.y += (s32)(182.04444885253906f * ang_spd.y);
	ang.z += (s32)(182.04444885253906f * ang_spd.z);
	ang_spd.x *= 0.989f;
	ang_spd.y *= 0.989f;
	ang_spd.z *= 0.989f;
	switch (mode) {
		case CRASH_EffCrash3DMode:
		case BLINX_EffCrash3DMode:
			--timer;
			if (mode != BLINX_EffCrash3DMode && (f32)__fabs(fn_801991B4(&spd)) < 0.01f) {
				mode = BLINX_EffCrash3DMode;
				if (timer >= gBlinkTime)
					timer = (s16)gBlinkTime;
			}
			if (alpha <= 0 || timer <= 0) {
				mode  = END_EffCrash3DMode;
				timer = 0;
			}
			SetPosition();
			break;
		case END_EffCrash3DMode:
			Signal |= 1;
			break;
	}
}
void TObjEffCrash3DChildObj::Disp()
{
	if (!lbl_8042C180->modeswitchflags[0x20]) {
		if (mode != BLINX_EffCrash3DMode || timer % 2 == 0)
			fn_8014FF2C((RpClump*)p_clump_instance);
	}
}
void TObjEffCrash3DChildObj::TDisp() { }
TObjEffCrash3DR::TObjEffCrash3DR(TObject* ptp, RwV3d* pPosition0, sAngle* pAngle0, RwV3d* pPower0,
    RwV3d* pScale0, f32 spd0, f32 yGroundPos, s32 checkGroundFlag, s16 time0, s16 lightNo,
    RwBlendFunction blend0, RpClump* pClumpCrashObj)
    : TObject(ptp)
{
	if (pPosition0) {
		pos.x = pPosition0->x;
		pos.y = pPosition0->y;
		pos.z = pPosition0->z;
	} else
		pos.x = pos.y = pos.z = 0;
	if (pAngle0) {
		ang.x = pAngle0->x;
		ang.y = pAngle0->y;
		ang.z = pAngle0->z;
	} else
		ang.x = ang.y = ang.z = 0;
	RwV3d pow, scl;
	if (pPower0) {
		pow.x = pPower0->x;
		pow.y = pPower0->y;
		pow.z = pPower0->z;
	} else
		pow.x = pow.y = pow.z = 0;
	if (pScale0) {
		scl.x = pScale0->x;
		scl.y = pScale0->y;
		scl.z = pScale0->z;
	} else
		scl.x = scl.y = scl.z = 1;
	blend            = blend0;
	p_clump_instance = fn_80150588(pClumpCrashObj);
	if (!p_clump_instance) {
		Signal |= 1;
		return;
	}
	if (lightNo == -1)
		fn_8005D5C8(p_clump_instance, 4);
	else
		fn_8005D5C8(p_clump_instance, lightNo);
	hierarchy = fn_800F3074(p_clump_instance);
	if (hierarchy)
		fn_8013F3A4(hierarchy);
	if (hierarchy) {
		for (s32 i = 1; i < hierarchy->numNodes; ++i) {
			RwFrame* pFrame = SearchNodeFrameFromNodeID(i);
			if (!pFrame)
				break;
			RpAtomic* pAtomic = SearchAtomicFromFrame(pFrame);
			if (pAtomic)
				new TObjEffCrash3DRChildObj(this, &pos, &ang, &pow, &scl, spd0, pFrame, pAtomic,
				    yGroundPos, checkGroundFlag, time0);
		}
	}
}
TObjEffCrash3DR::~TObjEffCrash3DR()
{
	if (p_clump_instance) {
		fn_80150958(p_clump_instance);
		p_clump_instance = 0;
	}
}
void TObjEffCrash3DR::Exec()
{
	s32 mode = lbl_8029C310.state;
	if (mode == 1 || (u32)(mode - 2) <= 3 || (Parent->Signal & 1))
		Signal |= 1;
	else if (setobjCheckRangeOut2(&pos, 225000000.0f))
		Signal |= 1;
	else if (!fn_80017830(this))
		Signal |= 1;
}
void TObjEffCrash3DR::Disp()
{
	if (blend != rwBLENDONE && !lbl_8042C180->modeswitchflags[0x20])
		fn_8014FF2C(p_clump_instance);
}
void TObjEffCrash3DR::TDisp()
{
	if (blend == rwBLENDONE && !lbl_8042C180->modeswitchflags[0x20]) {
		RwBlendFunction src, dst;
		fn_80194294(10, &src);
		fn_80194294(11, &dst);
		fn_80194234(10, (void*)rwBLENDSRCALPHA);
		fn_80194234(11, (void*)rwBLENDONE);
		fn_8014FF2C(p_clump_instance);
		fn_80194234(10, (void*)src);
		fn_80194234(11, (void*)dst);
	}
}
RwFrame* TObjEffCrash3DR::SearchNodeFrameFromNodeID(s32 nodeID)
{
	s32 no = -1;
	if (hierarchy) {
		for (s32 i = 0; i < hierarchy->numNodes; ++i) {
			if (hierarchy->pNodeInfo[i].nodeIndex == nodeID) {
				no = i;
				break;
			}
		}
	}
	if (no == -1)
		return 0;
	return hierarchy->pNodeInfo[no].pFrame;
}
static RpAtomic* SearchAtomicFromFrameCallBack(RpAtomic* atomic, void* data)
{
	if (atomic->object.parent == data) {
		sFindAtomic = atomic;
		return 0;
	}
	return atomic;
}
RpAtomic* TObjEffCrash3DR::SearchAtomicFromFrame(RwFrame* frame)
{
	sFindAtomic = 0;
	fn_8014FFBC(p_clump_instance, SearchAtomicFromFrameCallBack, frame);
	return sFindAtomic;
}
TObjEffCrash3DRChildObj::TObjEffCrash3DRChildObj(TObject* ptp, RwV3d* pPos, sAngle* pAng,
    RwV3d* pPow, RwV3d* pScl, f32 spd0, RwFrame* pFrame, RpAtomic* pAtomic, f32 yGroundPos,
    s32 checkGroundFlag, s16 disappearTime)
    : TObject(ptp)
{
	scl.x             = pScl->x;
	scl.y             = pScl->y;
	scl.z             = pScl->z;
	check_ground_flag = checkGroundFlag;
	mode              = CRASH_EffCrash3DMode;
	if (!disappearTime)
		timer = (s16)(gMoveTime + (s32)(gMoveTimeRnd * (0.000030517578125f * rand())));
	else
		timer = disappearTime;
	if (timer >= gBlinkTime * 4)
		blink_time = (s16)gBlinkTime;
	else
		blink_time = (s16)(0.25f * timer);
	alpha        = 1.0f;
	y_ground_pos = yGroundPos;
	ang_spd.x    = (f32)(s32)(182.04444885253906f * (0.1f * (0.000030517578125f * rand() - 0.5f)));
	ang_spd.y    = (f32)(s32)(182.04444885253906f * (0.06f * (0.000030517578125f * rand() - 0.5f)));
	ang_spd.z    = (f32)(s32)(182.04444885253906f * (0.05f * (0.000030517578125f * rand() - 0.5f)));
	RwV3d vec;
	f32 f;
	RwMatrix curMat, dstMat;
	fn_80196050(&curMat, pPos, 0);
	fn_80195790(&curMat, &lbl_80239990, 1.0f - fn_800D7AE4((*pAng).z), fn_800D7B00((*pAng).z), 1);

	fn_80195790(&curMat, &lbl_80239984, 1.0f - fn_800D7AE4((*pAng).y), fn_800D7B00((*pAng).y), 1);

	fn_80195790(&curMat, &lbl_80239978, 1.0f - fn_800D7AE4((*pAng).x), fn_800D7B00((*pAng).x), 1);

	fn_80195E44(&curMat, &scl, 1);
	fn_80195674(&dstMat, &pFrame->modelling, &curMat);
	// The shared matrix-position convention substitutes the current matrix for null.
	RwV3d* translation = (!&dstMat) ? &lbl_8042C178->pos : &dstMat.pos;
	pos.x              = translation->x;
	pos.y              = translation->y;
	pos.z              = translation->z;
	fn_800D1288(&dstMat, &ang.x, &ang.y, &ang.z);
	vec.x = pos.x - pPos->x;
	vec.y = pos.y - pPos->y;
	vec.z = pos.z - pPos->z;
	f     = fn_801991B4(&vec);
	if (f <= 0.01f) {
		vec.x = pPow->x;
		vec.y = spd0 + pPow->y;
		vec.z = pPow->z;
	} else {
		f32 scalorVec = spd0 / f;
		vec.x         = pPow->x + vec.x * scalorVec;
		vec.y         = pPow->y + vec.y * scalorVec;
		vec.z         = pPow->z + vec.z * scalorVec;
	}
	spd.x                      = vec.x;
	spd.y                      = vec.y;
	spd.z                      = vec.z;
	p_frame                    = pFrame;
	p_atomic                   = pAtomic;
	mode                       = CRASH_EffCrash3DMode;
	p_frame->modelling.right.x = p_frame->modelling.up.y = p_frame->modelling.at.z = 1;
	p_frame->modelling.right.y = p_frame->modelling.right.z = p_frame->modelling.up.x = 0;
	p_frame->modelling.up.z = p_frame->modelling.at.x = p_frame->modelling.at.y = 0;
	p_frame->modelling.pos.x = p_frame->modelling.pos.y = p_frame->modelling.pos.z = 0;
	p_frame->modelling.flags |= 0x20003;
	SetPosition();
	ignore_time_stop_flag = lbl_8042C180->modeswitchflags[0x1F] != 0;
}
TObjEffCrash3DRChildObj::~TObjEffCrash3DRChildObj() { }
void TObjEffCrash3DRChildObj::SetPosition()
{
	fn_8019EB94(p_frame, &pos, 0);
	fn_80195790(
	    &p_frame->modelling, &lbl_80239990, 1.0f - fn_800D7AE4(ang.z), fn_800D7B00(ang.z), 1);

	fn_80195790(
	    &p_frame->modelling, &lbl_80239984, 1.0f - fn_800D7AE4(ang.y), fn_800D7B00(ang.y), 1);

	fn_80195790(
	    &p_frame->modelling, &lbl_80239978, 1.0f - fn_800D7AE4(ang.x), fn_800D7B00(ang.x), 1);

	fn_8019EC30(p_frame, &scl, 1);
}
void TObjEffCrash3DRChildObj::Exec()
{
	if (!ignore_time_stop_flag && lbl_8042C180->modeswitchflags[0x1F])
		return;
	pos.x += spd.x;
	pos.y += spd.y;
	pos.z += spd.z;
	if (check_ground_flag && y_ground_pos >= pos.y) {
		spd.x *= 0.989f;
		spd.z *= 0.989f;
		pos.y = y_ground_pos;
		if ((f32)__fabs(spd.y) < 0.445f) {
			spd.y = 0;
			spd.x *= 0.6f;
			spd.z *= 0.6f;
			ang_spd.x = ang_spd.y = ang_spd.z = 0;
		} else {
			spd.y *= -0.6f;
			ang_spd.x *= 0.6f;
			ang_spd.y *= 0.6f;
			ang_spd.z *= 0.6f;
		}
	} else {
		spd.x *= 0.989f;
		spd.y = 0.989f * spd.y - 0.089f;
		spd.z *= 0.989f;
	}
	ang.x += (s32)(182.04444885253906f * ang_spd.x);
	ang.y += (s32)(182.04444885253906f * ang_spd.y);
	ang.z += (s32)(182.04444885253906f * ang_spd.z);
	ang_spd.x *= 0.989f;
	ang_spd.y *= 0.989f;
	ang_spd.z *= 0.989f;
	switch (mode) {
		case CRASH_EffCrash3DMode:
		case BLINX_EffCrash3DMode:
			--timer;
			if (check_ground_flag) {
				if (mode != BLINX_EffCrash3DMode && (f32)__fabs(fn_801991B4(&spd)) < 0.01f) {
					mode = BLINX_EffCrash3DMode;
					if (timer >= blink_time)
						timer = blink_time;
				}
			} else if (mode != BLINX_EffCrash3DMode && timer <= blink_time)
				mode = BLINX_EffCrash3DMode;
			if (alpha <= 0 || timer <= 0) {
				mode = END_EffCrash3DMode;
				p_atomic->object.flags &= ~4;
				timer = 0;
			}
			if (mode == BLINX_EffCrash3DMode) {
				if (timer & 2)
					p_atomic->object.flags &= ~4;
				else
					p_atomic->object.flags |= 4;
			}
			SetPosition();
			break;
		case END_EffCrash3DMode:
			Signal |= 1;
			return;
	}
	if (p_atomic->interpolatorFlags & 2)
		fn_8014F854(p_atomic);
	RwSphere* sphere = &p_atomic->boundingSphere;
	sphere->center.z = p_frame->modelling.pos.z;
	sphere->center.y = p_frame->modelling.pos.y;
	sphere->center.x = p_frame->modelling.pos.x;
	sphere->radius   = 1500.0f;
}