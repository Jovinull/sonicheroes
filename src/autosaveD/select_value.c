#include "types.h"

typedef struct Selector {
	s32 items[32];
	s32 count;
	s32 index;
	s32 wrap;
} Selector;

extern "C" void fn_2_40F0(Selector* selector);

extern "C" void fn_2_4098(Selector* selector, s32 value)
{
	s32 i;

	for (i = 0; i != selector->count; i++) {
		if (selector->items[i] == value) {
			selector->index = i;
			fn_2_40F0(selector);
			break;
		}
	}
}
