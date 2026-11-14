// Calls callback(camera, data) for every camera of the clump (cameras are linked at +0x4 of their clump plugin data, at the offset
// lbl_8042C8C8), stopping early when it
// returns null (HYPOTHESIS: RpClumpForAllCameras). The next link is read before the call. Returns
// the clump.
#include "game/rw_engine.h"

struct RpClump80150038 {
	u8 pad0[0x18];
	RwLinkList list; // 0x18
};

typedef void* (*Callback80150038)(void* camera, void* data);

extern "C" {
// Offset of the camera clump-link plugin data inside a camera (HYPOTHESIS).
extern s32 lbl_8042C8C8;

RpClump80150038* fn_80150038(RpClump80150038* clump, Callback80150038 callback, void* data)
{
	RwLLLink* cur       = clump->list.link.next;
	const RwLLLink* end = &clump->list.link;
	RwLLLink* next;
	while (cur != end) {
		void* camera = ((u8*)cur - 4) - lbl_8042C8C8;
		next         = cur->next;
		if (callback(camera, data) == 0) {
			return clump;
		}
		cur = next;
	}
	return clump;
}
}
