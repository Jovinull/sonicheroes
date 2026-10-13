#include "types.h"

// Two team mode setters: each sets the team's play mode (0x150, to 0x15 or
// 0x17) and returns the word at 0x154. The bobsleigh's InitRideOn uses the
// second one.

struct Team {
	u8 unk000[0x150];
	s32 playMode; // 0x150
	s32 value;    // 0x154
};

extern "C" s32 fn_80098710(Team* team)
{
	team->playMode = 0x15;
	return team->value;
}

extern "C" s32 fn_80098720(Team* team)
{
	team->playMode = 0x17;
	return team->value;
}
