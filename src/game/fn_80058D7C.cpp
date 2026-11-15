// Debug display of a set-object generator (HYPOTHESIS): while the debug byte +0x5 of lbl_8042C180
// is set, runs fn_8005864C in mode 1 (+0xA84; modes 0 and 2 do nothing here) and, when the
// word +0xAC0 is set, prints the text lbl_80243320 through RsCameraSize in magenta. Roles are
// UNKNOWN.
#include "types.h"

struct Gen80058D7C {
	u8 pad0[0xA84];
	s32 mode; // 0xA84
	u8 padA88[0xAC0 - 0xA88];
	s32 showText; // 0xAC0
};

struct Debug80058D7C {
	u8 pad0[0x5];
	s8 enabled; // 0x5
};

void njPrintColor(u32 color);

extern "C" {
extern Debug80058D7C* lbl_8042C180;
extern void* lbl_8042C0F0;
extern u8 lbl_80243320[];
void fn_8005864C(Gen80058D7C* gen);
void RsCameraSize(void* camera, void* rect, int viewWindow, int aspectRatio, int flags);

void fn_80058D7C(Gen80058D7C* gen)
{
	if (lbl_8042C180->enabled) {
		switch (gen->mode) {
			case 0:
				break;
			case 1:
				fn_8005864C(gen);
				break;
			case 2:
				break;
		}
		if (gen->showText) {
			njPrintColor(0xFF00FFFF);
			RsCameraSize(lbl_8042C0F0, lbl_80243320, 1, 2, 5);
			njPrintColor(0xFFFFFFFF);
		}
	}
}
}
