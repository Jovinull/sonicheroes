// Returns 1 when one of the object's entries resolves (fn_80146BC8 with kind 6) to a record whose
// type-6 data (fn_801439D8) holds an item with state 2 or 3 or a kind in 2..9, otherwise 0
// (HYPOTHESIS). Field names are inferred from this function only.
#include "types.h"

struct Item8014535C {
	u8 pad0[0x4];
	s32 kind;  // 0x4
	s32 state; // 0x8
	u8 padC[0x18 - 0xC];
};

struct Data8014535C {
	u8 pad0[0x9];
	u8 itemCount; // 0x9
	u8 padA[0x44 - 0xA];
	Item8014535C* items; // 0x44
};

struct Typed8014535C {
	s32 type; // 0x0
};

struct Record8014535C {
	u8 pad0[0x30];
	Typed8014535C* typed; // 0x30
};

struct Entry8014535C {
	u8 pad0[0x8];
	void* key; // 0x8
};

struct Header8014535C {
	u8 pad0[0x4];
	u16 count; // 0x4
	u8 pad6[0x10 - 0x6];
	Entry8014535C entries[1]; // 0x10
};

struct Object8014535C {
	u8 pad0[0x4];
	Header8014535C* header; // 0x4
};

extern "C" {
Record8014535C* fn_80146BC8(void* key, s32 kind);
Data8014535C* fn_801439D8(Typed8014535C* typed);

s32 fn_8014535C(Object8014535C* object)
{
	Header8014535C* header;
	Entry8014535C* entry;
	s32 i;

	header = object->header;
	entry  = header->entries;

	for (i = 0; i < header->count; i++, entry++) {
		Record8014535C* record = fn_80146BC8(entry->key, 6);
		if (record && record->typed && record->typed->type == 6) {
			Data8014535C* data = fn_801439D8(record->typed);
			s32 j;
			for (j = 0; j < data->itemCount; j++) {
				Item8014535C* item = &data->items[j];
				if (item->state == 2 || item->state == 3 || (item->kind >= 2 && item->kind <= 9)) {
					return 1;
				}
			}
		}
	}
	return 0;
}
}
