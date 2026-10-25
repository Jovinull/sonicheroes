#include "types.h"

// bigRingsMatchesNumber, the same in the twelve stage modules that share the
// engine core: whether a number is one of the three an object of the big
// rings keeps at 0x35. Nothing in the modules calls it.

typedef struct BigRingsObject {
	u8 unk00[0x35];
	s8 numbers[3]; // 0x35
} BigRingsObject;

extern "C" int bigRingsMatchesNumber(BigRingsObject* object, s8 number)
{
	for (int i = 0; i < 3; i++) {
		if (number == object->numbers[i]) {
			return 1;
		}
	}
	return 0;
}
