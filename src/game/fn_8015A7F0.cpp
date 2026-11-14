// Sync callback that fn_8015A8EC installs on atomics (HYPOTHESIS: the world plugin's atomic sync
// hook): runs the sync callback it replaced (kept in the atomic's world plugin data) and, when
// that succeeds and the atomic belongs to a world, unlinks and frees each of its sector ties that
// is attached to both an atomic and a sector (tie free list at the lbl_8042C928 offset of the
// engine globals), then re-adds the atomic to the world's sectors through fn_8015A610. Returns
// the atomic, or null when the original sync fails. Field names are inferred from these units.
#include "game/rw_engine.h"

struct Atomic8015A7F0;

// Link between an atomic and a world sector (HYPOTHESIS: RpTie).
struct Tie8015A7F0 {
	RwLLLink sectorLink; // 0x0
	void* atomic;        // 0x8
	RwLLLink atomicLink; // 0xC
	void* sector;        // 0x14
};

// World plugin data of an atomic (layout from fn_8015A8EC).
struct WorldData8015A7F0 {
	void* world;                                     // 0x0
	Atomic8015A7F0* (*sync)(Atomic8015A7F0* atomic); // 0x4: replaced sync callback
};

struct Atomic8015A7F0 {
	u8 pad0[0x64];
	RwLinkList ties; // 0x64
};

extern "C" {
// Offset of the world plugin data in an atomic and of the tie free list in the engine globals.
extern s32 lbl_8042C91C;
extern s32 lbl_8042C928;

void fn_8015A610(void* world, Atomic8015A7F0* atomic);

Atomic8015A7F0* fn_8015A7F0(Atomic8015A7F0* atomic)
{
	RwLLLink* link;
	WorldData8015A7F0* data;
	void* world;
	Tie8015A7F0* tie;

	data = (WorldData8015A7F0*)((u8*)atomic + lbl_8042C91C);

	if (data->sync(atomic)) {
		world = data->world;
		if (world) {
			link = atomic->ties.link.next;
			while (link != &atomic->ties.link) {
				tie  = (Tie8015A7F0*)((u8*)link - 0xC);
				link = link->next;
				if (tie->atomic && tie->sector) {
					RwLLLinkRemove(&tie->atomicLink);
					RwLLLinkRemove(&tie->sectorLink);
					lbl_8042C9A4->freeListFree(
					    *(RwFreeList**)((u8*)lbl_8042C9A4 + lbl_8042C928), tie);
				}
			}
			fn_8015A610(world, atomic);
		}
		return atomic;
	}
	return 0;
}
}
