// Starts the pending movie when the disc allows it (HYPOTHESIS; names inferred): unless
// fn_800C99F8 reports a ready state, waits for a DVD reading status of at most 5. Then flags the
// movie as playing (MoviePlaySub +0x8), runs MoviePlay's start callback (+0xC) when set, and calls
// the movie start sequence (fn_800CB95C, fn_8001F600, fn_800425E8 with the string lbl_80288B60
// and the buffer lbl_803E7518, fn_800CC7E8). Otherwise clears the playing flag.
#include "types.h"

struct MoviePlaySub8011253C {
	u8 pad0[0x8];
	s32 playing; // 0x8
	u8 padC[0x10 - 0xC];
};

struct MoviePlay8011253C {
	u8 pad0[0xC];
	void (*start)(void); // 0xC
	u8 pad10[0x14 - 0x10];
};

extern "C" {
extern MoviePlaySub8011253C MoviePlaySub;
extern MoviePlay8011253C MoviePlay;
extern char lbl_80288B60[];
extern u8 lbl_803E7518[];

s32 fn_800C99F8(void);
s32 GetDvdreadingStatus(void);
void fn_800CB95C(void);
void fn_8001F600(void);
void fn_800425E8(const char* name, void* buffer);
void fn_800CC7E8(void);

void fn_8011253C(void)
{
	if (fn_800C99F8() != 0 || GetDvdreadingStatus() <= 5) {
		MoviePlaySub.playing = 1;
		if (MoviePlay.start != 0) {
			MoviePlay.start();
		}
		fn_800CB95C();
		fn_8001F600();
		fn_800425E8(lbl_80288B60, lbl_803E7518);
		fn_800CC7E8();
	} else {
		MoviePlaySub.playing = 0;
	}
}
}
