#include "types.h"

// TObjPole's TDisp and Disp (the PS2 build's names), the same in the thirteen
// stage modules that share the engine core. Neither draws anything: TDisp only
// tests the game state's mode byte at 0x20 and returns, and Disp is empty.

extern "C" u8* lbl_8042C180;

extern "C" void TDisp__8TObjPoleFv(void* pole)
{
	if ((s8)lbl_8042C180[0x20] != 0) {
		return;
	}
}

extern "C" void Disp__8TObjPoleFv(void* pole) { }
