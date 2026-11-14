// Greedy colouring pass of the module around 0x801B56E8 (HYPOTHESIS): for each group, collects
// the colour bits already used by the owners of its entries, picks the lowest free colour,
// stores it in every entry and marks it used in their owners. Stores the number of colours in
// the result object and returns 0. Field names are inferred from this function only.
// NonMatching: the marking loop allocates node, entry and bit to r5/r6/r10 where the retail code
// uses r6/r10/r5 (10 words); declaration orders and loop forms tried so far do not reproduce it.
#include "types.h"

struct Owner801B6624 {
	u8 pad0[0x8];
	u32 usedColours; // 0x8
};

struct Entry801B6624 {
	u8 pad0[0x10];
	Entry801B6624* next;  // 0x10
	Owner801B6624* owner; // 0x14
	u8 pad18[0x4];
	u32 colour; // 0x1C
};

struct Node801B6624 {
	Entry801B6624* entries;  // 0x0
	Node801B6624* nextNode;  // 0x4
	Node801B6624* nextGroup; // 0x8
};

struct Graph801B6624 {
	Node801B6624* groups; // 0x0
};

struct Result801B6624 {
	u8 pad0[0xC];
	u32 numColours; // 0xC
};

extern "C" {
s32 fn_801B6624(Result801B6624* result, Graph801B6624* graph)
{
	u32 numColours = 0;
	Node801B6624* group;

	for (group = graph->groups; group; group = group->nextGroup) {
		Node801B6624* node;
		u32 used;
		Entry801B6624* entry;
		u32 colour;
		u32 bit;
		used = 0;
		node = group;

		do {
			for (entry = node->entries; entry; entry = entry->next) {
				used |= entry->owner->usedColours;
			}
			node = node->nextNode;
		} while (node);

		for (colour = 0; used & 1; colour++) {
			used >>= 1;
		}
		if (colour >= numColours) {
			numColours = colour + 1;
		}

		bit  = 1 << colour;
		node = group;
		do {
			for (entry = node->entries; entry; entry = entry->next) {
				entry->colour = colour;
				entry->owner->usedColours |= bit;
			}
			node = node->nextNode;
		} while (node);
	}
	result->numColours = numColours;
	return 0;
}
}
