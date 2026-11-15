// Fades the entries of a link list (the CLASS_LINK_MANAGER at +0x28 of the owner; the walk uses its
// current pointer): every entry ages (+0x12) and, after 6 frames, loses 0x48 of its alpha (+0x10)
// per call; an entry whose alpha runs out is unlinked from the manager at +0x28 of lbl_8042C4F8 and
// deleted. HYPOTHESIS: fading on-screen messages; the entry type's name is UNKNOWN.
#include "game/link.h"
#include "types.h"

struct Owner800F4E20 {
	u8 pad0[0x28];
	CLASS_LINK_MANAGER links; // 0x28
};

extern "C" Owner800F4E20* lbl_8042C4F8;

// An entry of the list: a CLASS_LINK with a fade state; deleting it unlinks it from the manager of
// lbl_8042C4F8 (the retail code tests the entry once, before the unlink).
struct FadeEntry800F4E20 : public CLASS_LINK {
	~FadeEntry800F4E20() { lbl_8042C4F8->links.UnlinkClass(this); }

	u8 alpha; // 0x10
	u8 pad11;
	s16 age; // 0x12
};

// Ages the entry; true once its alpha is used up.
static inline s32 Fade(FadeEntry800F4E20* entry)
{
	if (entry->age++ > 6) {
		s32 alpha = entry->alpha;

		if ((alpha -= 0x48) < 0) {
			entry->alpha = 0;
			return 1;
		}
		entry->alpha = alpha;
	}
	return 0;
}

extern "C" void fn_800F4E20(Owner800F4E20* owner)
{
	owner->links.pCurrent = owner->links.pHead;
	while (owner->links.pCurrent != NULL) {
		CLASS_LINK* link         = owner->links.pCurrent;
		FadeEntry800F4E20* entry = (FadeEntry800F4E20*)link->pData;

		owner->links.pCurrent = link->pNext;
		if (entry != NULL && Fade(entry)) {
			delete entry;
		}
	}
}
