// Orders two mesh records for sorting (HYPOTHESIS: a qsort comparator of the world-sector mesh
// builder): meshes with the same material compare equal; otherwise each side's key is built from
// its material (lbl_8042F378 when its texture raster has an alpha pixel format, or when the
// material colour is not opaque) and from the u16 fields at +0x10, +0x12, +0xE and +0xC, where
// the side with the larger value gets bit 8, 4, 2 and 1. Returns key(a) - key(b). Names are
// inferred from this function only.
// NonMatching: instruction stream matches; retail keeps the two mesh pointers in r11/r9 and the
// materials in r5/r6 while this source reuses the argument registers, which renames most volatile
// registers (47 words). Declaration permutations do not reproduce it.
#include "game/object.h"

#define RW_RASTER_FORMAT_1555 0x100
#define RW_RASTER_FORMAT_4444 0x300
#define RW_RASTER_FORMAT_8888 0x500

struct Material80156130 {
	RwTexture* texture; // 0x0
	u8 red;             // 0x4
	u8 green;           // 0x5
	u8 blue;            // 0x6
	u8 alpha;           // 0x7
};

struct Mesh80156130 {
	u8 pad0[0x8];
	Material80156130* material; // 0x8
	u16 keyC;                   // 0xC
	u16 keyE;                   // 0xE
	u16 key10;                  // 0x10
	u16 key12;                  // 0x12
};

extern "C" {
extern const u32 lbl_8042F378; // transparency sort key

// Transparency part of a mesh's sort key.
#define MATERIAL_KEY_80156130(material, key)                                                       \
	do {                                                                                           \
		if ((material) != 0) {                                                                     \
			if ((material)->texture != 0) {                                                        \
				s32 format = ((material)->texture->raster->cFormat << 8) & 0xF00;                  \
				if (format == RW_RASTER_FORMAT_1555 || format == RW_RASTER_FORMAT_4444             \
				    || format == RW_RASTER_FORMAT_8888) {                                          \
					(key) = lbl_8042F378;                                                          \
				}                                                                                  \
			}                                                                                      \
			if ((material)->alpha != 0xFF) {                                                       \
				(key) |= lbl_8042F378;                                                             \
			}                                                                                      \
		}                                                                                          \
	} while (0)

s32 fn_80156130(const void* pa, const void* pb)
{
	const Mesh80156130* b;
	u32 keyB;
	u32 keyA;
	Material80156130* materialB;
	const Mesh80156130* a;
	Material80156130* materialA;

	a         = *(const Mesh80156130**)pa;
	keyA      = 0;
	b         = *(const Mesh80156130**)pb;
	keyB      = 0;
	materialA = a->material;
	materialB = b->material;

	if (materialA == materialB) {
		return 0;
	}
	MATERIAL_KEY_80156130(materialA, keyA);
	MATERIAL_KEY_80156130(materialB, keyB);
	keyA |= (a->key10 > b->key10) ? 8 : 0;
	keyB |= (a->key10 < b->key10) ? 8 : 0;
	keyA |= (a->key12 > b->key12) ? 4 : 0;
	keyB |= (a->key12 < b->key12) ? 4 : 0;
	keyA |= (a->keyE > b->keyE) ? 2 : 0;
	keyB |= (a->keyE < b->keyE) ? 2 : 0;
	keyA |= (a->keyC > b->keyC);
	keyB |= (a->keyC < b->keyC);
	return keyA - keyB;
}
}
