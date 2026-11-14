// Walks the sector tree of a world depth first with an explicit stack (HYPOTHESIS: RpWorld sector
// iteration) and, for every leaf sector (negative type) that has no data at 0x80 yet, builds it:
// fn_80155864 resolves the sector's key at 0x8C and fn_80158B5C attaches the result with the
// world's entry for the sector index at 0x88. Returns the world, or null when either step fails.
// Field names are inferred from this function only.
// NonMatching: when pushing the right child the retail code loads the left child before the
// stack store; ours stores first (2 words differ, also under GC/2.0).
#include "types.h"

struct Sector801595B8 {
	s32 type; // 0x0: negative for leaf sectors
	u8 pad4[0x4];
	Sector801595B8* left;  // 0x8
	Sector801595B8* right; // 0xC
	u8 pad10[0x80 - 0x10];
	void* data; // 0x80
	u8 pad84[0x4];
	u16 index; // 0x88
	u8 pad8A[0x2];
	u16 key; // 0x8C
};

struct World801595B8 {
	u8 pad0[0x10];
	void** entries; // 0x10
	u8 pad14[0x8];
	Sector801595B8* root; // 0x1C
};

extern "C" {
void* fn_80155864(u16 key);
World801595B8* fn_80158B5C(
    World801595B8* world, void* resolved, Sector801595B8* sector, void** entry);

World801595B8* fn_801595B8(World801595B8* world)
{
	Sector801595B8* stack[64];
	Sector801595B8* sector = world->root;
	s32 top                = 0;

	do {
		if (sector->type < 0) {
			void** entry = &world->entries[sector->index];
			if (!sector->data) {
				void* resolved = fn_80155864(sector->key);
				if (resolved) {
					world = fn_80158B5C(world, resolved, sector, entry);
					if (!world) {
						return 0;
					}
				} else {
					return 0;
				}
			}
			sector = stack[top--];
		} else {
			stack[++top] = sector->right;
			sector       = sector->left;
		}
	} while (top >= 0);
	return world;
}
}
