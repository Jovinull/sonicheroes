#include "types.h"

// Replaces the top byte of the pointed-to word with the given value.

extern "C" void fn_16_469A0(s32 self, s32* word, u8 value)
{
	*word = (value << 24) | (*word & 0x00FFFFFF);
}
