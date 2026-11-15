#include "game/mobject.h"

// Initializes a menu module (an MObject; its +0x4 is cleared): sets the six module switches of
// lbl_8029BBD0 (+0x18..+0x2C) to 1, runs MObject::DefaultSetUp, resets the 64-entry selection
// table of lbl_80304580 (entry 0 = 1, the others -1; +0x0 and +0x4 = 1), its cursor block (+0x108
// = 0, +0x10C..+0x114 = -1) and clamps the four cursors below 4, and refreshes the current camera
// (fn_8016EF70). HYPOTHESIS: a menu Init; the names are UNKNOWN.

class Menu800C8C5C : public MObject
{
public:
	s32 unknown4; // 0x4
};

struct Switches800C8C5C {
	u8 pad0[0x18];
	s32 values[6]; // 0x18
};

struct Selection800C8C5C {
	s32 unknown0;      // 0x0
	s32 unknown4;      // 0x4
	s32 entries[0x40]; // 0x8
	s32 cursors[4];    // 0x108
};

extern "C" {
extern Switches800C8C5C lbl_8029BBD0;
extern Selection800C8C5C lbl_80304580;
void* memset(void* dst, int c, unsigned long n);
void fn_8016EF70(RwCamera* camera);
}

extern "C" void fn_800C8C5C(Menu800C8C5C* menu)
{
	s32 i;

	lbl_8029BBD0.values[0] = 1;
	lbl_8029BBD0.values[1] = 1;
	lbl_8029BBD0.values[2] = 1;
	lbl_8029BBD0.values[3] = 1;
	lbl_8029BBD0.values[4] = 1;
	lbl_8029BBD0.values[5] = 1;
	menu->DefaultSetUp();
	memset(lbl_80304580.entries, 0, sizeof(lbl_80304580.entries));
	lbl_80304580.unknown0   = 1;
	lbl_80304580.unknown4   = 1;
	lbl_80304580.entries[0] = 1;
	for (i = 1; i < 0x40; i++) {
		lbl_80304580.entries[i] = -1;
	}
	lbl_80304580.cursors[0] = 0;
	lbl_80304580.cursors[1] = -1;
	lbl_80304580.cursors[2] = -1;
	lbl_80304580.cursors[3] = -1;
	menu->unknown4          = 0;
	for (i = 0; i < 4; i++) {
		if (lbl_80304580.cursors[i] >= 4) {
			lbl_80304580.cursors[i] = 0;
		}
	}
	fn_8016EF70(GetCurrentCameraPointer());
}
