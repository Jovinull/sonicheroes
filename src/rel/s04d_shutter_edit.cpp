#include "types.h"

// The shutter's EditOnChange (s04dShutterEditOnChange here): its kind is
// kept at 0 or above, and one past 2 becomes 1.

typedef struct S04dShutterParams {
	s8 kind; // 0x00
} S04dShutterParams;

typedef struct S04dShutterEdit {
	u8 unk00[0x2C];
	S04dShutterParams* params; // 0x2C
} S04dShutterEdit;

extern "C" void s04dShutterEditOnChange(void* object, S04dShutterEdit* edit)
{
	S04dShutterParams* params = edit->params;

	if (params->kind < 0) {
		params->kind = 0;
	}
	if (params->kind > 2) {
		params->kind = 1;
	}
}
