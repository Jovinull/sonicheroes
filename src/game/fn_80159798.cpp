// Destroys a world (HYPOTHESIS: RpWorldDestroy): removes the world's entry from the world module's
// list (returning it to the module free list), releases the instanced data (+0x80) of every atomic
// sector by walking the sector tree with an explicit stack, runs fn_80154E54 on the block at +0x10,
// frees the sector tree (fn_80158DC4 when private flag 1 is set, fn_80158EAC otherwise), runs the
// world plugin destructors and frees the world. Returns 1.
// NonMatching: before the sector walk retail sets the stack index first and copies that zero into
// the register later stored into the released sectors (mr r29, r28); this source loads the root
// first and materialises both zeros (4 words). Declaration order, statement order, an inline
// release helper and other loop forms do not reproduce it.
#include "game/rw_engine.h"

// World list entry kept by the world module (link at +0x8).
struct WorldEntry80159798 {
	void* world; // 0x0
	u8 pad4[0x4];
	RwLLLink link; // 0x8
};

// World module globals (HYPOTHESIS): entry free list (+0x0) and the list of world entries (+0x4).
#define WORLD_80159798_ENTRY_FREE_LIST                                                             \
	(*(RwFreeList**)((u8*)lbl_8042C9A4 + lbl_8042C910.globalsOffset))
#define WORLD_80159798_WORLD_LIST                                                                  \
	(*(RwLinkList*)((u8*)lbl_8042C9A4 + lbl_8042C910.globalsOffset + 0x4))

// Sector node: negative types are atomic sectors, others are planes with two subtrees.
struct Sector80159798 {
	s32 type; // 0x0
	u8 pad4[0x4];
	Sector80159798* leftSubTree;  // 0x8
	Sector80159798* rightSubTree; // 0xC
	u8 pad10[0x80 - 0x10];
	void* instancedData; // 0x80: atomic sectors only
};

struct World80159798 {
	RwObject object; // 0x0
	u8 pad8[0x10 - 0x8];
	u8 block10[0xC];            // 0x10: passed to fn_80154E54
	Sector80159798* rootSector; // 0x1C
};

#define WORLD_80159798_SECTOR_STACK_SIZE 64

extern "C" {
// World module bookkeeping (HYPOTHESIS: worldModule) and plugin registry (worldTKList).
extern RwModuleInfo lbl_8042C910;
extern RwPluginRegistry lbl_8028D2E8;
// HYPOTHESIS: RwResourcesFreeResEntry.
void fn_801559E4(void* resEntry);
void fn_80154E54(void* block);
void fn_80158DC4(Sector80159798* rootSector);
void fn_80158EAC(Sector80159798* rootSector);

s32 fn_80159798(World80159798* world)
{
	RwLLLink* cur;
	RwLLLink* end;
	Sector80159798* stack[WORLD_80159798_SECTOR_STACK_SIZE];
	s32 sp;
	Sector80159798* sector;

	end = &WORLD_80159798_WORLD_LIST.link;
	for (cur = end->next; cur != end; cur = cur->next) {
		WorldEntry80159798* entry = (WorldEntry80159798*)((u8*)cur - 8);
		if (entry->world == world) {
			RwLLLinkRemove(&entry->link);
			lbl_8042C9A4->freeListFree(WORLD_80159798_ENTRY_FREE_LIST, entry);
			break;
		}
	}

	sp     = 0;
	sector = world->rootSector;
	do {
		if (sector->type < 0) {
			if (sector->instancedData != 0) {
				fn_801559E4(sector->instancedData);
				sector->instancedData = 0;
			}
			sector = stack[sp--];
		} else {
			stack[++sp] = sector->rightSubTree;
			sector      = sector->leftSubTree;
		}
	} while (sp >= 0);

	fn_80154E54(world->block10);
	if (world->object.privateFlags & 1) {
		fn_80158DC4(world->rootSector);
		fn_80198E04(&lbl_8028D2E8, world);
		lbl_8042C9A4->rwfree(world);
	} else {
		fn_80158EAC(world->rootSector);
		fn_80198E04(&lbl_8028D2E8, world);
		lbl_8042C9A4->rwfree(world);
	}
	return 1;
}
}
