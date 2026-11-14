// Creates a group table (HYPOTHESIS: the table fn_8020530C indexes): takes one from free list 9 of
// lbl_8040EB50 and gives it an empty list of 16-byte groups; when the list cannot be created the
// table is destroyed again (each group's id list released and its words reset to -1, then the
// group list itself) and returned to the free list. Returns the table, or null.
#include "game/free_lists_8040EB50.h"

#define FREE_LIST_8040EB50_GROUP_TABLE 9

struct Group80205354 {
	s32 word0;    // 0x0
	s32 word4;    // 0x4
	RwSList* ids; // 0x8
	s32 wordC;    // 0xC
};

struct GroupTable80205354 {
	RwSList* groups; // 0x0
	s32 valid;       // 0x4
};

extern "C" {
RwSList* fn_80194318(s32 entrySize);
s32 fn_80194628(RwSList* list);
s32 fn_8019469C(RwSList* list);
void* fn_8019460C(RwSList* list);
}

static inline GroupTable80205354* GroupTableInit(GroupTable80205354* table)
{
	RwSList* groups = fn_80194318(sizeof(Group80205354));

	table->groups = groups;
	if (!groups) {
		return 0;
	}
	table->valid = 1;
	return table;
}

static inline void GroupTableDestroy(GroupTable80205354* table)
{
	if (table->groups) {
		s32 i;
		s32 count             = fn_8019469C(table->groups);
		Group80205354* groups = (Group80205354*)fn_8019460C(table->groups);
		if (count > 0 && groups) {
			for (i = 0; i < count; i++) {
				if (groups->ids) {
					fn_80194628(groups->ids);
				}
				groups->ids   = 0;
				groups->word0 = -1;
				groups->word4 = -1;
				groups->wordC = -1;
				groups++;
			}
		}
		fn_80194628(table->groups);
		table->groups = 0;
	}
	table->valid = 0;
	lbl_8042C9A4->freeListFree(lbl_8040EB50.lists[FREE_LIST_8040EB50_GROUP_TABLE], table);
}

extern "C" {
GroupTable80205354* fn_80205354(void)
{
	GroupTable80205354* table = (GroupTable80205354*)lbl_8042C9A4->freeListAlloc(
	    lbl_8040EB50.lists[FREE_LIST_8040EB50_GROUP_TABLE]);

	if (!table) {
		return 0;
	}
	if (!GroupTableInit(table)) {
		GroupTableDestroy(table);
		table = 0;
	}
	return table;
}
}
