// Copy callback of the plugin whose data sits at the lbl_8042C828 offset (HYPOTHESIS): copies the
// leading word and, when the source holds a list that is not flagged shared (bit 0), creates a
// list with the same count (fn_8013ED8C, passing the source flags and the value at 0x20 of its
// owner) and copies the three words of each 16-byte entry, clearing the fourth; the copy then
// owns the new list, whose owner pointer at 0x14 is set to the destination. Returns the
// destination. Field names are inferred from this function only.
#include "types.h"

struct Entry8013E78C {
	s32 word0; // 0x0
	s32 word4; // 0x4
	s32 word8; // 0x8
	s32 wordC; // 0xC
};

struct Owner8013E78C {
	u8 pad0[0x20];
	s32 value; // 0x20
};

struct List8013E78C {
	u32 flags; // 0x0
	s32 count; // 0x4
	u8 pad8[0x8];
	Entry8013E78C* entries; // 0x10
	void* object;           // 0x14
	u8 pad18[0x8];
	Owner8013E78C* owner; // 0x20
};

struct Data8013E78C {
	s32 word0;          // 0x0
	List8013E78C* list; // 0x4
};

extern "C" {
extern s32 lbl_8042C828;

List8013E78C* fn_8013ED8C(s32 count, s32 a, s32 b, u32 flags, s32 value);

void* fn_8013E78C(void* dst, void* src)
{
	List8013E78C* list;
	Data8013E78C* source = (Data8013E78C*)((u8*)src + lbl_8042C828);
	Data8013E78C* copy   = (Data8013E78C*)((u8*)dst + lbl_8042C828);

	list = source->list;

	copy->word0 = source->word0;
	if (list && !(list->flags & 1)) {
		List8013E78C* newList = fn_8013ED8C(list->count, 0, 0, list->flags, list->owner->value);
		s32 i;
		for (i = 0; i < newList->count; i++) {
			newList->entries[i].wordC = 0;
			newList->entries[i].word8 = list->entries[i].word8;
			newList->entries[i].word4 = list->entries[i].word4;
			newList->entries[i].word0 = list->entries[i].word0;
		}
		copy->list      = newList;
		newList->object = dst;
	}
	return dst;
}
}
