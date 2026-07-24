#include "types.h"

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

extern MainState lbl_8029BB80;

extern void fn_2_26C0(void* window, const WindowConfig* config, const Color* color);

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
