// Drops one reference to an entry of the record lbl_803EC968's free list (count at +0x74). The last
// reference releases its texture (+0x68) through fn_801A491C (RwTextureDestroy) and returns the
// entry to the free list. Names are UNKNOWN. Returns 1 when the entry was released, otherwise 0.
#include "game/rw_engine.h"

struct Entry80169EF4 {
	u8 pad0[0x68];
	RwTexture* texture; // 0x68
	u8 pad6C[0x74 - 0x6C];
	s32 refCount; // 0x74
};

struct Rec80169EF4 {
	u8 pad0[0x140];
	RwFreeList* freeList; // 0x140
};

extern "C" {
extern Rec80169EF4 lbl_803EC968;
s32 fn_801A491C(RwTexture* texture);

s32 fn_80169EF4(Entry80169EF4* entry)
{
	if (--entry->refCount <= 0) {
		if (entry->texture != 0) {
			fn_801A491C(entry->texture);
		}
		lbl_8042C9A4->freeListFree(lbl_803EC968.freeList, entry);
		return 1;
	}
	return 0;
}
}
