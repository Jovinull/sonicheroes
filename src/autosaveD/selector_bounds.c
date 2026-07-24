#include "types.h"

typedef struct Selector {
	s32 items[32];
	s32 count;
	s32 index;
	s32 wrap;
} Selector;

extern "C" void fn_2_40F0(Selector* selector)
{
	if (selector->wrap) {
		if (selector->index < 0) {
			selector->index = selector->count - 1;
		}
		if (selector->count > selector->index) {
			return;
		}
		selector->index = 0;
	} else {
		if (selector->index < 0) {
			selector->index = 0;
		}
		if (selector->count > selector->index) {
			return;
		}
		selector->index = selector->count - 1;
	}
}
