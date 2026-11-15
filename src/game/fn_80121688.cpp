// Looks up the textures of the nine-entry menu texture table (HYPOTHESIS; names inferred): clears
// each entry's texture and the table pointer lbl_8042C700, then, unless the mode flag at 0x1E of
// lbl_8042C180 is clear and the game state (0x2C of lbl_8029C310) is outside 0x1D-0x23 and
// 0x34-0x3D, finds each entry's texture by name in the dictionary (fn_801A4BBC) and clears
// lbl_8042C710. Built with the game-unit flags (-opt noschedule,nopeephole).
// NonMatching: retail keeps the unrolled clearing loop's entry test (0 < 9) and rebuilds the table
// address for each loop, while this source folds the test and shares one base register (six
// instructions). Separate counters and an inline clearing helper with the count do not keep it.
#include "types.h"

#define MENU_TEXTURE_COUNT 9

struct MenuTexture80121688 {
	const char* name; // 0x0
	void* texture;    // 0x4
};

struct Mode80121688 {
	u8 pad0[0x1E];
	s8 flag; // 0x1E
};

struct GameState80121688 {
	u8 pad0[0x2C];
	s32 state; // 0x2C
};

extern "C" {
extern MenuTexture80121688 lbl_80289AE8[MENU_TEXTURE_COUNT];
extern void* lbl_8042C700;
extern s32 lbl_8042C710;
extern Mode80121688* lbl_8042C180;
extern GameState80121688 lbl_8029C310;
// HYPOTHESIS: RwTexDictionaryFindNamedTexture.
void* fn_801A4BBC(void* dictionary, const char* name);

void fn_80121688(void* dictionary)
{
	s32 i;

	for (i = 0; i < MENU_TEXTURE_COUNT; i++) {
		lbl_80289AE8[i].texture = 0;
	}
	lbl_8042C700 = 0;
	if (lbl_8042C180->flag == 0) {
		switch (lbl_8029C310.state) {
			case 0x1D:
			case 0x1E:
			case 0x1F:
			case 0x20:
			case 0x21:
			case 0x22:
			case 0x23:
			case 0x34:
			case 0x35:
			case 0x36:
			case 0x37:
			case 0x38:
			case 0x39:
			case 0x3A:
			case 0x3B:
			case 0x3C:
			case 0x3D:
				break;
			default:
				return;
		}
	}
	for (i = 0; i < MENU_TEXTURE_COUNT; i++) {
		lbl_80289AE8[i].texture = fn_801A4BBC(dictionary, lbl_80289AE8[i].name);
	}
	lbl_8042C710 = 0;
}
}
