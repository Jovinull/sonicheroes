#include "types.h"

extern "C" s32 fn_2_0(void* context, const u16* text)
{
	if (text == NULL) {
		return 1;
	}

	s32 line_count = 1;
	s32 character;
	while ((character = *text) != 0) {
		if (character == '\n') {
			line_count++;
		}
		text++;
	}

	return line_count;
}
