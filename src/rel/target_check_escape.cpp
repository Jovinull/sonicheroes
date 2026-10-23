#include "types.h"

// TObjTarget::CheckEscape (the PS2 build's name, by its place in the PS2
// order; targetCheckEscape here): with the game paused the target hides
// (state 4). A target of kind 0 or 1 runs away (state 3, sound 0x100C the
// first time) when a team's second member comes within reach; otherwise it
// hides.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct TargetTeam {
	u8 unk000[0x3A];
	s8 second; // 0x3A
	u8 unk03B[0xD5];
	s8 members[4]; // 0x110
} TargetTeam;

typedef struct Target {
	u8 unk00[0xB8];
	s32 state;     // 0xB8
	s8 kind;       // 0xBC
	u8 unkBD[0xB]; // 0xBD
	RwV3d pos;     // 0xC8
} Target;

extern "C" u8* lbl_8042C180;
extern "C" void* lbl_8042C388;
extern "C" TargetTeam* lbl_80303DC8[];
extern "C" const f32 targetEscapeReach[1];

extern "C" s32 fn_8003E2E4(s32 player, s32 a, RwV3d* pos, s32 b);
extern "C" void fn_800B52E8(void* sound, s32 id, s32 a, s32 b);
f32 DistanceP2P(const RwV3d* a, const RwV3d* b);

extern "C" s32 targetCheckEscape(Target* object)
{
	if ((s8)lbl_8042C180[0x1F] != 0) {
		object->state = 4;
		return 0;
	}
	if (object->kind != 0 && object->kind != 1) {
		return 0;
	}
	for (int i = 0; i < 4; i++) {
		TargetTeam* team = lbl_80303DC8[i];
		RwV3d pos;

		if (team == NULL) {
			continue;
		}
		if (fn_8003E2E4(team->members[team->second], 1, &pos, 0) == 0) {
			continue;
		}
		if (DistanceP2P(&pos, &object->pos) > targetEscapeReach[0]) {
			continue;
		}
		if (object->state != 3 && lbl_8042C388 != NULL) {
			fn_800B52E8(lbl_8042C388, 0x100C, 0x10, 0);
		}
		object->state = 3;
		return 1;
	}
	object->state = 4;
	return 0;
}
