#include "types.h"

typedef struct Selector {
	s32 items[32];
	s32 count;
	s32 index;
	s32 wrap;
} Selector;

extern "C" void fn_2_4074(Selector* selector, s32 index)
{
	if (index <= 0) {
		return;
	}
	if (index >= 3) {
		return;
	}
	selector->index = index;
}
