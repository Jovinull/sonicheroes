// Creates an entry of the record lbl_803EC968's free list (+0x140): clears its 0x78 bytes, sets all
// four corner colours to opaque white through fn_8016A4C4, all ranges to zero through fn_8016A804
// (with lbl_8042F428 components), runs fn_8016A8B8 with 0, sets +0x70 to lbl_8042F42C and the
// reference count (+0x74) to 1. Names are UNKNOWN. Returns the entry, or null when the free list is
// exhausted.
#include "game/rw_engine.h"
#include "MSL_C/string.h"

struct Vec2_80169E28 {
	float x;
	float y;
};

struct Entry80169E28 {
	u8 pad0[0x70];
	float f70;    // 0x70
	s32 refCount; // 0x74
};

struct Rec80169E28 {
	u8 pad0[0x140];
	RwFreeList* freeList; // 0x140
};

extern "C" {
extern Rec80169E28 lbl_803EC968;
// .sdata2 constants (non-const: reloaded as ordinary globals).
extern float lbl_8042F428;
extern float lbl_8042F42C;
void fn_8016A4C4(
    Entry80169E28* entry, const RwRGBA* a, const RwRGBA* b, const RwRGBA* c, const RwRGBA* d);
void fn_8016A804(Entry80169E28* entry, const Vec2_80169E28* originA, const Vec2_80169E28* a,
    const Vec2_80169E28* b, const Vec2_80169E28* originB);
void fn_8016A8B8(Entry80169E28* entry, s32 value);

Entry80169E28* fn_80169E28(void)
{
	Entry80169E28* entry = (Entry80169E28*)lbl_8042C9A4->freeListAlloc(lbl_803EC968.freeList);
	if (entry != 0) {
		RwRGBA white;
		Vec2_80169E28 zero;
		memset(entry, 0, 0x78);
		white.red   = 0xFF;
		white.green = 0xFF;
		white.blue  = 0xFF;
		white.alpha = 0xFF;
		fn_8016A4C4(entry, &white, &white, &white, &white);
		zero.x = lbl_8042F428;
		zero.y = lbl_8042F428;
		fn_8016A804(entry, &zero, &zero, &zero, &zero);
		fn_8016A8B8(entry, 0);
		entry->f70      = lbl_8042F42C;
		entry->refCount = 1;
		return entry;
	}
	return 0;
}
}
