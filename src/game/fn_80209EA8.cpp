#include "types.h"

// Stores whether the input is nonzero in the audio state byte at offset 0xFDFA.
extern "C" {
struct Audio80209EA8 {
	u8 pad[0xFDFA];
	s8 fdfa;
};
extern Audio80209EA8* lbl_8042CF6C;

void fn_80209EA8(s32 value)
{
	lbl_8042CF6C->fdfa = (value != 0);
}
}
