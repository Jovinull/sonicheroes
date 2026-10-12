#include "types.h"

// The fan's EditOnChange (fanEditOnChange here): it keeps the edited box within
// its bounds (width and depth -30..960, height -40..950, strength -0.3..2.1),
// the kind within 0..3 and the switch flag within 0..1, then names the editor's
// fields for the kind and the flag.

typedef struct FanParams {
	f32 height;    // 0x00
	f32 width;     // 0x04
	f32 depth;     // 0x08
	f32 strength;  // 0x0C
	s8 kind;       // 0x10
	u8 unk11[0x7]; // 0x11
	s8 flag;       // 0x18
} FanParams;

typedef struct FanEdit {
	u8 unk00[0x2C];    // 0x00
	FanParams* params; // 0x2C
} FanEdit;

extern "C" const char* fanFieldNames[];
extern "C" const char* fanKindFields0[4];
extern "C" const char* fanKindFields1[4];
extern "C" const char* fanFlagFields[2];

extern "C" void fanEditOnChange(void* object, FanEdit* edit)
{
	FanParams* params = edit->params;

	if (params->width < -30.0f) {
		params->width = -30.0f;
	}
	if (params->width >= 960.0f) {
		params->width = 960.0f;
	}
	if (params->depth < -30.0f) {
		params->depth = -30.0f;
	}
	if (params->depth >= 960.0f) {
		params->depth = 960.0f;
	}
	if (params->height < -40.0f) {
		params->height = -40.0f;
	}
	if (params->height >= 950.0f) {
		params->height = 950.0f;
	}
	if (params->strength < -0.3f) {
		params->strength = -0.3f;
	}
	if (params->strength >= 2.1f) {
		params->strength = 2.1f;
	}
	if (params->kind < 0) {
		params->kind = 0;
	}
	if (params->kind >= 4) {
		params->kind = 3;
	}
	if (params->flag < 0) {
		params->flag = 0;
	}
	if (params->flag > 1) {
		params->flag = 1;
	}
	fanFieldNames[4] = fanKindFields0[params->kind];
	fanFieldNames[5] = fanKindFields1[params->kind];
	fanFieldNames[7] = fanFlagFields[params->flag];
}
