// Finds the world that owns a memory address (HYPOTHESIS): walks the worlds registered in the
// list at 0x4 of the module globals (lbl_8042C910 offset); a world flagged with bit 0 of byte 0x3
// owns the address when it lies inside its own block (size from the registration), otherwise
// fn_80159E9C runs fn_80158A00 over the world to look for it. Returns the owning world or null.
// Field names are inferred from this function only.
#include "game/rw_engine.h"

struct World80159698 {
	u8 pad0[0x3];
	u8 flags; // 0x3: bit 0 set when the world is one block
};

// Registration of a world in the module list; the list link is at 0x8 (the walk subtracts 0x8).
struct Registration80159698 {
	World80159698* world; // 0x0
	u32 size;             // 0x4
	RwLLLink link;        // 0x8
};

// Search context for fn_80158A00.
struct Search80159698 {
	void* address; // 0x0
	s32 found;     // 0x4
};

extern "C" {
extern RwModuleInfo lbl_8042C910;

void fn_80159E9C(World80159698* world, void* callback, Search80159698* search);
extern u8 fn_80158A00[];

World80159698* fn_80159698(void* address)
{
	RwLinkList* list = (RwLinkList*)((u8*)lbl_8042C9A4 + lbl_8042C910.globalsOffset + 0x4);
	RwLLLink* link   = list->link.next;

	for (; link != &list->link; link = link->next) {
		Registration80159698* registration = (Registration80159698*)((u8*)link - 0x8);
		if (registration->world->flags & 1) {
			if (address >= registration->world
			    && address < (u8*)registration->world + registration->size) {
				return registration->world;
			}
		} else {
			Search80159698 search;
			search.address = address;
			search.found   = 0;
			fn_80159E9C(registration->world, fn_80158A00, &search);
			if (search.found) {
				return registration->world;
			}
		}
	}
	return 0;
}
}
