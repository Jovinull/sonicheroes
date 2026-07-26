#include "types.h"

// The same line counter autosaveD carries at 0x0, plus the two one-liners the
// module keeps next to it.
//
// The translation unit runs from fn_1_A6D8 at 0xA6D8 to the end of fn_1_A714
// at 0xA72C. It touches no private data of its own, and the only label it
// reaches is a DOL global, which is why the three functions cut cleanly out of
// the run around them.
//
// fn_1_A714 ignores the object it is handed. The parameter is there because
// every caller passes one, which attract_object.c shows: the call site sets it
// up alongside the four beside it that do use theirs.

extern "C" u8 lbl_8042C0C0;

extern "C" void fn_1_A6D8(void) { }

extern "C" s32 fn_1_A6DC(void* context, const u16* text)
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

extern "C" s32 fn_1_A714(void* owner)
{
	return lbl_8042C0C0 == 0;
}
