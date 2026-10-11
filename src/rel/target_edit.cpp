#include "types.h"

// The target's EditOnChange (targetEditOnChange here): it keeps the edited kind
// within 0..3 and the mode within 0..2, then names the editor's first and
// third fields for them.

typedef struct TargetParams {
	s8 kind; // 0x00
	s8 mode; // 0x01
} TargetParams;

typedef struct TargetEdit {
	u8 unk00[0x2C];       // 0x00
	TargetParams* params; // 0x2C
} TargetEdit;

extern "C" const char* targetFieldNames[];
extern "C" const char* targetKindFields[4];
extern "C" const char* targetModeFields[3];

extern "C" void targetEditOnChange(void* object, TargetEdit* edit)
{
	TargetParams* params = edit->params;

	if (params->kind < 0) {
		params->kind = 0;
	}
	if (params->kind >= 4) {
		params->kind = 3;
	}
	if (params->mode < 0) {
		params->mode = 0;
	}
	if (params->mode > 2) {
		params->mode = 2;
	}
	targetFieldNames[0] = targetKindFields[params->kind];
	targetFieldNames[2] = targetModeFields[params->mode];
}
