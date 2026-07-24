#include "types.h"

// Order follows the original binary, which for this compiler is source order.

// This unit is built with -sdata 4. The two range bounds are eight byte
// objects living in .sdata, and only a threshold below eight keeps them out
// of the small data area so they are reached the way the original does, with
// a separate address computation each. The zero it compares against is a
// literal, so it lands in .sdata2 and stays small data addressed.
//
// Not linked yet. Both functions match instruction for instruction, but the
// pooled zero they compare against is shared with the rest of the original
// translation unit, which is still uncarved: five references to it remain in
// the scanner and beyond, so claiming the constant here leaves them with an
// undefined symbol. This becomes Matching once the scanner lands and the unit
// owns its own pool.
extern double __double_min;
extern double __double_max;
extern s32 errno;

// The scanner and the callback that feeds it characters are still uncarved,
// so they keep their generated names for now.
typedef struct {
	const char* str;
	s32 pos;
} __StringRead;

double fn_801C4004(s32 max_width, void* read_proc, __StringRead* state, s32* consumed, s32* error);
extern void fn_801C29BC(void);

double atof(const char* s)
{
	__StringRead state;
	s32 error;
	s32 consumed;
	double value;
	double magnitude;

	state.str = s;
	state.pos = 0;

	value     = fn_801C4004(0x7FFFFFFF, fn_801C29BC, &state, &consumed, &error);
	magnitude = __fabs(value);

	if (error != 0 || (value != 0.0 && (magnitude < __double_min || magnitude > __double_max)))
		errno = 0x22;

	return value;
}

double strtod(const char* s, char** end)
{
	__StringRead state;
	s32 consumed;
	s32 error;
	double value;
	double magnitude;

	state.str = s;
	state.pos = 0;

	value = fn_801C4004(0x7FFFFFFF, fn_801C29BC, &state, &consumed, &error);

	if (end)
		*end = (char*)s + consumed;

	magnitude = __fabs(value);

	if (error != 0 || (0.0 != value && (magnitude < __double_min || magnitude > __double_max)))
		errno = 0x22;

	return value;
}
