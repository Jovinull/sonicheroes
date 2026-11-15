// Looks up a per-name byte of an object (HYPOTHESIS; names inferred): upper-cases the name (letters
// above 'Z' other than '_' and '.' lose 0x20), binary-searches it in the 43 sorted names of
// lbl_802891F4 and returns the byte at 0x6CC + index of the object, or 0 when the name is missing
// or not in the table. Built with the game-unit flags (-opt noschedule,nopeephole).
// NonMatching: retail reuses the character loaded by the loop test for the first comparison,
// while this source reloads it (one extra instruction), and the search registers differ. A
// character local in the test or in the body and hoisted declarations do not reproduce it.
#include "types.h"

#define NAME_TABLE_COUNT 43

struct Owner80116F5C {
	u8 pad0[0x6CC];
	u8 values[NAME_TABLE_COUNT]; // 0x6CC
};

extern "C" {
extern const char* lbl_802891F4[NAME_TABLE_COUNT];
int strcmp(const char* lhs, const char* rhs);

static inline s32 FindName80116F5C(const s8* name)
{
	s8 buffer[0x80];
	s8* dst;
	s32 length;
	s32 low;
	s32 high;

	if (name != 0) {
		length = 0;
		dst    = buffer;
		while (*name != 0) {
			if (*name <= 'Z' || *name == '_' || *name == '.') {
				*dst = *name;
			} else {
				*dst = *name - 0x20;
			}
			dst++;
			length++;
			name++;
		}
		buffer[length] = 0;

		low  = 0;
		high = NAME_TABLE_COUNT;
		while (low < high) {
			s32 middle = (low + high) >> 1;
			if (strcmp((const char*)buffer, lbl_802891F4[middle]) > 0) {
				low = middle + 1;
			} else {
				high = middle;
			}
		}
		if (strcmp((const char*)buffer, lbl_802891F4[low]) == 0) {
			return low;
		}
	}
	return -1;
}

u8 fn_80116F5C(Owner80116F5C* owner, const s8* name)
{
	s32 index = FindName80116F5C(name);
	if (index >= 0) {
		return owner->values[index];
	}
	return 0;
}
}
