#ifndef GAME_ENEMY_E_UTILITY_SEARCH_H
#define GAME_ENEMY_E_UTILITY_SEARCH_H

#include "game/pathctrl.h"

namespace nSearchPlayer
{
s32 GetTeamNoFromPlayerNum(s32 player_num);
s32 GetNearestLeaderPosition(const RwV3d* pin, RwV3d* pout, f32 distance);
s32 GetNearestPlayerNum(const RwV3d* pos, f32 distance);
s32 GetNearestLeaderNum(const RwV3d* pos, f32 distance);
}

#endif
