#include "types.h"

// TObjGoalring::CheckAndSetPlayerReached (the PS2 build's name). With the game
// running (not paused, not in its two other stop states) and in play (state
// 5), it goes through what touched the ring's collision, unless something hit
// it as kind 0x13: the first player that counts reaches the goal. On a stage
// with the two-part ring the stage is just told so (sound 0x103F); otherwise
// the player's team wins (stage notified, a victory added, sound 0x103A).
// Either way the ring goes to state 2.

#include "src/rel/goal_ring_class.inc"

struct GoalringHitter {
	u8 pad000[0x78];
	u32 type; // 0x78
};

struct GoalringHit {
	u8 pad00[0x4];
	GoalringHitter* hitter; // 0x04
};

struct GoalringPlayer {
	u8 pad000[0x25C];
	s8 team; // 0x25C
};

extern "C" u8 lbl_8042C1A4[];
extern "C" void* lbl_8042C388;
extern "C" void* lbl_802AD070[];
extern "C" GoalringPlayer* lbl_802AD0D0[];

extern "C" s32 fn_80018C98(void);
extern "C" void fn_800196AC(GoalringStage* stage);
extern "C" void fn_80019898(GoalringStage* stage, s32 team);
extern "C" void fn_80021824(void* world);
extern "C" GoalringHit* fn_80020BD8(C_COLLI* colli, s32 kind);
extern "C" GoalringHit* fn_800211A8(C_COLLI* colli);
extern "C" s32 fn_80041B64(u32 type);
extern "C" s32 fn_80089204(void* player);
extern "C" void fn_800B52E8(void* sound, s32 id, s32 a, s32 b);

static inline GoalringHitter* goalRingHitter(GoalringHit* hit)
{
	return hit != NULL ? hit->hitter : NULL;
}

void TObjGoalring::CheckAndSetPlayerReached()
{
	GoalringHitter* hitter;

	if (lbl_8042C180[0x22] == 0 && lbl_8042C180[0x21] == 0 && lbl_8042C180[0x20] == 0
	    && fn_80018C98() == 5) {
		fn_80021824(lbl_8042C1A4);
		if (goalRingHitter(fn_80020BD8(&Colli(), 0x13)) != NULL) {
			return;
		}
		while ((hitter = goalRingHitter(fn_800211A8(&Colli()))) != NULL) {
			s32 no = fn_80041B64(hitter->type);

			if (fn_80089204(lbl_802AD070[no]) != 0) {
				s32 team = lbl_802AD0D0[no]->team;

				if (goalRingHasTwoRings()) {
					fn_800196AC(&lbl_8029C310);
					if (lbl_8042C388 != NULL) {
						fn_800B52E8(lbl_8042C388, 0x103F, 0, 0);
					}
				} else {
					fn_80019898(&lbl_8029C310, team);
					addVictory(team, 1);
					if (lbl_8042C388 != NULL) {
						fn_800B52E8(lbl_8042C388, 0x103A, 0, 0);
					}
				}
				state = 2;
				return;
			}
		}
	}
}
