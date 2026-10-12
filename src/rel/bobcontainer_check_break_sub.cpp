// TObjBobcontainer::CheckBreak_Sub, as rel/container_check_break_sub.cpp: who a
// hitter's type names as the crate's breaker, or -1.
// rel/bobcontainer_check_break.cpp has the same switch inline twice, as the
// original's CheckBreak does; this copy has no caller and is kept with
// force_active. The class is in game/obj_container.h.

#include "game/obj_container.h"

struct ContainerTeam {
	u8 pad000[0x3B];
	s8 leader; // 0x3B
	u8 pad03C[0xD4];
	s8 members[1]; // 0x110
};

extern "C" ContainerTeam* lbl_80303DC8[];

s32 TObjBobcontainer::CheckBreak_Sub(int type)
{
	ContainerTeam* team;

	switch (type) {
		case 1:
			return 0;
		case 2:
			return 1;
		case 3:
			return 2;
		case 4:
			return 3;
		case 5:
			return 4;
		case 6:
			return 5;
		case 7:
			if ((team = lbl_80303DC8[0]) != NULL) {
				return team->members[team->leader];
			}
		case 8:
			if ((team = lbl_80303DC8[1]) != NULL) {
				return team->members[team->leader];
			}
		case 9:
			if ((team = lbl_80303DC8[2]) != NULL) {
				return team->members[team->leader];
			}
		case 10:
			if ((team = lbl_80303DC8[3]) != NULL) {
				return team->members[team->leader];
			}
	}
	return -1;
}
