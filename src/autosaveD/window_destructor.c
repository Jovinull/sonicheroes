#include "types.h"

typedef struct AutosaveWindow {
	u8 base[0x18];
	void* methods;
	u8 unk_0x1C[0x58];
	u8 selector[0x8C];
} AutosaveWindow;

extern void* lbl_2_data_43C[];

extern "C" void fn_2_4798(void* selector, s32 flags);
extern "C" void dtor_800186D0(void* window, s32 flags);
extern "C" void fn_2_13F4(void* allocation);

extern "C" AutosaveWindow* fn_2_3A70(AutosaveWindow* window, s32 flags)
{
	if (window != NULL) {
		window->methods = lbl_2_data_43C;
		fn_2_4798(window->selector, -1);
		dtor_800186D0(window, 0);
		if ((s16)flags > 0) {
			fn_2_13F4(window);
		}
	}
	return window;
}
