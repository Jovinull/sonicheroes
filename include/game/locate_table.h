#ifndef GAME_LOCATE_TABLE_H
#define GAME_LOCATE_TABLE_H
#include "game/rw_types.h"
struct START_LOCATE {
	RwV3d pos;
	s32 angy, formation, state;
	u32 data;
};
struct GOAL_LOCATE {
	RwV3d pos;
	s32 angy, formation;
};
struct INTRO_LOCATE {
	RwV3d pos;
	s32 angy;
};
struct START_STAGE_LOCATOR {
	s32 stage;
	START_LOCATE locator[4];
};
struct START_STAGE_LOCATOR_2P {
	s32 stage;
	START_LOCATE locator[2];
};
struct GOAL_STAGE_LOCATOR {
	s32 stage;
	GOAL_LOCATE locator[4];
};
struct INTRO_STAGE_LOCATOR {
	s32 stage;
	INTRO_LOCATE locator[4];
};
s32 InitStageTime(s8*, s8*, s8*);
s32 game1pSetLimitTime(s32, s8*, s8*);
INTRO_LOCATE* SearchIntroStageLocator(s32);
GOAL_LOCATE* SearchGoalStageLocator(s32);
START_LOCATE* SearchStartStageLocator(s32);
#endif
