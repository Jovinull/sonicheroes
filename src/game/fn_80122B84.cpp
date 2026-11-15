// Sets up the menu cursor quad (HYPOTHESIS; names inferred): remembers the clump (lbl_8042C718)
// and, when there is one, its first textured material (lbl_8042C71C) and switches its geometries to
// modulated material colours; then copies the four corner positions (lbl_80289C88) and texture
// coordinates (lbl_80289C68) into the 0x24-byte vertices of lbl_803E8008.
#include "game/matrix.h"

struct RpClump;
struct RpMaterial;

RpMaterial* objRpClumpGetMaterialWithSpecificTexture(RpClump* clump, RpMaterial* start, char* name);
void objRpClumpForAllGeometrysToModulateMaterialColor(RpClump* clump);

struct Vertex80122B84 {
	u8 pad0[0xC];
	RwV3d position; // 0xC
	u32 color;      // 0x18 (UNKNOWN)
	RwV2d uv;       // 0x1C
};

extern "C" {
extern RpClump* lbl_8042C718;
extern RpMaterial* lbl_8042C71C;
extern RwV2d lbl_80289C68[4];
extern RwV3d lbl_80289C88[4];
extern Vertex80122B84 lbl_803E8008[4];

void fn_80122B84(RpClump* clump)
{
	s32 i;

	lbl_8042C718 = clump;
	if (clump != 0) {
		lbl_8042C71C = objRpClumpGetMaterialWithSpecificTexture(clump, 0, 0);
		objRpClumpForAllGeometrysToModulateMaterialColor(lbl_8042C718);
	}
	for (i = 0; i < 4; i++) {
		lbl_803E8008[i].uv       = lbl_80289C68[i];
		lbl_803E8008[i].position = lbl_80289C88[i];
	}
}
}
