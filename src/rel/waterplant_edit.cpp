#include "types.h"

// TObjWaterplant::EditOnChange (the PS2 build's name; waterplantEditOnChange
// here): an edited size of zero becomes 1, and the size is kept at 0.1 at
// least.

typedef struct WaterplantParams {
	f32 size; // 0x00
} WaterplantParams;

typedef struct WaterplantEdit {
	u8 unk00[0x2C];
	WaterplantParams* params; // 0x2C
} WaterplantEdit;

extern "C" const f32 waterplantEditUnset[1];
extern "C" const f32 waterplantEditDefault[1];
extern "C" const f32 waterplantEditMin[1];

extern "C" void waterplantEditOnChange(void* object, WaterplantEdit* edit)
{
	WaterplantParams* params = edit->params;

	if (waterplantEditUnset[0] == params->size) {
		params->size = waterplantEditDefault[0];
	}
	const f32* min;
	if (params->size < *(min = waterplantEditMin)) {
		params->size = *min;
	}
}
