#ifndef GAME_ENEMY_E_MOTION_H
#define GAME_ENEMY_E_MOTION_H
#include "types.h"
#include "game/setObj.h"
#include "game/enemy/e_database.h"
struct RpClump;
struct RpHAnimHierarchy;
struct RtAnimAnimation;
enum ENEMYMTNMD {
	ENEMYMTNMD_INIT,
	ENEMYMTNMD_SET,
	ENEMYMTNMD_CHANGE,
	ENEMYMTNMD_LOOP,
	ENEMYMTNMD_NEXT,
	ENEMYMTNMD_STOP,
	ENEMYMTNMD_TXEN,
	ENEMYMTNMD_POTS,
	ENEMYMTNMD_SPEED,
	ENEMYMTNMD_SPEEDNEXT,
	ENEMYMTNMD_TURN,
	ENEMYMTNMD_MANUAL,
	ENEMYMTNMD_NEXT2,
	ENEMYMTNMD_LOOP2,
	ENEMYMTNMD_END
};
struct ENEMY_MOTION {
	RtAnimAnimation* pHAA;
	ENEMYMTNMD mtnmode;
	s32 next;
	f32 start, end, frame, racio;
	char* pName;
	u32 uid;
};
class ENEMYMTNMAN
{
public:
	ENEMYMTNMAN();
	~ENEMYMTNMAN();
	void RequestMotionEx(s32);
	RpHAnimHierarchy* GetActiveHAHPointer();
	void TerminateInterpolateMotion();
	void InitializeInterpolateMotion();
	void SetMotion_SetStartFrame();
	f32 GetMotionStartFrame(s32);
	void SetMotion_NextEx(s32);
	void SetMotion_Next(s32);
	void LimitFrameNumber(f32, f32);
	void UpdateMotion();
	s32 TstFlag(u32 bits)
	{
		const sBitFlag& flag = mtnflag;
		return (flag.Flag & bits) != 0;
	}
	void SetFlag(u32 bits) { mtnflag.Flag |= bits; }
	void ClearFlag() { mtnflag.Flag = 0; }
	ENEMY_MOTION* GetMotionTablePointer(s32 patno) { return &pEM[patno]; }
	f32 nframe, pframe, start_frame, framespeed;
	sBitFlag mtnflag;
	s32 mtntimer, motion, reqmotion, lastmotion, nextmotion;
	ENEMYMTNMD mtnmode;
	ENEMY_MOTION* pEM;
	RpClump* pClump;
	RpHAnimHierarchy* pNHAH;
	RpHAnimHierarchy* pTHAH;
	RpHAnimHierarchy* pIHAH;
	s32 subFrameID;
	RpHAnimHierarchy* pPHAH;
	s32 reqmotion2;
};
namespace nEnemyMotion
{
void ReleaseAnimationDataFromONEFILE(eEnemyDataBase, ENEMY_MOTION*);
void LoadAnimationDataFromONEFILE(eEnemyDataBase, ENEMY_MOTION*);
}
#endif
