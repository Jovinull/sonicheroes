#include "game/gparam.h"
#include "game/locate_table.h"
// GameCube 0x800663D0--0x80067050. C++ identities from symbolic metadata;
// all behavior, bounds and platform-specific saved-time operations from GameCube.
s32 PARAM_RING::num[4];
RwV3d PARAM_SAVEPOSITION::pos;
s32 PARAM_SAVEPOSITION::ang;
s32 PARAM_SAVEPOSITION::id;
s8 PARAM_SAVEPOSITION::Min;
s8 PARAM_SAVEPOSITION::Sec;
s8 PARAM_SAVEPOSITION::Frm;
s32 PARAM_CHALLENGE::num[4];
s32 PARAM_SCORE::score[4][3];
s8 PARAM_TIME::Min;
s8 PARAM_TIME::Sec;
s8 PARAM_TIME::Frm;
s32 PARAM_SFA::sfa_trigger[4];
f32 PARAM_SFA::sfa[4];
f32 PARAM_SFA::tb[4];
s8 PARAM_VICTORY::num[4];
extern "C" s8 lbl_8042C304[3];
s8 lbl_8042C304[3];
// Access-only prefixes of external objects, never allocated here.
struct ParamPlayerView {
	u8 reserved[0x25c];
	s8 team, member;
};
struct ParamTeamView {
	u8 reserved[0x3b];
	s8 member;
};
struct ParamModeView {
	s8 flags[44];
};
struct ParamActionView {
	u8 reserved[0x2c];
	s32 stage;
};
extern "C" {
extern ParamPlayerView* lbl_802AD0D0[];
extern ParamTeamView* lbl_80303DC8[];
extern ParamModeView* lbl_8042C180;
extern ParamActionView lbl_8029C310;
extern void* lbl_8042C388;
s32 fn_800AB104(s32);
void fn_800B52E8(void*, s32, s32, s32);
}
inline void PARAM_TIME::setTime(s8 min, s8 sec, s8 frm)
{
	Min = min;
	Sec = sec;
	Frm = frm;
}
inline s32 PARAM_TIME::addMin(s32 amount)
{
	s32 min = Min;
	min += amount;
	while (min < 0) {
		setTime(0, 0, 0);
		return 0;
	}
	if (min > 99) {
		setTime(99, 59, 59);
		return 0;
	}
	Min = (s8)min;
	return 1;
}
inline s32 PARAM_TIME::addSec(s32 amount)
{
	s32 sec = Sec;
	sec += amount;
	while (sec < 0) {
		sec += 60;
		if (!addMin(-1))
			return 0;
	}
	if (sec >= 60) {
		sec -= 60;
		if (!addMin(1))
			return 0;
	}
	Sec = (s8)sec;
	return 1;
}
inline void PARAM_SCORE::setScore(s32 team, s32 member, s32 value)
{
	if (value < 0)
		value = 0;
	if (value > 9999999)
		value = 9999999;
	score[team][member] = value;
}
// Shared operations on static parameter state; no assumed object hierarchy.
static inline void SetChallenge(s32 team, s32 value)
{
	if (value < -1)
		value = -1;
	if (value > 99)
		value = 99;
	PARAM_CHALLENGE::num[team] = value;
}
static inline void AddChallenge(s32 team, s32 amount)
{
	s32 value = PARAM_CHALLENGE::num[team];
	value += amount;
	if (value < -1)
		value = -1;
	if (value > 99)
		value = 99;
	SetChallenge(team, value);
}
static inline void SetSFA(s32 team, f32 value)
{
	if (value < 0.0f)
		value = 0.0f;
	if (value > 100.0f)
		value = 100.0f;
	PARAM_SFA::sfa[team] = value;
}
static inline s32 AddSFA(s32 team, f32 amount)
{
	switch (PARAM_SFA::sfa_trigger[team]) {
		case 1:
		case 2:
			return 1;
	}
	f32 value = PARAM_SFA::sfa[team];
	value += amount;
	if (value < 0.0f)
		value = 0.0f;
	if (value > 100.0f)
		value = 100.0f;
	SetSFA(team, value);
	if (value >= 100.0f)
		return 1;
	return 0;
}
void G_PARAM::InitGParam(GPARAM_INIT kind)
{
	switch (kind) {
		case GPARAM_INIT_DEFAULT:
			for (s32 i = 0; i < 4; i++)
				PARAM_CHALLENGE::num[i] = 3;
		case GPARAM_INIT_START:
			for (s32 i = 0; i < 4; i++)
				PARAM_VICTORY::num[i] = 0;
		case GPARAM_INIT_RETRY:
			PARAM_SAVEPOSITION::id  = -1;
			PARAM_SAVEPOSITION::Min = 0;
			PARAM_SAVEPOSITION::Sec = 0;
			PARAM_SAVEPOSITION::Frm = 0;
			if (lbl_8029C310.stage == 24) {
				PARAM_SAVEPOSITION::Min = lbl_8042C304[0];
				PARAM_SAVEPOSITION::Sec = lbl_8042C304[1];
				PARAM_SAVEPOSITION::Frm = lbl_8042C304[2];
			}
			InitStageTime(&PARAM_TIME::Min, &PARAM_TIME::Sec, &PARAM_TIME::Frm);
			break;
		case GPARAM_INIT_CONTINUE:
			break;
	}
	InitRing();
	for (s32 i = 0; i < 4; i++)
		for (s32 j = 0; j < 3; j++)
			PARAM_SCORE::score[i][j] = 0;
	for (s32 i = 0; i < 4; i++) {
		PARAM_SFA::sfa_trigger[i] = 0;
		PARAM_SFA::sfa[i]         = 0.0f;
		PARAM_SFA::tb[i]          = 0.0f;
	}
}

void G_PARAM::InitSavePosition()
{
	PARAM_SAVEPOSITION::id = -1;
	if (lbl_8042C180->flags[30] == 0) {
		PARAM_SAVEPOSITION::Min = PARAM_TIME::Min;
		PARAM_SAVEPOSITION::Sec = PARAM_TIME::Sec;
		PARAM_SAVEPOSITION::Frm = PARAM_TIME::Frm;
	}
}

void G_PARAM::InitRing()
{
	for (s32 i = 0; i < 4; i++)
		PARAM_RING::num[i] = 0;
}

void PARAM_SAVEPOSITION::setSavePos(const RwV3d* position, s32 angle, s32 number)
{
	if (number < id)
		return;
	id = number;
	if (position) {
		pos.x = position->x;
		pos.y = position->y;
		pos.z = position->z;
		ang   = angle;
	}
	if (lbl_8042C180->flags[30] == 0)
		saveTime();
}

s32 PARAM_SAVEPOSITION::getSavePos(RwV3d* position, s32* angle)
{
	if (lbl_8042C180->flags[30] == 0) {
		PARAM_TIME::Min = Min;
		PARAM_TIME::Sec = Sec;
		PARAM_TIME::Frm = Frm;
	}
	if (id == -1)
		return 0;
	// Retail checks angle before both writes, including the position copy.
	if (angle) {
		position->x = pos.x;
		position->y = pos.y;
		position->z = pos.z;
	}
	if (angle)
		*angle = ang;
	return 1;
}

void PARAM_SAVEPOSITION::saveTime()
{
	Min = PARAM_TIME::Min;
	Sec = PARAM_TIME::Sec;
	Frm = PARAM_TIME::Frm;
}

void PARAM_SAVEPOSITION::setSaveTime(s8 min, s8 sec, s8 frm)
{
	Min = min;
	Sec = sec;
	Frm = frm;
}

void PARAM_SAVEPOSITION::getSaveTime(s8* min, s8* sec, s8* frm)
{
	*min = Min;
	*sec = Sec;
	*frm = Frm;
}

void PARAM_RING::setRingNum(s32 team, s32 value)
{
	if (value < 0)
		value = 0;
	if (value > 999)
		value = 999;
	num[team] = value;
}

void PARAM_RING::addRingNum(s32 team, s32 amount)
{
	s32 value = num[team];
	s32 old   = value;
	value += amount;
	if (old < 999 && old < value && old / 100 < value / 100) {
		AddChallenge(team, 1);
		if (lbl_8042C388)
			fn_800B52E8(lbl_8042C388, 0x1034, 0, 0);
	}
	setRingNum(team, value);
	if (amount > 0)
		AddSFA(team, (f32)amount);
}

void PARAM_CHALLENGE::setChallenge(s32 team, s32 value)
{
	SetChallenge(team, value);
}

void PARAM_CHALLENGE::addChallenge(s32 team, s32 amount)
{
	AddChallenge(team, amount);
}

void PARAM_SCORE::addScore(s32 team, s32 amount)
{
	ParamTeamView* p = lbl_80303DC8[team];
	if (p)
		addScore(team, p->member, amount);
}

void PARAM_SCORE::addScore(s32 team, s32 member, s32 amount)
{
	s32 value = score[team][member];
	value += amount;
	if (value < 0)
		value = 0;
	if (value > 9999999)
		value = 9999999;
	setScore(team, member, value);
}

void PARAM_SCORE::addPlayerScore(s32 player, s32 amount)
{
	ParamPlayerView* p = lbl_802AD0D0[player];
	if (p)
		addScore(p->team, p->member, amount);
}

void PARAM_SCORE::addSomeonesScore(s32 team, s32 amount)
{
	addPlayerScore(fn_800AB104(team), amount);
}

s32 getScore(s32 team)
{
	return getMemberScore(team, 0) + getMemberScore(team, 1) + getMemberScore(team, 2);
}

s32 getMemberScore(s32 team, s32 member)
{
	return PARAM_SCORE::score[team][member];
}

void PARAM_SFA::setSFA(s32 team, f32 value)
{
	SetSFA(team, value);
}

s32 PARAM_SFA::addSFA(s32 team, f32 amount)
{
	return AddSFA(team, amount);
}

void PARAM_SFA::setTB(s32 team, f32 value)
{
	if (value < 0.0f)
		value = 0.0f;
	if (value > 1.0f)
		value = 1.0f;
	tb[team] = value;
}

s32 PARAM_SFA::subTB(s32 team, f32 amount)
{
	if (sfa_trigger[team] != 3)
		return 1;
	f32 value = tb[team];
	value -= amount;
	if (value < 0.0f)
		value = 0.0f;
	if (value > 1.0f)
		value = 1.0f;
	setTB(team, value);
	if (value <= 0.0f)
		return 1;
	return 0;
}

s32 PARAM_TIME::addFrm(s32 amount)
{
	s32 frm = Frm;
	frm += amount;
	while (frm < 0) {
		frm += 60;
		if (!addSec(-1))
			return 0;
	}
	while (frm >= 60) {
		frm -= 60;
		if (!addSec(1))
			return 0;
	}
	Frm = (s8)frm;
	return 1;
}

s32 getGameTime(s8* min, s8* sec, s8* frm)
{
	*min = PARAM_TIME::Min;
	*sec = PARAM_TIME::Sec;
	*frm = PARAM_TIME::Frm;
	return 1;
}

void PARAM_VICTORY::setVictory(s32 team, s32 value)
{
	if (value < -1)
		value = -1;
	if (value > 2)
		value = 2;
	num[team] = (s8)value;
}

void PARAM_VICTORY::addVictory(s32 team, s32 amount)
{
	s32 value = num[team] + amount;
	if (value < 0)
		value = 0;
	if (value > 2)
		value = 2;
	setVictory(team, value);
}

s32 getVictoryNum(s32 team)
{
	return PARAM_VICTORY::num[team];
}
