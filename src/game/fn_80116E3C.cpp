// Sets the flag byte (0x6CC + index) of a name found in the sorted 45-entry name table
// lbl_802891F4. The name is upper-cased into a local buffer (characters above 'Z' other than '_'
// and '.' lose 0x20) and binary-searched over the first 44 entries; a missing or NULL name changes
// nothing. What the names and flags stand for is UNKNOWN.
#include "types.h"

struct Obj80116E3C {
	u8 pad0[0x6CC];
	u8 flags[45]; // 0x6CC
};

extern "C" {
extern const char* lbl_802891F4[45];
s32 strcmp(const char* lhs, const char* rhs);
}

static inline s32 Find80116E3C(const char* name)
{
	char buffer[0x80];
	if (name != NULL) {
		s32 i     = 0;
		char* out = buffer;
		for (; *name != '\0'; out++, i++, name++) {
			if (*name <= 'Z' || *name == '_' || *name == '.') {
				*out = *name;
			} else {
				*out = *name - 0x20;
			}
		}
		buffer[i] = '\0';
		s32 lo, mid, hi;
		lo = 0;
		hi = 43;
		while (lo < hi) {
			mid = (lo + hi) >> 1;
			if (strcmp(buffer, lbl_802891F4[mid]) > 0) {
				lo = mid + 1;
			} else {
				hi = mid;
			}
		}
		if (strcmp(buffer, lbl_802891F4[lo]) == 0) {
			return lo;
		}
	}
	return -1;
}

extern "C" void fn_80116E3C(Obj80116E3C* o, const char* name)
{
	s32 index = Find80116E3C(name);
	if (index >= 0) {
		o->flags[index] = 1;
	}
}
