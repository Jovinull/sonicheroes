// Sets the default surface properties given to new materials (HYPOTHESIS:
// RpMaterialSetDefaultSurfaceProperties; fn_80154860 reads lbl_8028D2A8): copies the given
// properties, or resets ambient, diffuse and specular to the .sdata2 constant lbl_8042F370 for
// null.
#include "game/rw_engine.h"

// Surface properties (HYPOTHESIS: RwSurfaceProperties). The retail code copies them as plain
// words and writes the reset values as floats.
union RwSurfaceProperties8015472C {
	struct {
		f32 ambient;  // 0x0
		f32 specular; // 0x4
		f32 diffuse;  // 0x8
	} f;
	struct {
		u32 w[3];
	} words;
};

extern "C" {
extern RwSurfaceProperties8015472C lbl_8028D2A8;
extern f32 lbl_8042F370;

void fn_8015472C(const RwSurfaceProperties8015472C* properties)
{
	if (!properties) {
		lbl_8028D2A8.f.ambient  = lbl_8042F370;
		lbl_8028D2A8.f.diffuse  = lbl_8042F370;
		lbl_8028D2A8.f.specular = lbl_8042F370;
	} else {
		lbl_8028D2A8.words = properties->words;
	}
}
}
