// Runs one step of the memory card load in a card menu (HYPOTHESIS; names inferred). Step 0 starts
// reading the save into the buffer (fn_80127FC4). Step 1 waits for the card (fn_8012822C); on a
// read error stores the card result (fn_80128224) as the menu result, otherwise decodes the
// buffer (fn_80126460) and checks it (fn_80126374): a bad save gives result 8, a save of another
// game record (word 0x10 against the live save lbl_803E774C, fn_80116D2C) gives 0xB, and a good
// one is copied into the live save and applied (fn_80116C50) with result 0. Every finished step
// clears the progress and reformats the status text, the 0xB case twice, as retail does.
#include "types.h"
#include "MSL_C/string.h"

#define SAVE_DATA_SIZE 0x708

struct SaveData80124F48 {
	u8 pad0[0x10];
	u32 id; // 0x10
};

struct CardMenu80124F48 {
	u8 pad0[0x28];
	void* card; // 0x28
	u8 pad2C[0x30 - 0x2C];
	char text[0xB0 - 0x30]; // 0x30
	s32 valueB0;            // 0xB0
	u8 padB4[0xB8 - 0xB4];
	SaveData80124F48* buffer; // 0xB8
	s32 state;                // 0xBC
	s32 progress;             // 0xC0
	u8 padC4[0xC8 - 0xC4];
	s32 countC8; // 0xC8
	s32 result;  // 0xCC
	u8 padD0[0xD4 - 0xD0];
	s32 valueD4; // 0xD4
	u8 padD8[0x268 - 0xD8];
	s32 value268; // 0x268
	s32 value26C; // 0x26C
};

extern "C" {
extern u8 lbl_803E774C[];
extern char lbl_8042B96C[8];
extern s32 lbl_8042C724;
int sprintf(char* buffer, const char* format, ...);
void fn_80127FC4(void* card, char* text, s32 a, s32 b);
s32 fn_8012822C(void* card);
s32 fn_80128224(void* card);
void fn_80126460(SaveData80124F48* buffer, s32 mode);
s32 fn_80126374(SaveData80124F48* buffer);
SaveData80124F48* fn_80116D2C(void* save);
void fn_80116C50(void* save);

static inline void ResetStatus80124F48(CardMenu80124F48* menu)
{
	menu->state    = 0;
	menu->progress = 0;
	menu->value268 = 0;
	lbl_8042C724   = 0;
	sprintf(menu->text, lbl_8042B96C, menu->value26C, menu->countC8);
}

void fn_80124F48(CardMenu80124F48* menu, s32 step)
{
	switch (step) {
		case 0:
			fn_80127FC4(menu->card, menu->text, menu->valueD4, menu->valueB0);
			menu->progress = 1;
			break;
		case 1:
			if (fn_8012822C(menu->card) == 0) {
				switch (fn_80128224(menu->card)) {
					case 0: {
						SaveData80124F48* buffer = menu->buffer;
						fn_80126460(buffer, 0);
						if (fn_80126374(buffer) == 0) {
							menu->result = 8;
						} else if (fn_80116D2C(lbl_803E774C)->id != buffer->id) {
							menu->result = 0xB;
							ResetStatus80124F48(menu);
						} else {
							memcpy(fn_80116D2C(lbl_803E774C), buffer, SAVE_DATA_SIZE);
							fn_80116C50(lbl_803E774C);
							menu->result = 0;
						}
						ResetStatus80124F48(menu);
						break;
					}
					default:
						menu->result = fn_80128224(menu->card);
						ResetStatus80124F48(menu);
						break;
				}
			}
			break;
	}
}
}
