// Starts the save-data check of a memory card menu (HYPOTHESIS; names inferred): only from the idle
// state and when fn_8012822C reports the card object at 0x28 free, enters state 5, clears the
// progress counters (0xC0, 0x268, 0xC4, 0xC8) and the global lbl_8042C724, marks all 100 slots as
// unknown (2; 10 rows of 10) and formats the status text at 0x30 (format lbl_8042B96C with 0x26C and 0xC8).
// Returns 1 when started, 0 otherwise.
// NonMatching: retail clears the slot rows with a 10-iteration counter loop of ten stores; this
// source's row loop is unrolled once more and keeps its counter (eleven more instructions). An s16
// row counter gets closer (three), u8 counters, a row pointer and swapped loops do not.
#include "types.h"

#define CARD_MENU_SLOT_ROWS    10
#define CARD_MENU_SLOT_COLUMNS 10

struct CardMenu80125708 {
	u8 pad0[0x28];
	void* card; // 0x28
	u8 pad2C[0x30 - 0x2C];
	char text[0xBC - 0x30]; // 0x30
	s32 state;              // 0xBC
	s32 progress;           // 0xC0
	s32 countC4;            // 0xC4
	s32 countC8;            // 0xC8
	u8 padCC[0xD8 - 0xCC];
	s32 slots[CARD_MENU_SLOT_ROWS][CARD_MENU_SLOT_COLUMNS]; // 0xD8
	s32 value268;                                           // 0x268
	s32 value26C;                                           // 0x26C
};

extern "C" {
extern char lbl_8042B96C[8];
extern s32 lbl_8042C724;
s32 fn_8012822C(void* card);
int sprintf(char* buffer, const char* format, ...);

s32 fn_80125708(CardMenu80125708* menu)
{
	s32 i;
	s32 j;

	if (menu->state == 0 && fn_8012822C(menu->card) == 0) {
		menu->state    = 5;
		menu->progress = 0;
		menu->value268 = 0;
		lbl_8042C724   = 0;
		menu->countC4  = 0;
		menu->countC8  = 0;
		for (i = 0; i < CARD_MENU_SLOT_ROWS; i++) {
			for (j = 0; j < CARD_MENU_SLOT_COLUMNS; j++) {
				menu->slots[i][j] = 2;
			}
		}
		sprintf(menu->text, lbl_8042B96C, menu->value26C, menu->countC8);
		return 1;
	}
	return 0;
}
}
