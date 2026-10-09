// TObjEnemyStg27Sky's Exec: while the game state's mode (lbl_8029C310 +0x18) is
// 1, 2 or 3 the sky raises its kill bit; otherwise it moves its clump's frame
// to its position. The mode test is an inline helper returning an int built
// from the bool, which is the original's register use and its signed compare of
// the answer. The class is shared through enemy_stg27_sky_class.inc.

#define ENEMY_STG27_SKY_CTOR inline
#define ENEMY_STG27_SKY_DISP_FIRST
#include "src/rel/enemy_stg27_sky_class.inc"

// The game state lbl_8029C310 points into: the mode at +0x18.
struct SkyGameState {
	u8 unk00[0x18];
	s32 mode; // 0x18
};

extern "C" SkyGameState lbl_8029C310;

// Whether the game state's mode is one the skies end in.
inline s32 SkyModeEnds()
{
	s32 mode = lbl_8029C310.mode;
	return mode == 1 || mode == 2 || mode == 3;
}

void TObjEnemyStg27Sky::Exec()
{
	if (SkyModeEnds()) {
		Signal |= 1;
	} else if (clump != NULL) {
		fn_8019EB94(*(void**)((u8*)clump + 4), &pos, 0);
	}
}
