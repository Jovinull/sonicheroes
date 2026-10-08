// Complete e_motion.cpp. Six surviving bodies match natively; UpdateMotion
// retains three register fields for one captured-request local. Source trials
// covered metadata local order/types, helper lifetimes/accessors, flag references
// and SET branch forms. fix_e_motion_registers.py changes only those three fields;
// remove that step when source/compiler choices recover the allocation.
// Ordinary definitions preserve pool order; unused authentic helper copies are
// discarded by the linker. See docs/e-motion-unit-evidence.md.
#include "game/enemy/e_motion.h"
// GC SDK layouts accessed by this translation unit. Unrecovered SDK entry names
// retain address-based linkage; ignored return contracts remain provisional.
struct RpAtomic;
struct RwFrame;
struct RtAnimAnimation {
	void* interpInfo;
	s32 numFrames;
	s32 flags;
	f32 duration;
	void* pFrames;
	void* customData;
};
struct RtAnimInterpolator {
	unsigned char unknown00[0x24];
	s32 currentInterpKeyFrameSize;
};
struct RpHAnimHierarchy {
	s32 flags, numNodes;
	void* pMatrixArray;
	void* pMatrixArrayUnaligned;
	void* pNodeInfo;
	RwFrame* parentFrame;
	RpHAnimHierarchy* parentHierarchy;
	s32 rootParentOffset;
	RtAnimInterpolator* currentAnim;
};
struct sEnemyDataBase {
	void* addr;
	s32 filenum;
};
class TEnemyDataBase
{
public:
	TEnemyDataBase();
	RtAnimAnimation* SearchHAnim(eEnemyDataBase, u32);
	static TEnemyDataBase* GetInstance()
	{
		if (!mpDataBase)
			new TEnemyDataBase;
		return mpDataBase;
	}
	sEnemyDataBase EnemyDataBase[ENEMY_DB_NUM];
	static TEnemyDataBase* mpDataBase;
};
struct MotionModeSwitchView {
	signed char modeswitchflags[0x20];
};
extern "C" MotionModeSwitchView* lbl_8042C180;
namespace nHierarchy
{
RpHAnimHierarchy* GetHierarchy(RpClump*);
RpAtomic* SetHierarchyForSkinAtomic(RpAtomic*, void*);
}
extern "C" {
RpClump* fn_8014FFBC(RpClump*, RpAtomic* (*)(RpAtomic*, void*), void*);
RpHAnimHierarchy* fn_8013EFA0(RpHAnimHierarchy*, s32, s32, s32);
RpHAnimHierarchy* fn_8013F12C(RpHAnimHierarchy*, s32, s32);
RpHAnimHierarchy* fn_8013F3A4(RpHAnimHierarchy*);
s32 fn_8013FC30(RpHAnimHierarchy*);
s32 fn_8020C72C(RtAnimInterpolator*, RtAnimAnimation*);
s32 fn_8020D02C(RtAnimInterpolator*, f32);
s32 fn_8020CC18(RtAnimInterpolator*, f32);
s32 fn_8020C864(RtAnimInterpolator*, s32);
s32 fn_8020C92C(RtAnimInterpolator*, RtAnimInterpolator*);
s32 fn_8020D070(RtAnimInterpolator*, RtAnimInterpolator*, RtAnimInterpolator*, f32);
}
// 8013EEE0 returns zero; return type is provisional until SDK declaration proof.
extern "C" s32 fn_8013EEE0(RpHAnimHierarchy*);
extern "C" RpHAnimHierarchy* fn_8013F448(RpHAnimHierarchy*);

void nEnemyMotion::ReleaseAnimationDataFromONEFILE(eEnemyDataBase db, ENEMY_MOTION* pMotion)
{
	while (pMotion->mtnmode != ENEMYMTNMD_END) {
		if (pMotion->pHAA)
			pMotion->pHAA = 0;
		++pMotion;
	}
}
void nEnemyMotion::LoadAnimationDataFromONEFILE(eEnemyDataBase db, ENEMY_MOTION* pMotion)
{
	while (pMotion->mtnmode != ENEMYMTNMD_END) {
		if (!pMotion->pHAA)
			pMotion->pHAA = TEnemyDataBase::GetInstance()->SearchHAnim(db, pMotion->uid);
		++pMotion;
	}
}
void ENEMYMTNMAN::RequestMotionEx(s32 motionNo)
{
	if (pEM[motion].mtnmode == ENEMYMTNMD_LOOP2)
		reqmotion2 = motionNo;
	else
		reqmotion = motionNo;
}
ENEMYMTNMAN::~ENEMYMTNMAN()
{
	if (pNHAH && pPHAH) {
		fn_8013F448(pNHAH);
		fn_8013EEE0(pNHAH);
		pNHAH = 0;
	}
	if (pTHAH) {
		pTHAH->parentFrame = 0;
		fn_8013EEE0(pTHAH);
		pTHAH = 0;
	}
	if (pIHAH) {
		pIHAH->parentFrame = 0;
		fn_8013EEE0(pIHAH);
		pIHAH = 0;
	}
}
ENEMYMTNMAN::ENEMYMTNMAN()
{
	mtnflag.Flag = 0;
	nframe = pframe = start_frame = 0.0f;
	framespeed                    = 1.0f;
	mtnflag.Flag                  = 0;
	mtntimer                      = 0;
	motion = reqmotion = lastmotion = nextmotion = 0;
	reqmotion2                                   = -1;
	mtnmode                                      = ENEMYMTNMD_INIT;
	pEM                                          = 0;
	pClump                                       = 0;
	pNHAH = pTHAH = pIHAH = 0;
	pPHAH                 = 0;
	// Retail leaves subFrameID uninitialized.
}
RpHAnimHierarchy* ENEMYMTNMAN::GetActiveHAHPointer()
{
	return pNHAH;
}
f32 ENEMYMTNMAN::GetMotionStartFrame(s32 patno)
{
	f32 nframe_Return;
	ENEMYMTNMD mtnmode_Temp = pEM[patno].mtnmode;
	f32 nframe_Start        = pEM[patno].start;
	if (mtnmode_Temp == ENEMYMTNMD_TXEN || mtnmode_Temp == ENEMYMTNMD_POTS)
		nframe_Return = -1.0f;
	else if (mtnmode_Temp == ENEMYMTNMD_LOOP || mtnmode_Temp == ENEMYMTNMD_SPEED
	    || mtnmode_Temp == ENEMYMTNMD_MANUAL) {
		if (start_frame > 0.0f)
			nframe_Return = start_frame;
		else if (nframe_Start >= 0.0f)
			nframe_Return = nframe_Start;
		else
			nframe_Return = -1.0f;
	} else if (nframe_Start >= 0.0f)
		nframe_Return = nframe_Start;
	else
		nframe_Return = -1.0f;
	if (nframe_Return < 0.0f)
		nframe_Return = 60.0f * pEM[patno].pHAA->duration - 1.0f;
	return nframe_Return;
}
void ENEMYMTNMAN::SetMotion_SetStartFrame()
{
	nframe      = GetMotionStartFrame(motion);
	start_frame = 0.0f;
	fn_8020D02C(pNHAH->currentAnim, 0.0166667f * nframe);
	fn_8020CC18(pNHAH->currentAnim, 0.0f);
}
void ENEMYMTNMAN::TerminateInterpolateMotion()
{
	RtAnimAnimation* pNewHA = pEM[(u16)motion].pHAA;
	fn_8020C72C(pNHAH->currentAnim, pNewHA);
	if (pClump)
		fn_8014FFBC(pClump, nHierarchy::SetHierarchyForSkinAtomic, pNHAH);
	fn_8013F3A4(pNHAH);
	SetMotion_SetStartFrame();
	fn_8013FC30(pNHAH);
}
void ENEMYMTNMAN::LimitFrameNumber(f32 startFrame_Current, f32 endFrame_Current)
{
	f32 diffFrame_Temp = endFrame_Current - startFrame_Current;
	while (endFrame_Current <= nframe)
		nframe = nframe - diffFrame_Temp;
	while (startFrame_Current > nframe)
		nframe = diffFrame_Temp + nframe;
}
void ENEMYMTNMAN::SetMotion_NextEx(s32 mtnno)
{
	reqmotion  = mtnno;
	motion     = reqmotion;
	mtnmode    = pEM[motion].mtnmode;
	nextmotion = pEM[reqmotion].next;
	mtnflag.Flag |= 1;
	fn_8020C72C(pNHAH->currentAnim, pEM[motion].pHAA);
	if (pClump)
		fn_8014FFBC(pClump, nHierarchy::SetHierarchyForSkinAtomic, pNHAH);
	fn_8013F3A4(pNHAH);
	SetMotion_SetStartFrame();
}

void ENEMYMTNMAN::InitializeInterpolateMotion()
{
	u16 newpat = reqmotion;
	fn_8020C92C(pIHAH->currentAnim, pNHAH->currentAnim);
	fn_8020C72C(pTHAH->currentAnim, GetMotionTablePointer(newpat)->pHAA);
	RpHAnimHierarchy* hierarchy = pTHAH;
	f32 frame                   = GetMotionStartFrame(newpat);
	fn_8020D02C(hierarchy->currentAnim, 0.0166667f * frame);
	if (pClump)
		fn_8014FFBC(pClump, nHierarchy::SetHierarchyForSkinAtomic, pNHAH);
	fn_8013F3A4(pNHAH);
	nframe = 0.0f;
}
void ENEMYMTNMAN::SetMotion_Next(s32 patno)
{
	SetMotion_NextEx(pEM[patno].next);
}
void ENEMYMTNMAN::UpdateMotion()
{
	if (!pEM)
		return;
	s32 newmotion;
	s32 flag = 0;
	s32 running;
	if (lbl_8042C180->modeswitchflags[0x1f])
		running = 0;
	else
		running = 1;
	if (!running && !(mtnflag.Flag & 4))
		return;
	if (!running && TstFlag(8) == 1L)
		flag = 1;
	newmotion                = reqmotion;
	lastmotion               = motion;
	u32 keep                 = mtnflag.Flag & 12;
	mtnflag.Flag             = 0;
	const sBitFlag& retained = mtnflag;
	SetFlag(keep | retained.Flag);
	if (newmotion != motion && mtnmode != ENEMYMTNMD_CHANGE && mtnmode != ENEMYMTNMD_INIT
	    && mtnmode != ENEMYMTNMD_END) {
		mtnmode                 = ENEMYMTNMD_SET;
		mtntimer                = 0;
		ENEMY_MOTION* requested = &pEM[reqmotion];
		if (requested->mtnmode == ENEMYMTNMD_SPEED
		    && GetMotionTablePointer(motion)->mtnmode == ENEMYMTNMD_SPEED) {
			u32 oldlen  = (u32)(60.0f * GetMotionTablePointer(motion)->pHAA->duration);
			u32 newlen  = (u32)(60.0f * requested->pHAA->duration);
			start_frame = 0.1f * newlen + newlen * (oldlen - nframe) / oldlen;
			if (start_frame >= newlen)
				start_frame -= newlen;
		}
	} else
		++mtntimer;
	switch (mtnmode) {
		case ENEMYMTNMD_INIT: {
			nframe      = 0.0f;
			motion      = newmotion;
			start_frame = 0.0f;
			if (pClump) {
				pNHAH = nHierarchy::GetHierarchy(pClump);
				fn_8014FFBC(pClump, nHierarchy::SetHierarchyForSkinAtomic, pNHAH);
			} else if (pPHAH)
				pNHAH = fn_8013EFA0(pPHAH, subFrameID, pPHAH->flags, -1);
			else
				return;
			pNHAH->flags |= 0x3000;
			fn_8020C72C(pNHAH->currentAnim, GetMotionTablePointer(motion)->pHAA);
			fn_8013F3A4(pNHAH);
			fn_8013FC30(pNHAH);
			fn_8020D02C(pNHAH->currentAnim, 0.0f);
			fn_8020CC18(pNHAH->currentAnim, 0.0f);
			s32 flags = pNHAH->flags & ~1;
			pTHAH     = fn_8013F12C(pNHAH, flags, pNHAH->currentAnim->currentInterpKeyFrameSize);
			pTHAH->parentFrame = pNHAH->parentFrame;
			fn_8013F3A4(pTHAH);
			pIHAH = fn_8013F12C(pNHAH, flags, pNHAH->currentAnim->currentInterpKeyFrameSize);
			fn_8020C864(pIHAH->currentAnim, 2);
			pIHAH->parentFrame = pNHAH->parentFrame;
			fn_8013F3A4(pIHAH);
			mtnmode = ENEMYMTNMD_SET;
			return;
		}
		case ENEMYMTNMD_SET:
			if (reqmotion != motion && 1.0f != GetMotionTablePointer(newmotion)->frame)
				InitializeInterpolateMotion();
			else
				nframe = 1.0f;
			motion  = newmotion;
			mtnmode = ENEMYMTNMD_CHANGE;
		case ENEMYMTNMD_CHANGE:
			nframe += GetMotionTablePointer(motion)->frame;
			if (nframe >= 1.0f) {
				mtnmode = GetMotionTablePointer(motion)->mtnmode;
				TerminateInterpolateMotion();
				SetMotion_SetStartFrame();
			} else {
				fn_8020D070(pNHAH->currentAnim, pIHAH->currentAnim, pTHAH->currentAnim, nframe);
				fn_8013FC30(pNHAH);
			}
			return;
		case ENEMYMTNMD_END:
			TerminateInterpolateMotion();
			break;
	}
	ENEMY_MOTION* em     = &pEM[newmotion];
	RtAnimAnimation* pHA = em->pHAA;
	f32 start = em->start, end = em->end;
	if (-1.0f == start)
		start = (s32)(60.0f * pHA->duration);
	if (-1.0f == end)
		end = (s32)(60.0f * pHA->duration);
	if (flag) {
		fn_8020D02C(pNHAH->currentAnim, 0.0166667f * nframe);
		fn_8013FC30(pNHAH);
		return;
	}
	switch (mtnmode) {
		case ENEMYMTNMD_LOOP:
			nframe += GetMotionTablePointer(newmotion)->racio;
			if (end <= nframe + GetMotionTablePointer(newmotion)->racio)
				mtnflag.Flag |= 2;
			LimitFrameNumber(start, end);
			break;
		case ENEMYMTNMD_LOOP2:
			nframe += GetMotionTablePointer(newmotion)->racio;
			if (end <= nframe + GetMotionTablePointer(newmotion)->racio)
				mtnflag.Flag |= 2;
			LimitFrameNumber(start, end);
			if (reqmotion2 != -1 && (mtnflag.Flag & 2)) {
				SetMotion_NextEx(reqmotion2);
				reqmotion2 = -1;
			}
			break;
		case ENEMYMTNMD_SPEED:
			nframe += framespeed * GetMotionTablePointer(newmotion)->racio;
			if (end <= nframe + framespeed * GetMotionTablePointer(newmotion)->racio)
				mtnflag.Flag |= 2;
			LimitFrameNumber(start, end);
			break;
		case ENEMYMTNMD_SPEEDNEXT:
			nframe += framespeed;
			if (end <= nframe)
				SetMotion_Next(newmotion);
			break;
		case ENEMYMTNMD_NEXT:
			nframe += GetMotionTablePointer(newmotion)->racio;
			if (end <= nframe)
				SetMotion_Next(newmotion);
			else if (end <= nframe + GetMotionTablePointer(newmotion)->racio)
				mtnflag.Flag |= 2;
			break;
		case ENEMYMTNMD_TXEN:
			nframe -= GetMotionTablePointer(newmotion)->racio;
			if (end > nframe)
				SetMotion_Next(newmotion);
			break;
		case ENEMYMTNMD_STOP:
			nframe += GetMotionTablePointer(newmotion)->racio;
			if (end <= nframe) {
				nframe = end;
				mtnflag.Flag |= 1;
			} else if (end <= nframe + GetMotionTablePointer(newmotion)->racio)
				mtnflag.Flag |= 2;
			break;
		case ENEMYMTNMD_POTS:
			nframe -= GetMotionTablePointer(newmotion)->racio;
			if (end > nframe) {
				nframe = 0.0f;
				mtnflag.Flag |= 1;
			}
			break;
		case ENEMYMTNMD_MANUAL:
			LimitFrameNumber(start, end);
			break;
		case ENEMYMTNMD_NEXT2:
			nframe += GetMotionTablePointer(newmotion)->racio;
			if (end <= nframe)
				reqmotion = pEM[newmotion].next;
			else if (end <= nframe + GetMotionTablePointer(newmotion)->racio)
				mtnflag.Flag |= 2;
			break;
		case ENEMYMTNMD_END:
		default:
			TerminateInterpolateMotion();
			break;
	}
	fn_8020D02C(pNHAH->currentAnim, 0.0166667f * nframe);
	fn_8013FC30(pNHAH);
}
