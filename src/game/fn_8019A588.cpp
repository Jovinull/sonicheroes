// Returns the stream size of a string: its length plus the terminator, rounded
// up to a multiple of four bytes; a null string counts as the empty string
// lbl_8042F6C8 (an 8-byte .sdata2 object).
#include "game/rw_engine.h"

extern "C" {
extern const char lbl_8042F6C8[8];

u32 fn_8019A588(const char* string)
{
	if (string == 0) {
		string = lbl_8042F6C8;
	}
	return (lbl_8042C9A4->rwstrlen(string) + 4) & ~3;
}
}
