#include "types.h"

struct Slot {
	void* a; // 0x00
	void* b; // 0x04
	s32 c;   // 0x08
};

extern "C" void fn_8020C2D8(void* anim);

extern "C" void fn_16_4D9E4(Slot* arr)
{
	s32 i = 0;
	while (arr[i].b != NULL) {
		fn_8020C2D8(arr[i].a);
		i++;
	}
}
