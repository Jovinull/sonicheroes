// Puts player `index` on a path: its state record (lbl_802AD090) gets flag 0x1000 and state 0x21,
// and its path record (lbl_802AD0D0) the path (+0xC4), the position along it (+0x2C) and the
// matching point number (+0x1E, from SCPathOnposToPntnmb). Field roles are HYPOTHESIS.
#include "game/scanpath.h"

struct State800DF9F0 {
	s16 kind;  // 0x0
	s16 pad2;  // 0x2
	s16 state; // 0x4
	s16 flags; // 0x6
};

struct PathCtrl800DF9F0 {
	u8 pad0[0x1E];
	s16 point; // 0x1E
	u8 pad20[0x2C - 0x20];
	f32 position; // 0x2C
	u8 pad30[0xC4 - 0x30];
	PATHTAG* path; // 0xC4
};

extern "C" {
extern State800DF9F0* lbl_802AD090[8];
extern PathCtrl800DF9F0* lbl_802AD0D0[8];
}

extern "C" void fn_800DF9F0(s32 index, PATHTAG* path, f32 position)
{
	State800DF9F0* state   = lbl_802AD090[index];
	PathCtrl800DF9F0* ctrl = lbl_802AD0D0[index];
	u32 point;

	state->flags |= 0x1000;
	state->state   = 0x21;
	ctrl->path     = path;
	ctrl->position = position;
	SCPathOnposToPntnmb(path, position, &point);
	ctrl->point = point;
}
