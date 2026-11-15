#include "game/rw_engine.h"

// Releases what a PARTICLE_MATERIAL holds (called by its destructor and by fn_80065E84): runs
// fn_80064DF4 over its node list, deletes its owned block (+0x34; see MaterialBlock), unlinks it
// from the particle manager's material list (lbl_8042C2E0, head at +0x28) when it is registered,
// and releases +0x30 with fn_8019E480. HYPOTHESIS: the PS2 name and the field roles are UNKNOWN.

struct Clump80064CA8 {
	u8 pad0[0x4];
	void* unknown4; // 0x4
};

extern "C" {
void fn_80152220(Clump80064CA8* clump, s32 unknown);
void fn_801FD1F4(Clump80064CA8* clump);
void fn_8019E480(void* unknown);
}

// Owned block at +0x34. Its destructor is inline (the retail code repeats delete's null check).
struct MaterialBlock {
	~MaterialBlock()
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
				fn_80152220(unknownC, 0);
			}
			fn_801FD1F4(unknownC);
			unknownC = NULL;
		}
	}

	u8 pad0[0x4];
	void* unknown4; // 0x4
	u8 pad8[0xC - 0x8];
	Clump80064CA8* unknownC; // 0xC
	void* unknown10;         // 0x10
};

struct Material80064CA8 {
	u8 pad0[0x8];
	s32 registered; // 0x8 (1 once in the manager's list)
	u8 padC[0x30 - 0xC];
	void* unknown30;      // 0x30
	MaterialBlock* block; // 0x34
	u8 pad38[0x44 - 0x38];
	Material80064CA8* prev; // 0x44
	Material80064CA8* next; // 0x48
};

struct Manager80064CA8 {
	u8 pad0[0x28];
	Material80064CA8* materials; // 0x28
};

extern "C" {
extern Manager80064CA8* lbl_8042C2E0;
void fn_80064DF4(Material80064CA8* material);
}

extern "C" void fn_80064CA8(Material80064CA8* material)
{
	fn_80064DF4(material);
	if (material->block != NULL) {
		delete material->block;
		material->block = NULL;
	}
	if (material->registered) {
		Material80064CA8* next;
		if (material == lbl_8042C2E0->materials) {
			next = material->next;
			if (next == NULL) {
				lbl_8042C2E0->materials = NULL;
			} else {
				next->prev              = NULL;
				lbl_8042C2E0->materials = next;
			}
		} else {
			next = material->next;
			if (next != NULL) {
				next->prev = material->prev;
			}
			material->prev->next = next;
		}
		material->prev       = NULL;
		material->next       = NULL;
		material->registered = 0;
	}
	if (material->unknown30 != NULL) {
		fn_8019E480(material->unknown30);
		material->unknown30 = NULL;
	}
}
