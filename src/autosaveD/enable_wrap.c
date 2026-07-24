#include "types.h"

typedef struct Selector {
	s32 items[32];
	s32 count;
	s32 index;
	s32 wrap;
} Selector;

extern "C" void fn_2_408C(Selector* selector)
{
	selector->wrap = 1;
}
