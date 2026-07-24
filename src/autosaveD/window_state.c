#include "types.h"

typedef struct AutosaveWindow {
	u8 unk_0x0[0x6C];
	s32 state;
} AutosaveWindow;

s32 fn_2_3404(const AutosaveWindow* window)
{
	return window->state;
}
