#include "types.h"

// The no-input collision's EditOnChange (the PS2 build's name;
// noInputCollisionEditOnChange here): it keeps the edited kind within 0..2 and
// each side of the box within 0..1000, then names the editor's four fields for
// that kind.

typedef struct NoInputParams {
	s32 kind; // 0x00
	f32 x;    // 0x04
	f32 y;    // 0x08
	f32 z;    // 0x0C
} NoInputParams;

typedef struct NoInputEdit {
	u8 unk00[0x2C];        // 0x00
	NoInputParams* params; // 0x2C
} NoInputEdit;

extern "C" char* noInputCollisionObjectFieldNames[4];
extern "C" char* noInputCollisionKindFields0[3];
extern "C" char* noInputCollisionKindFields1[3];
extern "C" char* noInputCollisionKindFields2[3];
extern "C" char* noInputCollisionKindFields3[3];

extern "C" void noInputCollisionEditOnChange(void* object, NoInputEdit* edit)
{
	NoInputParams* params = edit->params;

	if (params->kind < 0) {
		params->kind = 0;
	}
	if (params->kind >= 3) {
		params->kind = 2;
	}
	if (params->x < 0.0f) {
		params->x = 0.0f;
	}
	if (params->x > 1000.0f) {
		params->x = 1000.0f;
	}
	if (params->y < 0.0f) {
		params->y = 0.0f;
	}
	if (params->y > 1000.0f) {
		params->y = 1000.0f;
	}
	if (params->z < 0.0f) {
		params->z = 0.0f;
	}
	if (params->z > 1000.0f) {
		params->z = 1000.0f;
	}
	noInputCollisionObjectFieldNames[0] = noInputCollisionKindFields0[params->kind];
	noInputCollisionObjectFieldNames[1] = noInputCollisionKindFields1[params->kind];
	noInputCollisionObjectFieldNames[2] = noInputCollisionKindFields2[params->kind];
	noInputCollisionObjectFieldNames[3] = noInputCollisionKindFields3[params->kind];
}
