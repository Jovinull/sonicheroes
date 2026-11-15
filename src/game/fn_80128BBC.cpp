// Registers up to four menu clumps and applies a custom FX texture to them (HYPOTHESIS; names
// inferred): stores the clumps in lbl_80289F80 and the texture in lbl_8042C730, then for each clump
// finds the material that uses the texture named lbl_8042B97C (kept in lbl_80289F90) and, when a
// texture was given and the material exists, sets the FX texture on the atomic that uses it (the
// FX data block lbl_803E80A8) and refreshes that atomic (fn_801491A8).
#include "types.h"

struct RpClump;
struct RpMaterial;
struct RpAtomic;

RpMaterial* objRpClumpGetMaterialWithSpecificTexture(RpClump* clump, RpMaterial* start, char* name);
RpAtomic* objRpClumpGetAtomicWithTexture(RpClump* clump, RpAtomic* start, char* name);
void AtomicSetCustomFXTexture(RpAtomic* atomic, void* data);

// Custom FX data passed to AtomicSetCustomFXTexture (only the texture is set here).
struct CustomFX80128BBC {
	void* texture; // 0x0
	u8 pad4[0x48 - 0x4];
};

extern "C" {
extern RpClump* lbl_80289F80[4];
extern RpMaterial* lbl_80289F90[4];
extern void* lbl_8042C730;
extern char lbl_8042B97C[8];
extern CustomFX80128BBC lbl_803E80A8;
void fn_801491A8(RpAtomic* atomic);

void fn_80128BBC(RpClump* clump0, RpClump* clump1, RpClump* clump2, RpClump* clump3, void* texture)
{
	s32 i;

	lbl_80289F80[0] = clump0;
	lbl_80289F80[1] = clump1;
	lbl_80289F80[2] = clump2;
	lbl_80289F80[3] = clump3;
	lbl_8042C730    = texture;
	for (i = 0; i < 4; i++) {
		if (lbl_80289F80[i] != 0) {
			lbl_80289F90[i]
			    = objRpClumpGetMaterialWithSpecificTexture(lbl_80289F80[i], 0, lbl_8042B97C);
			if (lbl_8042C730 != 0 && lbl_80289F90[i] != 0) {
				RpAtomic* atomic = objRpClumpGetAtomicWithTexture(lbl_80289F80[i], 0, lbl_8042B97C);
				lbl_803E80A8.texture = lbl_8042C730;
				AtomicSetCustomFXTexture(atomic, &lbl_803E80A8);
				fn_801491A8(atomic);
			}
		}
	}
}
}
