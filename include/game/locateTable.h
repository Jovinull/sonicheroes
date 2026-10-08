#ifndef GAME_LOCATE_TABLE_H
#define GAME_LOCATE_TABLE_H
#include "game/pathctrl.h"
enum ENUM_STAGE_START_STATE {
	ENUM_STAGE_START_STATE_NONE,
	ENUM_STAGE_START_STATE_MOVE,
	ENUM_STAGE_START_STATE_GRIND,
	NUM_ENUM_STAGE_START_STATE
};
enum ENUM_FORMATION {
	FORMATION_SPEED,
	FORMATION_POWER,
	FORMATION_FLY,
	FORMATION_FLY_FLYING,
	FORMATION_ROCKET_ACCEL,
	FORMATION_TRIANGLE_DIVE,
	FORMATION_LINE_DIVE,
	FORMATION_SPEED_HANG,
	FORMATION_POWER_HANG,
	FORMATION_FLY_HANG,
	FORMATION_SPEED_PINBALL,
	FORMATION_POWER_PINBALL,
	FORMATION_FLY_PINBALL,
	NUM_FORMATIONS
};
struct START_LOCATE {
	RwV3d pos;
	s32 angy;
	ENUM_FORMATION formation;
	ENUM_STAGE_START_STATE state;
	u32 data;
};
struct GOAL_LOCATE {
	RwV3d pos;
	s32 angy;
	ENUM_FORMATION formation;
};
struct INTRO_LOCATE {
	RwV3d pos;
	s32 angy;
};
struct START_STAGE_LOCATOR {
	s32 stage;
	START_LOCATE locator[4];
};
struct GOAL_STAGE_LOCATOR {
	s32 stage;
	GOAL_LOCATE locator[4];
};
struct START_STAGE_LOCATOR_2P {
	s32 stage;
	START_LOCATE locator[2];
};
struct INTRO_STAGE_LOCATOR {
	s32 stage;
	INTRO_LOCATE locator[4];
};
extern START_LOCATE DemoLocator[4];
extern START_STAGE_LOCATOR gStartStageLocator[39];
extern GOAL_STAGE_LOCATOR gGoalStageLocator[60];
extern START_STAGE_LOCATOR_2P gStartStageLocator2p[23];
extern INTRO_STAGE_LOCATOR gIntroStageLocator[21];
s32 InitStageTime(s8* min, s8* sec, s8* frm);
s32 game1pSetLimitTime(s32 team, s8* pMinute, s8* pSecond);
INTRO_LOCATE* SearchIntroStageLocator(s32 team);
GOAL_LOCATE* SearchGoalStageLocator(s32 team);
START_LOCATE* SearchStartStageLocator(s32 team);
#endif
