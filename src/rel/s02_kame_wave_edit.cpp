#include "types.h"

// The turtle wave's EditOnChange (s02KameWaveEditOnChange here): its kind is
// kept at 0 or 1 and copied to the object when it changed.

typedef struct S02KameWaveParams {
	s8 kind; // 0x00
} S02KameWaveParams;

typedef struct S02KameWaveEdit {
	u8 unk00[0x2C];
	S02KameWaveParams* params; // 0x2C
} S02KameWaveEdit;

typedef struct S02KameWaveObject {
	u8 unk00[0x30];
	s8 kind; // 0x30
} S02KameWaveObject;

extern "C" void s02KameWaveEditOnChange(S02KameWaveObject* object, S02KameWaveEdit* edit)
{
	S02KameWaveParams* params = edit->params;

	if (params->kind < 0) {
		params->kind = 0;
	}
	if (params->kind >= 2) {
		params->kind = 1;
	}
	if (object->kind != params->kind) {
		object->kind = params->kind;
	}
}
