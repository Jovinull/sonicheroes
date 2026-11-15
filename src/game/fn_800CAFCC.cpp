#include "types.h"

// Sets the stream mode (lbl_8042C470, 0..2) when both stream objects of lbl_8042B624 exist and are
// idle (state 0): modes 0 and 1 go to both streams (+0x2A); mode 2 goes to the first stream only,
// which also gets its name table (+0x4C, see fn_800CA77C) created when it has none, and the second
// stream's mode is cleared. HYPOTHESIS: mode 2 is the multi-track playback of fn_800CA77C; the
// names are UNKNOWN.

extern "C" void* memset(void* dst, int c, unsigned long n);

// The 0x10C-byte name table of a stream: its ADXT handle and eight 0x20-byte names from +0xC.
struct StreamNames {
	StreamNames(void* adxt)
	{
		this->adxt = adxt;
		unknown0 = unknown1 = -1;
		unknown4            = 0;
		memset(names, 0, sizeof(names));
	}

	s8 unknown0; // 0x0
	s8 unknown1; // 0x1
	u8 pad2[2];
	s32 unknown4;        // 0x4
	void* adxt;          // 0x8
	char names[8][0x20]; // 0xC
};

struct Stream800CAFCC {
	u8 pad0[0x29];
	s8 state; // 0x29
	s8 mode;  // 0x2A
	u8 pad2B[0x44 - 0x2B];
	void* adxt; // 0x44
	u8 pad48[0x4C - 0x48];
	StreamNames* names; // 0x4C

	void CreateNames()
	{
		if (names == NULL) {
			void* handle = adxt;
			names        = new StreamNames(handle);
		}
	}
};

extern "C" {
extern s8 lbl_8042C470;
extern Stream800CAFCC* lbl_8042B624[2];
}

extern "C" void fn_800CAFCC(s8 mode)
{
	BOOL idle = TRUE;

	if (mode < 0 || mode >= 3) {
		return;
	}
	for (s32 i = 0; i < 2; i++) {
		if (lbl_8042B624[i] == NULL) {
			idle = FALSE;
		}
		if (lbl_8042B624[i]->state != 0) {
			idle = FALSE;
		}
	}
	if (idle == TRUE) {
		switch (mode) {
			case 0:
			case 1:
				lbl_8042C470          = mode;
				lbl_8042B624[0]->mode = mode;
				lbl_8042B624[1]->mode = mode;
				break;
			case 2:
				lbl_8042C470          = mode;
				lbl_8042B624[0]->mode = mode;
				lbl_8042B624[0]->CreateNames();
				lbl_8042B624[1]->mode = 0;
				break;
		}
	}
}
