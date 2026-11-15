// Copies an instance heap into another one (HYPOTHESIS: the copy helper of the GameCube driver's
// instance heaps, the module opened by fn_801B3474; see fn_801B3E58). Unless both are the same
// heap, copies every 0x28-byte entry from the last one down, clears its four words at 0xC-0x18 and
// duplicates its 0x24-byte-sized data block (raising the out-of-memory error and returning 0 when
// the allocation fails), then takes the source count. The entries are then re-pointed at the
// destination's own slot blocks (0x80 bytes each, copied when the source has one) and cleared
// three-word records. Returns 1. Names are inferred.
// NonMatching: the slot and record loops get permuted registers (counter, offset, slot pointer
// and area base, 23 words). Tried permuted declarations and a separate slot-loop counter (which
// adds an instruction).
#include "game/rw_module_801B3414.h"
#include "MSL_C/string.h"

struct Record801B3C44 {
	s32 a; // 0x0
	s32 b; // 0x4
	s32 c; // 0x8
};

struct Entry801B3C44 {
	void* descriptor;       // 0x0
	u32 numSlots;           // 0x4
	s32* slots;             // 0x8
	s32 valueC;             // 0xC
	s32 value10;            // 0x10
	s32 value14;            // 0x14
	s32 value18;            // 0x18
	Record801B3C44* record; // 0x1C
	void* data;             // 0x20
	u32 dataSize;           // 0x24
};

struct Heap801B3C44 {
	u8 pad0[0x4];
	u32 count;              // 0x4
	Entry801B3C44* entries; // 0x8
};

#define ENTRY_SLOTS_SIZE      0x80
#define MODULE_801B3C44_LIMIT (*(u32*)(RW_MODULE_801B3414_GLOBALS + 0x38))

extern "C" {
s32 fn_801B3C44(Heap801B3C44* dst, Heap801B3C44* src)
{
	u8* area;
	u8* slots;
	Record801B3C44* record;
	s32 i;
	u32 j;

	if (dst != src) {
		for (i = src->count - 1; i >= 0; i--) {
			memcpy(&dst->entries[i], &src->entries[i], sizeof(Entry801B3C44));
			dst->entries[i].valueC  = 0;
			dst->entries[i].value10 = 0;
			dst->entries[i].value14 = 0;
			dst->entries[i].value18 = 0;
			if (dst->entries[i].dataSize != 0) {
				dst->entries[i].data = lbl_8042C9A4->rwmalloc(dst->entries[i].dataSize);
				if (dst->entries[i].data == 0) {
					RwError error;
					error.pluginID  = RW_ID_CORE_PLUGIN;
					error.errorCode = fn_8019408C(RW_ERROR_NO_MEMORY, dst->entries[i].dataSize);
					fn_80193FE8(&error);
					return 0;
				}
				memcpy(dst->entries[i].data, src->entries[i].data, dst->entries[i].dataSize);
			}
		}
		dst->count = src->count;
	}

	area  = (u8*)&dst->entries[MODULE_801B3C44_LIMIT];
	slots = area + (src->count - 1) * ENTRY_SLOTS_SIZE;
	for (i = src->count - 1; i >= 0; i--) {
		dst->entries[i].slots = (s32*)slots;
		if (src->entries[i].slots != 0) {
			memcpy(dst->entries[i].slots, src->entries[i].slots, ENTRY_SLOTS_SIZE);
		}
		slots -= ENTRY_SLOTS_SIZE;
	}

	record = (Record801B3C44*)(area + MODULE_801B3C44_LIMIT * ENTRY_SLOTS_SIZE);
	for (j = 0; j < src->count; j++) {
		record->a              = 0;
		record->b              = 0;
		record->c              = 0;
		dst->entries[j].record = record;
		record++;
	}
	return 1;
}
}
