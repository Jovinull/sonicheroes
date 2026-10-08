#include "game/player/player_search.h"

struct TASKWK {
	s16 mode, modeLast, smode, flag;
	u16 wtimer;
	sAngle ang;
	RwV3d pos, scl;
};
// Partial views: only fields accessed by this unit are reconstructed.
struct PLAYERWK {
	u8 unknown_000[0x25C];
	s8 teamNo;
};
class TObjTeam
{
public:
	u8 unknown_000[0x3A];
	s8 leaderNo;
	u8 unknown_03B[0x110 - 0x3B];
	s8 member_player_no[3];
};
extern "C" {
extern TObjOldPlayer* lbl_802AD070[8];
extern TASKWK* lbl_802AD090[8];
extern PLAYERWK* lbl_802AD0D0[8];
extern TObjTeam* lbl_80303DC8[4];
f32 Distance2P2P__FPC5RwV3dPC5RwV3d(const RwV3d*, const RwV3d*);
f32 fn_801991B4(const RwV3d*);
}

TObjOldPlayer* SearchVanishedPlayers(s32 order_no)
{
	for (s32 i = 0; i < 8; ++i) {
		TASKWK* twp = lbl_802AD090[i];
		if (twp && twp->mode == 39) {
			if (order_no <= 0)
				return lbl_802AD070[i];
			--order_no;
		}
	}
	return 0;
}

s32 CountVanishedPlayers()
{
	s32 i   = 0;
	s32 num = 0;
	for (; i < 8; ++i) {
		TASKWK* twp = lbl_802AD090[i];
		if (twp && twp->mode == 39)
			++num;
	}
	return num;
}

s32 SearchTheNearestRivalPlayer(s32 player_no)
{
	s32 i;
	s32 pno;
	f32 dist2 = 1.0e14f;
	pno       = -1;
	for (i = 0; i < 8; ++i) {
		if (i != player_no && lbl_802AD090[i]
		    && lbl_802AD0D0[player_no]->teamNo != lbl_802AD0D0[i]->teamNo
		    && lbl_802AD090[i]->mode != 39) {
			f32 dist2_Temp = Distance2P2P__FPC5RwV3dPC5RwV3d(
			    &lbl_802AD090[player_no]->pos, &lbl_802AD090[i]->pos);
			if (pno == -1 || dist2 > dist2_Temp) {
				pno   = i;
				dist2 = dist2_Temp;
			}
		}
	}
	return pno;
}

s32 SearchTheNearestLeaderPlayer(RwV3d* pPos)
{
	s32 leader_player_number;
	s32 i;
	f32 dist;
	RwV3d v;
	f32 tmp;
	s32 leader_Temp;
	leader_player_number = -1;
	dist                 = 1.0e7f;
	for (i = 0; i < 4; ++i) {
		if (lbl_80303DC8[i]) {
			leader_Temp = lbl_80303DC8[i]->member_player_no[lbl_80303DC8[i]->leaderNo];
			v.x         = pPos->x;
			v.y         = pPos->y;
			v.z         = pPos->z;
			v.x -= lbl_802AD090[leader_Temp]->pos.x;
			v.y -= lbl_802AD090[leader_Temp]->pos.y;
			v.z -= lbl_802AD090[leader_Temp]->pos.z;
			tmp = fn_801991B4(&v);
			if (dist > tmp) {
				dist                 = tmp;
				leader_player_number = leader_Temp;
			}
		}
	}
	return leader_player_number;
}
