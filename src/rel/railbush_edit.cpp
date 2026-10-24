#include "types.h"

// TObjRailbush::EditOnChange (the PS2 build's name; railbushEditOnChange
// here): an edited size of zero becomes 1, and the size is kept at 0.1 at
// least.

typedef struct RailbushParams {
	f32 size; // 0x00
} RailbushParams;

typedef struct RailbushEdit {
	u8 unk00[0x2C];
	RailbushParams* params; // 0x2C
} RailbushEdit;

extern "C" const f32 railbushEditUnset[1];
extern "C" const f32 railbushEditDefault[1];
extern "C" const f32 railbushEditMin[1];

extern "C" void railbushEditOnChange(void* object, RailbushEdit* edit)
{
	RailbushParams* params = edit->params;

	if (railbushEditUnset[0] == params->size) {
		params->size = railbushEditDefault[0];
	}
	const f32* min;
	if (params->size < *(min = railbushEditMin)) {
		params->size = *min;
	}
}
