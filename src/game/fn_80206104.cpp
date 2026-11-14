// Reserves region `id` (0..15) of the audio system's arena (see game/audio_system.h): `size`
// rounded up to 32 bytes, taken from the next free offset. Returns 0, or -1 after an OSReport of
// lbl_8023D568 when the id is out of range or the arena is too small.
// NonMatching: 10 word diffs, volatile register choice only (retail keeps the rounded size in r5
// and id * 8 in r6; MWCC swaps them). Declaration order and statement spellings did not help.
#include "game/audio_system.h"

extern "C" {
#include "dolphin/os.h"

extern char lbl_8023D568[];

int fn_80206104(int id, int size)
{
	int n      = (size + 0x1F) & ~0x1F;
	int result = -1;
	if (id >= 0 && id < 0x10 && lbl_8042CF6C->arenaFree >= n) {
		result                           = 0;
		lbl_8042CF6C->regions[id].offset = lbl_8042CF6C->arenaNext;
		lbl_8042CF6C->regions[id].size   = n;
		lbl_8042CF6C->arenaNext += n;
		lbl_8042CF6C->arenaFree -= n;
	}
	if (result != 0) {
		OSReport(lbl_8023D568, id);
	}
	return result;
}
}
