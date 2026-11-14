// Posts an ARAM transfer on the first free request of the audio system (see
// game/audio_system.h), records argA/argB for it and, unless async is set,
// spins until its busy byte is cleared (by fn_80205B08, the completion
// callback). Returns the request index. With all 0x40 requests busy it reports
// lbl_8023D4C8 with lbl_8023D4EC and line 0xC2 and hangs.
#include "game/audio_system.h"

extern "C" {
#include "dolphin/os.h"

extern char lbl_8023D4C8[];
extern char lbl_8023D4EC[];
void fn_80205B08(u32 request);

static inline int FindFreeArqRequest(void)
{
	int i;
	for (i = 0; i < 0x40; i++) {
		if (lbl_8042CF6C->busy[i] == 0) {
			return i;
		}
	}
	OSReport(lbl_8023D4C8, lbl_8023D4EC, 0xC2);
	while (1) {
	}
}

int fn_80205848(
    u32 source, u32 destination, u32 length, unsigned int argA, unsigned int argB, int async)
{
	int i                        = FindFreeArqRequest();
	lbl_8042CF6C->busy[i]        = 1;
	lbl_8042CF6C->requestArgA[i] = argA;
	lbl_8042CF6C->requestArgB[i] = argB;
	ARQPostRequest(&lbl_8042CF6C->requests[i], lbl_8042CF6C->arqOwner, 0, 1, source, destination,
	    length, fn_80205B08);
	{
		volatile PoolSystem* sys  = lbl_8042CF6C;
		volatile unsigned char* b = &sys->busy[i];
		if (async == 0) {
			while (*b != 0) {
			}
		}
	}
	return i;
}
}
