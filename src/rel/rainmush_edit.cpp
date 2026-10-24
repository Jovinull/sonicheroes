#include "types.h"

// The rain mushroom's EditOnChange (rainmushEditOnChange here): the edit's
// flags keep bit 0x80 set at least, and the mushroom's kind is 0 or 1.

typedef struct RainmushParams {
	u8 unk00[0x9];
	s8 kind; // 0x09
} RainmushParams;

typedef struct RainmushEdit {
	u8 unk00[0x2A];
	u8 flags; // 0x2A
	u8 unk2B[0x1];
	RainmushParams* params; // 0x2C
} RainmushEdit;

extern "C" void rainmushEditOnChange(void* object, RainmushEdit* edit)
{
	RainmushParams* params = edit->params;

	if (edit->flags < 0x80) {
		edit->flags = 0x80;
	}
	if (params->kind >= 2) {
		params->kind = 1;
	}
}
