// Counts the audio system's voice entries (see game/audio_system.h) whose flags are nonzero; 0
// when the system is absent.
#include "game/audio_system.h"

extern "C" {
int fn_80208C38(void)
{
	int n = 0;
	int i;
	if (lbl_8042CF6C != 0) {
		for (i = 0; i < 0x40; i++) {
			if (lbl_8042CF6C->entries10C[i].flags != 0) {
				n++;
			}
		}
	}
	return n;
}
}
