#include "types.h"

// TObjRaildash::EditOnChange (the PS2 build's name; raildashEditOnChange
// here): an edited size of zero becomes 1, and the size is kept at 0.1 at
// least.

typedef struct RaildashParams {
	f32 size; // 0x00
} RaildashParams;

typedef struct RaildashEdit {
	u8 unk00[0x2C];
	RaildashParams* params; // 0x2C
} RaildashEdit;

extern "C" const f32 raildashEditUnset[1];
extern "C" const f32 raildashEditDefault[1];

extern "C" void raildashEditOnChange(void* object, RaildashEdit* edit)
{
	RaildashParams* params = edit->params;

	if (raildashEditUnset[0] == params->size) {
		params->size = raildashEditDefault[0];
	}
	const f32* min;
	if (params->size < *(min = raildashEditDefault)) {
		params->size = *min;
	}
}
