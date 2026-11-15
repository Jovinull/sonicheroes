// Renders the atomics of a world sector (HYPOTHESIS: the default world sector render callback):
// after the world's sector callback (fn_80158928) accepts the sector, every renderable atomic
// (flag 0x4 of byte 0x2) tied to it through either tie list (0x38 and 0x40) that has not been
// rendered this frame is rendered with its callback at 0x48 when its world bounding sphere
// (fn_8014F9C4) is inside the current camera's frustum (fn_8019CE34), and stamped with the frame.
// Returns the sector. Field names are inferred from this function only.
// NonMatching: the second list walk swaps the tie and atomic registers (r28/r30, 10 words); the
// first walk matches.
#include "game/rw_engine.h"

struct Atomic80158A1C;
typedef Atomic80158A1C* (*AtomicRender80158A1C)(Atomic80158A1C* atomic);

struct Atomic80158A1C {
	u8 pad0[0x2];
	u8 flags; // 0x2
	u8 pad3[0x48 - 0x3];
	AtomicRender80158A1C render; // 0x48
	u8 pad4C[0x60 - 0x4C];
	u16 renderFrame; // 0x60
};

struct Tie80158A1C {
	RwLLLink link;          // 0x0
	Atomic80158A1C* atomic; // 0x8
};

struct Sector80158A1C {
	u8 pad0[0x38];
	RwLinkList atomics;            // 0x38
	RwLinkList atomicsNoCollision; // 0x40
};

extern "C" {
void* fn_80158928(Sector80158A1C* sector);
void* fn_8014F9C4(Atomic80158A1C* atomic);
s32 fn_8019CE34(RwCamera* camera, void* sphere);
}

static inline void RenderTiedAtomics(RwLinkList* list)
{
	RwLLLink* cur;
	RwLLLink* end = &list->link;

	for (cur = list->link.next; cur != end; cur = cur->next) {
		Atomic80158A1C* atomic = ((Tie80158A1C*)cur)->atomic;
		if ((atomic->flags & 0x4) && atomic->renderFrame != lbl_8042C9A4->renderFrame) {
			if (fn_8019CE34(lbl_8042C9A4->curCamera, fn_8014F9C4(atomic))) {
				atomic->render(atomic);
			}
			atomic->renderFrame = lbl_8042C9A4->renderFrame;
		}
	}
}

extern "C" {
Sector80158A1C* fn_80158A1C(Sector80158A1C* sector)
{
	if (fn_80158928(sector)) {
		RenderTiedAtomics(&sector->atomics);
		RenderTiedAtomics(&sector->atomicsNoCollision);
	}
	return sector;
}
}
