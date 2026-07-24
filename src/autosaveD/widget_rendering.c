#include "types.h"

typedef struct AutosaveWindow {
	u8 unk_0x0[0x6C];
	s32 state;
} AutosaveWindow;

typedef struct WindowConfig {
	u32 unk_0x0;
	u32 unk_0x4;
	u32 tick_0;
	u32 tick_1;
} WindowConfig;

typedef struct Color {
	u8 red;
	u8 green;
	u8 blue;
	u8 alpha;
} Color;

typedef struct MainState {
	u8 unk_0x0[4];
	u32 tick_0;
	u32 tick_1;
} MainState;

extern void* lbl_2_bss_54[5];
extern MainState lbl_8029BB80;

extern void fn_2_25A8();
extern void fn_80194234(s32 channel, void* resource);
extern void fn_2_2F94(void* context, const void* position, const void* size);
extern void fn_2_2868(void* context, const void* position, const void* size);
extern void fn_2_24FC(void* context);
extern void fn_2_26C0(void* window, const WindowConfig* config, const Color* color);

void fn_2_32F8(void* context, const void* position, const void* size)
{
	fn_2_25A8(context, position, size);
	fn_80194234(1, lbl_2_bss_54[4]);
	fn_2_2F94(context, position, size);
	fn_2_24FC(context);
}

void fn_2_3368(void* context, const void* position, const void* size, s32 selected)
{
	fn_2_25A8(context, position, size, selected);

	if (selected != 0) {
		fn_80194234(1, lbl_2_bss_54[0]);
	} else {
		fn_80194234(1, lbl_2_bss_54[1]);
	}

	fn_2_2868(context, position, size);
	fn_2_24FC(context);
}

s32 fn_2_3404(const AutosaveWindow* window)
{
	return window->state;
}

void fn_2_340C(void* window)
{
	WindowConfig config;
	Color color;

	config.unk_0x0 = 0;
	config.unk_0x4 = 0;
	config.tick_0  = lbl_8029BB80.tick_0;
	config.tick_1  = lbl_8029BB80.tick_1;

	color.red   = 0;
	color.green = 0;
	color.blue  = 0;
	color.alpha = 0xA0;

	fn_2_26C0(window, &config, &color);
}
