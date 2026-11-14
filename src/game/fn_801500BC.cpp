// Calls callback(light, data) for every light of the clump (lights are linked at +0x4 of their clump plugin data, at the offset
// lbl_8042C8CC), stopping early when it
// returns null (HYPOTHESIS: RpClumpForAllLights). The next link is read before the call. Returns
// the clump.
#include "game/rw_engine.h"

struct RpClump801500BC {
	u8 pad0[0x10];
	RwLinkList list; // 0x10
};

typedef void* (*Callback801500BC)(void* light, void* data);

extern "C" {
// Offset of the light clump-link plugin data inside a light (HYPOTHESIS).
extern s32 lbl_8042C8CC;

RpClump801500BC* fn_801500BC(RpClump801500BC* clump, Callback801500BC callback, void* data)
{
	RwLLLink* cur       = clump->list.link.next;
	const RwLLLink* end = &clump->list.link;
	RwLLLink* next;
	while (cur != end) {
		void* light = ((u8*)cur - 4) - lbl_8042C8CC;
		next        = cur->next;
		if (callback(light, data) == 0) {
			return clump;
		}
		cur = next;
	}
	return clump;
}
}
