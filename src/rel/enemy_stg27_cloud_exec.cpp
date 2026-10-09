// TObjEnemyStg27Cloud's Exec: while the game state's mode (lbl_8029C310 +0x18)
// is 1, 2 or 3 the cloud raises its kill bit, with the same inline mode test
// as rel/enemy_stg27_sky_exec.cpp; otherwise it moves each of its two clumps'
// frames to its position. The class is shared through
// enemy_stg27_cloud_class.inc.

#define ENEMY_STG27_CLOUD_CTOR inline
#define ENEMY_STG27_CLOUD_DISP_FIRST
#include "src/rel/enemy_stg27_cloud_class.inc"

// The game state lbl_8029C310 points into: the mode at +0x18.
struct CloudGameState {
	u8 unk00[0x18];
	s32 mode; // 0x18
};

extern "C" CloudGameState lbl_8029C310;

// Whether the game state's mode is one the clouds end in.
inline s32 CloudModeEnds()
{
	s32 mode = lbl_8029C310.mode;
	return mode == 1 || mode == 2 || mode == 3;
}

void TObjEnemyStg27Cloud::Exec()
{
	if (CloudModeEnds()) {
		Signal |= 1;
	} else {
		if (clump != NULL) {
			fn_8019EB94(*(void**)((u8*)clump + 4), &pos, 0);
		}
		if (clump2 != NULL) {
			fn_8019EB94(*(void**)((u8*)clump2 + 4), &pos2, 0);
		}
	}
}
