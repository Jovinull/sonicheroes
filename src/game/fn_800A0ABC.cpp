#include "types.h"

// Draws a HUD counter, unless play-mode flag 32 (lbl_8042C180) is set, only in game states 5 and
// 12 (fn_80018C98). Kind 1 (+0x30, when flag 26 is set) shows the time (+0x34 minutes, +0x35
// seconds; past 30 seconds only with play-mode byte 36 = 3) with fn_800C4BB8 at a position that
// moves left by lbl_8042DA3C/DA40/DA44 times the scale (+0x40) for 3, 2 or 1 digits; kinds 7 and
// 8 print the seconds left (+0x3C frames / 60, below 10) into lbl_8042C318 with the format
// lbl_8042B30C and draw it with fn_800C4B6C in the colour lbl_8042B2D0. HYPOTHESIS: the roles
// (a countdown) are UNKNOWN.

struct Hud800A0ABC {
	u8 pad0[0x30];
	s8 kind; // 0x30
	u8 pad31[0x34 - 0x31];
	s8 minutes; // 0x34
	s8 seconds; // 0x35
	u8 pad36[0x3C - 0x36];
	s32 frames; // 0x3C
	f32 scale;  // 0x40
	u8 pad44[0x8C - 0x44];
	u8 unknown8C[0x4]; // 0x8C
	u8 unknown90[0x4]; // 0x90
};

struct Pos800A0ABC {
	f32 x;
	f32 y;
};

struct PlayMode800A0ABC {
	s8 flags[44];
};

extern "C" {
extern PlayMode800A0ABC* lbl_8042C180;
extern u32 lbl_8042B2D0;
extern char lbl_8042B30C[3];
extern char lbl_8042C318[4];
extern const f32 lbl_8042D928;
extern const f32 lbl_8042DA3C;
extern const f32 lbl_8042DA40;
extern const f32 lbl_8042DA44;
extern const f32 lbl_8042DA48;
extern const f32 lbl_8042DA4C;
extern const f32 lbl_8042DA50;
extern const f32 lbl_8042DA54;
s32 fn_80018C98(void);
int sprintf(char* buffer, const char* format, ...);
void fn_800C4BB8(Pos800A0ABC* position, void* a, void* b, f32 scale);
void fn_800C4B6C(Pos800A0ABC* position, char* text, u32* color, f32 scale);
}

extern "C" void fn_800A0ABC(Hud800A0ABC* hud)
{
	if (lbl_8042C180->flags[32] != 0) {
		return;
	}
	switch (fn_80018C98()) {
		case 6:
			break;
		case 5:
		case 12:
			switch (hud->kind) {
				case 1: {
					PlayMode800A0ABC* mode = lbl_8042C180;
					if (mode->flags[26] == 0) {
						return;
					}
					if ((hud->minutes != 0 || hud->seconds > 30) && mode->flags[36] != 3) {
						return;
					}
					Pos800A0ABC position;
					if (hud->seconds + hud->minutes * 60 >= 100) {
						position.x = lbl_8042D928 - lbl_8042DA3C * hud->scale;
					} else if (hud->seconds >= 10) {
						position.x = lbl_8042D928 - lbl_8042DA40 * hud->scale;
					} else {
						position.x = lbl_8042D928 - lbl_8042DA44 * hud->scale;
					}
					position.y = lbl_8042DA48;
					fn_800C4BB8(&position, hud->unknown90, hud->unknown8C, hud->scale);
					break;
				}
				case 7:
				case 8: {
					Pos800A0ABC position;
					u32 color;
					position.x = lbl_8042DA4C;
					position.y = lbl_8042DA50;
					color      = lbl_8042B2D0;
					s32 left   = hud->frames / 60;
					if (left < 10) {
						sprintf(lbl_8042C318, lbl_8042B30C, left);
						fn_800C4B6C(&position, lbl_8042C318, &color, lbl_8042DA54);
					}
					break;
				}
			}
			break;
	}
}
