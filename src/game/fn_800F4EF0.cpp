// Destructor of the message list owner (vtable lbl_80259D1C; the class name is UNKNOWN; see
// fn_800F4E20): deletes every entry of its CLASS_LINK_MANAGER (+0x28), clears the singleton
// lbl_8042C4F8 when it is this object, destroys the manager and the TObject base, and frees the
// object when flags > 0. Returns the object.
#include "game/link.h"
#include "types.h"

struct Owner800F4EF0 {
	u8 pad0[0x18];
	void* vtable; // 0x18
	u8 pad1C[0x28 - 0x1C];
	CLASS_LINK_MANAGER links; // 0x28
};

struct THeapCtrl;

extern "C" {
extern Owner800F4EF0* lbl_8042C4F8;
extern void* lbl_80259D1C[];
extern THeapCtrl* lbl_8042C148;
void __dt__18CLASS_LINK_MANAGERFv(CLASS_LINK_MANAGER* manager, s32 flags);
void __dt__7TObjectFv(void* o, s32 flags);
void Free__9THeapCtrlFPv(THeapCtrl* heap, void* p);
}

// An entry of the list: a CLASS_LINK with a fade state; deleting it unlinks it from the manager of
// lbl_8042C4F8 (the retail code tests the entry once, before the unlink).
struct FadeEntry800F4EF0 : public CLASS_LINK {
	~FadeEntry800F4EF0() { lbl_8042C4F8->links.UnlinkClass(this); }

	u8 alpha; // 0x10
	u8 pad11;
	s16 age; // 0x12
};

extern "C" Owner800F4EF0* fn_800F4EF0(Owner800F4EF0* owner, s16 flags)
{
	if (owner != NULL) {
		owner->vtable         = lbl_80259D1C;
		owner->links.pCurrent = owner->links.pHead;
		while (owner->links.pCurrent != NULL) {
			CLASS_LINK* link         = owner->links.pCurrent;
			FadeEntry800F4EF0* entry = (FadeEntry800F4EF0*)link->pData;

			owner->links.pCurrent = link->pNext;
			if (entry != NULL) {
				delete entry;
			}
		}
		if (lbl_8042C4F8 == owner) {
			lbl_8042C4F8 = NULL;
		}
		__dt__18CLASS_LINK_MANAGERFv(&owner->links, 0);
		__dt__7TObjectFv(owner, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, owner);
		}
	}
	return owner;
}
