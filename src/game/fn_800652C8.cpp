#include "game/rw_engine.h"

// Makes sure a PARTICLE_MATERIAL has its owned block (+0x34; see fn_80064CA8): materials without
// flag 0x10000 (+0x4) or with a block already need nothing (true); without the source description
// (+0x2C) the block cannot be built (false). The block is built from the source (fn_80063454 does
// the rest of the set-up) and dropped again when it has no buffer (+0x10) or no clump (+0xC);
// otherwise the clump is bound to +0x30 (fn_80152220). Returns whether the block exists.
// HYPOTHESIS: the PS2 name and the field roles are UNKNOWN.

struct Clump800652C8 {
	u8 pad0[0x4];
	void* unknown4; // 0x4
};

// Source description at +0x2C, copied into the block's 0x18-byte buffer.
struct Source800652C8 {
	s32 unknown0; // 0x0
	s16 count;    // 0x4 (0 means 50; HYPOTHESIS)
	u8 pad6[0x8 - 0x6];
	s32 unknown8;  // 0x8
	s32 unknownC;  // 0xC
	s32 unknown10; // 0x10
	s32 unknown14; // 0x14
};

struct Block800652C8;

extern "C" {
void fn_80152220(Clump800652C8* clump, void* unknown);
void fn_801FD1F4(Clump800652C8* clump);
void fn_80063454(Block800652C8* block);
}

// The owned block (MaterialBlock in fn_80064CA8). Both its constructor and its destructor are
// inline.
struct Block800652C8 {
	Block800652C8(Source800652C8* source)
	{
		unknown1               = 0;
		unknown0               = 0;
		unknown4               = NULL;
		unknownC               = NULL;
		unknownA               = 0;
		count                  = 0;
		unknown10              = (Source800652C8*)lbl_8042C9A4->rwmalloc(sizeof(Source800652C8));
		Source800652C8* buffer = unknown10;
		if (buffer != NULL) {
			buffer->unknown0  = source->unknown0;
			buffer->count     = source->count;
			buffer->unknown8  = source->unknown8;
			buffer->unknownC  = source->unknownC;
			buffer->unknown10 = source->unknown10;
			buffer->unknown14 = source->unknown14;
		} else {
			unknownC = NULL;
			return;
		}
		unknownA = 0;
		if (source->count != 0) {
			count = source->count;
		} else {
			count = 50;
		}
		fn_80063454(this);
	}

	~Block800652C8()
	{
		if (unknown4 != NULL) {
			delete (u8*)unknown4;
			unknown4 = NULL;
		}
		if (unknown10 != NULL) {
			lbl_8042C9A4->rwfree(unknown10);
			unknown10 = NULL;
		}
		if (unknownC != NULL) {
			if (unknownC->unknown4 != NULL) {
				fn_80152220(unknownC, NULL);
			}
			fn_801FD1F4(unknownC);
			unknownC = NULL;
		}
	}

	u8 unknown0; // 0x0
	u8 unknown1; // 0x1
	u8 pad2[0x4 - 0x2];
	void* unknown4;            // 0x4
	s16 count;                 // 0x8
	s16 unknownA;              // 0xA
	Clump800652C8* unknownC;   // 0xC
	Source800652C8* unknown10; // 0x10
};

struct Material800652C8 {
	u8 pad0[0x4];
	u32 flags; // 0x4
	u8 pad8[0x2C - 0x8];
	Source800652C8* source; // 0x2C
	void* unknown30;        // 0x30
	Block800652C8* block;   // 0x34
};

static inline void Bind(Clump800652C8* clump, void* target)
{
	if (clump != NULL && target != NULL) {
		fn_80152220(clump, target);
	}
}

extern "C" bool fn_800652C8(Material800652C8* material)
{
	s32 flag = material->flags & 0x10000;

	if (flag == 0) {
		return true;
	}
	if (material->block == NULL) {
		if (material->source == NULL) {
			return false;
		}
		if (material->block == NULL && flag != 0) {
			material->block      = new Block800652C8(material->source);
			Block800652C8* block = material->block;
			if (block != NULL) {
				if (block->unknown10 == NULL || block->unknownC == NULL) {
					delete block;
					material->block = NULL;
				} else if (material->unknown30 != NULL) {
					Bind(block->unknownC, material->unknown30);
				}
			}
		}
		return material->block != NULL;
	}
	return true;
}
