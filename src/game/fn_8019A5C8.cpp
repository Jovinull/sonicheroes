// Writes a string to a stream as a string chunk (HYPOTHESIS: _rwStringStreamWrite): a null string
// is written as the empty string lbl_8042F6C8; the chunk holds the terminated string padded to four
// bytes (the size computation of fn_8019A588 is inlined), with a header written through fn_80192ED8
// (HYPOTHESIS: _rwStreamWriteVersionedChunkHeader, library version 0x35000, build 0xFFFF) and the
// data through fn_80197B48 (HYPOTHESIS: RwStreamWrite). Returns the string, or null on a write
// failure.
#include "game/rw_engine.h"

#define RW_ID_STRING               2
#define RW_LIBRARY_CURRENT_VERSION 0x35000
#define RW_LIBRARY_CURRENT_BUILD   0xFFFF

extern "C" {
extern const char lbl_8042F6C8[8];
void* fn_80192ED8(void* stream, s32 type, u32 size, u32 version, u32 buildNum);
void* fn_80197B48(void* stream, const void* buffer, u32 length);
}

// Same body as fn_8019A588 (_rwStringStreamGetSize).
static inline u32 StringStreamGetSize(const char* string)
{
	if (string == 0) {
		string = lbl_8042F6C8;
	}
	return (lbl_8042C9A4->rwstrlen(string) + 4) & ~3;
}

extern "C" {
const char* fn_8019A5C8(const char* string, void* stream)
{
	u32 size;
	if (string == 0) {
		string = lbl_8042F6C8;
	}
	size = StringStreamGetSize(string);
	if (fn_80192ED8(
	        stream, RW_ID_STRING, size, RW_LIBRARY_CURRENT_VERSION, RW_LIBRARY_CURRENT_BUILD)
	    == 0) {
		return 0;
	}
	if (fn_80197B48(stream, string, size) != 0) {
		return string;
	}
	return 0;
}
}
