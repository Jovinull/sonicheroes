// Chooses a player's next motion (+0x8AE) from its team's mode (+0x140 of the team record at
// +0x9B8). Modes 2/3: follow the leader (copy its motion +0x8B0 below 0x5A while it is in action
// 2 or 0x1C; with flag 0x8000 of +0x780, pick motion 8..4 from the leader's speed +0x7C0 against
// the thresholds +0x85C/+0x854/+0x850/+0x84C; motion 0x40 when the player at slot +0x3B is in motion
// 0x43, unless that is this player; else map the leader's motion 0xD/0x19/0x41-0x42/0x4E, default
// 0x40). Modes 7-9: motion 0x3C. Modes 5/6, in action 0x29: motion 0x3F, and in team phase 2/3
// (+0x34) copy the leader's +0x8C0 when both are in motion 0x3F. The motion changes clear flags
// 0x500 of +0x6F6. HYPOTHESIS: formation animation logic; all names are UNKNOWN.
#include "types.h"

struct Team80046768;

struct Player80046768 {
	u8 pad0[0x6F0];
	s16 action; // 0x6F0
	u8 pad6F2[4];
	s16 flags; // 0x6F6
	u8 pad6F8[0x780 - 0x6F8];
	s32 flags780; // 0x780
	u8 pad784[0x7C0 - 0x784];
	f32 speed; // 0x7C0
	u8 pad7C4[0x84C - 0x7C4];
	f32 threshold84C; // 0x84C
	f32 threshold850; // 0x850
	f32 threshold854; // 0x854
	u8 pad858[4];
	f32 threshold85C; // 0x85C
	u8 pad860[0x8AE - 0x860];
	s16 nextMotion; // 0x8AE
	s16 motion;     // 0x8B0
	u8 pad8B2[0x8C0 - 0x8B2];
	f32 unknown8C0; // 0x8C0
	u8 pad8C4[0x9B8 - 0x8C4];
	Team80046768* team; // 0x9B8
};

struct Team80046768 {
	u8 pad0[0x34];
	s32 phase; // 0x34
	u8 pad38[2];
	s8 leader;   // 0x3A
	s8 previous; // 0x3B
	u8 pad3C[0x114 - 0x3C];
	Player80046768* players[3]; // 0x114
	u8 pad120[0x140 - 0x120];
	s32 mode; // 0x140
};

extern "C" void fn_80046768(Player80046768* p)
{
	Player80046768* leader;
	Player80046768* other;
	Team80046768* team;

	team = p->team;
	switch (team->mode) {
		case 2:
		case 3: {
			leader = team->players[team->leader];
			other  = team->players[team->previous];

			if (leader->action == 2 || leader->action == 0x1C) {
				if (leader->motion < 0x5A) {
					p->nextMotion = leader->motion;
				}
				return;
			}
			if (p->flags780 & 0x8000) {
				if (leader->speed >= p->threshold85C) {
					p->nextMotion = 8;
				} else if (leader->speed >= p->threshold854) {
					p->nextMotion = 7;
				} else if (leader->speed >= p->threshold850) {
					p->nextMotion = 6;
				} else if (leader->speed >= p->threshold84C) {
					p->nextMotion = 5;
				} else {
					p->nextMotion = 4;
				}
				return;
			}
			if (other->motion == 0x43 || other->nextMotion == 0x43) {
				if (other != p) {
					p->nextMotion = 0x40;
				}
				return;
			}
			switch (leader->motion) {
				case 0xD:
					p->nextMotion = 0xD;
					break;
				case 0x19:
					p->nextMotion = 0x19;
					break;
				case 0x41:
				case 0x42:
					p->nextMotion = 0x41;
					break;
				case 0x4E:
					p->nextMotion = 0x41;
					break;
				default:
					p->nextMotion = 0x40;
					break;
			}
			p->flags &= ~0x500;
			break;
		}
		case 7:
		case 8:
		case 9:
			p->nextMotion = 0x3C;
			p->flags &= ~0x500;
			break;
		case 5:
		case 6:
			if (p->action == 0x29) {
				p->flags &= ~0x500;
				p->nextMotion = 0x3F;
				team          = p->team;
				if (team->phase < 4 && team->phase >= 2) {
					leader = team->players[team->leader];

					if (p->motion == 0x3F && leader->motion == 0x3F) {
						p->unknown8C0 = leader->unknown8C0;
					}
				}
			}
			break;
	}
}
