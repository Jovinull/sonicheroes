#include "game/enemy/e_utility_search.h"

// Complete e_utility_search.cpp. Symbolic metadata supplies the four namespace
// functions and field types; retail establishes the final GameCube offsets.
// The preceding team/character helper keeps its address name because its
// original identity is absent from the earlier metadata.
struct TASKWK {
	u8 prefix[0x18];
	RwV3d pos;
	RwV3d scl;
};

struct PLAYERWK {
	s8 playerno;
	s8 characterno;
	u8 rest[0x25C - 2];
	s8 teamNo;
};

struct TObjOldPlayer {
	u8 prefix[0x6F0];
	TASKWK taskwk;
	u8 motionwk[0x40];
	PLAYERWK playerwk;
};

struct TObjTeam {
	u8 prefix[0x3B];
	s8 leaderNo_Backup;
	u8 beforeMembers[0x110 - 0x3C];
	s8 member_player_no[3];
	u8 beforeFormation[0x120 - 0x113];
	s8 numFormationMembers;
	u8 beforeFormationPointers[0x128 - 0x121];
	TObjOldPlayer* formation_class_ptr[3];
};

extern "C" {
extern TObjTeam* lbl_80303DC8[4];
extern TObjOldPlayer* lbl_802AD070[8];
extern TASKWK* lbl_802AD090[8];
extern PLAYERWK* lbl_802AD0D0[8];
f32 fn_800D71DC(const RwV3d*, const RwV3d*);
s32 fn_800AB32C(TObjOldPlayer*);
}

extern "C" s32 fn_80103178(s32 team_num)
{
	TObjTeam* pteam = lbl_80303DC8[team_num];
	if (pteam) {
		s32 pl_num = pteam->member_player_no[pteam->leaderNo_Backup];
		if (pl_num != -1) {
			PLAYERWK* pwk = lbl_802AD0D0[pl_num];
			if (pwk)
				return pwk->characterno;
		}
	}
	return -1;
}

s32 nSearchPlayer::GetTeamNoFromPlayerNum(s32 player_num)
{
	if (player_num >= 0 && player_num < 8) {
		TObjOldPlayer* plp = lbl_802AD070[player_num];
		if (plp)
			return plp->playerwk.teamNo;
	}
	return -1;
}

s32 nSearchPlayer::GetNearestLeaderPosition(const RwV3d* pin, RwV3d* pout, f32 distance)
{
	s32 pl = GetNearestLeaderNum(pin, distance);
	if (pl != -1) {
		TASKWK* ptwk = lbl_802AD090[pl];
		if (ptwk) {
			*pout = ptwk->pos;
			return 1;
		}
	}
	return 0;
}

s32 nSearchPlayer::GetNearestPlayerNum(const RwV3d* pos, f32 distance)
{
	s32 ret  = -1;
	f32 dist = distance * distance;
	for (s32 i = 0; i < 8; ++i) {
		TASKWK* ptwk = lbl_802AD090[i];
		if (ptwk) {
			f32 tmp = fn_800D71DC(&ptwk->pos, pos);
			if (tmp < dist) {
				dist = tmp;
				ret  = i;
			}
		}
	}
	return ret;
}

s32 nSearchPlayer::GetNearestLeaderNum(const RwV3d* pos, f32 distance)
{
	f32 dist = distance * distance;
	s32 ret  = -1;
	for (s32 i = 0; i < 4; ++i) {
		TObjTeam* pteam = lbl_80303DC8[i];
		if (pteam) {
			s32 pl_num = pteam->member_player_no[pteam->leaderNo_Backup];
			if (pl_num != -1) {
				TObjOldPlayer* plp0 = lbl_802AD070[pl_num];
				if (plp0 && fn_800AB32C(plp0)) {
					s32 member_num = pteam->numFormationMembers;
					for (s32 i = 0; i < member_num; ++i) {
						TObjOldPlayer* plp1 = pteam->formation_class_ptr[i];
						if (plp1 && plp0 != plp1) {
							f32 tmp = fn_800D71DC(&plp1->taskwk.pos, pos);
							if (tmp <= dist) {
								dist = tmp;
								ret  = i;
							}
						}
					}
				} else {
					TASKWK* ptwk = lbl_802AD090[pl_num];
					if (ptwk) {
						f32 tmp = fn_800D71DC(&ptwk->pos, pos);
						if (tmp <= dist) {
							dist = tmp;
							ret  = pl_num;
						}
					}
				}
			}
		}
	}
	return ret;
}
