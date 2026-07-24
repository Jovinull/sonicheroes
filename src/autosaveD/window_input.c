#include "types.h"

typedef struct AutosaveWindow {
	u8 unk_0x0[0x38];
	s32 mode;
	u8 unk_0x3C[0x24];
	s32 close_on_confirm;
	s32 input_mode;
	s32 play_confirm_sound;
	s32 result;
	s32 input_delay;
	u8 selector[0x8C];
	s32 selection;
} AutosaveWindow;

extern void* lbl_8042C388;

extern s32 fn_2_2488(s32 input_mode);
extern s32 fn_2_46B4(void* selector, s32 direction);
extern void fn_800B52E8(void* sound_manager, u32 sound, s32 arg2, s32 arg3);
extern void fn_80014154(void);

void fn_2_38F4(AutosaveWindow* window)
{
	s32 action;
	s32 selection;

	if (window->input_delay == 0) {
		switch (window->mode) {
			case 0:
			case 2:
				action = fn_2_2488(window->input_mode);
				switch (action) {
					case 0:
						switch (window->input_mode) {
							case 1:
								selection = fn_2_46B4(window->selector, 0);
								break;
							case 2:
								selection = fn_2_46B4(window->selector, 1);
								break;
							case 0:
							default:
								selection = fn_2_46B4(window->selector, -1);
								break;
						}

						if (selection == -1 || selection == window->selection) {
							break;
						}

						window->selection = selection;
						if (lbl_8042C388 != NULL) {
							fn_800B52E8(lbl_8042C388, 0xE007, 0, 0);
						}
						break;
					case 1:
						break;
					case 2:
						window->result = window->selection;
						if (window->play_confirm_sound != 0 && lbl_8042C388 != NULL) {
							fn_800B52E8(lbl_8042C388, 0xE008, 0, 0);
						}
						if (window->close_on_confirm != 0) {
							fn_80014154();
						}
						break;
				}
				break;
			case 1:
				window->result = 1;
				break;
		}
	} else {
		window->input_delay--;
	}
}
