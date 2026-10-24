#include "types.h"

// The train core's EditOnChange (traincoreEditOnChange here): its kind is kept
// between 0 and 3.

typedef struct TraincoreParams {
	s32 kind; // 0x00
} TraincoreParams;

typedef struct TraincoreEdit {
	u8 unk00[0x2C];
	TraincoreParams* params; // 0x2C
} TraincoreEdit;

extern "C" void traincoreEditOnChange(void* object, TraincoreEdit* edit)
{
	TraincoreParams* params = edit->params;

	if (params->kind < 0) {
		params->kind = 0;
	}
	if ((u32)params->kind >= 4) {
		params->kind = 3;
	}
}
