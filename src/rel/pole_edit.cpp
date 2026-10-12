#include "types.h"

// The pole's EditOnChange (poleEditOnChange here): it keeps the edited
// heights, lengths and speeds within their limits (the third value at most 40
// above the first, the fourth no lower than 40 below it, mirrored) and names
// the editor's eighth field by the switch flag.

typedef struct PoleParams {
	s16 top;    // 0x00
	s16 bottom; // 0x02
	s16 upper;  // 0x04
	s16 lower;  // 0x06
	f32 speedA; // 0x08
	f32 speedB; // 0x0C
	f32 range;  // 0x10
	u8 flag;    // 0x14
	u8 pad15;
	s16 wait; // 0x16
} PoleParams;

typedef struct PoleEdit {
	u8 unk00[0x2C];
	PoleParams* params; // 0x2C
} PoleEdit;

extern "C" const char* poleFieldNames[];
extern "C" const char* poleFlagFields[];
extern "C" const f32 poleMinSpeed[1];
extern "C" const f32 poleMaxSpeed[1];
extern "C" const f32 poleMinRange[1];
extern "C" const f32 poleMaxRange[1];

extern "C" void poleEditOnChange(void* object, PoleEdit* edit)
{
	PoleParams* params = edit->params;
	const f32* limit;

	if (params->top < -0x20) {
		params->top = -0x20;
	}
	if (params->top > 0x3C0) {
		params->top = 0x3C0;
	}
	if (params->bottom < -0x23) {
		params->bottom = -0x23;
	}
	if (params->bottom > 0x3C0) {
		params->bottom = 0x3C0;
	}
	if (params->upper < 5) {
		params->upper = 5;
	}
	if (params->upper > params->top + 0x28) {
		params->upper = params->top + 0x28;
	}
	if (params->lower > -3) {
		params->lower = -3;
	}
	if (params->lower < -(params->top + 0x28)) {
		params->lower = 0x28 - params->top;
	}
	if (params->speedA < *(limit = poleMinSpeed)) {
		params->speedA = *limit;
	}
	if (params->speedA > *(limit = poleMaxSpeed)) {
		params->speedA = *limit;
	}
	if (params->speedB < *(limit = poleMinSpeed)) {
		params->speedB = *limit;
	}
	if (params->speedB > *(limit = poleMaxSpeed)) {
		params->speedB = *limit;
	}
	if (params->range < *(limit = poleMinRange)) {
		params->range = *limit;
	}
	if (params->range > *(limit = poleMaxRange)) {
		params->range = *limit;
	}
	if (params->wait < 0) {
		params->wait = 0;
	}
	if (params->flag == 0) {
		poleFieldNames[7] = poleFlagFields[0];
	} else {
		poleFieldNames[7] = poleFlagFields[1];
	}
}
