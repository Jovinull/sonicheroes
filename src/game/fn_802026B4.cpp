// Finds the entry of a table with the given id and name (HYPOTHESIS): walks the 0x10-byte
// entries of the list at 0xC and compares each one whose id matches by the name string that
// fn_80202364 (a forwarder to the list entry lookup fn_8019472C) fetches from the name list at
// 0x1C. Stores the entry's index through the optional pointer and returns the entry, or null.
// Field names are inferred from this function only.
#include "game/rw_engine.h"

struct Entry802026B4 {
	u32 id;        // 0x0
	s32 nameIndex; // 0x4
	u8 pad8[0x8];
};

struct Table802026B4 {
	u8 pad0[0xC];
	RwSList* entries; // 0xC
	u8 pad10[0xC];
	RwSList* names; // 0x1C
};

extern "C" {
s32 fn_8019469C(RwSList* list);
void* fn_8019460C(RwSList* list);
const char* fn_80202364(RwSList* names, s32 index);

Entry802026B4* fn_802026B4(Table802026B4* table, u32 id, const char* name, s32* index)
{
	s32 count;
	Entry802026B4* entry;
	Entry802026B4* found;
	s32 i;
	const char* entryName;

	found = 0;
	if (table->entries) {
		count = fn_8019469C(table->entries);
		if (count > 0) {
			entry = (Entry802026B4*)fn_8019460C(table->entries);
			for (i = 0; i < count; i++) {
				entryName = fn_80202364(table->names, entry->nameIndex);
				if (entry->id == id && !lbl_8042C9A4->rwstrcmp(entryName, name)) {
					found = entry;
					if (index) {
						*index = i;
					}
					break;
				}
				entry++;
			}
		}
	}
	return found;
}
}
