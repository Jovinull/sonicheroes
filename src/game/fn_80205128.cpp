// Reads a group table from a stream (HYPOTHESIS): creates and initialises the table when none is
// given (fn_80205354, fn_80205560), reads the group count, appends that many 0x10-byte groups and
// reads each one: its two ids, its list of s32 ids (count, then the ids into a growable list) and
// a final id; fields start at -1. Returns the table, or null on failure. Names are inferred from
// this function and fn_80203A6C.
#include "game/rw_engine.h"

struct Group80205128 {
	s32 id0;      // 0x0
	s32 id4;      // 0x4
	RwSList* ids; // 0x8: list of s32
	s32 idC;      // 0xC
};

struct GroupTable80205128 {
	RwSList* groups; // 0x0
};

extern "C" {
GroupTable80205128* fn_80205354(void);
void fn_80205560(GroupTable80205128* table);
// HYPOTHESIS: RwStreamReadInt32 and the SList helpers.
void* fn_80193884(void* stream, void* ints, u32 numBytes);
RwSList* fn_80194318(s32 entrySize);
void* fn_80194510(RwSList* sList, s32 count);
}

static inline Group80205128* ReadGroup80205128(Group80205128* group, void* stream)
{
	s32 numIds;

	group->id0 = -1;
	group->id4 = -1;
	group->idC = -1;
	group->ids = fn_80194318(sizeof(s32));
	if (fn_80193884(stream, &group->id0, sizeof(s32)) == 0) {
		return 0;
	}
	if (fn_80193884(stream, &group->id4, sizeof(s32)) == 0) {
		return 0;
	}
	if (fn_80193884(stream, &numIds, sizeof(numIds)) == 0) {
		return 0;
	}
	if (numIds > 0) {
		s32* ids;
		if (group->ids == 0) {
			group->ids = fn_80194318(sizeof(s32));
		}
		if (group->ids == 0) {
			return 0;
		}
		ids = (s32*)fn_80194510(group->ids, numIds);
		if (ids == 0) {
			return 0;
		}
		if (fn_80193884(stream, ids, numIds * sizeof(s32)) == 0) {
			return 0;
		}
	}
	if (fn_80193884(stream, &group->idC, sizeof(s32)) == 0) {
		return 0;
	}
	return group;
}

extern "C" {
GroupTable80205128* fn_80205128(void* unused, GroupTable80205128* table, void* stream)
{
	s32 count;

	if (table == 0) {
		table = fn_80205354();
		if (table == 0) {
			return 0;
		}
		fn_80205560(table);
	}
	if (fn_80193884(stream, &count, sizeof(count)) == 0) {
		return 0;
	}
	if (count > 0) {
		s32 i;
		Group80205128* group = (Group80205128*)fn_80194510(table->groups, count);
		if (group == 0) {
			return 0;
		}
		for (i = 0; i < count; i++) {
			if (ReadGroup80205128(group, stream) == 0) {
				return 0;
			}
			group++;
		}
	}
	return table;
}
}
