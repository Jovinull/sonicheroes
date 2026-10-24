#include "types.h"

// TObjBridge::EditOnChange (the PS2 build's name; bridgeEditOnChange
// here): an edited size of zero becomes 1, and the size is kept at 0.1 at
// least.

typedef struct BridgeParams {
	f32 size; // 0x00
} BridgeParams;

typedef struct BridgeEdit {
	u8 unk00[0x2C];
	BridgeParams* params; // 0x2C
} BridgeEdit;

extern "C" const f32 bridgeEditUnset[1];
extern "C" const f32 bridgeEditDefault[1];
extern "C" const f32 bridgeEditMin[1];

extern "C" void bridgeEditOnChange(void* object, BridgeEdit* edit)
{
	BridgeParams* params = edit->params;

	if (bridgeEditUnset[0] == params->size) {
		params->size = bridgeEditDefault[0];
	}
	const f32* min;
	if (params->size < *(min = bridgeEditMin)) {
		params->size = *min;
	}
}
