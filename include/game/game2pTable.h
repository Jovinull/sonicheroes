#ifndef GAME_GAME2P_TABLE_H
#define GAME_GAME2P_TABLE_H

#include "types.h"

struct RwV3d;

void game2pCallIntroVoice(s32 team);
s32 game2pGetMainMemberNo(s32 team);
s32 game2pSetLimitTime(s8* pMinute, s8* pSecond);
s32 game2pSetGoalPosition(RwV3d* pPosition, s32 team);
s32 game2pSetStartPosition(RwV3d* pPosition, s32 team);

#endif
