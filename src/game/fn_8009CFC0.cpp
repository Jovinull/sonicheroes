#include "types.h"

// For each member of the team (count at 0x39, members from 0x114) it calls
// fn_8003FC44 on the member, reports the member's motion block (0x760) to the
// team (fn_80092814) and clears the member's status byte (0x20D + index).

struct Team {
	u8 unk000[0x39];
	s8 memberCount; // 0x39
	u8 unk03A[0x114 - 0x3A];
	void* member; // 0x114 (one per slot, 4 bytes apart)
	u8 unk118[0x20D - 0x118];
	u8 status[0x80]; // 0x20D
};

extern "C" void fn_8003FC44(void* member);
extern "C" void fn_80092814(void* team, void* motion);

extern "C" void fn_8009CFC0(Team* team)
{
	u8* slot;
	s32 i;
	register u32 zero = 0;

	i    = 0;
	slot = (u8*)team;
	while (i < team->memberCount) {
		Team* entry = (Team*)slot;
		fn_8003FC44(entry->member);
		fn_80092814(team, (u8*)entry->member + 0x760);
		team->status[i] = zero;
		slot += 4;
		i += 1;
	}
}
