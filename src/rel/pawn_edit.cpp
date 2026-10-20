#include "types.h"

// TObjEnemyPawn::EditOnChange (the PS2 build's name): keeps each edited
// parameter within its bounds and names the editor's fields for the values
// that pick them. The fields are named by their offsets. The field at 0x18 goes
// through the nVariable::Limit template, whose limits are literal constants in
// the original (named here). The two limits of the float at 0x08 are read
// again for the store, as from volatile data.

namespace nVariable
{

template <class T> inline const T& Limit(const T& value, const T& min, const T& max)
{
	if (value < min) {
		return min;
	}
	if (value > max) {
		return max;
	}
	return value;
}

} // namespace nVariable

typedef struct PawnParams {
	s8 f00;  // 0x00
	s8 f01;  // 0x01
	s8 f02;  // 0x02
	s8 f03;  // 0x03
	s16 f04; // 0x04
	u8 pad06[0x2];
	f32 f08; // 0x08
	f32 f0C; // 0x0C
	f32 f10; // 0x10
	f32 f14; // 0x14
	s32 f18; // 0x18
} PawnParams;

typedef struct PawnEdit {
	u8 unk00[0x2C];
	PawnParams* params; // 0x2C
} PawnEdit;

extern "C" const s32 pawnMin18;
extern "C" const s32 pawnMax18;
extern "C" const f32 pawnZero[1];
extern "C" const volatile f32 pawnBound0[1];
extern "C" const volatile f32 pawnBound1[1];
extern "C" const f32 pawnBound2[1];
extern "C" const f32 pawnBound3[1];
extern "C" const f32 pawnBound4[1];
extern "C" const f32 pawnBound5[1];

extern "C" const char* pawnFieldNames[];
extern "C" const char* pawnFields0[];
extern "C" const char* pawnFields1[];
extern "C" const char* pawnFields2[];
extern "C" const char* pawnFields3[];
extern "C" const char* pawnFields4[];
extern "C" const char* pawnFields5[];
extern "C" const char* pawnFields6[];
extern "C" const char* pawnFields7[];
extern "C" const char* pawnFields8[];

extern "C" void EditOnChange__13TObjEnemyPawnFP13SETDATA_PARAM(void* object, PawnEdit* edit)
{
	PawnParams* params = edit->params;
	const f32* limit;

	if (params->f00 < 0) {
		params->f00 = 0;
	}
	if (params->f00 >= 7) {
		params->f00 = 6;
	}
	if (params->f01 < 0) {
		params->f01 = 0;
	}
	if (params->f01 >= 8) {
		params->f01 = 7;
	}
	if (params->f02 < 0) {
		params->f02 = 0;
	}
	if (params->f02 >= 7) {
		params->f02 = 6;
	}
	if (params->f03 < 0) {
		params->f03 = 0;
	}
	if (params->f03 >= 4) {
		params->f03 = 3;
	}
	if (params->f04 < -100) {
		params->f04 = -100;
	}
	if (params->f04 > 1900) {
		params->f04 = 1900;
	}
	params->f18 = nVariable::Limit(params->f18, pawnMin18, pawnMax18);
	if (params->f08 < pawnBound0[0]) {
		params->f08 = pawnBound0[0];
	}
	if (params->f08 > pawnBound1[0]) {
		params->f08 = pawnBound1[0];
	}
	if (params->f0C < *(limit = pawnZero)) {
		params->f0C = *limit;
	}
	if (params->f0C > *(limit = pawnBound2)) {
		params->f0C = *limit;
	}
	if (params->f10 < *(limit = pawnBound3)) {
		params->f10 = *limit;
	}
	if (params->f10 > *(limit = pawnBound4)) {
		params->f10 = *limit;
	}
	if (params->f14 < *(limit = pawnBound5)) {
		params->f14 = *limit;
	}
	pawnFieldNames[0]  = pawnFields0[params->f00];
	pawnFieldNames[1]  = pawnFields1[params->f01];
	pawnFieldNames[2]  = pawnFields2[params->f02];
	pawnFieldNames[3]  = pawnFields3[params->f03];
	pawnFieldNames[6]  = pawnFields4[params->f01];
	pawnFieldNames[7]  = pawnFields5[params->f00];
	pawnFieldNames[8]  = pawnFields6[params->f00];
	pawnFieldNames[9]  = pawnFields7[params->f02];
	pawnFieldNames[10] = pawnFields8[params->f02];
}
