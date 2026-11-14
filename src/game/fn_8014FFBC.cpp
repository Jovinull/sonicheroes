// Calls callback(atomic, data) for every atomic of the clump (atomics are linked at +0x40), stopping early when it
// returns null (HYPOTHESIS: RpClumpForAllAtomics). The next link is read before the call. Returns
// the clump.
#include "game/rw_engine.h"

struct RpClump8014FFBC {
	u8 pad0[0x8];
	RwLinkList list; // 0x8
};

typedef void* (*Callback8014FFBC)(void* atomic, void* data);

extern "C" {

RpClump8014FFBC* fn_8014FFBC(RpClump8014FFBC* clump, Callback8014FFBC callback, void* data)
{
	RwLLLink* cur       = clump->list.link.next;
	const RwLLLink* end = &clump->list.link;
	RwLLLink* next;
	while (cur != end) {
		void* atomic = (u8*)cur - 0x40;
		next         = cur->next;
		if (callback(atomic, data) == 0) {
			return clump;
		}
		cur = next;
	}
	return clump;
}
}
