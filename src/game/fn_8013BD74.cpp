// Frees a table of 8-byte entries through RwFree: the data pointer (0x4) of each of the `count`
// entries when set, then the table itself. Returns 0. The table's role is UNKNOWN.
#include "game/rw_engine.h"

struct Entry8013BD74 {
	s32 f0;
	void* data; // 0x4
};

struct Table8013BD74 {
	u32 count;              // 0x0
	Entry8013BD74* entries; // 0x4
};

extern "C" s32 fn_8013BD74(Table8013BD74* table)
{
	u32 i;
	Entry8013BD74* entry = table->entries;
	for (i = 0; i < table->count; entry++, i++) {
		if (entry->data != NULL) {
			lbl_8042C9A4->rwfree(entry->data);
		}
	}
	lbl_8042C9A4->rwfree(table);
	return 0;
}
