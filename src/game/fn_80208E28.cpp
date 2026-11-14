// Sets up the audio system's voice entries (see game/audio_system.h): AX mode 0, all 0x40
// entries cleared and numbered, then up to voiceCount (at most 0x40) AX voices acquired up front
// (priority 0x1B, callback fn_80208FF8), stopping at the first failure.
#include "game/audio_system.h"

extern "C" {
void* memset(void* dst, int value, unsigned long n);
void fn_80208FF8(void* voice);

void fn_80208E28(void)
{
	int i;
	int n;
	AXSetMode(0);
	memset(lbl_8042CF6C->entries10C, 0, sizeof(lbl_8042CF6C->entries10C));
	for (i = 0; i < 0x40; i++) {
		lbl_8042CF6C->entries10C[i].index = i;
	}
	n = lbl_8042CF6C->voiceCount;
	if (n > 0x40) {
		n = 0x40;
	}
	for (i = 0; i < n; i++) {
		lbl_8042CF6C->entries10C[i].voice
		    = AXAcquireVoice(0x1B, fn_80208FF8, (u32)&lbl_8042CF6C->entries10C[i]);
		if (lbl_8042CF6C->entries10C[i].voice == 0) {
			break;
		}
		lbl_8042CF6C->voicesAcquired++;
	}
}
}
