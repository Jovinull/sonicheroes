// Destroys an atomic (HYPOTHESIS: RpAtomicDestroy): runs the atomic plugin destructors (registry
// lbl_8028D230), releases its resource entry (+0x14) through fn_80197384, drops its geometry (+0x18)
// through fn_80152EEC and, when fn_8015BAFC reports it, resynchronizes its frame; then detaches it
// from the frame and returns it to the atomic free list (first field of the clump module globals).
// Always returns 1.
#include "game/rw_frame.h"

// Atomic fields used here (HYPOTHESIS: RpAtomic layout).
struct RpAtomic80150358 {
	RwObjectHasFrame object; // 0x0
	void* repEntry;          // 0x14
	void* geometry;          // 0x18
};

extern "C" {
extern RwModuleInfo lbl_8042C8D8;
extern RwPluginRegistry lbl_8028D230;
void fn_80197384(void* entry);
void fn_80152EEC(void* geometry);
void* fn_8015BAFC(RpAtomic80150358* atomic);
void fn_801A53E4(void* object);

s32 fn_80150358(RpAtomic80150358* atomic)
{
	fn_80198E04(&lbl_8028D230, atomic);
	if (atomic->repEntry != 0) {
		fn_80197384(atomic->repEntry);
	}
	if (atomic->geometry != 0) {
		RwFrame* frame;
		if (atomic->geometry != 0) {
			fn_80152EEC(atomic->geometry);
		}
		atomic->geometry = 0;
		frame            = (RwFrame*)atomic->object.object.parent;
		if (frame != 0 && fn_8015BAFC(atomic) != 0) {
			fn_8019E880(frame);
		}
	}
	fn_801A53E4(atomic);
	lbl_8042C9A4->freeListFree(
	    *(RwFreeList**)((u8*)lbl_8042C9A4 + lbl_8042C8D8.globalsOffset), atomic);
	return 1;
}
}
