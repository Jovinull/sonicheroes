#include "types.h"

// The capture enemy's two ways to let its held player go (the same in the
// seven stage modules that carry the capture): captureDropPlayer only forgets
// the player, first calling fn_80043DEC when the player's object is in state
// 0x26; captureFreePlayer puts the player in mode 0xF.

typedef struct CapturePlayer {
	u8 unk000[0x6F0];
	s16 state; // 0x6F0
} CapturePlayer;

typedef struct Capture {
	u8 unk000[0x278];
	s32 player; // 0x278
} Capture;

extern "C" CapturePlayer* lbl_802AD070[];

extern "C" void fn_80043DEC(void);
extern "C" void fn_800E1208(s32 player, s32 mode, s32 arg);

extern "C" void captureDropPlayer(Capture* object)
{
	s32 player = object->player;

	if (player != -1) {
		CapturePlayer* body = lbl_802AD070[player];

		if (body != NULL) {
			if (body->state == 0x26) {
				fn_80043DEC();
			}
			object->player = -1;
		}
	}
}

extern "C" void captureFreePlayer(Capture* object)
{
	if (object->player != -1) {
		fn_800E1208(object->player, 0xF, 0);
		object->player = -1;
	}
}
