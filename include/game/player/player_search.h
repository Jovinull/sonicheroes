#ifndef GAME_PLAYER_SEARCH_H
#define GAME_PLAYER_SEARCH_H
#include "game/pathctrl.h"
class TObjOldPlayer;
TObjOldPlayer* SearchVanishedPlayers(s32 order_no);
s32 CountVanishedPlayers();
s32 SearchTheNearestRivalPlayer(s32 player_no);
s32 SearchTheNearestLeaderPlayer(RwV3d* pPos);
#endif
