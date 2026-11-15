// Sets up a pipeline entry in a heap (HYPOTHESIS: one of the GameCube driver's instance-heap
// helpers of the module opened by fn_801B3474): clears the 0x28-byte entry, rejects a descriptor
// with more than 32 elements at +0x2C or +0x20, or with +0x2C not below the module limit at +0x38
// (errors 0x29, 0x28 and 0x2A of plugin 1). A valid descriptor gets its element slots (heap
// block after the 0x28-byte headers, 0x80 bytes per entry, all set to -1) and a cleared
// three-word record (after the slot area, 0xC bytes per entry), and the heap count grows.
// Returns 1, or 0 when the descriptor is rejected. Names are inferred from this function only.
// NonMatching: retail adds the heap base to the header area first and then the per-entry offset,
// while the compiler folds this source's offsets before adding the base, which shifts the
// registers of both address computations (43 words, one instruction). Typed pointer arithmetic
// is folded the same way.
#include "game/rw_module_801B3414.h"
#include "MSL_C/string.h"

struct Heap801B3E58 {
	u8 pad0[0x4];
	u32 count; // 0x4
	u8* base;  // 0x8
};

struct Record801B3E58 {
	s32 a; // 0x0
	s32 b; // 0x4
	s32 c; // 0x8
};

struct Descriptor801B3E58 {
	u8 pad0[0x20];
	u32 numB; // 0x20
	u8 pad24[0x2C - 0x24];
	u32 numA; // 0x2C
};

struct Entry801B3E58 {
	Descriptor801B3E58* descriptor; // 0x0
	u32 numSlots;                   // 0x4
	s32* slots;                     // 0x8
	u8 padC[0x1C - 0xC];
	Record801B3E58* record; // 0x1C
	s32 value20;            // 0x20
	s32 value24;            // 0x24
};

#define MODULE_801B3E58_LIMIT (*(u32*)(RW_MODULE_801B3414_GLOBALS + 0x38))

static inline void RecordError801B3E58(s32 code)
{
	RwError error;
	error.pluginID  = 1;
	error.errorCode = fn_8019408C(code);
	fn_80193FE8(&error);
}

extern "C" {
s32 fn_801B3E58(Heap801B3E58* heap, Entry801B3E58* entry, Descriptor801B3E58* descriptor)
{
	s32 ok;
	u32 numA;

	numA = descriptor->numA;
	ok   = 1;

	memset(entry, 0, sizeof(Entry801B3E58));
	if (numA > 32) {
		RecordError801B3E58(0x29);
		ok = 0;
	}
	if (descriptor->numB > 32) {
		RecordError801B3E58(0x28);
		ok = 0;
	}
	if (numA >= MODULE_801B3E58_LIMIT) {
		RecordError801B3E58(0x2A);
		ok = 0;
	}
	if (ok) {
		s32* slot;
		Record801B3E58* record;
		u32 i;

		slot            = (s32*)(heap->base + MODULE_801B3E58_LIMIT * 0x28 + heap->count * 0x80);
		entry->slots    = slot;
		entry->numSlots = numA;
		for (i = 0; i < entry->numSlots; i++) {
			*slot++ = -1;
		}
		record            = (Record801B3E58*)(heap->base + MODULE_801B3E58_LIMIT * 0x28
		    + MODULE_801B3E58_LIMIT * 0x80 + heap->count * 0xC);
		record->a         = 0;
		record->b         = 0;
		record->c         = 0;
		entry->record     = record;
		entry->value20    = 0;
		entry->value24    = 0;
		entry->descriptor = descriptor;
		heap->count++;
	}
	return ok;
}
}
