// Returns the slot (0-3) of the first team in lbl_80303DC8 whose team-blast trigger
// (PARAM_SFA::sfa_trigger, indexed by the team number at +0x38) is in state 3, or -1. HYPOTHESIS:
// state 3 is "team blast running"; the team field name is inferred.
// NonMatching (57 words, 53 vs 77 instructions): the retail code is this loop unrolled four times
// (the sfa_trigger address hoisted, the slot pointer stepped by 4, the helper's 1/0 result kept and
// tested); MWCC 1.3.2 does not unroll a loop with an early return here. Tried: index types
// (s32/long/u32/u8/s16), nested ifs, indexing in place, -inline deferred/auto, four explicit
// checks (with and without a stepped pointer).
#include "game/gparam.h"

struct Team80090B3C {
	u8 pad0[0x38];
	s8 number; // 0x38
};

extern "C" {
extern Team80090B3C* lbl_80303DC8[4];
}

static inline s32 IsBlastRunning(Team80090B3C* team)
{
	if (PARAM_SFA::sfa_trigger[team->number] == 3) {
		return 1;
	}
	return 0;
}

extern "C" s32 fn_80090B3C(void)
{
	s32 i;

	for (i = 0; i < 4; i++) {
		Team80090B3C* team = lbl_80303DC8[i];

		if (team && IsBlastRunning(team)) {
			return i;
		}
	}
	return -1;
}
