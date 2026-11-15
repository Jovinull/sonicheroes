// Runs the GameCube all-in-one world-sector node (HYPOTHESIS: its node body): unless the current
// world is flagged 0x01000000, a sector with triangles and meshes reuses its instanced data when
// the mesh serial number still matches (moving the resource entry to the front of the resource
// list) or re-instances through the node's instance callback; then the node's two render
// callbacks run. Each callback must return the sector. Returns 1, or 0 when a callback fails.
// Names are inferred from this function and rw_resources.h.
// NonMatching: only the prologue schedule differs: retail loads the sector before saving r30 and
// reads the engine globals after storing the callbacks into the info block (5 words). Declaration
// and statement orders do not reproduce it.
#include "game/rw_resources.h"

struct MeshHeader8015D67C {
	u8 pad0[0x4];
	u16 numMeshes; // 0x4
	u16 serialNum; // 0x6
};

struct ResEntry8015D67C {
	RwLLLink link; // 0x0
	u8 pad8[0x1A - 0x8];
	u16 serialNum; // 0x1A
};

struct Sector8015D67C {
	u8 pad0[0x34];
	ResEntry8015D67C* repEntry; // 0x34
	u8 pad38[0x80 - 0x38];
	MeshHeader8015D67C* mesh; // 0x80
	u8 pad84[0x8A - 0x84];
	u16 numTriangles; // 0x8A
};

struct InstanceInfo8015D67C;

typedef Sector8015D67C* (*SectorCallBack8015D67C)(
    Sector8015D67C* sector, InstanceInfo8015D67C* info);

struct NodeCallBacks8015D67C {
	SectorCallBack8015D67C instance; // 0x0
	void* reinstance;                // 0x4
	SectorCallBack8015D67C setup;    // 0x8
	SectorCallBack8015D67C render;   // 0xC
};

struct InstanceInfo8015D67C {
	ResEntry8015D67C* repEntry; // 0x0
	MeshHeader8015D67C* mesh;   // 0x4
	u32 worldFlags;             // 0x8
	u8 padC[0x28 - 0xC];
	NodeCallBacks8015D67C* callbacks; // 0x28
};

struct World8015D67C {
	u8 pad0[0x8];
	u32 flags; // 0x8
};

struct Node8015D67C {
	u8 pad0[0x14];
	NodeCallBacks8015D67C* callbacks; // 0x14
};

#define WORLD_8015D67C_NATIVE 0x01000000
#define RESOURCES_LIST_8015D67C                                                                    \
	(*(RwLinkList**)((u8*)lbl_8042C9A4 + lbl_8042C970.globalsOffset + 0x24))

extern "C" {
// HYPOTHESIS: RwResourcesFreeResEntry.
s32 fn_80197384(void* resEntry);
}

extern "C" {
s32 fn_8015D67C(Node8015D67C* node, Sector8015D67C** params)
{
	Sector8015D67C* sector           = *params;
	NodeCallBacks8015D67C* callbacks = node->callbacks;
	InstanceInfo8015D67C info;
	u32 worldFlags;

	info.callbacks = callbacks;
	worldFlags     = ((World8015D67C*)lbl_8042C9A4->curWorld)->flags;
	if (!(worldFlags & WORLD_8015D67C_NATIVE)) {
		MeshHeader8015D67C* mesh;
		if (sector->numTriangles == 0) {
			return 1;
		}
		mesh = sector->mesh;
		if (mesh->numMeshes == 0) {
			return 1;
		}
		info.repEntry   = sector->repEntry;
		info.mesh       = mesh;
		info.worldFlags = worldFlags;
		if (info.repEntry != 0 && info.repEntry->serialNum != mesh->serialNum) {
			fn_80197384(info.repEntry);
			info.repEntry = 0;
		}
		if (info.repEntry != 0) {
			if (info.repEntry->link.next != 0) {
				info.repEntry->link.prev->next           = info.repEntry->link.next;
				info.repEntry->link.next->prev           = info.repEntry->link.prev;
				info.repEntry->link.next                 = RESOURCES_LIST_8015D67C->link.next;
				info.repEntry->link.prev                 = &RESOURCES_LIST_8015D67C->link;
				RESOURCES_LIST_8015D67C->link.next->prev = &info.repEntry->link;
				RESOURCES_LIST_8015D67C->link.next       = &info.repEntry->link;
			}
		} else if (callbacks->instance != 0 && callbacks->instance(sector, &info) != sector) {
			return 0;
		}
	} else {
		info.repEntry   = sector->repEntry;
		info.mesh       = sector->mesh;
		info.worldFlags = worldFlags;
	}
	if (callbacks->setup != 0 && callbacks->setup(sector, &info) != sector) {
		return 0;
	}
	if (callbacks->render != 0 && callbacks->render(sector, &info) != sector) {
		return 0;
	}
	return 1;
}
}
