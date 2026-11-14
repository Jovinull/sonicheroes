// Reads a named record of the module around 0x8014A3A0 from a stream (HYPOTHESIS): a 0x28-byte
// header (32-byte name, then the entry count and a kind converted from little-endian with
// fn_80193270) read with fn_801979AC (HYPOTHESIS: RwStreamRead), count 12-byte entries read into
// an engine heap block with fn_801937A0 (HYPOTHESIS: RwStreamReadReal); fn_8014D92C builds the
// record from them, which then takes the name and type byte 0xC. Returns the record, or null on
// a short read or allocation failure (core error 0x80000013 with the size, plugin 0x102).
#include "game/rw_engine.h"

struct Header8014D05C {
	char name[0x20]; // 0x0
	s32 count;       // 0x20
	s32 kind;        // 0x24
};

struct Record8014D05C {
	u8 type; // 0x0
	u8 pad1[0x17];
	char name[0x20]; // 0x18
};

extern "C" {
u32 fn_801979AC(void* stream, void* buffer, u32 length);
void* fn_80193270(void* mem, u32 size);
void* fn_801937A0(void* stream, void* buffer, u32 length);
Record8014D05C* fn_8014D92C(s32 count, s32 kind, void* entries);

Record8014D05C* fn_8014D05C(void* stream)
{
	Header8014D05C header;
	u32 size;
	void* entries;
	Record8014D05C* record;
	s32 count;

	if (fn_801979AC(stream, &header, sizeof(header)) != sizeof(header)) {
		return 0;
	}
	fn_80193270(&header.count, sizeof(header.count));
	fn_80193270(&header.kind, sizeof(header.kind));
	count   = header.count;
	size    = count * 12;
	entries = lbl_8042C9A4->rwmalloc(size);
	if (!entries) {
		RwError error;
		error.pluginID  = 0x102;
		error.errorCode = fn_8019408C(RW_ERROR_NO_MEMORY, size);
		fn_80193FE8(&error);
		return 0;
	}
	if (!fn_801937A0(stream, entries, size)) {
		return 0;
	}
	record = fn_8014D92C(count, header.kind, entries);
	lbl_8042C9A4->rwstrncpy(record->name, header.name, sizeof(record->name));
	record->type = 0xC;
	lbl_8042C9A4->rwfree(entries);
	return record;
}
}
