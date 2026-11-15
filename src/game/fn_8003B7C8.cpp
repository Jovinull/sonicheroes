// Records a hit between entry `entryA` of collision object `a` and entry `entryB` of object `b`
// (entries are 0x30 bytes, from the list at +0x10). Unless flag 8 of entryA or flag 4 of entryB is
// set, `a` gets bit 0 of +0x8, and its first free hit slot (8 slots of 8 bytes at +0x14, free
// when the second byte is -1) takes both entry indices and `b`, counting the hit at +0x2; the same
// is done the other way for `b` (flag 8 of entryB, flag 4 of entryA). The first argument is unused.
// HYPOTHESIS: part of the C_COLLI/CCL collision code; the flag meanings are UNKNOWN.
#include "types.h"

struct Entry8003B7C8 {
	u8 pad0[4];
	u32 flags; // 0x4
	u8 pad8[0x30 - 0x8];
};

struct Object8003B7C8;

struct Hit8003B7C8 {
	s8 entry;      // 0x0 (this object's entry)
	s8 otherEntry; // 0x1 (-1: free)
	u8 pad2[2];
	Object8003B7C8* other; // 0x4
};

struct Object8003B7C8 {
	u8 pad0[2];
	s16 hitCount; // 0x2
	u8 pad4[4];
	u16 flags; // 0x8
	u8 padA[0x10 - 0xA];
	Entry8003B7C8* entries; // 0x10
	Hit8003B7C8 hits[8];    // 0x14
};

extern "C" void fn_8003B7C8(
    s32 unused, Object8003B7C8* a, Entry8003B7C8* entryA, Object8003B7C8* b, Entry8003B7C8* entryB)
{
	s32 indexA;
	s32 indexB;
	Entry8003B7C8* e;
	Hit8003B7C8* hit;
	Hit8003B7C8* end;

	for (e = a->entries, indexA = 0; e < entryA; e++) {
		indexA++;
	}
	for (e = b->entries, indexB = 0; e < entryB; e++) {
		indexB++;
	}
	if (!(entryA->flags & 8) && !(entryB->flags & 4)) {
		end = &a->hits[8];
		a->flags |= 1;
		for (hit = a->hits; hit < end; hit++) {
			if (hit->otherEntry == -1) {
				a->hitCount++;
				hit->entry      = indexA;
				hit->otherEntry = indexB;
				hit->other      = b;
				break;
			}
		}
	}
	if (!(entryB->flags & 8) && !(entryA->flags & 4)) {
		end = &b->hits[8];
		b->flags |= 1;
		for (hit = b->hits; hit < end; hit++) {
			if (hit->otherEntry == -1) {
				b->hitCount++;
				hit->entry      = indexB;
				hit->otherEntry = indexA;
				hit->other      = a;
				break;
			}
		}
	}
}
