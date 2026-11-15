#include "game/object.h"

extern "C" {
RwMatrix* fn_8019E8EC(RwFrame* frame);

RpClump* fn_8014FF2C(RpClump* clump)
{
	RpClump* result = clump;
	RwLLLink* cur   = clump->atomicList.link.next;
	RwLLLink* end   = &clump->atomicList.link;

	while (cur != end) {
		RpAtomic* atomic = (RpAtomic*)((u8*)cur - 0x40);
		if (atomic->object.object.flags & 4) {
			fn_8019E8EC((RwFrame*)atomic->object.object.parent);
			if (atomic->renderCallBack(atomic) == 0) {
				result = 0;
			}
		}
		cur = cur->next;
	}
	return result;
}
}
