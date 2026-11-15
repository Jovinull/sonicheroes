// Applies a packed list of entry updates to the entry table of a context (HYPOTHESIS): each record
// is a 0x10-byte header (flags, entry index) followed by the optional blocks its flags select: a
// 0x40-byte block (flag 0x1, to +0xC), three 0x10-byte blocks (flags 0x2/0x4/0x8, to +0x50,
// +0x64 and +0x78) and a 0x10-byte block of two references resolved through fn_80202274 (flag
// 0x10, to +0x8C). Each copied block sets its own valid word and the entry's changed word. Flag
// 0x20 ends the list. Returns the source. Names are inferred from this function only.
#include "game/rw_engine.h"
#include "MSL_C/string.h"

struct UpdateHeader80201B10 {
	u32 flags; // 0x0: UPDATE_80201B10_* bits
	s32 index; // 0x4: entry index in the context table
	u8 pad8[0x8];
};

#define UPDATE_80201B10_BLOCK_C  0x1
#define UPDATE_80201B10_BLOCK_50 0x2
#define UPDATE_80201B10_BLOCK_64 0x4
#define UPDATE_80201B10_BLOCK_78 0x8
#define UPDATE_80201B10_BLOCK_8C 0x10
#define UPDATE_80201B10_END      0x20

// Flag 0x10 block: two references resolved through fn_80202274, then two words.
struct Block8C80201B10 {
	void* references[2]; // 0x0
	u8 pad8[0x8];
};

struct Entry80201B10 {
	s32 changed; // 0x0
	u8 pad4[0x4];
	s32 validC;              // 0x8
	u8 blockC[0x40];         // 0xC
	s32 valid50;             // 0x4C
	u8 block50[0x10];        // 0x50
	s32 valid64;             // 0x60
	u8 block64[0x10];        // 0x64
	s32 valid78;             // 0x74
	u8 block78[0x10];        // 0x78
	s32 valid8C;             // 0x88
	Block8C80201B10 block8C; // 0x8C
};

struct Context80201B10 {
	u8 pad0[0xC];
	RwSList* entries; // 0xC
};

struct Source80201B10 {
	u8 pad0[0x8];
	u8* updates; // 0x8
};

extern "C" {
void* fn_8019472C(RwSList* sList, s32 index);
void* fn_80202274(Context80201B10* context, void* reference);

Source80201B10* fn_80201B10(Source80201B10* source, Context80201B10* context)
{
	u8* cur                      = source->updates;
	UpdateHeader80201B10* header = (UpdateHeader80201B10*)cur;

	while (!(header->flags & UPDATE_80201B10_END)) {
		Entry80201B10* entry = (Entry80201B10*)fn_8019472C(context->entries, header->index);
		cur += sizeof(UpdateHeader80201B10);
		if (header->flags & UPDATE_80201B10_BLOCK_C) {
			memcpy(entry->blockC, cur, sizeof(entry->blockC));
			cur += sizeof(entry->blockC);
			entry->validC  = 1;
			entry->changed = 1;
		}
		if (header->flags & UPDATE_80201B10_BLOCK_50) {
			memcpy(entry->block50, cur, sizeof(entry->block50));
			cur += sizeof(entry->block50);
			entry->valid50 = 1;
			entry->changed = 1;
		}
		if (header->flags & UPDATE_80201B10_BLOCK_64) {
			memcpy(entry->block64, cur, sizeof(entry->block64));
			cur += sizeof(entry->block64);
			entry->valid64 = 1;
			entry->changed = 1;
		}
		if (header->flags & UPDATE_80201B10_BLOCK_78) {
			memcpy(entry->block78, cur, sizeof(entry->block78));
			cur += sizeof(entry->block78);
			entry->valid78 = 1;
			entry->changed = 1;
		}
		if (header->flags & UPDATE_80201B10_BLOCK_8C) {
			memcpy(&entry->block8C, cur, sizeof(entry->block8C));
			entry->valid8C               = 1;
			entry->changed               = 1;
			entry->block8C.references[0] = fn_80202274(context, entry->block8C.references[0]);
			entry->block8C.references[1] = fn_80202274(context, entry->block8C.references[1]);
			cur += sizeof(entry->block8C);
		}
		header = (UpdateHeader80201B10*)cur;
	}
	return source;
}
}
