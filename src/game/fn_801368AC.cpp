// Draws the seven icons of a menu (HYPOTHESIS; names inferred): the selected icon (0x94) is drawn
// grown by its zoom (0x98) around its position and the zoom shrinks by lbl_8042F088 down to
// lbl_8042F08C; an icon in state 1 is drawn plainly; any other icon is drawn dimmed (fn_80136C24
// with 0xDC) with the placeholder texture lbl_8042C7C8. Icon textures come from lbl_8028AFA0,
// positions from 0x5C and the base size from lbl_8042BBD0 (fn_80136C40 draws). Built with the
// game-unit flags (-opt noschedule,nopeephole).
// NonMatching: the zoom clamp loads the zoom into f1 and the minimum into f0 in retail, the
// reverse here (4 words). A zoom local, a minimum local, a const minimum and a plain subtraction
// do not change it.
#include "game/matrix.h"

#define MENU_ICON_COUNT 7

struct Menu801368AC {
	u8 pad0[0x40];
	s32 states[MENU_ICON_COUNT];      // 0x40
	RwV2d positions[MENU_ICON_COUNT]; // 0x5C
	s32 selected;                     // 0x94
	f32 zoom;                         // 0x98
};

extern "C" {
extern void* lbl_8028AFA0[MENU_ICON_COUNT];
extern RwV2d lbl_8042BBD0;
extern void* lbl_8042C7C8;
extern f32 lbl_8042F088;
extern f32 lbl_8042F08C;
void fn_80136C24(Menu801368AC* menu, s32 alpha);
void fn_80136C40(Menu801368AC* menu, void* texture, f32 x, f32 y, f32 width, f32 height);

void fn_801368AC(Menu801368AC* menu)
{
	s32 i;

	for (i = 0; i < MENU_ICON_COUNT; i++) {
		if (lbl_8028AFA0[i] != 0) {
			if (i == menu->selected) {
				f32 grow = menu->zoom * lbl_8042F088;
				fn_80136C40(menu, lbl_8028AFA0[menu->selected],
				    menu->positions[menu->selected].x - grow,
				    menu->positions[menu->selected].y - grow, lbl_8042BBD0.x + menu->zoom,
				    lbl_8042BBD0.y + menu->zoom);
				menu->zoom -= lbl_8042F088;
				if (menu->zoom < lbl_8042F08C) {
					menu->zoom = lbl_8042F08C;
				}
			} else if (menu->states[i] == 1) {
				fn_80136C40(menu, lbl_8028AFA0[i], menu->positions[i].x, menu->positions[i].y,
				    lbl_8042BBD0.x, lbl_8042BBD0.y);
			} else {
				fn_80136C24(menu, 0xDC);
				fn_80136C40(menu, lbl_8042C7C8, menu->positions[i].x, menu->positions[i].y,
				    lbl_8042BBD0.x, lbl_8042BBD0.y);
			}
		}
	}
}
}
