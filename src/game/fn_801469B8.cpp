// (Re)creates the plugin 0x12C data block of an object for record index of lbl_803EC3F8: releases
// the block already stored at object + record->offset (its children at +0x08 through fn_801A491C,
// the block at +0x30 through fn_80147288, then the block itself), allocates 0x38 bytes plus the
// record's extra size, clears it and links it to the record, the given count and its extra area.
// Returns the object, or null when the allocation fails (error 0x80000013 of plugin 0x120).
// NonMatching: instruction stream and relocations match; only the saved-register assignment
// differs (retail: offset r31, record r30, count r29, object r28; 20 words). Declaration-order
// permutations and splitting the create step into an inline do not reproduce it.
#include "game/rw_engine.h"
#include "MSL_C/string.h"

// Record of lbl_803EC3F8 (layout from fn_801467E4 and fn_80146B08).
struct Rec801469B8 {
	s32 id;     // 0x0
	s32 key;    // 0x4
	s32 offset; // 0x8: offset of the data-block pointer in the object
	u32 extra;  // 0xC: extra bytes after the 0x38-byte block
};

// Data block (HYPOTHESIS: names inferred from this function and fn_80146B08).
struct Block801469B8 {
	Rec801469B8* record; // 0x0
	u32 count;           // 0x4: used child slots
	void* children[10];  // 0x8: released through fn_801A491C
	void* f30;           // 0x30: released through fn_80147288
	void* extraData;     // 0x34: points at the extra area, or null
};

#define PLUGIN_ID_801469B8 0x120

extern "C" {
extern Rec801469B8 lbl_803EC3F8[];
void fn_801A491C(void* child);
void fn_80147288(void* block);

static inline void ReleaseBlock801469B8(Block801469B8* block)
{
	void** p;
	u32 i;

	i = 0;
	p = (void**)block;
	for (; i < block->count; i++) {
		if (p[2] != 0) {
			fn_801A491C(p[2]);
			p[2] = 0;
		}
		p++;
	}
	if (block->f30 != 0) {
		fn_80147288(block->f30);
		block->f30 = 0;
	}
	lbl_8042C9A4->rwfree(block);
}

u8* fn_801469B8(u8* object, s32 index, u32 count)
{
	Rec801469B8* record;
	s32 offset;
	Block801469B8* block;
	u32 size;

	record = &lbl_803EC3F8[index];
	offset = record->offset;
	block  = *(Block801469B8**)(object + offset);
	if (block != 0) {
		ReleaseBlock801469B8(block);
	}

	size  = record->extra + sizeof(Block801469B8);
	block = (Block801469B8*)lbl_8042C9A4->rwmalloc(size);
	if (block == 0) {
		RwError error;
		error.pluginID  = PLUGIN_ID_801469B8;
		error.errorCode = fn_8019408C(RW_ERROR_NO_MEMORY, size);
		fn_80193FE8(&error);
		block = 0;
	} else {
		memset(block, 0, size);
		block->record = record;
		block->count  = count;
		if (record->extra != 0) {
			block->extraData = block + 1;
		}
	}
	*(Block801469B8**)(object + offset) = block;
	if (*(Block801469B8**)(object + offset) == 0) {
		return 0;
	}
	return object;
}
}
