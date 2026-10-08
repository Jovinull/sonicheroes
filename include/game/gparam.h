#ifndef GAME_GPARAM_H
#define GAME_GPARAM_H
#include "game/rw_types.h"
class PARAM_VICTORY
{
public:
	static s8 num[4];
	void addVictory(s32, s32);
	void setVictory(s32, s32);
};
class PARAM_TIME
{
public:
	static s8 Min, Sec, Frm;
	s32 addMin(s32);
	s32 addSec(s32);
	s32 addFrm(s32);
	void setTime(s8, s8, s8);
};
class PARAM_SFA
{
public:
	static s32 sfa_trigger[4];
	static f32 sfa[4], tb[4];
	s32 subTB(s32, f32);
	void setTB(s32, f32);
	s32 addSFA(s32, f32);
	void setSFA(s32, f32);
};
class PARAM_SCORE
{
public:
	static s32 score[4][3];
	void addSomeonesScore(s32, s32);
	void addPlayerScore(s32, s32);
	void addScore(s32, s32, s32);
	void setScore(s32, s32, s32);
	void addScore(s32, s32);
};
class PARAM_CHALLENGE
{
public:
	static s32 num[4];
	void addChallenge(s32, s32);
	void setChallenge(s32, s32);
};
class PARAM_RING
{
public:
	static s32 num[4];
	void addRingNum(s32, s32);
	void setRingNum(s32, s32);
};
class PARAM_SAVEPOSITION
{
public:
	static RwV3d pos;
	static s32 ang, id;
	static s8 Min, Sec, Frm;
	// GameCube additions; names inferred from the saved-time operations.
	void getSaveTime(s8*, s8*, s8*);
	void setSaveTime(s8, s8, s8);
	void saveTime();
	s32 getSavePos(RwV3d*, s32*);
	void setSavePos(const RwV3d*, s32, s32);
};
enum GPARAM_INIT {
	GPARAM_INIT_DEFAULT,
	GPARAM_INIT_START,
	GPARAM_INIT_RETRY,
	GPARAM_INIT_CONTINUE,
	NUM_GPARAM_INIT
};
class G_PARAM
{
public:
	void InitRing();
	void InitSavePosition();
	void InitGParam(GPARAM_INIT);
};
s32 getVictoryNum(s32);
s32 getGameTime(s8*, s8*, s8*);
s32 getMemberScore(s32, s32);
s32 getScore(s32);
#endif
